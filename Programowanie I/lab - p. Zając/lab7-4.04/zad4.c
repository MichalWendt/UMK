#include <stdio.h>
#include <stdlib.h>

typedef struct{
	double a;
	double b;
}LiczbaZespolona;

LiczbaZespolona dodawanie(LiczbaZespolona *liczba1, LiczbaZespolona *liczba2){
	LiczbaZespolona wynik;
	wynik.a = liczba1->a + liczba2->a;
	wynik.b = liczba1->b + liczba2->b;

	return wynik;
}


int main(int argc, char **argv)
{
	LiczbaZespolona *liczba1;
	LiczbaZespolona *liczba2;
	LiczbaZespolona wynik;
	
	liczba1 = malloc(sizeof(LiczbaZespolona));
	liczba2 = malloc(sizeof(LiczbaZespolona));

	printf("Podaj pierwsza liczbe");
	scanf("%lf %lf", &liczba1->a, &liczba1->b);
	printf("Podaj druga liczbe");
	scanf("%lf %lf", &liczba2->a, &liczba2->b);
	
	
	wynik = dodawanie(liczba1, liczba2);
	printf("Wynik dodawania liczb zespolonych %lf + %lf i", wynik.a, wynik.b);
	
	free(liczba1);
	free(liczba2);
	return 0;
}

