#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
	int n, i, j, licznikP, licznikNP;
	int **matrixA;
	int **matrixB;
	int **matrixC;
	
	sscanf(argv[1], "%d", &n); 
	licznikP = 0;
	licznikNP = 1;
	
	matrixA = malloc(sizeof(int*) * n); /* alokuje pierwszy "wiersz" */
	matrixB = malloc(sizeof(int*) * n);
	matrixC = malloc(sizeof(int*) * n);
	
	for(i = 0; i < n; i++) {
		*(matrixA + i) = malloc(sizeof(int) * n); /* alokuje "kolumny" */
		*(matrixB + i) = malloc(sizeof(int) * n);
		*(matrixC + i) = malloc(sizeof(int) * n);
	}
	
	for(i = 0; i < n; i++) { /* zapelniam macierze A i B wartosciami */
		for( j = 0; j < n; j++) {
			*(*(matrixA + i) + j) = licznikP;
			licznikP += 2;
			
			*(*(matrixB + i) + j) = licznikNP;
			licznikNP += 2;
		}
	}
	
	printf("\nMacierz A \n");
	
	for(i = 0; i < n; i++) { /* wyswietlam macierz A */
		for( j = 0; j < n; j++) {
			printf("%d ", *(*(matrixA + i) + j));
		}
		printf("\n");
	}
	
	printf("\nMacierz B \n"); /* wyswietlam macierz B */

	for(i = 0; i < n; i++) {
		for( j = 0; j < n; j++) {
			printf("%d ", *(*(matrixB + i) + j));
		}
		printf("\n");
	}
	
	for(i = 0; i < n; i++) { /* zapelniam macierz C wartosciami z macierzy A i B */
		for( j = 0; j < n; j++) {
			*(*(matrixC + i) + j) = *(*(matrixA + i) + j) + *(*(matrixB + i) + j);
		}
	}
	
	printf("\nMacierz C (dodane macierze A + B) \n");
	
	for(i = 0; i < n; i++) { /* wyswietlam macierz C */
		for( j = 0; j < n; j++) {
			printf("%d ", *(*(matrixC + i) + j));
		}
		printf("\n");
	}
	
	for(i = 0; i < n; i++) { /* zwalniam pamiec */
		free(*(matrixA + i));
		free(*(matrixB + i));
		free(*(matrixC + i));
	}
	
	free(matrixA);
	free(matrixB);
	free(matrixC);
	
	return 0;
}

