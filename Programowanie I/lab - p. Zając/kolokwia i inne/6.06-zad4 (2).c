#include <stdio.h>

struct ulamek{
	int licznik;
	int mianownik;
};

void dodaj(struct ulamek* liczba1, struct ulamek* liczba2, struct ulamek* wynik){
	wynik -> mianownik = liczba1 -> mianownik * liczba2 -> mianownik;
	wynik -> licznik = (liczba1 -> licznik * liczba2 -> mianownik) + (liczba2 -> licznik * liczba1 -> mianownik); 
}

void przemnoz(struct ulamek* liczba1, struct ulamek* liczba2, struct ulamek* wynik){
	wynik -> licznik = liczba1 -> licznik * liczba2 -> licznik;
	wynik -> mianownik = liczba1 -> mianownik * liczba2 -> mianownik;
}

int main(int argc, char **argv)
{
	struct ulamek liczba1;
	struct ulamek liczba2;
	struct ulamek wynik = { 0, 0};
	printf("Pierwszy ulamek");
	scanf("%d %d", &liczba1.licznik, &liczba1.mianownik);
	printf("Drugi ulamek");
	scanf("%d %d", &liczba2.licznik, &liczba2.mianownik);
	dodaj(&liczba1, &liczba2, &wynik);
	printf("wynik %d / %d \n",  wynik.licznik, wynik.mianownik);
	przemnoz(&liczba1, &liczba2, &wynik);
	printf("wynik %d / %d \n",  wynik.licznik, wynik.mianownik);
	return 0;
}

