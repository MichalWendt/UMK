#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct
{
    char imie[100];
    int rok_urodzenia;
    char rasa[100];
    char masc[100];
    char imie_ojca[100];
    char imie_matki[100];
    char imie_ojca_matki[100];
} kon;


int min(int a, int b)
{
    if(a<b)
    {
        return a;
    }
    else
    {
        return b;
    }
}

int compare_imie (const void * a, const void* b)
{
    kon *kon1 = (kon*)a;
    kon *kon2 = (kon*)b;
    return strcmp(kon1->imie, kon2->imie);
}

int compare_wiek (const void * a, const void* b)
{
    kon *kon1 = (kon*)a;
    kon *kon2 = (kon*)b;
    return (kon1->rok_urodzenia - kon2->rok_urodzenia);
}

int compare_rasa (const void * a, const void* b)
{
    kon *kon1 = (kon*)a;
    kon *kon2 = (kon*)b;
    return strcmp(kon1->rasa, kon2->rasa);
}

int compare_masc (const void * a, const void* b)
{
    kon *kon1 = (kon*)a;
    kon *kon2 = (kon*)b;
    return strcmp(kon1->masc, kon2->masc);
}

int main()
{
    kon ogiertmp;
    int j=5;
    int i=0;
    int z=0;
    int wybor;
    int zapisz;
    char nazwa[30];
    FILE *plik;
    FILE *zapis;
    kon *ogiery;
    ogiery = malloc(j * sizeof(kon));
    plik= fopen("ogiery.txt","r");
    while(!feof(plik))
    {
        fscanf(plik,"%[^,], %d, %[^,], %[^,], %[^,], %[^,], %[^,],\n", ogiertmp.imie, &(ogiertmp.rok_urodzenia), ogiertmp.rasa, ogiertmp.masc, ogiertmp.imie_ojca, ogiertmp.imie_matki, ogiertmp.imie_ojca_matki);
        ogiery[i]=ogiertmp;
        i++;
        if(i == j-1)
        {
            ogiery=realloc(ogiery,2*j*sizeof(kon));
            j=j*2;
        }
    }
    printf("\nProsze wybrac opcje:\n 1 - Nieposortowane \n 2 - Posortowane imieniem \n 3 - Posortowane wiekiem \n 4 - Posortowane rasa \n 5 - Posortowane wzgledem masci \n");
    scanf("%d",&wybor);
    if(wybor == 1)
    {
        printf("\n-------------- Nieposortowane --------------\n");
        for(z=0; z<i; z++)
        {
            printf("%s, %d, %s, %s, %s, %s, %s, \n", ogiery[z].imie, ogiery[z].rok_urodzenia, ogiery[z].rasa, ogiery[z].masc, ogiery[z].imie_ojca, ogiery[z].imie_matki,ogiery[z].imie_ojca_matki);
        }
        printf("Czy zapisac dane do pliku? (1/0) \n");
        scanf("%d",&zapisz);
        if (zapisz == 1)
        {
            printf("Do jakiego pliku? ");
            scanf("%30s",nazwa);
            zapis = fopen(nazwa,"w");
            for(z=0; z<i; z++)
            {
                fprintf(zapis,"%s, %d, %s, %s, %s, %s, %s, \n",ogiery[z].imie, ogiery[z].rok_urodzenia, ogiery[z].rasa, ogiery[z].masc, ogiery[z].imie_ojca, ogiery[z].imie_matki,ogiery[z].imie_ojca_matki);
            }
            fclose(zapis);
        }
    }
    if(wybor == 2)
    {
        qsort(ogiery,i,sizeof(kon),compare_imie);
        printf("\n-------------- Posortowane imieniem --------------\n");
        for(z=0; z<i; z++)
        {
            printf("%s, %d, %s, %s, %s, %s, %s, \n", ogiery[z].imie, ogiery[z].rok_urodzenia, ogiery[z].rasa, ogiery[z].masc, ogiery[z].imie_ojca, ogiery[z].imie_matki,ogiery[z].imie_ojca_matki);
        }
        printf("Czy zapisac dane do pliku? (1/0) \n");
        scanf("%d",&zapisz);
        if (zapisz == 1)
        {
            printf("Do jakiego pliku? ");
            scanf("%30s",nazwa);
            zapis = fopen(nazwa,"w");
            for(z=0; z<i; z++)
            {
                fprintf(zapis,"%s, %d, %s, %s, %s, %s, %s, \n",ogiery[z].imie, ogiery[z].rok_urodzenia, ogiery[z].rasa, ogiery[z].masc, ogiery[z].imie_ojca, ogiery[z].imie_matki,ogiery[z].imie_ojca_matki);
            }
            fclose(zapis);
        }
    }
    if(wybor == 3)
    {
        qsort(ogiery,i,sizeof(kon),compare_wiek);
        printf("\n-------------- Posortowane wiekiem --------------\n");
        for(z=0; z<i; z++)
        {
            printf("%s, %d, %s, %s, %s, %s, %s, \n", ogiery[z].imie, ogiery[z].rok_urodzenia, ogiery[z].rasa, ogiery[z].masc, ogiery[z].imie_ojca, ogiery[z].imie_matki,ogiery[z].imie_ojca_matki);
        }
        printf("Czy zapisac dane do pliku? (1/0) \n");
        scanf("%d",&zapisz);
        if (zapisz == 1)
        {
            printf("Do jakiego pliku? ");
            scanf("%30s",nazwa);
            zapis = fopen(nazwa,"w");
            for(z=0; z<i; z++)
            {
                fprintf(zapis,"%s, %d, %s, %s, %s, %s, %s, \n",ogiery[z].imie, ogiery[z].rok_urodzenia, ogiery[z].rasa, ogiery[z].masc, ogiery[z].imie_ojca, ogiery[z].imie_matki,ogiery[z].imie_ojca_matki);
            }
            fclose(zapis);
        }
    }
    if(wybor == 4)
    {
        qsort(ogiery,i,sizeof(kon),compare_rasa);
        printf("\n-------------- Posortowane rasa --------------\n");
        for(z=0; z<i; z++)
        {
            printf("%s, %d, %s, %s, %s, %s, %s, \n", ogiery[z].imie, ogiery[z].rok_urodzenia, ogiery[z].rasa, ogiery[z].masc, ogiery[z].imie_ojca, ogiery[z].imie_matki,ogiery[z].imie_ojca_matki);
        }
        printf("Czy zapisac dane do pliku? (1/0) \n");
        scanf("%d",&zapisz);
        if (zapisz == 1)
        {
            printf("Do jakiego pliku? ");
            scanf("%30s",nazwa);
            zapis = fopen(nazwa,"w");
            for(z=0; z<i; z++)
            {
                fprintf(zapis,"%s, %d, %s, %s, %s, %s, %s, \n",ogiery[z].imie, ogiery[z].rok_urodzenia, ogiery[z].rasa, ogiery[z].masc, ogiery[z].imie_ojca, ogiery[z].imie_matki,ogiery[z].imie_ojca_matki);
            }
            fclose(zapis);
        }
    }
    if(wybor == 5)
    {
        qsort(ogiery,i,sizeof(kon),compare_masc);
        printf("\n-------------- Posortowane wzgledem masci --------------\n");
        for(z=0; z<i; z++)
        {
            printf("%s, %d, %s, %s, %s, %s, %s, \n", ogiery[z].imie, ogiery[z].rok_urodzenia, ogiery[z].rasa, ogiery[z].masc, ogiery[z].imie_ojca, ogiery[z].imie_matki,ogiery[z].imie_ojca_matki);
        }
        printf("Czy zapisac dane do pliku? (1/0) \n");
        scanf("%d",&zapisz);
        if (zapisz == 1)
        {
            printf("Do jakiego pliku? ");
            scanf("%30s",nazwa);
            zapis = fopen(nazwa,"w");
            for(z=0; z<i; z++)
            {
                fprintf(zapis,"%s, %d, %s, %s, %s, %s, %s, \n",ogiery[z].imie, ogiery[z].rok_urodzenia, ogiery[z].rasa, ogiery[z].masc, ogiery[z].imie_ojca, ogiery[z].imie_matki,ogiery[z].imie_ojca_matki);
            }
            fclose(zapis);
        }
    }
    free(ogiery);
    fclose(plik);
    return 0;
}
