#include <stdio.h>

struct foo{
    char c1;        // 1 Bytes
    int i;          // 4 Bytes
    char c2;        // 1 Bytes
    double d;       // 8 Bytes
};

void func(double *d)
{
    struct foo tmp;
    int diff = (char*)&tmp.i - (char*)&tmp.d;
    int *i = (int*)((char*)d + diff);
    printf("%d", *i);
}

int main(void)
{
    struct foo bar;
    bar.i = 10; // for example 
    
    func(&bar.d);

    // printf(" %zu %zu", sizeof(char), sizeof(struct foo));  // 1, 24
    return 0;
}
