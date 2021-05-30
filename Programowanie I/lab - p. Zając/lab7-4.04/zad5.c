#include <stdio.h>

typedef union {
	int calkowita;
	double rzeczywista;
}Liczba;

int main(int argc, char **argv)
{
	char odp;
	Liczba a;
	
	printf("Chcesz pracowac na liczbach calkowitych(c) czy rzeczywistych(r)?");
	scanf("%c", &odp);
	printf("Podaj liczbe");
	if(odp == 'c'){
		scanf("%d", &a.calkowita);
		printf("\n %d", a.calkowita * a.calkowita);
	}
	else{
		scanf("%lf", &a.rzeczywista);
		printf("\n %lf", a.rzeczywista * a.rzeczywista);
	}

	return 0;
}

