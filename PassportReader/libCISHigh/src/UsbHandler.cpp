#include "UsbHandler.h"
#include "internalLogging.h"
#include <chrono>



int sem_timedwait_millsecs(sem_t *sem, long msecs);

UsbHandler::UsbHandler() {
    result = result_false;
    firstin = true;
    lightChangeOn = false;
    getImg = false;
    getPicMode = normal;
    setJZ(80);
    setLight(25, 52, 45, 30, 875, 875);
    for (int i = 0; i < BUFSIZE; i++) {
        inbuf[i] = new unsigned char[RECEIVESIZE];
        memset(inbuf[i], 0, RECEIVESIZE);
    }

    throwbuf = new unsigned char[RECEIVESIZE];

    memset(blackPix, 0, 9 * PICWIDTH);
    memset(kArr, 0, 9 * PICWIDTH);
}

UsbHandler::~UsbHandler() {
    for (int i = 0; i < BUFSIZE; i++) {
        delete[] inbuf[i];
    }
    delete[] throwbuf;
    delete[] blackPix;
    delete[] kArr;
}

void UsbHandler::init(std::string folder) {
    workFolder = folder;
    mediaStatusTrue = MEDIA_STATUS_NOTEXIST;
    mediaStatus = MEDIA_STATUS_NOTEXIST;
}

void UsbHandler::clearUSBSerial() {
    unsigned char *data = new unsigned char[10240];
    while (usbDevice.bulk_read(data, 10240, 10) > 0);
    LOGI("USB data cleared");
}

long long UsbHandler::getTimeStamp() {
    std::chrono::time_point<std::chrono::system_clock, std::chrono::milliseconds> tp = std::chrono::time_point_cast<std::chrono::milliseconds>(
            std::chrono::system_clock::now());//获取当前时间点
    long long timestamp = tp.time_since_epoch().count(); //计算距离1970-1-1,00:00的时间长度
    return timestamp;
}

void UsbHandler::beginListenData() {
    pthread_t t;
    pthread_create(&t, NULL, USBDataListener, (void *) this);
}

void *UsbHandler::USBDataListener(void *thisPointer) {
    UsbHandler *p = (UsbHandler *) thisPointer;
    unsigned char *data = new unsigned char[512000];
    long long duration = 0;
    p->clearUSBSerial();
    while (true) {
       LOGI("begin wait usb data");
        int ret = p->usbDevice.bulk_read(data, 512, 0);
       LOGI("received usb data, ret = %d", ret);
        if (ret <= 0) {
            if (ret == LIBUSB_ERROR_NO_DEVICE || ret == LIBUSB_ERROR_OTHER) {
                LOGE("USBDataListener exit");
                break;
            }
            continue;
        }


        if (p->scanning) {//收到图像数据
            memcpy(p->databuf, data, 512);
            int count = 0;
            while (true) {
                int received = p->usbDevice.bulk_read(data, 512000, 100);
                if (received <= 0) {
                    LOGI("receive end and count is:%d", count);
                    break;
                }
                if (512 + count * 512000 + received < DATALENGTH * 9) {
                    memcpy(p->databuf + 512 + count * 512000, data, received);
                } else {
                    memcpy(p->databuf + 512 + count * 512000, data,
                           DATALENGTH * 9 - (512 + count * 512000));
                    break;
                }
                count++;
            }

            p->scanning = false;
            p->mediaStatus = MEDIA_STATUS_NOTEXIST;
            LOGI("send receive img signal\n");
            sem_post(&(p->imgSem));//先发结束采图指令再清空usb
            p->clearUSBSerial();
            continue;
        }

        bool check = false;
        if (data[0] == FpgaDocumentIn) {//证件放入
            check = true;
            for (int i = 1; i < 512; ++i) {
                if (data[i] != FpgaDocumentIn) {
                    check = false;
                    break;
                }
            }
            if (check) {
                p->mediaStatusTrue = MEDIA_STATUS_EXIST;
                duration = p->getTimeStamp() - duration;
//                LOGI("Document out and in duration is:%lld", duration);
                if (duration > 500) {
                    p->mediaStatus = MEDIA_STATUS_EXIST;
                }
                LOGI("Document in");
            } else {
                LOGE("USB data analysis error");
                p->clearUSBSerial();
            }
        } else if (data[0] == FpgaDocumentOut) {//证件离开
            check = true;
            for (int i = 1; i < 512; ++i) {
                if (data[i] != FpgaDocumentOut) {
                    check = false;
                    break;
                }
            }
            if (check) {
                p->mediaStatusTrue = MEDIA_STATUS_NOTEXIST;
                p->mediaStatus = MEDIA_STATUS_NOTEXIST;
                duration = p->getTimeStamp();
                LOGI("Document out");
            } else {
                LOGE("USB data analysis error");
                p->clearUSBSerial();
            }
        } else {
            LOGE("USB data analysis error");
            p->clearUSBSerial();
        }

    }
    return NULL;
}

