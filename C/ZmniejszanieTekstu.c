#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

int main()
{
    FILE *plik1;
    FILE *plik2;
    char znak, poprzedni = '.';
    plik1 = fopen("in.txt","r");
    plik2 = fopen("out.txt","w");
    while(!feof(plik1))
    {
            znak=getc(plik1);
            if(poprzedni==' ' && znak == ' ')
            {
                poprzedni=znak;
            }
            else if(poprzedni=='.')
            {
                if(znak == ' ')
                {
                    poprzedni = znak;
                }
                else
                {
                    znak = toupper(znak);
                    poprzedni = znak;
                    fprintf(plik2,"%c",znak);
                }
            }
            else
            {
                znak = tolower(znak);
                poprzedni = znak;
                fprintf(plik2,"%c",znak);
            }
    }
    fclose(plik1);
    fclose(plik2);
    return 0;
}
