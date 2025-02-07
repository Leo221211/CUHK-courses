#include <stdio.h>
#include "bmp_access.h"
#include "palette.h"
#include <stdlib.h>     // abs()
#include <limits.h>

grayness_t grayness_tbl[ASCII_NUM] =
{
    {0.000000, 32},
    {0.015625, 96},
    {0.031250, 39},
    {0.046875, 45},
    {0.062500, 58},
    {0.070313, 123},
    {0.078125, 47},
    {0.085938, 63},
    {0.093750, 61},
    {0.101563, 108},
    {0.109375, 55},
    {0.117188, 114},
    {0.125000, 73},
    {0.132813, 76},
    {0.140625, 54},
    {0.148438, 110},
    {0.156250, 70},
    {0.164063, 97},
    {0.171875, 88},
    {0.179688, 82},
    {0.187500, 103}, 
    {0.195313, 64},
    {0.210938, 72},
    {0.218750, 35},
    {0.226563, 78},
    {0.234375, 77},
};

// !checked: may overflow
// hex converter: 4 Bytes in little endienness
int hex_dec_4Ble(unsigned char bits[4])
{   
    int sum = 0;
    sum += bits[0];
    sum += bits[1] * 256;
    sum += bits[2] * 256 * 256;
    sum += bits[3] * 256 * 256 * 256;

    return sum;
}

// read the header, move the pointer to pixel data, read image height and width
bmpdata_t rheader()
{
    // input the header
    unsigned char header[HEADER_SIZE];

    // unsigned char tmp;
    for(int i = 0; i < HEADER_SIZE; i ++)
    {
        if(scanf("%c", &header[i]));
        // printf("%c ", tmp);
    }

    bmpdata_t data;
    data.h = hex_dec_4Ble(&header[HEIGHT_OFFSET]);
    data.w = hex_dec_4Ble(&header[WIDTH_OFFSET]);

    return data;
}

// checked
// input the pixel's row and col of the pixel and return the R, G, B value
pixel_t grab_pixelRGB(int row, int col, unsigned char** pxlmap)
{
    int R, G, B;

    // starting address: [row][col * BITSpPXL / 8]
    B = (int)pxlmap[row][col * (BITSpPXL / 8)];
    G = (int)pxlmap[row][col * (BITSpPXL / 8) + 1];
    R = (int)pxlmap[row][col * (BITSpPXL / 8) + 2];
    // printf("RGB: %02x %02x %02x", R, G, B);  // ff fd 55
    // printf("B:%02x ", B);
    // printf("%d ", R);      // 0

    return (pixel_t){R, G, B};
}

// input bmp block address and return the terminal pixel RGB
pixel_t grab_tmnRGB(bmpadr_t pxladr, unsigned char** pxlmap)
{
    int pix_num = 0;    // how many pixels counted
    // printf("%d ", pix_num);
    long Rsum = 0, Gsum = 0, Bsum = 0;

    for(int i = pxladr.srow; i <= pxladr.erow; i ++)
    {
        for(int j = pxladr.scol; j <= pxladr.ecol; j ++)
        {
            Rsum += (long)grab_pixelRGB(i, j, pxlmap).R;
            Gsum += (long)grab_pixelRGB(i, j, pxlmap).G;
            Bsum += (long)grab_pixelRGB(i, j, pxlmap).B;

            pix_num ++;
        }
    }

    // printf("%d", Rsum); // 0
    // printf("%lf %lf %lf", (double)Rsum / pix_num, (double)Gsum / pix_num, (double)Bsum / pix_num); // wrong

    return (pixel_t){(double)Rsum / pix_num, (double)Gsum / pix_num, (double)Bsum / pix_num};

}

// input the block address, output the grayness
double find_greyness(bmpadr_t block_adr, unsigned char** pxlmap)
{
    pixel_t tmn_pxl_RGB = grab_tmnRGB(block_adr, pxlmap);
    // printf("%02x %02x %02x", tmn_pxl_RGB.R, tmn_pxl_RGB.G, tmn_pxl_RGB.B);
    // printf("%lf ", (255 - (0.3 * tmn_pxl_RGB.R + 0.59 * tmn_pxl_RGB.G + 0.11 * tmn_pxl_RGB.B)) / 255 * MAX_GRAYNESS);   // minus
    return (255 - (0.3 * tmn_pxl_RGB.R + 0.59 * tmn_pxl_RGB.G + 0.11 * tmn_pxl_RGB.B)) / 255 * MAX_GRAYNESS;
}

// input the grayness, output the correspoding ascii
unsigned char find_ascii(double grayness)
{
    if(grayness <= grayness_tbl[0].grayness)
    {
        return grayness_tbl[0].ascii;
    }

    if(grayness >= grayness_tbl[ASCII_NUM - 1].grayness)
    {
        return grayness_tbl[ASCII_NUM - 1].ascii;
    }

    int i;
    for(i = 0; i < ASCII_NUM; i ++)
    {
        if(grayness == grayness_tbl[i + 1].grayness)
        {
            return grayness_tbl[i + 1].ascii;
        }

        if(grayness_tbl[i].grayness < grayness && grayness < grayness_tbl[i + 1].grayness)
        {
            break;
        }
    }

    if(grayness_tbl[i + 1].grayness - grayness < grayness - grayness_tbl[i].grayness)   // closer to the higher ones
    {
        return grayness_tbl[i + 1].ascii;
    }
    else
    {
        return grayness_tbl[i].ascii;
    }
}

// calculate the MHT distance between a pxl_RGB_t and a 3 Bytes color
int mht_dis(pixel_t p1, pixel_t p2)
{
    return abs(p1.R - p2.R) + abs(p1.G - p2.G) + abs(p1.B - p2.B);
}

// checked
pixel_t int_pxl(int color)     // convert a 0x color to pixel_t type
{
    int R = color / 256 / 256;
    int G = color / 256 % 256;
    int B = color % 256;

    return (pixel_t){R, G, B};
}

// input the block address find the closest color in 256-RGB
int find_color(bmpadr_t blkadr, unsigned char** pxlmap)
{
    pixel_t tmn_pxl_RGB = grab_tmnRGB(blkadr, pxlmap);      // find the tmn pxl_t of the block
    // printf("%d %d %d", tmn_pxl_RGB.R, tmn_pxl_RGB.G, tmn_pxl_RGB.B);    // all 0

    int min_dis = INT_MAX;
    int apxm_color;

    for(int i = 0; i < 256; i ++)
    {
        if(mht_dis(tmn_pxl_RGB, int_pxl(palette[i])) < min_dis)
        {
            min_dis = mht_dis(tmn_pxl_RGB, int_pxl(palette[i]));
            apxm_color = i;
        }
    }

    return apxm_color;
}