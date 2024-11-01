#include <stdio.h>

int* array;

void qsort(int lo, int hi)
{
    // check if end recursion
    if (lo >= hi)
    {
        return;
    }

    int pivot = array[hi];
    int i = lo - 1;

    // partition
    for (int j = lo; j < hi; j++)
    {
        if (array[j] <= pivot)
        {
            i++;
            int temp = array[i];
            array[i] = array[j];
            array[j] = temp;
        }
    }

    int temp = array[i + 1];
    array[i + 1] = array[hi];
    array[hi] = temp;

    // qsort sub-arrays
    qsort(array, lo, i);
    qsort(array, i + 2, hi);
}


int main()
{
    int array[] = {5, 3, 8, 4, 2};
    int length = sizeof(array) / sizeof(array[0]);

    qsort(array, 0, length - 1);

    for (int i = 0; i < length; i++)
    {
        printf("%d ", array[i]);
    }

    return 0;
}