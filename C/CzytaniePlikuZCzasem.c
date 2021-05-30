#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>


int main()
{
    int il_znak=0, il_wyr=0, il_lin=0;
    FILE *in;
    FILE *out;
    char a;
    time_t start;
    time_t koniec;
        time(&start);
    in = fopen("dane.txt","r");
    out = fopen("out.txt","w");
    while((a=getc(in)) != EOF){
        il_znak++;
        if(a==' ')
            il_wyr++;
        if(a=='\n')
            il_lin++;
        putc(a,out);

    }
    system("pause");
    time(&koniec);
    close(in);
    close(out);
    printf("ilosc znakow %d, wyrazow: %d, lini %d \n",il_znak,il_wyr,il_lin+1);
    printf("czas: %f", difftime(koniec,start));
    return 0;
}
