#include <stdio.h>
#include <stdlib.h>

#define SIZE 255
#define LICZBA_WOJ 16

int ile_zdawalo_kraj = 0;

struct wyniki_wojewodztwa{
	char nazwa_woj[SIZE];
	int ile_zdawalo_woj;
	int procent;

};

void czytanie(FILE *matury, char *linia, struct wyniki_wojewodztwa *tab){
	int i = 0;
	tab = malloc(LICZBA_WOJ * sizeof(struct wyniki_wojewodztwa));
	if(matury){
		while(fgets(linia , SIZE, matury)!= NULL){
			sscanf(linia, "%s %d %d", tab[i].nazwa_woj, &tab[i].ile_zdawalo_woj, &tab[i].procent);
			printf("%s %d %d \n", tab[i].nazwa_woj, tab[i].ile_zdawalo_woj, tab[i].procent);
			ile_zdawalo_kraj += tab[i].ile_zdawalo_woj;
			i++;
			
		}
	}
}

int zamiana_z_proc(int a, int b){
	
}

int main(int argc, char **argv)
{
	char *linia;
	FILE *matury;
	struct wyniki_wojewodztwa *tab;
	/*int i;*/
	int ile_zdalo_kraj = 0;
	
	matury = fopen("matury.txt", "r");
	linia = malloc(SIZE * sizeof(char));
	tab = malloc(LICZBA_WOJ * sizeof(struct wyniki_wojewodztwa));
	
	/*if(matury){
		while(fgets(linia , SIZE, matury)!= NULL){
			sscanf(linia, "%s %d %d", tab[i].nazwa_woj, &tab[i].ile_zdawalo_woj, &tab[i].procent);
			printf("%s %d %d \n", tab[i].nazwa_woj, tab[i].ile_zdawalo_woj, tab[i].procent);
			i++;
		}
	}	*/
	czytanie(matury, linia, tab);
	fclose(matury);
	
	matury = fopen("wynik.txt", "r");
	fprintf(matury, "Liczba osob zdajacych mature %d", ile_zdawalo_kraj);
	/*for(i = 0; i < LICZBA_WOJ; i++){
		
	}*/
	fclose(matury);
	return 0;
}
