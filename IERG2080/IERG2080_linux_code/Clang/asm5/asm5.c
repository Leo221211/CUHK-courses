/**
 * 1. fseek(END) + ftell(fp) is directly the size: for unix file or windows files in rb: there is a '\0' at the end ;; 
 *    actually it is not well defined
 * 2. FILE * ifp, ofp;;
 * 3. fprintf(ofp, "%u", size): things printed out to screen are characters! for characters, is OK, but for num, ... if want to print out as binary, should print out the binary sequence: fwrite()
 * 4. memcpy(ofp, &size, sizeof(size));: also don't work: memcpy can't copy across files
 * 5. (WRONG) about feof(): after scan operation, the pointer doesn't go to the next position, it goes when next time scanf is called
 * 6. EOF is not stored in a file. It is a message returned by OS when unable to keep reading.
*/
#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h> // exit
#include <string.h> // memcpy

// input DNA character and output 2 digit binary number
unsigned char char_to_bin(int chara)
{
    switch(chara)
    {
        case 'C':
            return 0x0;
            break;
        
        case 'G':
            return 0x1;
            break;
        
        case 'A':
            return 0x2;
            break;
        
        case 'T':
            return 0x3;
            break;

        default:
            return -1;
            break;
    }
}

// input 2 digit binary number and output corresponding DNA character
unsigned char bin_to_char(int bin)
{
    switch(bin)
    {
        case 0x0:
            return 'C';
            break;
        
        case 0x1:
            return 'G';
            break;
        
        case 0x2:
            return 'A';
            break;
        
        case 0x3:
            return 'T';
            break;

        default:
            return -1;
            break;
    }
}

int main(int argc, char* argv[])
{
    // open file
    FILE *ifp, *ofp;
    ifp = fopen(argv[2], "r");
    ofp = fopen(argv[3], "w");
    if(/*ifp == NULL ||*/ ofp == NULL) {perror("error: can't open file\n"); exit(1);}
    // if(!(ifp = fopen(argv[2], "r")) && !(ofp = fopen(argv[3], "w"))) {exit(1);}

    // compress or decompress
    if(argv[1][0] == 'c')           // compress
    {
        // find size and put to file
        fseek(ifp, 0L, SEEK_END);
        unsigned int size = ftell(ifp);
        rewind(ifp);
        // fprintf(ofp, "hello\n");
        for(int i = 0; i < sizeof(size); i ++)
        {
            fputc(*((unsigned char *)&size + i), ofp);
        }
        // fprintf(stdout, "%u", size);
        fflush(ofp);

        // compress
        unsigned char tmp_group[4] = {0};
        int grp_flag = 0;

        for(int i = 0; i < size + size / 4; i ++)
        {
            if(grp_flag == 4)       // fill output file and clear
            {
                unsigned char tmp_char = 0;
                for(int i = 0; i < 4; i ++)
                {
                    tmp_char |= tmp_group[i] << (6 - 2 * i);
                }
                fputc(tmp_char, ofp);
                // fflush(ofp);

                grp_flag = 0;
                for(int i = 0; i < 4; i ++)
                {
                    tmp_group[i] = 0;
                }
            }
            else                    // keep reading
            {
                unsigned char tmpchar = fgetc(ifp);

                tmp_group[grp_flag] = char_to_bin(tmpchar);
                grp_flag ++;
                // printf("char: %d gf: %d\n", tmpchar, grp_flag);
            }
        }

        // printf("%d\n", grp_flag);
        // return 0

        if(grp_flag != 0)
        {
            // printf("here\n");
            unsigned char tmp_char = 0;
            // printf("%d\n", grp_flag);
            for(int i = 0; i < size % 4; i ++)
            {
                // printf("%02x ", tmp_group[i]);
                tmp_char |= tmp_group[i] << (6 - 2 * i);
            }
            // printf("\n%x\n", tmp_char);
            fputc(tmp_char, ofp);
        }
    }
    else                            // decompress
    {
        // get size
        unsigned int size;
        if(fread(&size, sizeof(unsigned), 1, ifp));
        // printf("%u\n", size);

        // decompose
        // complete groups
        unsigned char tmp_char;
        for(int i = 0; i < size / 4; i ++)
        {
            tmp_char = fgetc(ifp);
            for(int j = 3; j >= 0; j--)
            {
                fputc(bin_to_char(tmp_char >> (2*j) & 0x3), ofp);
            }
        }

        // incomplete groups
        tmp_char = fgetc(ifp);
        for(int j = 3; j >= 4 - size % 4; j--)
        {
            fputc(bin_to_char(tmp_char >> (2*j) & 0x3), ofp);
            // printf("%x ", tmp_char);
        }

    }

    // closefile
    fcloseall();

    return 0;
}