int sem_timedwait_millsecs(sem_t *sem, long msecs) {
    //原本这里使用的是sem_timedwait函数等待接收线程接收完数据，但是使用显示加载的方式加载库时该函数会失效，所以改为sem_trywait+usleep实现
    // struct timespec ts;
    // clock_gettime(CLOCK_REALTIME, &ts);
    // long secs = msecs / 1000;
    // msecs = msecs % 1000;

    // long add = 0;
    // msecs = msecs * 1000 * 1000 + ts.tv_nsec;
    // add = msecs / (1000 * 1000 * 1000);
    // ts.tv_sec += (add + secs);
    // ts.tv_nsec = msecs % (1000 * 1000 * 1000);

    // return sem_timedwait(sem, &ts);
    //-----------------------------------------------------------------------------------------------------------------
    const long waitTimeUs = msecs * 1000;
    const long maxTimeWait = 10000;
    long timeWait = 1; // 睡眠时间，默认为1微秒
    long delayUs = 0; // 剩余需要延时睡眠时间
    uint64_t elapsedUs = 0; // 已计数的时间，单位微秒

    int ret = 0;
    do
    {
        // 如果信号量大于0，则减少信号量并立马返回true
        if( sem_trywait(sem) == 0 )
            return true;
        // 系统信号则立马返回false
        if( errno != EAGAIN )
            return false;
        delayUs = waitTimeUs - elapsedUs;
        // 睡眠时间取最小的值
        timeWait = std::min( delayUs, timeWait );
        ret = usleep( timeWait );
        if( ret != 0 )
            return false;
        elapsedUs += timeWait;
        // 睡眠延时时间双倍自增
        timeWait *= 2;
        // 睡眠延时时间不能超过最大值
        timeWait = std::min( timeWait, maxTimeWait );
    } while( elapsedUs <= waitTimeUs ); // 如果当前循环的时间超过预设延时时间则退出循环
    // 超时退出，则返回false
    return false;
}

resultdata UsbHandler::acquireImage(int timeout) {
    result = result_false;
    mediaStatus = MEDIA_STATUS_NOTEXIST;
//	if(firstin){
//		if(usbDevice.open() == STATUS_FAILED)
//			LOGE("打开设备失败!\n");
//	}
//不再重新打开了
    if (isDeviceDisconnected()) {
        LOGE("device not connect!\n");
        getImg = false;
        return result_disconnect;
    }

    if (firstin) {
        UCHAR bufOrder[2] = {0x40, fpga_roffset};  // 0 低位 1 高位
        if (sendSignal(bufOrder[0], bufOrder[1]) == STATUS_FAILED) {
            LOGE("roffset signal send error!\n");
            return result_false;
        }
        bufOrder[1] = fpga_goffset;
        if (sendSignal(bufOrder[0], bufOrder[1]) == STATUS_FAILED) {
            LOGE("goffset signal send error!\n");
            return result_false;
        }
        bufOrder[1] = fpga_boffset;
        if (sendSignal(bufOrder[0], bufOrder[1]) == STATUS_FAILED) {
            LOGE("boffset signal send error!\n");
            return result_false;
        }

        bufOrder[0] = 0x51;
        bufOrder[1] = fpga_rpga;
        if (sendSignal(bufOrder[0], bufOrder[1]) == STATUS_FAILED) {
            LOGE("rpga signal send error!\n");
            return result_false;
        }
        bufOrder[1] = fpga_gpga;
        if (sendSignal(bufOrder[0], bufOrder[1]) == STATUS_FAILED) {
            LOGE("gpga signal send error!\n");
            return result_false;
        }
        bufOrder[1] = fpga_bpga;
        if (sendSignal(bufOrder[0], bufOrder[1]) == STATUS_FAILED) {
            LOGE("bpga signal send error!\n");
            return result_false;
        }
        bufOrder[1] = fpga_adcfg;
        if (sendSignal(bufOrder[0], bufOrder[1]) == STATUS_FAILED) {
            LOGE("adcfg signal send error!\n");
            return result_false;
        }
        bufOrder[0] = 0xFB;
        bufOrder[1] = 0x2C;
        if (sendSignal(bufOrder[0], bufOrder[1]) == STATUS_FAILED) {
            LOGE("图像有效 signal send error!\n");
            return result_false;
        }

        if (sendSignal(rLight[0], rLight[1]) == STATUS_FAILED) {
            LOGE("红光 signal send error!\n");
            return result_false;
        }
        if (sendSignal(gLight[0], gLight[1]) == STATUS_FAILED) {
            LOGE("绿光 signal send error!\n");
            return result_false;
        }
        if (sendSignal(bLight[0], bLight[1]) == STATUS_FAILED) {
            LOGE("蓝光 signal send error!\n");
            return result_false;
        }
        if (sendSignal(irLight[0], irLight[1]) == STATUS_FAILED) {
            LOGE("红外光 signal send error!\n");
            return result_false;
        }
        if ((sendSignal(uv1Light[0], uv1Light[1]) == STATUS_FAILED) ||
            (sendSignal(uv2Light[0], uv2Light[1]) == STATUS_FAILED)) {
            LOGE("紫外光 signal send error!\n");
            return result_false;
        }

        firstin = false;

    }

    if (startCap())
        LOGI("start cap success!\n");

    scanning = true;//用于区分在此之后来的数据，之后来的都是图像数据
    sem_init(&imgSem, 0, 0);


    if (sem_timedwait_millsecs(&imgSem, timeout) == -1) {
        LOGE("wait imgSem timeout");
        result = result_timeout;
        return result;
    }
//    for (int bufindex = 0; bufindex < BUFSIZE; bufindex++) {
//        int receivedSize = usbDevice.bulk_read(inbuf[bufindex], RECEIVESIZE, 0);
//        if (!receivedSize) {
//            break;
//        }
//        LOGI("receivedSize = %d,bufindex = %d\n", receivedSize, bufindex);
//    }

    if (endCap())LOGI("end cap success!\n");
//
//    //memcpy(databuf, inbuf+2048, DATALENGTH * 9);
//    recvnum = 0;
//    for (int i = 0; i < BUFSIZE; i++) {
//        if (recvnum < DATALENGTH * 9 && (recvnum + RECEIVESIZE) < DATALENGTH * 9 + 2048) {
//            memcpy(databuf + recvnum, inbuf[i] + 2048, RECEIVESIZE - 2048);
//            recvnum += RECEIVESIZE;
//        } else if (recvnum < DATALENGTH * 9 && (recvnum + buflength) >= DATALENGTH * 9 + 2048) {
//            memcpy(databuf + recvnum, inbuf[i] + 2048, DATALENGTH * 9 - recvnum);
//            recvnum = DATALENGTH * 9;
//        }
//    }
//
//    if (recvnum < DATALENGTH * 9) {
//        result = result_false;
//        printf("%d\n", buflength);
//        return result_false;
//    }

    int flag_caitu = MyImageProcess(databuf);
    if (flag_caitu != 0) {
        //采图失败
        result = result_false;
        return result;
    }
    if (getPicMode == normal) {
        result = result_normal;
        return result;
    }
    if (getPicMode == white) {
        result = result_white;
        return result;
    }
    if (getPicMode == black) {
        result = result_black;
        return result;
    }

}


