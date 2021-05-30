#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE 255
#define LICZBA_WOJ 16

struct wyniki_wojewodztwa {
	char nazwa_woj[50];
	int liczba_zdajacych;
	int zdalo;
};

int main(int argc, char **argv)
{
	char linia[SIZE];
	int i, procent;
	struct wyniki_wojewodztwa *tab;
	FILE *plik = fopen("matury.txt", "r");
	FILE *zapis = fopen("wynik.txt", "w");
	tab = malloc(sizeof(struct wyniki_wojewodztwa)*LICZBA_WOJ);
	if(plik){
		i = 0;
		while(fgets(linia, SIZE, plik) != NULL){
			sscanf(linia, "%s %d %d", tab[i].nazwa_woj, &tab[i].liczba_zdajacych, &procent);
			/* printf("%s %d %d\n", tab[i].nazwa_woj, tab[i].liczba_zdajacych, tab[i].zdalo); */
			tab[i].zdalo = tab[i].liczba_zdajacych * procent / 100;
			i++;
		}
		
		fclose(plik);
		if(zapis){
			for(i = 0; i < LICZBA_WOJ; i++)
				fprintf(zapis, "%s %d %d\n", tab[i].nazwa_woj, tab[i].liczba_zdajacych, tab[i].zdalo);
			
		}
	
	}
		
	free(tab);
	return 0;
}

