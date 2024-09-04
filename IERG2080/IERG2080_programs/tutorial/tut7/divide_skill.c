/**
 * sort and compare!!
*/
#include<stdio.h>


int main() {
    // initialize
    int n, i, j, temp, sum = 0;

    // input
    scanf("%d", &n);
    int a[n];
    for(i = 0; i < n; i++)
        scanf("%d", &a[i]);

    // sort
    for(i = 0; i < n; i++) {
        for(j = i + 1; j < n; j++) {
            if(a[j] < a[i]) {
                temp = a[i];
                a[i] = a[j];
                a[j] = temp;
            }
        }
    }

    // tell if OK
    int skill_sum = a[0] + a[n - 1];
    for(i = 0; i < n / 2; i ++) {
        if(a[i] + a [n - 1 - i] != skill_sum) {
            printf("-1");
            return 0;
        }
        else
            sum += a[i] * a[n - i - 1];
    }
    printf("%d", sum);
    return 0;
}
