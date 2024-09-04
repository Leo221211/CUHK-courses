int hex_dec_4Ble(char bits[4])
{
    /*
    for(int i = 0; i < 4; i ++)
    {
        printf("%02x ", bits[i]);
    }
    */
    
    int sum = 0;
    sum += bits[0];
    sum += bits[1] * 256;
    sum += bits[2] * 256 * 256;
    sum += bits[3] * 256 * 256 * 256;

    return sum;
}

int main()
{
    

    return 0;
}