int UsbHandler::MyImageProcess(unsigned char *data) {
    //2、生成图像
    DataExtractToImg(data, mat0);

    //线性拉伸，校正图像，并且剪裁图像
    if (getPicMode == normal)ReviseImage(mat0);
    if (getPicMode == white)getReviseData(mat0);

    return 0;
}

void
UsbHandler::DataExtractToImg(unsigned char *data, unsigned char mat0[][3 * PICLENGTH], int len) {
    int i1, i2;
    memset(mat0, 0, 2 * len * 3 * PICLENGTH);
    //FPGA没有传废数据
    for (int i = 0; i < len * PICHEIGHT; i++) {
        i1 = i % 3;
        i2 = i / 3;
        for (int j = 0; j < 3 * IMGWIDTH; j++)
            mat0[i1][i2 * IMGWIDTH * 3 + j + 2 - (j % 3) * 2] = data[(i + UPOFFSET) * IMGWIDTH * 3 +
                                                                     j + LEFTOFFSET];
        //for (int j = 0; j < 3 * PICWIDTH; j++)mat0[i1][(i2+1) * PICWIDTH * 3 - j - 1] = data[(i + UPOFFSET) * IMGWIDTH * 3 + j + LEFTOFFSET];
    }


    cv::Mat picWhite = cv::Mat(PICHEIGHT, PICWIDTH, CV_8UC3, mat0[0]);
    cv::Mat picRed = cv::Mat(PICHEIGHT, PICWIDTH, CV_8UC3, mat0[1]);
    cv::Mat picPurple = cv::Mat(PICHEIGHT, PICWIDTH, CV_8UC3, mat0[2]);

    /*
    cv::Mat redPic = cv::Mat(IMGHEIGHT * 3, IMGWIDTH, CV_8UC1, mat0[3]);
    cv::Mat greenPic = cv::Mat(IMGHEIGHT * 3, IMGWIDTH, CV_8UC1, mat0[4]);
    cv::Mat bluePic = cv::Mat(IMGHEIGHT * 3, IMGWIDTH, CV_8UC1, mat0[5]);
    */


    int maxR, maxG, maxB;
    int colR, colG, colB;
    maxR = 0;
    maxG = 0;
    maxB = 0;
    int Rmax, Gmax, Bmax;
    Rmax = 0;
    Gmax = 0;
    Bmax = 0;
    if (lightChangeOn) {
        for (int i = 0; i < PICWIDTH; i++) {
            colR = 0;
            colG = 0;
            colB = 0;
            for (int j = 0; j < PICHEIGHT; j++) {
                colR += mat0[0][j * PICWIDTH * 3 + 3 * i + 2];
                colG += mat0[0][j * PICWIDTH * 3 + 3 * i + 1];
                colB += mat0[0][j * PICWIDTH * 3 + 3 * i];
                if (Rmax != 255 && mat0[0][j * PICWIDTH * 3 + 3 * i + 2] > Rmax)
                    Rmax = mat0[0][j * PICWIDTH * 3 + 3 * i + 2];
                if (Gmax != 255 && mat0[0][j * PICWIDTH * 3 + 3 * i + 1] > Gmax)
                    Gmax = mat0[0][j * PICWIDTH * 3 + 3 * i + 1];
                if (Bmax != 255 && mat0[0][j * PICWIDTH * 3 + 3 * i] > Bmax)
                    Bmax = mat0[0][j * PICWIDTH * 3 + 3 * i];
            }
            if ((colR / PICHEIGHT) > maxR)maxR = colR / PICHEIGHT;
            if ((colG / PICHEIGHT) > maxG)maxG = colG / PICHEIGHT;
            if ((colB / PICHEIGHT) > maxB)maxB = colB / PICHEIGHT;
        }
        printf("normal:R = %d,max = %d,G = %d,max = %d, B = %d,max = %d\n", maxR, Rmax, maxG, Gmax,
               maxB, Bmax);
        maxR = 0;
        maxG = 0;
        maxB = 0;
        Rmax = 0;
        Gmax = 0;
        Bmax = 0;
        for (int i = 0; i < PICWIDTH; i++) {
            colR = 0;
            colG = 0;
            colB = 0;
            for (int j = 0; j < PICHEIGHT; j++) {
                colR += mat0[1][j * PICWIDTH * 3 + 3 * i + 2];
                colG += mat0[1][j * PICWIDTH * 3 + 3 * i + 1];
                colB += mat0[1][j * PICWIDTH * 3 + 3 * i];
                if (Rmax != 255 && mat0[1][j * PICWIDTH * 3 + 3 * i + 2] > Rmax)
                    Rmax = mat0[1][j * PICWIDTH * 3 + 3 * i + 2];
                if (Gmax != 255 && mat0[1][j * PICWIDTH * 3 + 3 * i + 1] > Gmax)
                    Gmax = mat0[1][j * PICWIDTH * 3 + 3 * i + 1];
                if (Bmax != 255 && mat0[1][j * PICWIDTH * 3 + 3 * i] > Bmax)
                    Bmax = mat0[1][j * PICWIDTH * 3 + 3 * i];
            }
            if ((colR / PICHEIGHT) > maxR)maxR = colR / PICHEIGHT;
            if ((colG / PICHEIGHT) > maxG)maxG = colG / PICHEIGHT;
            if ((colB / PICHEIGHT) > maxB)maxB = colB / PICHEIGHT;
        }
        printf("ir:R = %d,max = %d,G = %d,max = %d, B = %d,max = %d\n", maxR, Rmax, maxG, Gmax,
               maxB, Bmax);
        maxR = 0;
        maxG = 0;
        maxB = 0;
        Rmax = 0;
        Gmax = 0;
        Bmax = 0;
        for (int i = 0; i < PICWIDTH; i++) {
            colR = 0;
            colG = 0;
            colB = 0;
            for (int j = 0; j < PICHEIGHT; j++) {
                colR += mat0[2][j * PICWIDTH * 3 + 3 * i + 2];
                colG += mat0[2][j * PICWIDTH * 3 + 3 * i + 1];
                colB += mat0[2][j * PICWIDTH * 3 + 3 * i];
                if (Rmax != 255 && mat0[2][j * PICWIDTH * 3 + 3 * i + 2] > Rmax)
                    Rmax = mat0[2][j * PICWIDTH * 3 + 3 * i + 2];
                if (Gmax != 255 && mat0[2][j * PICWIDTH * 3 + 3 * i + 1] > Gmax)
                    Gmax = mat0[2][j * PICWIDTH * 3 + 3 * i + 1];
                if (Bmax != 255 && mat0[2][j * PICWIDTH * 3 + 3 * i] > Bmax)
                    Bmax = mat0[2][j * PICWIDTH * 3 + 3 * i];
            }
            if ((colR / PICHEIGHT) > maxR)maxR = colR / PICHEIGHT;
            if ((colG / PICHEIGHT) > maxG)maxG = colG / PICHEIGHT;
            if ((colB / PICHEIGHT) > maxB)maxB = colB / PICHEIGHT;
        }
        printf("uv:R = %d,max = %d,G = %d,max = %d, B = %d,max = %d\n", maxR, Rmax, maxG, Gmax,
               maxB, Bmax);
    }

    std::string folder = workFolder + "/images";
    if (access(folder.c_str(), F_OK) == -1)    //如果文件夹不存在
        mkdir(folder.c_str(), 0777);                //则创建

    folder = workFolder + "/fix";
    if (access(folder.c_str(), F_OK) == -1)    //如果文件夹不存在
        mkdir(folder.c_str(), 0777);                //则创建

    //正常采图存图
    /*
    if (getPicMode == normal) {

        for (int i = 0; i < PICHEIGHT; i++) {
            for (int j = 0; j < 3 * PICWIDTH; j++) {
                i1 = j % 3;
                i2 = j / 3;
                mat0[i1 + 3][i * PICWIDTH + i2] = data[(3 * i + UPOFFSET) * PICWIDTH * 3 + j + LEFTOFFSET];
            }
        }
        cv::Mat redPic = cv::Mat(PICHEIGHT, PICWIDTH, CV_8UC1, mat0[3]);
        cv::Mat greenPic = cv::Mat(PICHEIGHT, PICWIDTH, CV_8UC1, mat0[4]);
        cv::Mat bluePic = cv::Mat(PICHEIGHT, PICWIDTH, CV_8UC1, mat0[5]);
        cv::imwrite("./image/outP_r.bmp", redPic);
        cv::imwrite("./image/outP_g.bmp", greenPic);
        cv::imwrite("./image/outP_b.bmp", bluePic);
        for (int i = 0; i < PICHEIGHT; i++) {
            for (int j = 0; j < 3 * PICWIDTH; j++) {
                i1 = j % 3;
                i2 = j / 3;
                mat0[i1 + 3][i * PICWIDTH + i2] = data[(3 * i + UPOFFSET + 1) * PICWIDTH * 3 + j + LEFTOFFSET];
            }
        }
        cv::imwrite("./image/outP_r_ir.bmp", redPic);
        cv::imwrite("./image/outP_g_ir.bmp", greenPic);
        cv::imwrite("./image/outP_b_ir.bmp", bluePic);
        for (int i = 0; i < PICHEIGHT; i++) {
            for (int j = 0; j < 3 * PICWIDTH; j++) {
                i1 = j % 3;
                i2 = j / 3;
                mat0[i1 + 3][i * PICWIDTH + i2] = data[(3 * i + UPOFFSET + 2) * PICWIDTH * 3 + j + LEFTOFFSET];
            }
        }
        cv::imwrite("./image/outP_0.bmp", picWhite);
        cv::imwrite("./image/outP_1.bmp", picRed);
        cv::imwrite("./image/outP_2.bmp", picPurple);
        cv::imwrite("./image/outP_r_uv.bmp", redPic);
        cv::imwrite("./image/outP_g_uv.bmp", redPic);
        cv::imwrite("./image/outP_b_uv.bmp", redPic);
    }
        */
    FILE *file = NULL;
    if (getPicMode == black) {
        //计算黑色正常图
        std::string dir1 = workFolder + "/fix/black_n.bmp";
        std::string dir2 = workFolder + "/fix/black_ir.bmp";
        std::string dir3 = workFolder + "/fix/black_uv.bmp";
        cv::imwrite(dir1.c_str(), picWhite);
        cv::imwrite(dir2.c_str(), picRed);
        cv::imwrite(dir3.c_str(), picPurple);
        for (int i = 0; i < 9 * PICWIDTH; i++) {
            blackPix[i] = 0;
        }
        for (int i = 0; i < 3 * PICWIDTH; i++) {
            for (int j = SPOINT; j < PICHEIGHT - EPOINT; j++) {
                blackPix[i] += mat0[0][i + 3 * PICWIDTH * j];
            }
            blackPix[i] = blackPix[i] * 1.0 / (PICHEIGHT - SPOINT - EPOINT);
        }

        //计算黑色红外图
        for (int i = 0; i < 3 * PICWIDTH; i++) {
            for (int j = SPOINT; j < PICHEIGHT - EPOINT; j++) {
                blackPix[i + 3 * PICWIDTH] += mat0[1][i + 3 * PICWIDTH * j];
            }
            blackPix[i + 3 * PICWIDTH] =
                    blackPix[i + 3 * PICWIDTH] * 1.0 / (PICHEIGHT - SPOINT - EPOINT);
        }

        //计算黑色紫外图
        for (int i = 0; i < 3 * PICWIDTH; i++) {
            for (int j = SPOINT; j < PICHEIGHT - EPOINT; j++) {
                blackPix[i + 6 * PICWIDTH] += mat0[2][i + 3 * PICWIDTH * j];
            }
            blackPix[i + 6 * PICWIDTH] =
                    blackPix[i + 6 * PICWIDTH] * 1.0 / (PICHEIGHT - SPOINT - EPOINT);
        }
        std::string dir4 = workFolder + "/fix/" + deviceID + "/black";
        std::string dir5 = workFolder + "/fix/blackUVRead.txt";
        file = fopen(dir4.c_str(), "wb");
        if (file == NULL) {
            LOGE("write blackerr");
            return;
        }
        fwrite(blackPix, sizeof(int), 9 * PICWIDTH, file);
        fclose(file);
        file = fopen(dir5.c_str(), "wt");
        if (file == NULL)return;
        for (int i = 0; i < PICWIDTH; i++) {
            fprintf(file, "%d %d %d\n", blackPix[6 * PICWIDTH + 3 * i],
                    blackPix[6 * PICWIDTH + 3 * i + 1], blackPix[6 * PICWIDTH + 3 * i + 2]);
        }
        fclose(file);
    }
    //储存校正白图
    if (getPicMode == white) {
        cv::imwrite(workFolder + "/fix/outP_fix0.bmp", picWhite);
        cv::imwrite(workFolder + "/fix/outP_fix1.bmp", picRed);
        cv::imwrite(workFolder + "/fix/outP_fix2.bmp", picPurple);
    }
}

