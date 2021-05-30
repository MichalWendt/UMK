#include <stdio.h>
#include <stdlib.h>

struct transakcja{
	char data[11];
	char NIP_klienta[14];
	unsigned int ilosc_cukru;
};

int my_compare(const void *a, const void *b){
	return((struct transakcja*)a) -> ilosc_cukru - ((struct transakcja*)b) -> ilosc_cukru;
}

int main(int argc, char **argv)
{
	FILE *plik; 
	int wiersze = 0;
	char c;
	int i;
	struct transakcja *tablica;
	
	plik = fopen("cukier.txt", "r");
	
	/*ilosc wierszy w pliku*/
	while(!feof(plik)){
		c = fgetc(plik);
		if(c == '\n'){
			wiersze++;
		}
	}
	printf("%d\n", wiersze);
	rewind(plik);
	tablica = malloc(wiersze * sizeof(struct transakcja));
	
	/*zapisywanie z pliku do struktury */
	for(i = 0; i < wiersze; i++){
		 fscanf(plik, "%s %s %u", tablica[i].data, tablica[i].NIP_klienta, &tablica[i].ilosc_cukru);
	}
	
	/*sortowanie po ilosci cukru p1*/
	qsort(tablica, wiersze, sizeof(struct transakcja), my_compare);

	for(i = (wiersze - 1); i > (wiersze - 4); i--){
		printf("%s %u\n", tablica[i].NIP_klienta, tablica[i].ilosc_cukru);
	}
	
	fclose(plik);
	free(tablica);
	return 0;
}

