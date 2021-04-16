#ifndef __EZUSB_API_H
#define __EZUSB_API_H

#include "libusb-1.0/libusb.h"

#define USB_VENDOR_ID			0x04b4
#define USB_PRODUCT_ID			0x1004
//#define USB_VENDOR_ID			0x206D
//#define USB_PRODUCT_ID			0x0681

#define BULK_ENDPOINT_OUT 0x02
#define BULK_ENDPOINT_IN  0x86

typedef int STATUS;
#define STATUS_SUCESS 0
#define STATUS_FAILED -1

class Ezusb
{
private:
    /* data */
    libusb_device_handle* dev_handle;
    // struct userDevice user_device;
    // struct libusb_device_descriptor dev_desc;
public:
    Ezusb();
    ~Ezusb();
    STATUS open(void);
    STATUS bulk_write(unsigned char *data, int length, unsigned int timeout);
    STATUS bulk_read(unsigned char *data,int length, unsigned int timeout);
    STATUS close(void);
    bool isConnect(){
        return (dev_handle == NULL);
    }
};


int list_devices(void);
int get_descriptor_with_vid_pid(int vid, int pid);

#endif
