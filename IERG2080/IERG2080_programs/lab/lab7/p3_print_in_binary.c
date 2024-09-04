#include <stdio.h>

int main() {
    double x;
    scanf("%lf", &x);
    unsigned char *ptr = (unsigned char*)&x;
    for(int i = 0; i < sizeof(double); i++) {
        printf("%02X ", ptr[i]);
    }
    printf("\n");
    return 0;
}

/*
Answer:
In little-endian systems (like Intel and AMD CPUs), 
the least significant byte (LSB) is stored first in memory, 
followed by the more significant bytes
*/