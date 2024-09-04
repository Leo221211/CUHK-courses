#include <bits/stdc++.h>
using namespace std;

const int BIT_WIDTH=200;    // Width of the bitmap in pixels.
const int BIT_HEIGHT=250;   // Height of the bitmap in pixels.
const int BITS_PER_PIXEL=4; // Number of bits used to represent a pixel.
const int COLOR_COUNT=16;

struct bfhead{
    uint16_t bfType;
    uint32_t bfSize;
    uint16_t bfReserved1;
    uint16_t bfReserved2;
    uint32_t bfOffBits;
}bitmap_head;

struct bihead{
    uint32_t biSize;
    uint32_t biWidth;
    uint32_t biHeight;
    uint16_t biPlanes;
    uint16_t biBitCount;
    uint32_t biCompression;
    uint32_t biSizeImage;
    uint32_t biXPelsPerMeter;
    uint32_t biYPelsPerMeter;
    uint32_t biClrUsed;
    uint32_t biClrImportant;
}info_head;

struct bcolor{
    uint8_t blue;
    uint8_t green;
    uint8_t red;
    uint8_t alpha;
}palette[COLOR_COUNT];

uint32_t gs_bitmap[BIT_HEIGHT][BIT_WIDTH];     // Grey-scale bit map.


// Bitmap pixel data loader.
void loadGreyScaleBitmap(std::string _map_file_){
    // Initiate loading process.
    printf("[LOADER] Loading gray-scale bitmap data from file %s.\n", _map_file_.c_str());
    FILE* map=fopen(_map_file_.c_str() ,"r+");
    _sleep(1000);

    // Obtain width and height in pixels.
    int _wid_, _hgt_;
    fscanf(map,"%u %u", &_wid_, &_hgt_);
    printf("[LOADER] Bitmap size: (pixels) %d x %d\n", _wid_, _hgt_);
    _sleep(1000);

    // Load pixel values.
    printf("[LOADER] Loading pixel values ...\n");
    for(int i=0;i<_hgt_;++i){
        for(int j=0;j<_wid_;++j){
            fscanf(map, "%u", &gs_bitmap[i][j]);
            //printf("[LOADER] ROW (%d/%d)\tCOL (%d/%d)\n", i, _hgt_, j, _wid_);
        }
        printf("[LOADER] ROW (%d/%d)\n",i, _hgt_);
    }
    fclose(map);
}

// Print out the grey-scale bitmap on panel.
void chkGreyScaleBitmap(){
    printf("[CHECKER] Showing grey-scale bitmap:\n");
    printf("Grey-scale Bitmap --- %dx%d\n", BIT_WIDTH, BIT_HEIGHT);
    for(int i=0;i<BIT_HEIGHT;++i){
        for(int j=0;j<BIT_WIDTH;++j){
            printf("%d ", gs_bitmap[i][j]);
        }
        printf("\n");
    }
}

void genBfHeader(){
    printf("[GENERATOR] Generating bitmap file header. [-----] (0/5)\n");

    bitmap_head.bfType=0x4d42; // Bitmap type specifies to be "BM". Written in big-endian.
    printf("[GENERATOR] Generating bitmap file header. [+----] (1/5) bfType\n");

    bitmap_head.bfSize=14+40+(4*COLOR_COUNT)+(4*BIT_HEIGHT*ceil((double)BITS_PER_PIXEL*(double)BIT_WIDTH*(1.0/32.0)));
    //bitmap_head.bfSize=14+40+ 4*(COLOR_COUNT) + BIT_HEIGHT*BIT_WIDTH*((double)BITS_PER_PIXEL/8.0);
    printf("[GENERATOR] Generating bitmap file header. [++---] (2/5) bfSize\n");

    bitmap_head.bfReserved1=0x0000;
    printf("[GENERATOR] Generating bitmap file header. [+++--] (3/5) bfReserved1\n");

    bitmap_head.bfReserved2=0x0000;
    printf("[GENERATOR] Generating bitmap file header. [++++-] (4/5) bfReserved2\n");

    bitmap_head.bfOffBits=14+40+(4*COLOR_COUNT);
    printf("[GENERATOR] Generating bitmap file header. [+++++] (5/5) bfType\n");
    printf("[GENERATOR] Generating bitmap file header. Done.\n");
}