void UsbHandler::ReviseImage(unsigned char mat0[][3 * PICLENGTH], int len) {
    int temp;
    FILE *file = NULL;
    int tempr, tempg, tempb;


    /*
    for (int i = 0; i < 9 * IMGWIDTH; i++) {
        blackPix[i] = 0;
    }*/


    //正常图片校正
    for (int i = 0; i < 3 * PICWIDTH; i++) {
        for (int j = 0; j < PICHEIGHT; j++) {
            temp = mat0[0][i + 3 * PICWIDTH * j] - blackPix[i];
            if (temp < 0)temp = 0;
            else temp = kArr[i] * temp / 64;
            if (temp > 255)temp = 255;
            mat0[0][i + 3 * PICWIDTH * j] = (UCHAR) temp;
        }
    }

    //红外图片校正
    for (int i = 0; i < 3 * PICWIDTH; i++) {
        for (int j = 0; j < PICHEIGHT; j++) {
            temp = mat0[1][i + 3 * PICWIDTH * j] - blackPix[i + 3 * PICWIDTH];
            if (temp < 0)temp = 0;
            else temp = kArr[i + 3 * PICWIDTH] * temp / 64;
            //temp = kArr[i] * (mat0[1][i + 3 * IMGWIDTH * j] - blackPix[i]) / 64;
            if (temp > 255)temp = 255;
            mat0[1][i + 3 * PICWIDTH * j] = (UCHAR) temp;
        }
    }

    //紫外图片校正
    /*
    int fix1, fix2;
    fix1 = IMGWIDTH - (IMGWIDTH * 3 - PICWIDTH * 3 - LEFTOFFSET);
    fix2 = PICWIDTH * 3 - IMGWIDTH  + LEFTOFFSET;*/
    for (int j = 0; j < PICHEIGHT; j++) {
        for (int i = 0; i < PICWIDTH; i++) {
            tempb = mat0[2][3 * i + 3 * PICWIDTH * j] - blackPix[3 * i + 6 * PICWIDTH];
            tempg = mat0[2][3 * i + 1 + 3 * PICWIDTH * j] - blackPix[3 * i + 1 + 6 * PICWIDTH];
            tempr = mat0[2][3 * i + 2 + 3 * PICWIDTH * j] - blackPix[3 * i + 2 + 6 * PICWIDTH];
            //r分量 g分量
            /*
            if (tempr < 1 && tempg < 1) {
                tempr = 0;
                tempg = 0;
            }
            else {
                tempr = kArr[3 * i + 2 + 6 * PICWIDTH] * tempr / 64;
                //temp = kArr[i] * (mat0[2][i + 3 * IMGWIDTH * j] - blackPix[i]) / 64;
                tempg = kArr[3 * i + 1 + 6 * PICWIDTH] * tempg / 64;
                //temp = kArr[i] * (mat0[2][i + 3 * IMGWIDTH * j] - blackPix[i]) / 64;
            }*/
            if (tempr < 0)tempr = 0; else tempr = kArr[3 * i + 2 + 6 * PICWIDTH] * tempr / 64;
            if (tempg < 0)tempg = 0; else tempg = kArr[3 * i + 1 + 6 * PICWIDTH] * tempg / 64;
            if (tempr > 255)tempr = 255;
            if (tempg > 255)tempg = 255;
            mat0[2][3 * i + 2 + 3 * PICWIDTH * j] = (UCHAR) tempr;
            mat0[2][3 * i + 1 + 3 * PICWIDTH * j] = (UCHAR) tempg;
            //b分量
            if (tempb < 0)tempb = 0;
            else tempb = kArr[3 * i + 6 * PICWIDTH] * tempb / 64;
            //temp = kArr[i] * (mat0[2][i + 3 * IMGWIDTH * j] - blackPix[i]) / 64;
            if (tempb > 255)tempb = 255;
            mat0[2][3 * i + 3 * PICWIDTH * j] = (UCHAR) tempb;
        }
        /*
        mat0[2][fix1 + 3 * PICWIDTH*j] = (mat0[2][fix1 - 3 + 3 * PICWIDTH*j] + mat0[2][fix1 + 3 + 3 * PICWIDTH*j]) / 2;
        mat0[2][fix1 + 1 + 3 * PICWIDTH*j] = (mat0[2][fix1 - 2 + 3 * PICWIDTH*j] + mat0[2][fix1 + 4 + 3 * PICWIDTH*j]) / 2;
        mat0[2][fix1 + 2 + 3 * PICWIDTH*j] = (mat0[2][fix1 - 1 + 3 * PICWIDTH*j] + mat0[2][fix1 + 5 + 3 * PICWIDTH*j]) / 2;
        mat0[2][fix2 + 3 * PICWIDTH*j] = (mat0[2][fix2 - 3 + 3 * PICWIDTH*j] + mat0[2][fix2 + 3 + 3 * PICWIDTH*j]) / 2;
        mat0[2][fix2 + 1 + 3 * PICWIDTH*j] = (mat0[2][fix2 - 2 + 3 * PICWIDTH*j] + mat0[2][fix2 + 4 + 3 * PICWIDTH*j]) / 2;
        mat0[2][fix2 + 2 + 3 * PICWIDTH*j] = (mat0[2][fix2 - 1 + 3 * PICWIDTH*j] + mat0[2][fix2 + 5 + 3 * PICWIDTH*j]) / 2;*/
    }

    cv::Mat picWhite = cv::Mat(PICHEIGHT, PICWIDTH, CV_8UC3, mat0[0]);
    cv::Mat picRed = cv::Mat(PICHEIGHT, PICWIDTH, CV_8UC3, mat0[1]);
    cv::Mat picPurple = cv::Mat(PICHEIGHT, PICWIDTH, CV_8UC3, mat0[2]);
    /*
    cv::Mat lastWhite;
    cv::Mat lastRed;
    cv::Mat lastPurple;
    lastWhite.zeros(picWhite.size(), picWhite.type());
    lastRed.zeros(picRed.size(), picRed.type());
    lastPurple.zeros(picPurple.size(), picPurple.type());
    picWhite.convertTo(lastWhite, -1, configCont["normal"], configBri["normal"]-50);
    picRed.convertTo(lastRed, -1, configCont["infrared"], configBri["infrared"]-50);
    picPurple.convertTo(lastPurple, -1, configCont["ultraviolet"], configBri["ultraviolet"]-50);

    cv::imwrite("./image/out_fix_n.bmp", lastWhite);
    cv::imwrite("./image/out_fix_ir.bmp", lastRed);
    cv::imwrite("./image/out_fix_uv.bmp", lastPurple);*/
    cv::resize(picWhite, picWhite, cv::Size(), 1, 1.05, cv::INTER_CUBIC);
    cv::resize(picRed, picRed, cv::Size(), 1, 1.05, cv::INTER_CUBIC);
    cv::resize(picPurple, picPurple, cv::Size(), 1, 1.05, cv::INTER_CUBIC);
    cv::imwrite(workFolder + "/images/Scan_White.jpg", picWhite);
    cv::imwrite(workFolder + "/images/Scan_IR.jpg", picRed);
    cv::imwrite(workFolder + "/images/Scan_UV.jpg", picPurple);



//	pictures[0] = picWhite;
//	pictures[1] = picRed;
//	pictures[2] = picPurple;

}

