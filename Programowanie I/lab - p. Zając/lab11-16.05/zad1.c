#include <stdio.h>
#include <stdlib.h>

struct wojewodztwo{
	short kod;
	char nazwa[32];
	unsigned int glosy_wazne;
};	

int my_compare (const void * a, const void * b)
{
    return ((struct wojewodztwo*)a) -> glosy_wazne - ((struct wojewodztwo*)b) -> glosy_wazne;
}

int main(int argc, char **argv)
{
	FILE *plik;
	FILE *wyniki;
	struct wojewodztwo tab[16];
	int i;

	
	plik = fopen("wybory.bin", "rb");
	
	if(!plik){
		printf("Blad odczytu");
		return -1;
	}
	
	fread(tab, sizeof(struct wojewodztwo), 16, plik);
	fclose(plik);
	
	qsort(tab, 16, sizeof(struct wojewodztwo), my_compare);
	
	for(i = 0; i < 16; i++){
		printf("%s \t %d\n", tab[i].nazwa, tab[i].glosy_wazne);
	}
	
	wyniki=fopen("wynik.txt", "awt");
	
	for(i = 0; i < 16; i++){
		fprintf(plik, "%s %d\n", tab[i].nazwa, tab[i].glosy_wazne);
	}
	
	fclose(wyniki);
	return 0;
}

