#ifndef _BMP_ACCESS_H
#define _BMP_ACCESS_H

#include "rescale.h"

// basic data access
#define HEADER_TYPE 0x4D42
#define HEADER_SIZE 0x36
#define FILESIZE_OFFSET 0x2
#define FILESIZE_SIZE 4
#define IMG_OFFSET 0xA
#define IMG_SIZE 4
#define WIDTH_OFFSET 0x12
#define WIDTH_SIZE 4
#define HEIGHT_OFFSET 0x16
#define HEIGHT_SIZE 4
#define BITSpPXL 24

// hex converter: 4 Bytes in little endienness
int hex_dec_4Ble(unsigned char bits[32]);

// bmp data reading: the height and width of bmp image
typedef struct{
    int h, w;
}bmpdata_t;

// read the header, move the pointer to pixel data, read image height and width of bmp file
bmpdata_t rheader();

// the RGB value of each pixel
typedef struct{
    int R, G, B;
}pixel_t;

// input the pixel's row and col of the bmp pixel and return the R, G, B value
pixel_t grab_pixelRGB(int row, int col, unsigned char** pxlmap);

// input bmp block address and return the terminal pixel RGB
pixel_t grab_tmnRGB(bmpadr_t pxladr, unsigned char** pxlmap);

// find grayness
#define MAX_GRAYNESS 0.234375
#define ASCII_NUM 26

typedef struct{
    double grayness;
    unsigned char ascii;
}grayness_t;

// input the block address, output the grayness of the terminal pixel
double find_greyness(bmpadr_t block_adr, unsigned char** pxlmap);

// input the grayness, output the correspoding ascii
unsigned char find_ascii(double grayness);

// calculate the MHT distance between pxl_RGB_t
int mht_dis(pixel_t p1, pixel_t p2);
pixel_t int_pxl(int color);     // convert a 0x color to pixel_t type

// input the block address find the closest color in 256-RGB
int find_color(bmpadr_t blkadr, unsigned char** pxlmap);

#endif