#include<stdio.h>

int main()
{
    int l, b, t=0;
    scanf("%d", &l);
    printf("Szesnastkowy: %X , Ósemkowy: %o, Binarnie: ", l, l);
    b = sizeof(l)*8;
    while(b--)
    {
        if(l&(1<<b))
        {
            t=1;
        }
        if(t)
        {
            if(l & (1<<b))
            {
                printf("1");
            }
            else
            {
                printf("0");
            }
        }
    }
    /*
        wczytujemy liczbę całkowitą, i wypisujemy ją w postaci binarnej, ósemkowej i szesnastkowej
    */
    return 0;
}
