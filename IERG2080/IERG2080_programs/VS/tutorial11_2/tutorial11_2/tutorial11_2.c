#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#define scan scanf


int main()
{
	// input
	int len;
	scan("%d", &len);
	int* array = (int*)malloc(len * sizeof(int));
	for (int i = 0; i < len; i++)
	{
		scan("%d", &array[i]);
	}

	// loop from left to right until find not the smallest or the last
	int left = 0;
	for (; left < len; left++) 
	{
		// smaller than all right?
		for (int i = left + 1; i < len; i++) 
		{
			if (array[i] < array[left]) 
			{	
				// left is not suitable
				left--;
				goto right;
			}
		}
	}
	left--;

	// loop from right until not the biggest or the smallest
right:;
	int right = len - 1;
	for (; right > left; right--)
	{
		// bigger than all left?
		for (int i = right - 1; i > left; i--)
		{
			if (array[i] > array[right])	// right is not suitable
			{
				right++;
				goto end;
			}
		}
	}
	right++;

	// print
end:;
	printf("%d", right - left -1);

	return 0;
}