void genBiHeader(){
    printf("[GENERATOR] Generating bitmap info header. [-----------] (0/11)\n");

    info_head.biSize=0x00000028;
    printf("[GENERATOR] Generating bitmap info header. [+----------] (1/11) biSize\n");

    info_head.biWidth=BIT_WIDTH;
    printf("[GENERATOR] Generating bitmap info header. [++---------] (2/11) biWidth\n");

    info_head.biHeight=BIT_HEIGHT;
    printf("[GENERATOR] Generating bitmap info header. [+++--------] (3/11) biHeight\n");

    info_head.biPlanes=1;
    printf("[GENERATOR] Generating bitmap info header. [++++-------] (4/11) biPlanes\n");

    info_head.biBitCount=BITS_PER_PIXEL;
    printf("[GENERATOR] Generating bitmap info header. [+++++------] (5/11) biBitCount\n");

    info_head.biCompression=0;
    printf("[GENERATOR] Generating bitmap info header. [++++++-----] (6/11) biCompression\n");

    info_head.biSizeImage=0;
    printf("[GENERATOR] Generating bitmap info header. [+++++++----] (7/11) biSizeImage\n");

    info_head.biXPelsPerMeter=0;
    printf("[GENERATOR] Generating bitmap info header. [++++++++---] (8/11) biXPelsPerMeter\n");

    info_head.biYPelsPerMeter=0;
    printf("[GENERATOR] Generating bitmap info header. [+++++++++--] (9/11) biYPelsPerMeter\n");

    info_head.biClrUsed=COLOR_COUNT;
    printf("[GENERATOR] Generating bitmap info header. [++++++++++-] (10/11) biClrUsed\n");

    info_head.biClrImportant=COLOR_COUNT;
    printf("[GENERATOR] Generating bitmap info header. [+++++++++++] (11/11) biClrImportant\n");
}

void genGreyScalePalette(){
    printf("[GENERATOR] Generating bitmap palette.\n");
    switch(COLOR_COUNT){
        case(2):{
            printf("[GENERATOR] Using 2-color schematics.\n");
            palette[0]=bcolor{0x00,0x00,0x00,0x00};
            palette[1]=bcolor{0xff,0xff,0xff,0x00};
            break;
        }
        case(16):{
            printf("[GENERATOR] Using 16-color schematics.\n");
            uint8_t cur_color_val=0x00;
            for(int i=0;i<COLOR_COUNT;++i){
                printf("[GENERATOR] Generating bitmap palette (%d/%d)\n", i, COLOR_COUNT);
                palette[i].blue=cur_color_val;
                palette[i].green=cur_color_val;
                palette[i].red=cur_color_val;
                palette[i].alpha=0x00;
                cur_color_val+=0x11;
            }
            break;
        }
        case(256):{
            printf("[GENERATOR] Using 8-digit (256-color) schematics.\n");
            uint8_t cur_color_val=0x00;
            for(int i=0;i<COLOR_COUNT;++i){
                printf("[GENERATOR] Generating bitmap palette (%d/%d)\n", i, COLOR_COUNT);
                palette[i].blue=cur_color_val;
                palette[i].green=cur_color_val;
                palette[i].red=cur_color_val;
                palette[i].alpha=0x00;
                cur_color_val+=0x01;
            }
            break;
        }
        default:{
            printf("[GENERATOR] Fatal error. Unable to find color schematics.\n");
            throw("Illegal value of color counts.");
        }
    }
    printf("[GENERATOR] Generating bitmap palette. Done.\n");
}

void writeByte(FILE* _file_, uint8_t item){
    fprintf(_file_, "%c", item);
}

void writeBigEndianUint16(FILE* _file_, uint16_t item){
    char item_00=(char)(item&(0xff));
    char item_01=(char)(((item&(0xff00)))>>8);
    fprintf(_file_,"%c%c", item_00, item_01);
}

void writeBigEndianDword(FILE* _file_, uint32_t item){
    char item_00=(char)(item&0xff);
    char item_01=(char)((item&0xff00)>>8);
    char item_02=(char)((item&0xff0000)>>16);
    char item_03=(char)((item&0xff000000)>>24);
    fprintf(_file_,"%c%c%c%c", item_00, item_01, item_02, item_03);
}

void writeBfHeader(FILE* _file_){
    printf("[WRITER] Writing bitmap file header...\n");
    writeBigEndianUint16(_file_, bitmap_head.bfType);
    writeBigEndianDword(_file_, bitmap_head.bfSize);
    writeBigEndianUint16(_file_, bitmap_head.bfReserved1);
    writeBigEndianUint16(_file_, bitmap_head.bfReserved2);
    writeBigEndianDword(_file_, bitmap_head.bfOffBits);
}

