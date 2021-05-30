#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
	int i, j, n, *tab, sprawdzana;
	
	sscanf(argv[1], "%d", &n);
	tab = malloc(n*sizeof(int));
	
	for(i = 2; i < n; i++){
		tab[i] = i;
	}
	
	/*for(i = 2; i < n; i++){
		printf(" %d ", tab[i]);	
	}*/
	
	for(i = 2; i < n; i++){
		if(tab[i] != 0){
			sprawdzana = i;
			for(j = sprawdzana + 1; j < n; j++){
				if(j%sprawdzana == 0){
					tab[j] = 0;
				}
			}
		}
	}
	for(i = 2; i < n; i++){
		printf(" %d ", tab[i]);	
	}
	free(tab);
	
	return 0;
}

