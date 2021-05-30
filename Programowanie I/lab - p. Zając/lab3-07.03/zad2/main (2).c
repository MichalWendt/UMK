#include <stdio.h>
#include <stdlib.h>

void wypisz(FILE *plik){
    char linia[999];

    if(plik) {
        while(!feof(plik)){
            *linia = *fgets(linia, 999, plik);
            printf("%s", linia);
        }
    }
}

int znaki_w_pliku(FILE *plik){
    char znak;
    int licz = 0;

    rewind(plik);

    if(plik){
        while(!feof(plik))
        {
            licz++;
            znak = getc(plik);

        }
    }
    return licz;
}

int znaki_w_linii(FILE *plik){
    char linia[999];
    char znak;
    int licz = 0;
    int i = 0;
    int j = 1;

    rewind(plik);

    if(plik){
        while(!feof(plik)) {
            *linia = *fgets(linia, 999, plik);
            while(linia[i] != NULL)
            {
                licz ++;
                i ++;
            }
            printf("Liczba znakow w lini %d : %d\n", j, licz);
            i = 0;
            licz = 0;
            j ++ ;
        }
    }
}

void kapitaliki(FILE *plik, FILE *wynik) { /* Zadanie 2 podpunkt d */
    char znak;

    rewind(plik);

    if (plik) {
        while ((znak = getc(plik)) != EOF) { /* pobiera do znak znak */
            znak = toupper(znak);
            printf("%c", znak);
            fputc(znak, wynik);
        }
    }
}

int main()
{
    FILE *plik;
    plik = fopen("dane.txt","r");
    FILE * wynik;
    wynik = fopen("wynik.txt", "w");

    wypisz(plik);
    printf("\n");
    printf("Ilosc znakow w pliku %d", znaki_w_pliku(plik));
    znaki_w_linii(plik);
    kapitaliki(plik, wynik);

    fclose(plik);
    fclose(wynik);

    return 0;
}
