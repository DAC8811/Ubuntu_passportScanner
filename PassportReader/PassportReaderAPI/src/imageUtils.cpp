#include <opencv2/opencv.hpp>

#include "getData.h"
#include "mrzUtils.h"

using namespace cv;
int cropFace(string srcImgPath, string faceImgPath, int cardType) {
    Mat img = imread(srcImgPath);
    resize( img, img , Size(0,0) , 2, 2);
    Mat face;
    switch (cardType) {
        case PASSPORT:
            face = img(Rect( 40, 100, 246, 322));
            break;
        case PASSPORT_WITHOUT_CHIP:
            face = img(Rect( 40, 100, 246, 322));
            break;
        case HKMO_EXIT_ENTRY_PERMIT:
            face = img(Rect( 20, 90, 180, 220));
            break;
        case TAIWAN_PASSPORT:
            face = img(Rect( 20, 90, 180, 220));
            break;
        case HKMO_HOME_RETURN_PERMIT:
            face = img(Rect( 10, 80, 180, 255));
            break;
        case MO_HOME_RETURN_PERMIT:
            face = img(Rect( 10, 80, 180, 255));
            break;
        case HK_HOME_RETURN_PERMIT:
            face = img(Rect( 10, 80, 180, 255));
            break;
        case TW_HOME_RETURN_PERMIT:
            face = img(Rect( 10, 80, 180, 255));
            break;
        case HKMO_HOME_RETURN_PERMIT_NOCHIP:
            face = img(Rect( 24, 70, 225, 270));
            break;
        default:
            face = img(Rect( 0, 0, 180, 220));
            break;
    }
    resize( face, face, Size(0,0) , 0.5, 0.5);
    imwrite(faceImgPath,face);
    return 0;
}