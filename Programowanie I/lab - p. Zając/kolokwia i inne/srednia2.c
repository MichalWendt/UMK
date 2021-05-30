#include <stdio.h>

#define AVG(X, Y, Z) (((X) + (Y) + (Z)) / 3);

enum precyzja {INT, DOUBLE};
enum precyzja decyzja;

int main(int argc, char **argv)
{
	int sredniaI = 0;
	double sredniaD = 0;
	int tabi[3];
	double tabd[3];
	int i = 0;
	
	FILE* plik;
	plik = fopen("liczby.txt", "r");
	
	printf("Jaka precyzja? (0: int; 1: double)\n");
	scanf("%d", &decyzja);
	
	while(!feof(plik))
	{
		if(fgetc(plik) == '\n'){
		i++;
		}
	}
	
	rewind(plik);
	
	while(i != 0)
	{
		if(decyzja == 0)
		{
			fscanf(plik, "%d %d %d", &tabi[0], &tabi[1], &tabi[2]);
			sredniaI = AVG(tabi[0], tabi[1], tabi[2]);
			printf("Srednia: %d\n", sredniaI);
			i--;
		}
		else
		{
			fscanf(plik, "%lf %lf %lf", &tabd[0], &tabd[1], &tabd[2]);
			sredniaD = AVG(tabd[0], tabd[1], tabd[2]);
			printf("Srednia: %.2f\n", sredniaD);
			i--;
		}
	}
	fclose(plik);
	return 0;
}

