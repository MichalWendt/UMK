#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct pacjent pacjent ;

struct pacjent
{
    char imie[50];
    char nazwisko[50];
    char PESEL[20];
    pacjent *nastepny;
};

pacjent *p=NULL;
pacjent *k=NULL;



void ad(pacjent dod)
{
    pacjent *tmp;
    if(p==0)
    {

        p=malloc(sizeof(pacjent));
        memmove(p->imie,dod.imie,50);
        memmove(p->nazwisko,dod.nazwisko,50);
        memmove(p->PESEL,dod.PESEL,20);
        k=p;
        k->nastepny=NULL;
    }
    else
    {
        tmp=malloc(sizeof(pacjent));
        memmove(tmp->imie,dod.imie,50);
        memmove(tmp->nazwisko,dod.nazwisko,50);
        memmove(tmp->PESEL,dod.PESEL,20);
        k->nastepny=tmp;
        k=tmp;
        k->nastepny=NULL;
    }
}
void wypisz()
{
    pacjent *t=p;
    int i=0;
    while(t!=NULL)
    {
        printf("Pacjent %d \nImie: %s \nNazwisko: %s\nPESEL: %s\n",i,t->imie,t->nazwisko,t->PESEL);
        t=t->nastepny;
        i++;
    }
}

void znajdz(u)
{
    pacjent *t=p;
    int i=0;
    while(t!=NULL)
    {
        if(i==u)
        printf("Pacjent %d \nImie: %s \nNazwisko: %s\nPESEL: %s\n",i,t->imie,t->nazwisko,t->PESEL);
        t=t->nastepny;
        i++;

    }
}

void usun(int u)
{
    pacjent *t=p;
    pacjent *z;
    int i=0;
    while(t!=NULL && i < u-1)
    {
        t=t->nastepny;
        i++;
    }
    if(u!=0)
    {
        z=t->nastepny;
        if(t->nastepny->nastepny==NULL)
            k=t;
        t->nastepny=t->nastepny->nastepny;
        free(z);
    }
    else if(u==0 && p!=NULL)
    {
        p=p->nastepny;
        free(t);
    }


}

int main()
{
    int chose;
    pacjent dod;
    int u;
    do
    {
        printf("\n0-Koniec, 1 - dodaj, 2 usun, 3 znajdz, 4 wypisz \n");
        scanf("%d",&chose);
        if(chose==1)
        {
            scanf("%50s %50s %20s",&dod.imie,&dod.nazwisko,&dod.PESEL);
            ad(dod);
        }
        if(chose==2)
        {
            scanf("%d",&u);
            usun(u);
        }
        if(chose==3)
        {
            scanf("%d",&u);
            znajdz(u);
        }
        if(chose==4)
        {
            printf("\n \n");
            wypisz();
        }

    }
    while(chose!=0);



    return 0;

}
