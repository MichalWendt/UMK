#include <stdio.h>
#include <stdlib.h>

struct element{
		int wartosc;
		struct element *nastepny;
};

void list_print(struct element *lst){
		struct element *tmp = lst;
		
		while (tmp != NULL) {
				printf("%d\n", tmp -> wartosc);
				tmp = tmp -> nastepny;
		}
}	

struct element *list_insert_begining(int val, struct element *lst){
		struct element * a;
		a = malloc(sizeof(struct element));
		a -> wartosc = val;
		a -> nastepny = malloc(sizeof(struct element));
		a-> nastepny = lst;
		return a;
}

struct element *list_insert_end(int val, struct element *lst){
		struct element *pocz = lst;
		struct element *a;
		
		a = malloc(sizeof(struct element));
		a -> wartosc = val;
		a -> nastepny = malloc(sizeof(struct element));
		a -> nastepny = NULL;
		
		while(lst -> nastepny != NULL){
				lst = lst -> nastepny;
		}
		lst -> nastepny = a;
		
		return pocz;
}

int list_index_left(int val, struct element *lst){
		int indeks = -1;
		int pom = 0;
		while( lst -> nastepny != NULL)
		{
				pom = pom + 1;
				if(lst -> wartosc == val)
				{
					indeks = pom;
				}
			lst = lst -> nastepny;
		}
		return indeks;
}

int list_index_right(int val, struct element *lst){
	
}

int main(int argc, char **argv)
{
	struct element *lista;
	int wart = 0;
	int odp = 0;
	char jeszcze = 'T';
	int indeks = 0;
	lista = malloc( sizeof(struct element));
	lista -> wartosc = wart;
	lista -> nastepny = malloc(sizeof(struct element));
	lista -> nastepny = NULL;
	while(jeszcze == 'T')
	{
		printf("Czy chcesz dodac element na poczatek(1) czy koniec(2) listy?\n");
		scanf("%d", &odp);
		if(odp == 1) 
		{
			printf("Podaj wartosc\n");
			scanf("%d", &wart);
			lista = list_insert_begining(wart, lista);
		}
		else 
		{
			printf("Podaj wartosc");
			scanf("%d", &wart);
			lista = list_insert_end(wart, lista);	
		}
		printf("Jeszcze? T/N");
		scanf("%s", &jeszcze);
	};
	list_print(lista);
	printf("-------");
	
	printf("Szukac od poczatku(1) czy od konca(2)");
	scanf("%d", &odp);
	if(odp == 1)
	{
			printf("Podaj szukana wartosc\n");
			scanf("%d", &wart);
			indeks = list_index_left(wart, lista);
			printf("Indeks %d\n", indeks);
	}
	else
	{
		printf("Podaj szukana wartosc\n");
		scanf("%d", &wart);
	}
	
	list_print(lista);
	free(lista);
	return 0;
}

