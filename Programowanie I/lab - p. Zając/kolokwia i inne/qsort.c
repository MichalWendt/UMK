#include <stdio.h>
#include <stdlib.h>

struct  wojewodztwo{
	short kod;
	char nazwa[32];
	unsigned int glosy_wazne;
};

int porownaj(const void *a, const void *b){
	return ((struct wojewodztwo *)a) -> glosy_wazne - ((struct wojewodztwo*)b)-> glosy_wazne;
}

int main(int argc, char **argv)
{
	FILE *plik;
	FILE *wyniki;
	struct wojewodztwo *tab;
	int rozmiar = 0, i;
	char litera;
	plik = fopen("wybory.txt", "r");
	wyniki = fopen("wyniki.txt", "w");
	
	while(!feof(plik)){
		litera  =  fgetc(plik);
		if(litera == '\n'){
			rozmiar++;
		}
	}
	
	tab = malloc(rozmiar*sizeof(struct wojewodztwo));
	rewind(plik);
	
	for(i = 0; i < rozmiar; i++){
		fscanf(plik, "%hd %s %u", &tab[i].kod, tab[i].nazwa, &tab[i].glosy_wazne);
	}
	
	
	
	qsort(tab, rozmiar, sizeof(struct wojewodztwo), porownaj);
	
	for(i = 0; i < rozmiar; i++){
		printf("%s, %u\n", tab[i].nazwa, tab[i].glosy_wazne);
	}
	
	for(i = 0; i < rozmiar; i++){
		fprintf(wyniki, "%s, %u\n", tab[i].nazwa, tab[i].glosy_wazne);
	}
	
	free(tab);
	fclose(plik);
	fclose(wyniki);
	return 0;
}

