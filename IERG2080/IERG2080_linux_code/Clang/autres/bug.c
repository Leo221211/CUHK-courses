#include <stdio.h>

int main()
{
	int array[10];

	scanf("%d", &array[0]);
	
	for(int i = 0; i < 10; i ++){
		array[i] = i;
	}
	return 0;
}
