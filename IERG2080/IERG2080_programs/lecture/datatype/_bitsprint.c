// use unsigned char instead of signed char or integer expansion to make a 1 byte 4 bytes with expansion
// %X is 4 bytes by default
void bitsprint(void *ptr, int bytes)
{
    for(int i = 0; i < bytes; i ++)
    {
        for(int j = 0; j < 8; j ++)
        {
            printf("%d", ( (*((unsigned char*)ptr + i) >> j) & 1));
        }
        putchar(' ');
    }
    putchar('\n');
}

void hexprint(void *ptr, int bytes)
{
    for(int i = 0; i < bytes; i ++)
    {
        printf("%02X ", *((unsigned char*)ptr + i));
    }
    putchar('\n');
}