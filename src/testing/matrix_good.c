#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <limits.h>

int main(int argc, char *argv[])
{
	int *matA;
	int *matB;
	int *matC;
	int dim;

	if (argc < 2) {
		printf("Wrong number.\n");
		return 42;
	} else {
		dim = strtol(argv[1], NULL, 10);
	}

	matA = (int *) malloc(dim * dim * sizeof(int));
	matB = (int *) malloc(dim * dim * sizeof(int));
	matC = (int *) malloc(dim * dim * sizeof(int));

	srand(time(NULL));
	for (int i = 0; i < dim*dim; i++) {
		matA[i] = rand() % INT_MAX;
		matB[i] = rand() % INT_MAX;
		matC[i] = rand() % INT_MAX;
	}

	for (int i=0;i<dim;i++) {
		for(int j=0;j<dim;j++) {
			for(int k=0;k<dim;k++){
				matC[i * dim + j] += matA[i * dim + k] * matB[k* dim + j];
			}
		}
	}

	free(matA);
	free(matB);
	free(matC);
}
