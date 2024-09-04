#include<stdio.h>

int main()
{
    int i,c,n,r;

    /* We get the range of matrix in variable n and use
       to set the range for magic square box  */

    printf("Enter the range of magic square\n");
    scanf("%d",&n);
    int arr[n][n];

    /*   In first for loop we use to arrange the elements
         on the equations of magic square box     */


    for(i=1;i<=n*n;i++)
    {
        r=(n-i%n+1+2*((i-1)/n))%n;    // for row  //
        c=((n-1)/2+i-1-(i-1)/n)%n;   // for column //
        arr[r][c]=i;
    }

    /*    Here we print the generated magic square box using nested for loops   */
    
    for(r=0;r<n;r++)
    {
        for(c=0;c<n;c++)
        {
            printf("%d\t",arr[r][c]);
        }
        printf("\n");
    }

    return 0;    
}