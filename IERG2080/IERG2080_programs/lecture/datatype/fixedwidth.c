#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>

int main()
{
    uint8_t int1;
    scanf("%"SCNu8, &int1);
    printf("%"PRIu8"\n", int1);
    printf("%zu\n", sizeof(int1));

    return 0;
}