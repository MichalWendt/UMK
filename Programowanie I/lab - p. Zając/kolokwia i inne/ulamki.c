#include <stdio.h>
#include <stdlib.h>

struct ulamek{
	int licznik;
	int mianownik;
};

int nwd(int a, int b){
	int tmp;
	while(b != 0){
		tmp = b;
		b = a%b;
		a = tmp;
	}
	return a;
}

int nww(int a, int b){
	return a*b / nwd(a,b);
}

struct ulamek dodawanie (struct ulamek liczba1, struct ulamek liczba2){
	int tmp1, tmp2, NWW;
	struct ulamek suma;
	NWW = nww(liczba1.mianownik, liczba2.mianownik);
	
	tmp1 = NWW / liczba1.mianownik;
	tmp2 = NWW / liczba2.mianownik;
	
	suma.licznik = liczba1.licznik * tmp1 + liczba2.licznik * tmp2;
	suma.mianownik = NWW;
	
	return suma;
}

int main(int argc, char **argv)
{
	struct ulamek tab[9];
	int i, a=1, b=2;
	
	for(i = 0; i < 9; i++){
		tab[i].licznik = a;
		tab[i].mianownik = b;
		a++;
		b++;
	}
	
	/*for(i = 0; i < 9; i++){
		printf("%d /%d   ", tab[i].licznik, tab[i].mianownik);
	}*/
	for(i = 0; i < 8; i++){
		tab[i+1] = dodawanie(tab[i], tab[i+1]);
	}
	
	printf("wynik %d / %d", tab[8].licznik, tab[8].mianownik);
	return 0;
}

