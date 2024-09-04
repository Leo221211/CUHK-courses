// This file is named as lab0-q4-tc1.c
#include"lab0-q4.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<limits.h>

int main(int argc, char *argv[]){

    FILE *fout = fopen(argv[1], "w");
    int value1, value2, value3;
    int ans1, ans3;

    value2 = 0; // input is 0
    ans1 = 0;   // 0 is not negative
    ans3 = 0;   // 0 is not prime

    value1 = isprime(value2, &value3);

    /* output "Correct" if isprime() is correctly implemented */
    if (value1 != ans1 || value3 != ans3) {
        fprintf(fout, "Prime: Wrong Answer\n");
    } else {
        fprintf(fout, "Prime: Correct\n");
    }
    fclose(fout);

    return 0;
}
