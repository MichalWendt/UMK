#include <stdio.h>
#include <stdlib.h>

int main()
{
    char *woj[100];
    int ilezdawalo = 0;
    char *procent[100];
    int ilezdawaloKraj = 0;
    float pom;
    int pom1;
    int ilezdaloKraj = 0;
    int najw = 0;
    FILE *plik;
    plik = fopen("matury.txt", "r");
    if(plik){
        while(!feof(plik)){
            fscanf(plik, "%s %d %s", woj, &ilezdawalo, procent);
            printf("%s %d %s\n", woj, ilezdawalo, procent);
            pom = strtol(procent, NULL, 10);
            pom = pom / 100;
            pom1 = ilezdawalo * pom;
            if(pom1 > najw) najw = pom1;
            ilezdawaloKraj += ilezdawalo;
            ilezdaloKraj += pom1;
        }
    }
   /*ile zdawalo i ile zdalo*/
   printf("W kraju mature zdawalo %d\n", ilezdawaloKraj);
   printf("W kraju mature zdalo %d\n", ilezdaloKraj);
    /*pow 15000 w woj*/
   rewind(plik);
   printf("Wojewodztwa w ktorych zdawalo ponad 15000 osob\n");
   if(plik){
        while(!feof(plik)){
            fscanf(plik, "%s %d %s", woj, &ilezdawalo, procent);
            if(ilezdawalo > 15000)
            {
                printf("%s\n", woj);
            }
        }
   }
   /*  33333 */
   rewind(plik);
   printf("Wojewodztwa w ktorych zdalo mniej niz 70%\n");
   if(plik){
    while(!feof(plik)){
        fscanf(plik, "%s %d %s", woj, &ilezdawalo, procent);
        pom = strtol(procent, NULL, 10);
        if(pom < 70){
            printf("%s\n", woj);
        }
        }
    }

    /* 444444 */
    rewind(plik);
    printf("Wojewodztwo w ktorym zdalo najwiecej osob ");
    if(plik){
        while(!feof(plik)){
            fscanf(plik, "%s %d %s", woj, &ilezdawalo, procent);
            pom = strtol(procent, NULL, 10);
            pom = pom / 100;
            pom1 = ilezdawalo * pom;
            if(pom1 == najw) {
                printf("%s", woj);
            }
        }
    }
    fclose(plik);
    return 0;
}
