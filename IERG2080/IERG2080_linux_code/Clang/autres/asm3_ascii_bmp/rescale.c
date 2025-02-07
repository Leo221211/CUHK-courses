#include "rescale.h"
#include <sys/ioctl.h>
#include <unistd.h>

// rounding
int my_round(double num)
{
    return (int)(num + 0.5);
}

// return terminal widthqq
int tmn_width()
{
    struct winsize w;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
    return (int)w.ws_col;

}

// return the row number of ascii art (number of columns in terminal)
int tmn_height(int img_w, int tmn_w, int img_h)
{
    double blk_w = 1 > (double)img_w / tmn_w ? 1 : (double)img_w / tmn_w;
    double tmp_blk_h = blk_w * 2;
    return my_round(img_h / tmp_blk_h);
}

// return scaled block in struct
rscblk_t rescale(int img_w, int tmn_w, int img_h)
{
    double blk_w = 1 > (double)img_w / tmn_w ? 1 : (double)img_w / tmn_w;
    double tmp_blk_h = blk_w * 2;
    int row_num = my_round(img_h / tmp_blk_h);
    double blk_h = (double)img_h / row_num;

    return (rscblk_t){blk_h, blk_w};
}

// input the row and col of terminal and block width and height      output start / end row, col 
bmpadr_t bmp_map(int tmn_row, int tmn_col, double blk_w, double blk_h)
{
    int bmp_s_row = my_round(blk_h * tmn_row);
    int bmp_s_col = my_round(blk_w * tmn_col);
    int bmp_e_row = my_round(blk_h * (tmn_row + 1)) - 1;
    int bmp_e_col = my_round(blk_w * (tmn_col + 1)) - 1;

    return (bmpadr_t){bmp_s_row, bmp_s_col, bmp_e_row, bmp_e_col};
}

