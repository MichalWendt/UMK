#include <stdio.h>
#include <stdlib.h>
#include <time.h>
int main()
{
    int liczba;
    int a;
    srand(time(NULL));
    liczba=rand()%15+1;
    printf("Podaj liczbe \n");
    scanf("%d" , &a);
    while(liczba != a)
    {
        if(liczba > a) printf("za malo \n");
        else printf("za duzo \n");
        scanf("%d" , &a);
    }
    printf("szukana %d" , liczba);
    return 0;
}
