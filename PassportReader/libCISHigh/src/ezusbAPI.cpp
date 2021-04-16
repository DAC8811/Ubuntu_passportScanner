#include "ezusbAPI.h"
#include "libusb-1.0/libusb.h"
#include "internalLogging.h"
#include <stdio.h>

#define LOG_TAG "PassportReaderCPP-CIS-USBAPI"

Ezusb::Ezusb(void) {

}


Ezusb::~Ezusb() {
    libusb_exit(NULL);
    dev_handle = NULL;
}

STATUS Ezusb::open(void) {
    int ret;

    ret = libusb_init(NULL);
    if (ret < 0) {
        LOGE("ezusbAPI init failed\n");
        return STATUS_FAILED;
    } else {
        LOGI("ezusbAPI init success.\n");
    }

    extern int ScanReader_FD;
    libusb_wrap_sys_device(NULL, (intptr_t) ScanReader_FD, &dev_handle);

    //dev_handle = libusb_open_device_with_vid_pid(NULL, USB_VENDOR_ID, USB_PRODUCT_ID);  //open a usb device with VID&PID
    if (dev_handle == NULL) {
        LOGE("ezusbAPI cannot open device\n");
        return STATUS_FAILED;
    } else {
        LOGI(" ezusbAPI usb device opened.\n");;
    }

    return STATUS_SUCESS;
}

STATUS Ezusb::bulk_write(unsigned char *data, int length, unsigned int timeout) {
    int ret;
    int writeAccLen = 0;
    ret = libusb_bulk_transfer(dev_handle, BULK_ENDPOINT_OUT, data, length, &writeAccLen, timeout);
    if (ret < 0) {
//        LOGE("write error.\n");
        return STATUS_FAILED;
    } else {
//        LOGI("write successful.\n");
        return writeAccLen;
    }
}

STATUS Ezusb::bulk_read(unsigned char *data, int length, unsigned int timeout) {
    int ret;
    int readAccLen = 512;
    ret = libusb_bulk_transfer(dev_handle, BULK_ENDPOINT_IN, data, length, &readAccLen, timeout);
    if (ret < 0 && ret != LIBUSB_ERROR_TIMEOUT) {
        LOGE("read error : %d\n", ret);
        return ret;
    } else {
//        LOGI("read successful.\n");
        return readAccLen;
    }
}

STATUS Ezusb::close(void) {
    if (dev_handle)
        libusb_close(dev_handle);
    dev_handle = NULL;
    return STATUS_SUCESS;
}

