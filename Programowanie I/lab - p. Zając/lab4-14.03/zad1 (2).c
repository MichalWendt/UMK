#include <stdio.h>
#include <stdlib.h>

struct napis {
	char *str;
	unsigned int len;
};

 

int main(int argc, char **argv)
{
	struct napis *tab;
	FILE *plik;
	int rozmiar;
	int i;
	
	plik  = fopen("napisy.txt", "r");
	fscanf(plik, "%d", &rozmiar);
	tab = malloc(rozmiar * sizeof(struct napis));
	for(i = 0; i < rozmiar;  i++)
	{
		fscanf(plik, "%d", &tab[i].len);
		tab[i].str = malloc((tab[i].len+1) * sizeof(char));
		fscanf(plik, "%s", tab[i].str);
	}
	printf("Rozmiar %d\n", rozmiar);
	for(i = 0; i < rozmiar; i++)
	{
		free(tab[i].str);
	}

	free(tab);
	fclose(plik);
	return 0;
}

