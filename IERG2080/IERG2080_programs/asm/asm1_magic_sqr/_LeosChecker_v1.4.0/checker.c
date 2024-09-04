#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

char buf[100000];
int square[5000][5000];

int main(int argc, char **argv)
{
    int N = atoi(argv[1]);
    long long sum = (long long)N * (N * N + 1) / 2;

    int i, j;
    for (i = 0; i < N; i++)
    {
        fgets(buf, sizeof(buf), stdin);
        char *ptr = buf;
        for (j = 0; j < N; j++)
        {
            if (!ptr)
                return 1;
            while (isspace(*ptr))
                ptr++;
            if (sscanf(ptr, "%d", &square[i][j]) < 1)
                return 1;
            ptr = strchr(ptr, ' ');
        }
    }

    long long diagsum1 = 0;
    long long diagsum2 = 0;
    for (i = 0; i < N; i++)
    {
        long long rowsum = 0;
        long long colsum = 0;
        for (j = 0; j < N; j++)
        {
            rowsum += square[i][j];
            colsum += square[j][i];
        }
        if (rowsum != sum || colsum != sum)
            return 1;
        diagsum1 += square[i][i];
        diagsum2 += square[i][N - 1 - i];
    }
    if (diagsum1 != sum || diagsum2 != sum)
        return 1;
    return 0;
}
