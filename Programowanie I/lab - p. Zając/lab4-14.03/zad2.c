#include <stdio.h>
#include <stdlib.h>

struct napis {
	char *str;
	unsigned int len;
};

int zadipom(struct napis element)
{
	int i;
	for(i = 0; i < element.len - 1; i++)
	{
		if(element.str[i] > element.str[i + 1])
			return 0;
		if(element.str[i] == element.str[i + 1])
			return 0;
	}
	return 1;	
}

void zadi(struct napis *tab, int rozmiar)
{
	int i;
	int pom;
	int suma = 0;
	for(i = 0; i < rozmiar; i++)
	{
		pom = zadipom(tab[i]);
		if(pom == 1)
		{
			suma = suma + 1;
			printf("%s, ", tab[i].str);
		}
	}
	printf("\n Suma napisow rosnacych: %d\n", suma);
}

int main(int argc, char **argv)
{
	struct napis *tab;
	FILE *plik;
	int rozmiar;
	int i;
	plik = fopen("napisy.txt", "r");
	if (plik == NULL)
	{
		perror("Blad odczytu pliku.\n");
		return -1;
	}
	
	fscanf(plik, "%d", &rozmiar);
	tab = malloc(rozmiar * sizeof(struct napis));
	for(i = 0; i < rozmiar; i++)
	{
		fscanf(plik, "%d", &tab[i].len);
		tab[i].str = malloc((tab[i].len + 1) * sizeof(char));
		fscanf(plik, " %s", tab[i].str);
	}
	
	printf("Rozmiar tablicy: %d\n", rozmiar);
	
	zadi(tab, rozmiar);
	
	for(i = 0; i < rozmiar; i++)
	{
		free(tab[i].str);
	}
	free(tab);
	fclose(plik); 
	return 0;
}
