#include <stdlib.h>
#include <stdio.h>
#include <sys/wait.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>

int main() {

    // printf("%s", getcwd());
    int a[] = {1, 2, 3};
    printf("%d\n", int(sizeof(a) / sizeof(a[0])));

    return 0;
}