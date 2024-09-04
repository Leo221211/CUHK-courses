#include <stdio.h>
#include <stdlib.h>
#include "rescale.h"
#include "bmp_access.h"

#define str(s) #s

int main()
{
    // find image width, height
    bmpdata_t img_data = rheader();
    int img_w = img_data.w;
    int img_h = img_data.h;


    // input pixel data
        // define 2D pixel array
    int row_num = img_h;
    int col_num = (int)((BITSpPXL * img_w + 31) / 32) * 4;
    unsigned char **pxlmap = (unsigned char**)malloc(row_num * sizeof(unsigned char*));
    for(int i = 0; i < row_num; i ++)
    {
        pxlmap[i] = (unsigned char*)malloc(col_num * sizeof(unsigned char));
    }

    
        // input pixel data, first row first
    for(int i = 0; i < row_num; i ++)
    {
        for(int j = 0; j < col_num; j ++)
        {
            scanf("%c", &pxlmap[row_num - 1 - i][j]);
            // printf("%d", pxlmap[row_num - 1 - i][j]);
        }
    }

    // terminal height and width
    int tmn_w = tmn_width();        // terminal height and width
    int tmn_h = tmn_height(img_w, tmn_w, img_h);
    
    const rscblk_t block_status = rescale(img_w, tmn_w, img_h);
    

    // find block data
    bmpadr_t block_adr;

    unsigned char grns_c;

//test
/*
    int row = 0, col = 0;
    block_adr = bmp_map(row, col, block_status.w, block_status.h);
    // find color;
    printf("\x1b[38;5;%dm", find_color(block_adr, pxlmap));
    // printf("%d ", find_color(block_adr, pxlmap));    // all 0

    // find the grayness coresponding ascii
    grns_c = find_ascii(find_greyness(block_adr, pxlmap));

    // print char
    printf("%c", grns_c);
    */


    // for row_num
    for(int row = 0; row < tmn_h; row ++)
    {
        // for col_num
        for(int col = 0; col < tmn_w; col ++)
        {
            // find the BMP block address
            block_adr = bmp_map(row, col, block_status.w, block_status.h);


            // find color;
            printf("\x1b[38;5;%dm", find_color(block_adr, pxlmap));
            // printf("%d ", find_color(block_adr, pxlmap));    // all 0

            // find the grayness coresponding ascii
            grns_c = find_ascii(find_greyness(block_adr, pxlmap));

            // print char
            printf("%c", grns_c);

        }
        putchar('\n');
    }


    // free memory
    for(int i = 0; i < row_num; i ++)
    {
        free(pxlmap[i]);
    }
    free(pxlmap);
    // reset default colour
    printf("\x1b[0m");

    return 0;
}


