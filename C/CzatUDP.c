/* Czat UDP - Michal Wendt */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <netinet/in.h>
#include <netdb.h>
#include <signal.h>
#include <arpa/inet.h>

struct wiadomosc    /* Struktura do przechowywania informacji o wiadomosciach */
{
    char nazwa[20];
	char tresc[300];
};

int main(int argc, char **argv)
{
    int PID;            /* Zmienna okreslajaca id procesu */
	int gniazdo;        /* Zmienna gniazda */
    socklen_t dlugosc;      /* Zmienna przechowujaca dlugosc adresu */
	struct wiadomosc wychodzace, przychodzace;              /* Zmienne strukturalne przechowywujace informacje o wiadomosciach rozmowcow */
	struct sockaddr_in moj_adres, rozmowca_adres, *ip_docelowy; /* Zmienne strukturalne przechowujace adresy: nasz i rozmowcy */
	struct addrinfo *informacje;                            /* Zmienna stukturalna do przechowywania informacji o adresie hosta z getaddrinfo */

	if(argc < 2 || argc > 3)
    {
        printf("ERROR: Nieprawidlowa ilosc argumentow\n");      /* Obslugujemy blad niepoprawnej liczby argumentow */
		printf("Nalezy podac: %s adres_maszyny_zdalnej [nick]\n", argv[0]);
		return -1;
	}
	else if(argc == 2)
    {
		strcpy(wychodzace.nazwa,"NN");     /* Pobieramy nasza nazwe (domyslnie "NN") */
	}
    else
    {
        if(strlen(argv[2]) > 19)        /* Sprawdzamy czy nasza nazwa nie jest zbyt dluga */
        {
            printf("ERROR: Prosze wybrac krotsza nazwe uzytkownika [do 20 znakow]\n");     /*Obslugujemy blad dlugosci nazwy rozmowcy(naszej) */
            return -1;
        }
        if(strlen(argv[2]) < 2)         /* Sprawdzamy czy nasza nazwa nie jest zbyt krotka */
        {
            printf("ERROR: Prosze wybrac dluzsza nazwe uzytkownika [wiecej niz 1 znak]\n");     /*Obslugujemy blad dlugosci nazwy rozmowcy(naszej) */
            return -1;
        }
        strcpy(wychodzace.nazwa, argv[2]);  /* Zapisujemy nasza nazwe */
    }
    gniazdo = socket(AF_INET, SOCK_DGRAM, 0);    /* Tworzymy gniazdo UDP */
	if(gniazdo < 0)
    {
		printf("ERROR: Nie udalo sie utworzyc gniazda!\n");     /*Obslugujemy blad utworzenia gniazda */
		return -1;
	}
	if(getaddrinfo(argv[1], "5272", NULL, &informacje) != 0)    /* Pobieramy informacje o adresie podanego hosta */
    {
		printf("ERROR: Nie mozna uzyskac informacji o maszynie z takim adresem!\n");        /*Obslugujemy blad adresu rozmowcy(hosta) */
		return -1;
	}
	else
    {
        ip_docelowy = (struct sockaddr_in *)(informacje->ai_addr); /* Zapamietujemy IP naszego rozmowcy */
        /* Wypelniamy strukture z informacjami o naszej maszynie */
        moj_adres.sin_family	    = AF_INET;              /* IPv4 */
        moj_adres.sin_port          = htons(5272);          /* port serwera */
        moj_adres.sin_addr.s_addr   = htonl(INADDR_ANY);    /* Nasz dowolny interfejs */

        /* Wypelniamy strukture z informacjami o maszynie rozmowcy */
        rozmowca_adres.sin_family	= AF_INET;                  /* IPv4 */
        rozmowca_adres.sin_port     = htons(5272);              /* port hosta */
        rozmowca_adres.sin_addr 	= ip_docelowy->sin_addr;    /* IP docelowego hosta */

        dlugosc = sizeof(rozmowca_adres);   /* Zapamietujemy dlugosc adresu rozmowcy */
    }

	if(bind(gniazdo, (struct sockaddr *)&moj_adres, sizeof(moj_adres)) < 0)     /* Rejestrujemy nasze gniazdo w systemie */
    {
		printf("ERROR: Bindowanie gniazda nie powiodlo sie!\nMaszyna jest zajeta\n");        /* Obslugujemy blad przypisania gniazda do rozmowcy */
		close(gniazdo);
		return -1;
	}
	printf("Rozpoczynam czat z %s. Napisz <koniec> by zakonczyc czat.\n", inet_ntoa(ip_docelowy->sin_addr));    /* Wypisujemy informacje o rozpoczeciu czatu */
	strcpy(wychodzace.tresc, "<poczatek>");     /* Wysylamy wiadomosc poczatkowa o naszym dolaczeniu do czatu */
	if(sendto(gniazdo, &wychodzace, sizeof(wychodzace), 0,(struct sockaddr *)&rozmowca_adres, sizeof(rozmowca_adres)) < 0)
    {
		printf("ERROR: Nie udalo sie wyslac wiadmosci o dolaczeniu do czatu!\n");  /*Obslugujemy blad braku powiadomienia o dolaczeniu do czatu */
		close(gniazdo);      /* Zamykamy socket */
		return -1;
	}
	PID = fork();     /* Tworzymy potomka */
	if(PID == 0)      /* Potomek jest odpowiedzalny za wypisywanie odebranych wiadomosci */
    {
		while(1)
		{
			if(recvfrom(gniazdo, &przychodzace, sizeof(przychodzace), 0, (struct sockaddr *)&rozmowca_adres, &dlugosc) < 0)   /* Pobieramy tresc wiadomosci od drugiego rozmowcy */
			{
				printf("ERROR: Nie udalo sie pobrac wiadomosc!\n");  /* Obslugujemy blad uzyskania tresci */
				return -1;
			}
			if(strcmp(przychodzace.tresc,"<poczatek>") == 0)    /* Informujemy o dolaczeniu nowego rozmowcy */
            {
				printf("\n[%s (%s) dolaczyl do rozmowy]\n", przychodzace.nazwa, inet_ntoa(rozmowca_adres.sin_addr));
			}
			else if(strcmp(przychodzace.tresc,"<koniec>") == 0) /* Informujemy o odlaczeniu ktoregosc z rozmowcow */
            {
				printf("\n[%s (%s) zakonczyl rozmowe]\n", przychodzace.nazwa, inet_ntoa(rozmowca_adres.sin_addr));
			}
			else    /* Wypisujemy otrzymana wiadomosc */
            {
				printf("\n[%s (%s)]: %s\n", przychodzace.nazwa, inet_ntoa(rozmowca_adres.sin_addr), przychodzace.tresc);
			}

			printf("[%s]> ", wychodzace.nazwa); /* Wypisujemy nasza nazwe */
			fflush(stdout); /*Przenosimy dane z bufora do strumienia wyjscia */
		}
		close(gniazdo);  /* Zamykamy socket */
		exit(0);
	}
	else            /* Rodzic jest odpowiedzialny za wysylanie wiadomosci */
    {
		while(1)
		{
			printf("[%s]> ", wychodzace.nazwa);            /* Wypiujemy nasza nazwe */
			fgets(wychodzace.tresc, 300, stdin);           /* Pobieramy wiadomosc do wyslania */
			wychodzace.tresc[strlen(wychodzace.tresc)-1] = '\0';  /* Dopisujemy znak konca wiadomosci */
			if(sendto(gniazdo, &wychodzace, sizeof(wychodzace), 0,(struct sockaddr *)&rozmowca_adres, sizeof(rozmowca_adres)) < 0)   /* Wysylamy wiadomosc */
			{
				printf("ERROR: Wysylanie wiadmosci zakonczone niepowodzeniem!\n");   /*Obslugujemy blad wyslania tresci */
				close(gniazdo);      /* Zamykamy socket */
				return -1;
			}
			if(strcmp(wychodzace.tresc,"<koniec>") == 0)   /* Obslugujemy infromacje o zakonczeniu rozmowy */
			{
				if(kill(PID, SIGINT) < 0)     /* Konczymy prace procesu potomka */
				{
					printf("ERROR: Potomek nie zostal zamkniety!\n");  /*Obslugujemy blad zakonczenia pracy potomka */
					close(gniazdo);     /* Zamykamy socket */
					return -1;
				}
				close(gniazdo);         /* Zamykamy socket */
				return 0;               /* Konczymy dzialanie czatu */
			}
		}
	}
	return 0;   /* Pomyslnie konczymy program */
}
