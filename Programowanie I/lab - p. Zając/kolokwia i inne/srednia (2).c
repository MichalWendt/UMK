#include <stdio.h>
#define AVG(X, Y, Z) (((X) + (Y) + (Z)) / 3)

enum precyzja {INT, DOUBLE};
enum precyzja decyzja;

int main(int argc, char **argv)
{
	int sredniaINT = 0;
	double sredniaD = 0;
	double a, b, c;
	int tab[3];
	
	FILE *liczby;
	liczby = fopen("liczby.txt", "r");
	
	printf("Jaka precyzja?");
	scanf("%d", &decyzja);
	

		while(!feof(liczby)){
				fscanf(liczby, "%d %d %d", &tab[0], &tab[1], &tab[2]);
				
				switch(decyzja){
					case INT:
						sredniaINT = (AVG(tab[0], tab[1], tab[2]));
						printf("%d\n", sredniaINT);
						break;
					
					case DOUBLE:
						a = tab[0];
						b = tab[1];
						c = tab[2];
						sredniaD = (AVG(a, b, c));
						printf("%.5f\n", sredniaD);
					break;
				}
				printf("\n");
		}
	
	
	fclose(liczby);
	return 0;
}

