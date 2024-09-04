#include <stdio.h>
#include <math.h>

int sq(int i)
{
    return sqrt(i);
}

int det3x3(int matA[3][3])
{
    return matA[0][0] * (matA[1][1] * matA[2][2] - matA[2][1] * matA[1][2]) \
        - matA[0][1] * (matA[1][0] * matA[2][2] - matA[2][0] * matA[1][2]) \
        + matA[0][2] * (matA[1][0] * matA[2][1] - matA[2][0] * matA[1][1]);
}

int main()
{
    int mat[3][4];
    int tmp_mat[3][3];
    int detA, detA1, detA2, detA3;

    // input mat
    for(int i = 0; i < 3; i ++)
    {
        for(int j = 0; j < 4; j ++)
        {
            scanf("%d", &mat[i][j]);
        }
    }

    // cal detA and tell uniqueness
    for(int i = 0; i < 3; i ++)
    {
        for(int j = 0; j < 3; j ++)
        {
            tmp_mat[i][j] = mat[i][j];
        }
    }
    detA = det3x3(tmp_mat);

    if(detA == 0)
    {
        printf("No unique solution");
        return 0;
    }

    // if unique calulate sol
    // cal det 123
    for(int i = 0; i < 3; i ++)
    {
        for(int j = 0; j < 3; j ++)
        {
            tmp_mat[i][j] = mat[i][j];
        }
    }
    for(int i = 0; i < 3; i ++)
    {
        tmp_mat[i][0] = mat[i][3];
    }
    detA1 = det3x3(tmp_mat);
    for(int i = 0; i < 3; i ++)
    {
        for(int j = 0; j < 3; j ++)
        {
            tmp_mat[i][j] = mat[i][j];
        }
    }
    for(int i = 0; i < 3; i ++)
    {
        tmp_mat[i][1] = mat[i][3];
    }
    detA2 = det3x3(tmp_mat);
    for(int i = 0; i < 3; i ++)
    {
        for(int j = 0; j < 3; j ++)
        {
            tmp_mat[i][j] = mat[i][j];
        }
    }
    for(int i = 0; i < 3; i ++)
    {
        tmp_mat[i][2] = mat[i][3];
    }
    detA3 = det3x3(tmp_mat);

    double x,y,z;
    x=1.0*detA1/detA;
    y=1.0*detA2/detA;
    z=1.0*detA3/detA;
    printf("%lf %lf %lf", x,y,z);

    return 0;
}