void UsbHandler::getReviseData(unsigned char mat0[][3 * PICLENGTH]) {
    float whitePix[9 * PICWIDTH];
    FILE *file = NULL;

    for (int i = 0; i < 9 * PICWIDTH; i++) {
        whitePix[i] = 0;
    }
    LOGI("SPOINT: %d, EPOINT: %d", SPOINT, EPOINT);
    //计算正常图校正常数
    for (int i = 0; i < 3 * PICWIDTH; i++) {
        for (int j = SPOINT; j < PICHEIGHT - EPOINT; j++) {
            whitePix[i] += mat0[0][i + 3 * PICWIDTH * j];
        }
        whitePix[i] = whitePix[i] * 1.0 / (PICHEIGHT - SPOINT - EPOINT);
    }

    //计算红外光校正常数
    for (int i = 0; i < 3 * PICWIDTH; i++) {
        for (int j = SPOINT; j < PICHEIGHT - EPOINT; j++) {
            whitePix[i + 3 * PICWIDTH] += mat0[1][i + 3 * PICWIDTH * j];
        }
        whitePix[i + 3 * PICWIDTH] =
                whitePix[i + 3 * PICWIDTH] * 1.0 / (PICHEIGHT - SPOINT - EPOINT);
    }

    //计算紫外光校正常数
    for (int i = 0; i < 3 * PICWIDTH; i++) {
        for (int j = SPOINT; j < PICHEIGHT - EPOINT; j++) {
            whitePix[i + 6 * PICWIDTH] += mat0[2][i + 3 * PICWIDTH * j];
        }
        whitePix[i + 6 * PICWIDTH] =
                whitePix[i + 6 * PICWIDTH] * 1.0 / (PICHEIGHT - SPOINT - EPOINT);
    }

    for (int i = 0; i < 6 * PICWIDTH; i++) {
        kArr[i] = 240.0 * 64 / (whitePix[i] - blackPix[i]);
        //kArr[i] = 245.0 * 64/ (whitePix[i]);
    }
    for (int i = 6 * PICWIDTH; i < 9 * PICWIDTH; i++) {
        kArr[i] = JZ * 64 / (whitePix[i] - blackPix[i]);
    }
    std::string dir1 = workFolder + "/fix/" + deviceID + "/kArr";
    std::string dir2 = workFolder + "/fix/kArrUVRead.txt";
    LOGI("write kArr");
    file = fopen(dir1.c_str(), "wb");
    if (file == NULL) {
        LOGE("write kArrerr");
        return;
    }
    fwrite(kArr, sizeof(int), 9 * PICWIDTH, file);
    fclose(file);
    file = fopen(dir2.c_str(), "wt");
    if (file == NULL)return;
    for (int i = 0; i < PICWIDTH; i++) {
        fprintf(file, "%d %d %d\n", kArr[6 * PICWIDTH + 3 * i], kArr[6 * PICWIDTH + 3 * i + 1],
                kArr[6 * PICWIDTH + 3 * i + 2]);
    }
    fclose(file);

    //白图自我校正
    int tempr, tempg, tempb;
    for (int j = 0; j < PICHEIGHT; j++) {
        for (int i = 0; i < PICWIDTH; i++) {
            tempb = mat0[2][3 * i + 3 * PICWIDTH * j] - blackPix[3 * i + 6 * PICWIDTH];
            tempg = mat0[2][3 * i + 1 + 3 * PICWIDTH * j] - blackPix[3 * i + 1 + 6 * PICWIDTH];
            tempr = mat0[2][3 * i + 2 + 3 * PICWIDTH * j] - blackPix[3 * i + 2 + 6 * PICWIDTH];
            if (tempr < 0)tempr = 0; else tempr = kArr[3 * i + 2 + 6 * PICWIDTH] * tempr / 64;
            if (tempg < 0)tempg = 0; else tempg = kArr[3 * i + 1 + 6 * PICWIDTH] * tempg / 64;
            if (tempr > 255)tempr = 255;
            if (tempg > 255)tempg = 255;
            mat0[2][3 * i + 2 + 3 * PICWIDTH * j] = (UCHAR) tempr;
            mat0[2][3 * i + 1 + 3 * PICWIDTH * j] = (UCHAR) tempg;
            //b分量
            if (tempb < 0)tempb = 0;
            else tempb = kArr[3 * i + 6 * PICWIDTH] * tempb / 64;
            if (tempb > 255)tempb = 255;
            mat0[2][3 * i + 3 * PICWIDTH * j] = (UCHAR) tempb;
        }
    }
    cv::Mat picUVSelf = cv::Mat(PICHEIGHT, PICWIDTH, CV_8UC3, mat0[2]);
    cv::imwrite(workFolder + "/fix/UV_self_fix.bmp", picUVSelf);

    return;
}

