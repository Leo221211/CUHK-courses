#include <stdio.h>

struct Type1{
    int a1;
};

typedef struct{
    int a;
} Test;

typedef struct BestType BestType;
struct BestType{
    int Ba;
};

int main()
{
    printf("Hello World!\n");

    struct Type1 obj1;

    Test obj;
    obj.a = 1;
    printf("%d", obj.a);

    BestType objB;


    return 0;
}