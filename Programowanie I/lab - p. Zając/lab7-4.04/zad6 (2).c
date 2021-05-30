#include <stdio.h>
#include <stdlib.h>

#define AVG(X, Y, Z) (((X) + (Y) + (Z)) / 3)
enum precyzja {INT, DOUBLE};
enum precyzja decyzja;


int main() {

    int sumaINT = 0;
    double sumaDouble = 0;
    double a, b, c;
    int tablica[3];

    FILE * liczby = fopen("liczby.txt", "r");

    printf("Z jaka precyzja chcialby Pan / Pani zobaczyc swoja srednia: INT (0) lub DOUBLE(1): \n");
    scanf("%d", &decyzja);
    printf("\n%d", decyzja);


    if(liczby) {
        while(!feof(liczby)) {

            fscanf(liczby, "%d %d %d", &tablica[0], &tablica[1], &tablica[2]);

            printf("%d %d %d\n", tablica[0], tablica[1], tablica[2]);


            switch(decyzja) {
                case INT:
                    sumaINT = AVG(tablica[0], tablica[1], tablica[2]);
                    printf("Srednia int: %d\n", sumaINT);

                    break;
                case DOUBLE:
                    a = tablica[0];
                    b = tablica[1];
                    c = tablica[2];
                    sumaDouble = AVG(a, b, c);
                    printf("Srednia double: %.5f\n", sumaDouble);
                    break;
            }
            }
        }
    printf("\n");
    fclose(liczby);
    return 0;
}