bool UsbHandler::startCap() {
    UCHAR bufOrder[2] = {0x01, fpga_ready};  // 0 低位 1 高位
    if (lightChangeOn) {
        if (sendSignal(rLight[0], rLight[1]) == STATUS_FAILED) {
            LOGE("R signal send error!\n");
            return false;
        }
        if (sendSignal(gLight[0], gLight[1]) == STATUS_FAILED) {
            LOGE("G signal send error!\n");
            return false;
        }
        if (sendSignal(bLight[0], bLight[1]) == STATUS_FAILED) {
            LOGE("B signal send error!\n");
            return false;
        }
        if (sendSignal(irLight[0], irLight[1]) == STATUS_FAILED) {
            LOGE("IR signal send error!\n");
            return false;
        }
        if ((sendSignal(uv1Light[0], uv1Light[1]) == STATUS_FAILED) ||
            (sendSignal(uv2Light[0], uv2Light[1]) == STATUS_FAILED)) {
            LOGE("UV signal send error!\n");
            return false;
        }
    }
    bufOrder[0] = 0x00;
    bufOrder[1] = fpga_cap;
    if (sendSignal(bufOrder[0], bufOrder[1]) == STATUS_FAILED) {
        LOGE("Finish\n");
        return false;
    }
    return true;

}

