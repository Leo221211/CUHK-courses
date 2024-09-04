#include <stdio.h>
#include <stdlib.h>

int wiggleMaxLength(int* nums, int numsSize) {
    if (numsSize < 2) {
        return numsSize;
    }

    int* up = (int*) calloc(numsSize, sizeof(int));
    int* down = (int*) calloc(numsSize, sizeof(int));
    int i, j, result = 1;

    for (i = 1; i < numsSize; i++) {
        for (j = 0; j < i; j++) {
            if (nums[i] > nums[j]) {
                up[i] = (up[i] > down[j] + 1) ? up[i] : down[j] + 1; // the bigger one
            } else if (nums[i] < nums[j]) {
                down[i] = (down[i] > up[j] + 1) ? down[i] : up[j] + 1;  // the bigger one
            }
        }
        result = (result > up[i] + 1) ? result : up[i] + 1; 
        result = (result > down[i] + 1) ? result : down[i] + 1;     // the bigger one
    }

    free(up);
    free(down);

    return result;
}

int main()
{
    int size;
    scanf("%d", &size);

    int *nums = (int*)malloc(size * sizeof(int));
    for(int i = 0; i < size; i ++)
    {
        scanf("%d", nums + i);
    }

    printf("%d", wiggleMaxLength(nums, size));

    free(nums);

    return 0;
}