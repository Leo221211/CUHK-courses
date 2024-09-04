#ifndef _RESCALE_H
#define _RESCALE_H

// rounding
int my_round(double num);

// find the width of the terminal
int tmn_width();

// find the row number of ascii art (number of columns in terminal)
int tmn_height(int img_w, int tmn_w, int img_h);

// return the rescaled block height and width in a structure rscblk_t
typedef struct{
    double h, w;
} rscblk_t;

rscblk_t rescale(int img_w, int tmn_w, int img_h);

// input the row and col of terminal and block width and height      output start row, col ,, height, width
typedef struct{
    int srow, scol, erow, ecol;
} bmpadr_t;


// input the row and col of terminal and block width and height      output start / end row, col 
bmpadr_t bmp_map(int tmn_row, int tmn_col, double blk_w, double blk_h);

#endif