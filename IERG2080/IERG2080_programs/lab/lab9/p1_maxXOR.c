#include <stdio.h>

unsigned int next_same_bits(unsigned int x)
{
    // count number of set bits in x
    int set_bits = 0;
    for (int i = 0; i < sizeof(unsigned int) * 8; i++)
    {
        if ((x & (1 << i)) != 0)
        {
            set_bits++;
        }
    }

    // find next number with same number of set bits
    unsigned int y = x + 1;
    // flip rightmost non-trailing zero bit
    unsigned int flip = y ^ (y & (y - 1));


    // shift bits to the right
    unsigned int shift = flip | (flip - 1);
    // set low-order bits to 1
    unsigned int next_num = (y | shift) & ~(shift >> 1);

    
    // check if number of set bits is the same
    int next_set_bits = 0;
    for (int i = 0; i < sizeof(unsigned int) * 8; i++)
    {
        if ((next_num & (1 << i)) != 0)
        {
            next_set_bits++;
        }
    }
    if (next_set_bits == set_bits)
    {
        return next_num;
    }
    else
    {
        return 0; // error: no next number found
    }
}

int main()
{
    printf("%d", next_same_bits(9999));
    return 0;
}