/*szyfrowanie catem - Michal Wendt*/
#include <sys/ptrace.h>
#include <sys/types.h>
#include <sys/reg.h>
#include <sys/wait.h>
#include <sys/user.h>
#include <sys/syscall.h>
#include <syscall.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <errno.h>

const int long_size = sizeof(long);     /*Pobieramy rozmiar long w systemie*/

void pobieranie(pid_t proces, long wielBufora, long adres, char *bufor)
{
    long i, wartosc;
    for(i = 0; i < wielBufora; i += long_size)
    {
        wartosc = ptrace(PTRACE_PEEKDATA, proces, adres + i, NULL);   /*Pobieramy kolejne znaki*/
        memcpy(bufor + i, (char *)&wartosc, long_size);    /*Zapisyjemy do napisu pobrane dane, rzutujac na chara*/
    }
    if(wielBufora % long_size != 0) /*Pobieramy pozostale znaki (jezeli jakies zostaly)*/
    {
        wartosc = ptrace(PTRACE_PEEKDATA, proces, adres + i, NULL); /*Pobieramy kolejne znaki*/
        memcmp(bufor + i * 4, (char *)&wartosc, wielBufora % long_size);    /*Zapisyjemy do napisu pobrane dane, rzutujac na chara*/
    }
    bufor[wielBufora] ='\0';    /*Konczymy tablice znakiem konca*/
}

void wstawianie(pid_t proces, long wielBufora, long adres, char *bufor)  /*Funkcja podmieniajce dane*/
{
    long i, wartosc;
    for(i = 0; i < wielBufora; i += long_size)   /*Wpsujemy w pamiec dane*/
    {
        memcpy((char *)&wartosc, bufor + i , long_size);     /*Rzutujemy znaki na liczby*/
        ptrace(PTRACE_POKEDATA, proces, adres + i, wartosc);    /*Wysylamy dane*/
    }
    if(wielBufora % long_size != 0) /*Pobieramy pozostale znaki (jezeli jakies zostaly)*/
    {
        memcmp((char *)&wartosc, bufor + i, long_size); /*Rzutujemy znaki na liczby*/
        ptrace(PTRACE_POKEDATA, proces, adres + i * 4, wartosc);    /*Wysylamy dane*/
    }
}

void szyfrowanie(char *bufor, int klucz)
{
    int i;          /*iterator*/
    char pom;       /*pomocnicza zmienna*/
    for(i = 0; i < strlen(bufor)-1 ; ++i)   /*funkcja szyfrujaca bufor*/
    {
        pom = bufor[i];
        bufor[i] = bufor[i+1];
        bufor[i+1] = pom;
        bufor[i] = (bufor[i]+klucz);
    }
}

void deszyfrowanie(char *bufor, int klucz)
{
    int i;          /*iterator*/
    char pom;       /*pomocnicza zmienna*/
    for(i = strlen(bufor)-1; i > 0 ; --i)   /*funkcja deszyfrujaca bufor*/
    {
        pom = bufor[i];
        bufor[i] = bufor[i-1];
        bufor[i-1] = pom;
        bufor[i] = (bufor[i]-klucz);
    }
}

int main(int argc, char **argv)
{
    pid_t proces;   /*deklarujemy zmienna do procesu dziecka*/
    char *bufor;    /*tablica na dane*/
    int status;     /*status procesu*/
    long adres;     /*adres procesu*/
    long wielBufora;   /*wielkosc tablicy*/
    int wywol = 1;   /*pomocnicza zmienna do sprawdzania parzsystosci wywolan*/
    int klucz = atoi(argv[4]);
    FILE *plik;
    char polecenie[15];
    char *nazwa = argv[2];
    strcpy (polecenie, "/bin/");
    strcat (polecenie, argv[1]);
    if(argc != 5)   /*komunikujemy sie z uzytkowanikiem*/
    {
        printf("Sposob uzycia: polecenie nazwa_pliku/flagi [opcja] [klucz szyfrowania(liczba)]\n");
        printf("Opcje do wyboru:\n");
        printf("1 - szyfrowanie pliku \n");
        printf("2 - deszyfrowanie pliku \n");
        return(-1);
    }
    proces = fork();    /*forkujemy proces*/
    if(proces == 0)     /*polecenia dla potomka*/
    {
        ptrace(PTRACE_TRACEME, NULL, NULL, NULL);
        execl(polecenie,argv[1],argv[2],NULL);    /*wydajemy polecenia cat dla potomka*/
    }
    else if(proces == -1)   /*obslugujemy kod bledu*/
    {
        perror("Wystapil blad ");
    }
    else        /*przechwytujemy sygnaly wyslane przez proces potomka*/
    {
        while(1)
        {
            wait(&status);  /*Kontrolujemy stan procesu (czy wysyla sygnaly)*/
            if(WIFEXITED(status))
            {
                 break;     /*Jezeli nie, konczymy*/
            }
            if(ptrace(PTRACE_PEEKUSER, proces, long_size * ORIG_RAX, NULL) == SYS_write)    /*Jezeli potomek wysyla sygnaly pisania podmieniamy dane*/
            {
                if(wywol)   /*sprawdzenie nieparzystosci wywolania*/
                {
                    adres = ptrace(PTRACE_PEEKUSER, proces, long_size * RSI,NULL);  /*Pobieramy adres oraz wielkosc danych od potomka*/
                    wielBufora = ptrace(PTRACE_PEEKUSER, proces, long_size * RDX, NULL);
                    bufor = malloc(sizeof(char)*(wielBufora + 1 ));    /*Alokujemy pamiec dla tablicy do ktorej pobierzemy dane*/
                    pobieranie(proces,wielBufora,adres,bufor);     /*Pobieramy dane z procesu*/
                    if(atoi(argv[3]) == 1)      /*Szyfrowanie pliku*/
                    {
                        szyfrowanie(bufor,klucz);
                        plik = fopen(nazwa, "w");
                        fprintf (plik, "%s", bufor);
                    }
                    if(atoi(argv[3]) == 2)      /*Deszyfrowanie pliku*/
                    {
                        deszyfrowanie(bufor,klucz);
                        plik = fopen(nazwa, "w");
                        fprintf (plik, "%s", bufor);
                    }
                    else
                    {

                    }
                    wstawianie(proces,wielBufora,adres,bufor);     /*Wstawiamy nowe dane do procesu*/
                    wywol = 0;
                }
                else
                {
                    wywol = 1;
                }
            }
            ptrace(PTRACE_SYSCALL, proces, NULL, NULL);     /*Sygnal do potomka by wykonal operacje*/
        }
    }
    free(bufor);
    fclose(plik);
    return 0;       /*Konczymy zwracajac 0*/
}
