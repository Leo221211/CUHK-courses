#include<stdio.h>

int main() {
    int n, i, sum = 0;
    scanf("%d", &n);
    int a[n], freq[1001] = {0};
    for(i = 0; i < n; i++) {
        scanf("%d", &a[i]);
        freq[a[i]]++;
    }
    for(i = 1; i <= 1000; i++) {
        if(freq[i] % 2 != 0) {
            printf("-1");
            return 0;
        }
        else
            sum += i * (freq[i] / 2);
    }
    printf("%d", sum);
    return 0;
}
