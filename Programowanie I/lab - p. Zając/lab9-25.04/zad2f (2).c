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

int my_compare_zdalo (const void * a, const void * b)
{
    const struct wyniki_wojewodztwa *_a = (struct wyniki_wojewodztwa *)a;
    const struct wyniki_wojewodztwa *_b = (struct wyniki_wojewodztwa *)b;
    if(_a->zdalo < _b->zdalo) return -1;
    else if(_a->zdalo == _b->zdalo) return 0;
    else return 1;
}

int my_compare_nazwa_woj (const void * a, const void * b)
{
    const struct wyniki_wojewodztwa *_a = (struct wyniki_wojewodztwa *)a;
    const struct wyniki_wojewodztwa *_b = (struct wyniki_wojewodztwa *)b;
    if(_a->nazwa_woj < _b->nazwa_woj) return -1;
    else if(_a->nazwa_woj == _b->nazwa_woj) return 0;
    else return 1;
}

int my_compare_liczba_zdajacych (const void * a, const void * b)
{
    const struct wyniki_wojewodztwa *_a = (struct wyniki_wojewodztwa *)a;
    const struct wyniki_wojewodztwa *_b = (struct wyniki_wojewodztwa *)b;
    if(_a->liczba_zdajacych < _b->liczba_zdajacych) return -1;
    else if(_a->liczba_zdajacych == _b->liczba_zdajacych) return 0;
    else return 1;
}

int main(int argc, char **argv)
{
	char linia[SIZE];
	int i, procent;
	struct wyniki_wojewodztwa *tab;
	FILE *plik = fopen("matury.txt", "r");
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
		
		qsort(tab, LICZBA_WOJ, sizeof(struct wyniki_wojewodztwa), my_compare_zdalo);
		
		for( i = 0; i < LICZBA_WOJ; i++) printf("%s %d %d\n", tab[i].nazwa_woj, tab[i].liczba_zdajacych, tab[i].zdalo);
		qsort(tab, LICZBA_WOJ, sizeof(struct wyniki_wojewodztwa), my_compare_liczba_zdajacych);
		for( i = 0; i < LICZBA_WOJ; i++) printf("%s %d %d\n", tab[i].nazwa_woj, tab[i].liczba_zdajacych, tab[i].zdalo);
		qsort(tab, LICZBA_WOJ, sizeof(struct wyniki_wojewodztwa), my_compare_zdalo);
		for( i = 0; i < LICZBA_WOJ; i++) printf("%s %d %d\n", tab[i].nazwa_woj, tab[i].liczba_zdajacych, tab[i].zdalo);
	}
		
	free(tab);
	return 0;
}

