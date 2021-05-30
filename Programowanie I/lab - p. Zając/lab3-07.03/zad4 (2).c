#include <stdio.h>
#include <stdlib.h>
#include <math.h>

struct ulamek {
int licznik;
int mianownik;
};

int NWD(int a, int b) {
    int pom;
    while(b != 0) {
        pom = b;
        b = a % b;
        a = pom;
    }
    return a;
}

int NWW(int a, int b, int nwd) {
    int nww = a * b / nwd;

    return nww;
}

struct ulamek dodawanieUlamkow(struct ulamek ulamek1, struct ulamek ulamek2) {
    struct ulamek suma;
    int mnoznik1, mnoznik2;

    int nww = NWW(ulamek1.mianownik, ulamek2.mianownik, NWD(ulamek1.mianownik, ulamek2.mianownik));

    mnoznik1 = nww / ulamek1.mianownik;
    mnoznik2 = nww / ulamek2.mianownik;

    suma.licznik = ulamek1.licznik * mnoznik1 + ulamek2.licznik * mnoznik2;
    suma.mianownik = nww;

    return suma;
}

int main()
{
    int i = 0;
    int licznik, mianownik, iloscUlamkow;
    printf("Podaj ilosc ulamkow do dodania: \n");

    scanf("%d", &iloscUlamkow);

    struct ulamek ulamki[iloscUlamkow];

    for(i = 0; i < iloscUlamkow; i++) {
        scanf("%d %d", &licznik, &mianownik);
        ulamki[i].licznik = licznik;
        ulamki[i].mianownik = mianownik;
    }

    for(i = 0; i < iloscUlamkow; i++) {
        printf("%d / %d\n", ulamki[i].licznik, ulamki[i].mianownik);
    }

    for(i = 0; i < iloscUlamkow-1; i++) {
        ulamki[i+1] = dodawanieUlamkow(ulamki[i], ulamki[i+1]);
    }

    printf("%d / %d", ulamki[iloscUlamkow-1].licznik, ulamki[iloscUlamkow-1].mianownik);

    return 0;
}
