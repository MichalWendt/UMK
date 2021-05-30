#include<stdio.h>
#include<stdlib.h>
#include<time.h>

typedef struct
{
    int x;
    int y;
} odcinek;

void swap(odcinek *od1, odcinek *od2)
{
    odcinek tmp= *od1;
    *od1 =* od2;
    *od2 = tmp;
}

odcinek * sort_pocz_ros(odcinek *odc, int n)
{
    int i,j;
    for(i = 0; i< n; ++i)
    {
        for(j = 0; j<n-1; ++j)
        {
            if(odc[j].x > odc[j+1].x)
                swap(&odc[j],&odc[j+1]);
        }
    }
    for(i = 0; i < n; ++i)
    {
        printf("%d %d\n",odc[i].x,odc[i].y);
    }
    return NULL;
}

odcinek * sort_dlug_mal(odcinek *odc, int n)
{
    int i,j;
    for(i = 0; i< n; ++i)
    {
        for(j = 0; j<n-1; ++j)
        {
            if((odc[j].y - odc[j].x) < (odc[j+1].y-odc[j+1].x))
                swap(&odc[j],&odc[j+1]);
        }
    }
    for(i = 0; i < n; ++i)
    {
        printf("%d %d\n",odc[i].x,odc[i].y);
    }
    return NULL;
}

odcinek * najdluzszy(odcinek * odc, int n)
{
    odcinek *tmp=odc;
    int i;
    for(i = 1; i < n; ++i)
    {
        if((tmp->y - tmp->x) < (odc[i].y-odc[i].x))
            swap(tmp,&odc[i]);
    }
    return tmp;
}
odcinek * najkrotszy(odcinek * odc, int n)
{
    odcinek *tmp=odc;
    int i;
    for(i = 1; i < n; ++i)
    {
        if((tmp->y - tmp->x) > (odc[i].y-odc[i].x))
            swap(tmp,&odc[i]);
    }
    return tmp;
}

int main()
{
    char a;
    srand(time(NULL));
    int n,i;
    FILE *plik;
    odcinek *odc;
    plik = fopen("odcinki.txt","r");
    fscanf(plik,"%d",&n);
    odc=malloc(n*sizeof(odcinek));
    for(i = 0; i < n; ++i)
    {
        fscanf(plik,"%d %d",&(odc[i].x),&(odc[i].y));
    }
    odcinek* (*wykonaj)(odcinek*,int);
    printf("a wypisanie na ekranie najkrótszego odcinka,\n");
    printf("b wypisanie na ekranie najd³u¿szego odcinka,\n");
    printf("c wypisanie na ekranie wszystkich odcinków, posortowanych rosnaco po pocz¹tku,\n");
    printf("d wypisanie na ekranie wszystkich odcinków, posortowanych malejaco po d³ugoœci.\n");
    scanf("%c",&a);
    if(a=='a')
    {
        wykonaj=najkrotszy;
        printf("%d %d\n",wykonaj(odc,n)->x,wykonaj(odc,n)->x);
    }
    else if(a=='b')
    {
        wykonaj=najdluzszy;
        printf("%d %d\n",wykonaj(odc,n)->x,wykonaj(odc,n)->x);
    }
    else if(a=='c')
    {
        wykonaj=sort_pocz_ros;
        wykonaj(odc,n);
    }
    else if(a=='d')
    {
        wykonaj=sort_dlug_mal;
        wykonaj(odc,n);
    }
    return 0;
}