void writeBiHeader(FILE* _file_){
    printf("[WRITER] Writing bitmap info header...\n");
    writeBigEndianDword(_file_, info_head.biSize);
    writeBigEndianDword(_file_, info_head.biWidth);
    writeBigEndianDword(_file_, info_head.biHeight);
    writeBigEndianUint16(_file_, info_head.biPlanes);
    writeBigEndianUint16(_file_, info_head.biBitCount);
    writeBigEndianDword(_file_, info_head.biCompression);
    writeBigEndianDword(_file_, info_head.biSizeImage);
    writeBigEndianDword(_file_, info_head.biXPelsPerMeter);
    writeBigEndianDword(_file_, info_head.biYPelsPerMeter);
    writeBigEndianDword(_file_, info_head.biClrUsed);
    writeBigEndianDword(_file_, info_head.biClrImportant);
}

void writePalette(FILE* _file_){
    for(int i=0;i<COLOR_COUNT;++i){

        writeByte(_file_, (uint8_t)palette[i].blue);
        writeByte(_file_, (uint8_t)palette[i].green);
        writeByte(_file_, (uint8_t)palette[i].red);
        writeByte(_file_, (uint8_t)palette[i].alpha);
        
        printf("[WRITER] Writing palette... (%d/%d)\n", i+1, COLOR_COUNT);
    }
}

void writeGreyScalePixelData(FILE* _file_){
    printf("[WRITER] Writing greyscale pixel data...\n");
    switch(BITS_PER_PIXEL){
        case(4):{
            printf("[WRITER] Implementing 4-bit schematics.\n");
            // For 16-color bitmaps, each pixel takes up 4 bits, for 8 pixels. As shown below, numbers are pixels while "[]"s are bytes.
            // [0|1] [2|3] [4|5] [6|7]
            char buf[4]={(char)0, (char)0, (char)0, (char)0};
            int buf_top=0;  // Top index of PIXELs, not bytes.
            for(int i=0;i<BIT_HEIGHT;++i){
                for(int j=0;j<BIT_WIDTH;++j){   // Iterate every pixel in the grey-scale bitmap.
                    //printf("[WRITER] Writing greyscale pixel data...(%d/%d)\n", i*BIT_WIDTH+j, BIT_HEIGHT*BIT_WIDTH);
                    if(buf_top==8){     // If the buffer is full, dump its content and empty it.
                        for(int k=0;k<4;++k){
                            writeByte(_file_, buf[k]);      // Write every byte.
                            buf[k]=(char)0;     // Empty every byte.
                        }
                        buf_top=0;      // Reset the top index to 0.
                    }
                    if((buf_top%2)==0){     // If the top index is even-numbered, then the pixel takes up higher digits of a byte.
                        buf[buf_top/2]+=(gs_bitmap[i][j])<<4;   // Displace the pixel's data to the left by 4 bits.
                    }   else{       // If the top index is odd-numbered, then the pixel takes up lower digits of a byte.
                        buf[buf_top/2]+=gs_bitmap[i][j];    // Pixel's data needn't be displaced.
                    }   
                    buf_top++;
                }
                
                // At the end of each row, dump content of the buffer regardless of whether it is full.
                for(int i=0;i<4;++i){
                    writeByte(_file_, buf[i]);
                    buf[i]=0;
                }
                buf_top=0;

            }
            break;
        }
        case(8):{
            // For 256-color, or 8-digit bitmaps, each pixel takes up 1 byte.
            char buf[4]={(char)0, (char)0, (char)0, (char)0};   // For windows a 4-byte buffer is usually implemented for bitmap IO.
            int buf_top=0;
            for(int i=0;i<BIT_HEIGHT;++i){
                for(int j=0;j<BIT_WIDTH;++j){  // Iterate every pixel in the grey-scale bitmap.
                    if(buf_top==4){     // Dump the buffer if it's already full.
                        buf_top=0;  // Reset the top index of the buffer.
                        for(int k=0;k<4;++k){
                            writeByte(_file_, buf[k]);      // Write each entry of the buffer into file.
                            buf[k]=(char)0;     // Reset each entry to 0.
                        }
                    }      
                    buf[buf_top]=gs_bitmap[i][j];   // If the buffer is not full, append the byte of the pixel to the end of the buffer.
                    buf_top++;  // Advance top index of buffer by 1.
                }

                // At the end of each row Dump the last buffer session to file, maintaining all blanks.
                for(int i=0;i<4;++i){
                    writeByte(_file_, buf[i]);
                    buf[i]=0;
                }
                buf_top=0;
            }
        }
        break;
    }
}

int main(){
    loadGreyScaleBitmap("gs_bitmap.txt");

    genBfHeader();
    genBiHeader();
    genGreyScalePalette();

    FILE* bitmap_file=fopen("01.bmp", "w+");
    writeBfHeader(bitmap_file);
    writeBiHeader(bitmap_file);
    writePalette(bitmap_file);

    writeGreyScalePixelData(bitmap_file);

    fclose(bitmap_file);
    exit(0);
}
