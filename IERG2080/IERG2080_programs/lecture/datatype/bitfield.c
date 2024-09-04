#include <stdio.h>

#pragma pack(2)
struct bitfield{
    short s1:1;
    short s2:2;
    short s3:3;
    int i;
};

int main()
{
    struct bitfield bf;
    printf("%zu", sizeof(struct bitfield));
    return 0;
}