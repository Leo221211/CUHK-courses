#include <stdio.h>
int max(int x, int y)
{
    return (x > y ? x : y);
}\

int wiggle_len(int *num, int len)
{
    if (len <= 2)
        return len;
    else
    {
        int up = 1, down = 1;
        for (int i = 1; i < len; i++)
        {
            if (num[i] > num[i - 1])
                up = down + 1;
            else if (num[i] < num[i - 1])
                down = up + 1;
        }
        return max(up, down);
    }
}
int main()
{
    int sequence[1005];
    int len;
    scanf("%d", &len);
    for (int i = 0; i < len; i++)
    {
        scanf("%d", &sequence[i]);
    }
    printf("%d", wiggle_len(sequence, len));
}