bool UsbHandler::endCap() {
    UCHAR bufOrder[2] = {0x00, fpga_finish};  // 0 低位 1 高位
    if (sendSignal(bufOrder[0], bufOrder[1]) == STATUS_FAILED) {
        LOGE("End Cap send error\n");
        return false;
    }
    bufOrder[1] = fpga_feedback;
    if (sendSignal(bufOrder[0], bufOrder[1]) == STATUS_FAILED) {
        LOGE("Feedback send error\n");
        return false;
    }
    return true;
}

bool UsbHandler::sendSignal(UCHAR low, UCHAR high) {
    UCHAR bufOrder[2];
    bufOrder[0] = low;
    bufOrder[1] = high;
    if (usbDevice.bulk_write(bufOrder, 2, 1000) == STATUS_FAILED) {
        return false;
    }
    return true;
}

bool UsbHandler::setLight(int r, int g, int b, int ir, int uv1, int uv2) {
    rLight[0] = r & 0xff;
    gLight[0] = g & 0xff;
    bLight[0] = b & 0xff;
    irLight[0] = ir & 0xff;
    uv1Light[0] = uv1 & 0xff;
    uv2Light[0] = uv2 & 0xff;
    rLight[1] = ((r & 0xff00) >> 8) + fpga_r;
    gLight[1] = ((g & 0xff00) >> 8) + fpga_g;
    bLight[1] = ((b & 0xff00) >> 8) + fpga_b;
    irLight[1] = ((ir & 0xff00) >> 8) + fpga_ir;
    uv1Light[1] = ((uv1 & 0xff00) >> 8) + fpga_uv1;
    uv2Light[1] = ((uv2 & 0xff00) >> 8) + fpga_uv2;
    return true;
}

bool UsbHandler::calibrate(std::string id) {
    deviceID = id;
    LOGI("calibrate deviceID:%s", deviceID.c_str());
    setLightChangeOn(true);
    setMode(black);
    LOGI("get black image**********************\n");
    setLight(0, 0, 0, 0, 0, 0);
    acquireImage();
    setMode(white);
    sleep(2);
    LOGI("after sleep get white image**********************\n");
    setLight(25, 52, 45, 30, 875, 875);
    acquireImage();
    setLightChangeOn(false);
    setMode(normal);
    return true;
}

void UsbHandler::setRevisionPara(FILE *black, FILE *k) {
    fread(blackPix, sizeof(int), 9 * PICWIDTH, black);
    fread(kArr, sizeof(int), 9 * PICWIDTH, k);

}