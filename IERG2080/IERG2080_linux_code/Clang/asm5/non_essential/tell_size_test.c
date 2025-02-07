#include <stdio.h>

int main(int argc, char *argv[])
{
    FILE * fp = fopen(argv[1], "r");
    if(fp == NULL) {perror("can't open file\n"); exit(1);}

    printf("STT: %ld\n", ftell(fp));

    fseek(fp, 0L, SEEK_END);
    printf("END: %ld\n", ftell(fp));

    return 0;
}