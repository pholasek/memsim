#include <stdlib.h>
#include <string.h>

#define SIZE 1000000

int main()
{
	int *p;

	p = (int *) malloc(SIZE * sizeof(int));
	memset(p, SIZE * sizeof(int), 0);
	free(p);

	return 0;
}
