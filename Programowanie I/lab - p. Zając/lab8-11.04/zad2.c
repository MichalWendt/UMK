#include <stdio.h>
#include <stdlib.h>

void swap_int(int *a, int *b){
	int tmp;
	tmp = *a;
	*a = *b;
	*b = tmp;
	
}

int main(int argc, char **argv)
{
	int a, b, i, j;
	int *tab;
	sscanf(argv[1], "%d", &a);
	
	tab = malloc(sizeof(a));
	printf("Podaj liczby do tablicy:\n");
	for(i = 0; i < a; i ++){
		scanf("%d", &b);
		tab[i] = b;
	}
	
	for(i = 0; i <  a; i++){
		for(j = 0; j < a-1; j++){
			if(tab[j] > tab[j+1]){
				swap_int(&tab[j], &tab[j+1]);
			}
		}
	}
	
	printf("\n Posortowane \n");
	
	for(i = 0; i < a; i++){
		printf("%d ", tab[i]);

	}
	
	return 0;
}

