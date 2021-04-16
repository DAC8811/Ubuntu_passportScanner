#pragma once
#ifndef DATASTRUCT_H
#define DATASTRUCT_H

#define IMGHEIGHT 670
#define IMGWIDTH  1008
#define PICHEIGHT 670
#define PICWIDTH  1008
#define LEFTOFFSET 0*3
#define UPOFFSET 0*3
//#define PICHEIGHT 2507
//#define PICWIDTH  1728
//#define LEFTOFFSET 0
//#define UPOFFSET 0
//#define	SPOINT 100
//#define	EPOINT 100
#define    SPOINT 0
#define    EPOINT (IMGHEIGHT-20)
#define DATALENGTH IMGHEIGHT*IMGWIDTH
#define PICLENGTH PICHEIGHT*PICWIDTH
#define RECEIVESIZE 512*6000
#define BUFSIZE 5
#define COEFFICIENTS 0.8

typedef unsigned char UCHAR;

enum msg_type : UCHAR {
    fpga_ready = 0x00,

    fpga_r = 0x04,
    fpga_g = 0x08,
    fpga_b = 0x0C,
    fpga_ir = 0x10,
    fpga_uv1 = 0x18,
    fpga_uv2 = 0x1C,

    fpga_cap = 0x14,

    fpga_feedback = 0x24,
    fpga_finish = 0x28,

    fpga_roffset = 0x30,
    fpga_goffset = 0x34,
    fpga_boffset = 0x38,

    fpga_rpga = 0x3D,
    fpga_gpga = 0x41,
    fpga_bpga = 0x45,
    fpga_adcfg = 0x48,


    FpgaStatusLightHigh = 0x4c,
    FpgaStatusLightGreen = 0x00,
    FpgaStatusLightBlue = 0x01,
    FpgaBuzzerHigh = 0x50,
    FpgaBuzzerOne = 0x01,
    FpgaBuzzerTwo = 0x02,
    FpgaBuzzerThree = 0x03,


    FpgaDocumentIn = 0x99,
    FpgaDocumentOut = 0x88,


};

enum mode : UCHAR {
    normal,
    white,
    black
};

enum resultdata : int {
    result_normal = 0,
    result_white,
    result_black,
    result_false = -1,
    result_disconnect = -5,
    result_timeout = -2
};
#endif // !DATASTRUCT_H


