#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct student student ;

struct student{
    char imie[50];
    char nazwisko[50];
    int punkty;
};


void swap2(student *a, student *b){
    student tmp = *a;
    *a = *b;
    *b = tmp;
}


void sort(student *st, int n){
    int i, j;
    for(i = 0; i < n; ++i){
        for(j = 0; j < n-1 ; ++j){
            if(st[j].punkty < st[j+1].punkty){
                swap2(&(st[j]),&(st[j+1]));

            }
        }
    }
}
int main()
{
    int n;
    int i;

    scanf("%d", &n);
    student *st;
    st = malloc(n * sizeof(student));
    for(i = 0; i < n; ++i){
        scanf("%50s %50s %d",&(st[i].imie),&(st[i].nazwisko),&(st[i].punkty));
    }
    printf("\n \n \n");
    sort(st,n);
        for(i = 0; i<n; i++){
            printf("%s \n%s \n%d \n",st[i].imie,st[i].nazwisko,st[i].punkty);

    }

    system("pause");
    return 0;
}
