/* Multiproxy - Michal Wendt */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <netinet/tcp.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <poll.h>

#define _GNU_SOURCE     /* Definicja potrzebna do POLLRDHUP */

void zamknij(unsigned int ilosc_polaczen, struct pollfd *deskryptory)   /* Funckja konczaca komunikacje */
{
	unsigned int k;
	for(k = 0; k < ilosc_polaczen; k = k+2)    /* Zamykamy wszystkie gniazda */
    {
		close(deskryptory[k].fd);
	}
	free(deskryptory);      /* Zwalniamy pamiec zajmowana przez wszystkich klientow */
}

int tworzenie_gniazda(unsigned int port_zrodla)     /* Funckja tworzaca nowe gniazdo */
{
	struct sockaddr_in serwer;  /* Zmienna strukturalna przechowujaca adres naszej maszyny */
	int gniazdo;        /* Zmienna gniazda */
	int otwarte = 1;    /* Tryb polaczenia */
	gniazdo = socket(AF_INET, SOCK_STREAM, 0);   /* Tworzymy gniazdo */
	if(gniazdo == -1)
    {
		printf("ERROR: Nie mozna stworzyc gniazda!\n"); /* Obslugujemy blad utworzenia gniazda */
		exit(-1);
	}
	bzero(&serwer, sizeof(serwer)); /* Ustawiamy wszystkie bity na 0 */
	serwer.sin_family = AF_INET;    /* Ustawiamy odpowiedna rodzine */
	serwer.sin_port = htons(port_zrodla);  /* port_zrodla */
	serwer.sin_addr.s_addr = htonl(INADDR_ANY); /* Oraz nasz dowolny interfejs */
	if (ioctl(gniazdo, FIONBIO, (char *) &otwarte) == -1)   /* Ustawiamy na wersje nieblokujaca */
    {
        printf("ERROR: Nie ustawiono na nieblokujaca!\n");  /* Obslugujemy blad zmiany stanu gniazda */
		close(gniazdo); /* Zamykamy gniazdo */
        exit(-1);
    }
	if (bind(gniazdo, (struct sockaddr *) &serwer, sizeof(serwer)) < 0) /* Przypisujemy gniazdu odpowienie parametry */
    {
        printf("ERROR: Blad bindowania gniazda!\n");     /*Obslugujemy blad bindowania gniazda */
		close(gniazdo); /* Zamykamy gniazdo */
        exit(-1);
    }
	listen(gniazdo, SOMAXCONN); /* Ustawiamy gniazdo do nasluchu */
	return gniazdo;         /* Zwracamy gotowe do uzycia gniazdo */
}

struct pollfd *polacz_zamknij(unsigned int ilosc_polaczen, unsigned int wartosc_1, unsigned int wartosc_2, struct pollfd *deskryptory)    /* Struktura usuwajaca zbedne polacznie */
{
    struct pollfd *deskryptory_2 = malloc((ilosc_polaczen - 2) * sizeof(struct pollfd));    /* Tworzymy nowa tablice klientow do ktorej bedziemy przepisywac wszystkie polaczenia bez zakonczonego */
    unsigned int k, j;  /* Liczniki petli */
	for (k = 0, j = 0; k < ilosc_polaczen; k++, j++)    /* Przepisujemy potrzebne informacje */
    {
		if (k == wartosc_1 || k == wartosc_2)     /* Jezeli jest do usuniacia pomijamy */
		{
			j--;
            continue;
		}
        deskryptory_2[j].fd = deskryptory[k].fd;    /* Informacje o uchwytach i eventach/odpowiedziach */
        deskryptory_2[j].revents = deskryptory[k].revents;
        deskryptory_2[j].events = deskryptory[k].events;
    }
    free(deskryptory);      /* Zwalniamy pamiec zajmowana przez aktualych klientow */
    return deskryptory_2;   /* Zwracamy zbior pomiejszony o zbedne polaczenie */
}

struct pollfd *polacz_nowe(int gniazdo, struct pollfd *deskryptory, unsigned int ilosc_polaczen, struct addrinfo *docelowy)  /* Struktura tworzaca nowe polacznie */
{
    struct sockaddr_in adres_klienta;
	struct addrinfo *zrodlowy;
	int otwarte = 1;    /* Tryb polaczenia */
	int polaczenie;     /* Zmienna nawiazujaca polaczenie */
	deskryptory = realloc(deskryptory, sizeof(struct pollfd) * (ilosc_polaczen + 2));   /* Rozszerzamy baze polaczanych klientow o zroblowy i docelowy */
    deskryptory[ilosc_polaczen].events = POLLIN | POLLRDHUP;    /* Ustawiamy pierwszy jako zrodlowy */
    deskryptory[ilosc_polaczen + 1].events = POLLIN | POLLRDHUP;
	bzero(&adres_klienta, sizeof(adres_klienta));   /* Ustawiamy wszystkie bity na 0 dla adresu docelowego*/
	socklen_t dlugosc_adresu_klienta = sizeof(adres_klienta);

	if((deskryptory[ilosc_polaczen].fd = accept(gniazdo,(struct sockaddr *) &adres_klienta,&dlugosc_adresu_klienta)) < 0)  /* Sprawdzmy czy polaczenie bedzie dostepne */
    {
        printf("ERROR: Nie zaakceptowano polaczenia!\n");    /* Obslugujemy blad odmowy dostepu */
		zamknij(ilosc_polaczen, deskryptory);   /* Wywolujemy funkcje czyszczace */
        exit(-1);
    }
    if((deskryptory[ilosc_polaczen + 1].fd = socket(AF_INET, SOCK_STREAM, 0)) == -1)   /* Tworzymy gniazdo przez ktore bedziemy wysylac do docelowego */
    {
        printf("ERROR: Blad tworzenia gniazda!\n");     /* Obslugujemy blad utworzenia gniazda */
		zamknij(ilosc_polaczen, deskryptory);   /* Wywolujemy funkcje czyszczace */
        exit(-1);
    }
	polaczenie = -1;
	zrodlowy = docelowy;
	while(docelowy != NULL) /* Probujemy nawiazac polaczenie */
    {
		polaczenie = connect(deskryptory[ilosc_polaczen + 1].fd, docelowy->ai_addr, docelowy->ai_addrlen);
		if(polaczenie == -1)
        {
			docelowy = docelowy->ai_next;
		}
        else
        {
			break;
		}
	}
	docelowy = zrodlowy;
	if(polaczenie == -1)
    {
		printf("ERROR: Brak polaczenia z hostem docelowym!\n"); /*Obslugujemy blad nawiazania polaczenia */
		zamknij(ilosc_polaczen, deskryptory);               /* Wywolujemy funkcje czyszczace */
		exit(-1);
	}
    if (ioctl(deskryptory[ilosc_polaczen + 1].fd, FIONBIO, (char *) &otwarte) == -1)    /* Przechodzimy do trybu nieblokujacego */
    {
        printf("ERROR: Nie ustawiono na nieblokujaca!\n");  /* Obslugujemy blad zmiany stanu .... */
		zamknij(ilosc_polaczen, deskryptory);               /* Wywolujemy funkcje czyszczace */
        exit(-1);
    }
    return deskryptory;     /* Zwracamy zbior powiekszony o nowe polaczenie */
}

int main(int argc, char **argv)
{
	unsigned int k;         /* Licznik petli */
	int ile_portow = argc;  /* Zmienna do przechowania ilosci argumentow wywolania */
	// if(ile_portow != 2)     /* Obslugujemy blad niepoprawnej ilosci argumentow */
    // {
	//	printf("ERROR: Nieprawidlowa ilosc argumentow!\n");
    //  printf("Prawidlowa fraza to: %s local_port_1:host_1:host_port_1 [local_port_2:host_2:host_port_2 ...]\n", argv[0]);
	//	return -1;
	// }
	for(k = 1; k < ile_portow; k++) /* Wykonujemy dopoki nie przetworzymy wszystkich portow */
    {
		if(fork() == 0)     /* Sprawdzamy czy obsluguje nas potomek */
		{
			struct addrinfo *info;/* Zmienna stukturalna do przechowywania informacji o adresie hosta z getaddrinfo */
			struct pollfd *deskryptory; /* Zmienna strukturalna przechowujaca deskryptory plikow */
            int ilosc_danych;           /* Licznik znakow z recv */
			int gniazdo;                /* Zmienna gniazda sieciowego */
			unsigned int port_zrodla;   /* Numer portu */
			unsigned int ilosc_polaczen;/* Ilosc aktualnych polaczen */
			char adres_docelowy[120];   /* Zmienna przechowujaca adres docelowy */
			char port_docelowy[5];      /* Zmienna przechowujaca port docelowy */
			char buf[15000];            /* Bufor przechowujacy dane deskryptorow */

			sscanf(argv[k], "%u:%[^:]:%s", &port_zrodla, adres_docelowy, port_docelowy);   /* Zapisujemy port zrodlowy oraz port i adres docelowy dla przesylanych pakietow */
            ilosc_polaczen = 1;     /* Ustawiamy poczatkowa ilosc polaczen */
			if(getaddrinfo(adres_docelowy, port_docelowy, NULL, &info) < 0)   /* Pobieramy informacje o hoscie docelowym */
            {
                printf("ERROR: Blad pobierania informacji o adresie!\n");   /*Obslugujemy blad adresu */
                return -1;
            }
			gniazdo = tworzenie_gniazda(port_zrodla);   /* Tworzymy gniazdo na odpowieni port */
			deskryptory = malloc(sizeof(struct pollfd) * ilosc_polaczen);   /* Tworzymy tablice polaczen */
			deskryptory[0].fd = gniazdo;    /* Ustawiamy 1 klienta jako nasze gniazdo */
			deskryptory[0].events = POLLIN | POLLRDHUP; /* Ustawanimy na odbior danych i utrate polaczenia */

			while(1)
            {
				if(poll(deskryptory, ilosc_polaczen, 5000) < 0)     /* Sprawdzamy czy jest jakis ruch siociowy z odpowiednim timeout'em */
                {
					printf("ERROR: Brak ruchu sieciowego!\n");      /* Obslugujemy brak ruchu sieciowego */
					zamknij(ilosc_polaczen, deskryptory);           /* Wywolujemy funkcje czyszczace */
					exit(-1);
				}
				for(k = 0; k < ilosc_polaczen; k++)     /* Sprawdzamy dla ktorego polaczanie cos przyszlo */
                {
					if(deskryptory[k].revents == 0)     /* Pomijamy k-ty deskryptor jezeli nic nie zwrocono */
                    {
						continue;
					}
					if((deskryptory[k].revents & POLLIN) == POLLIN) /* Sprawdzamy czy przyszly jakies dane */
                    {
						if(deskryptory[k].fd == gniazdo)            /* Jezeli przyszly pakiety do nas */
                        {
							deskryptory = polacz_nowe(gniazdo, deskryptory, ilosc_polaczen, info);    /* Tworzymy polaczenie do przesylania */
							ilosc_polaczen = ilosc_polaczen + 2;
						}
						else
						{
							errno = 0;
							if((ilosc_danych = recv(deskryptory[k].fd, buf, 1024, 0)) < 0)    /* W przeciwnym wypadku pobieramy dane */
                            {
								if(errno != EAGAIN)     /* Sprawdzamy czy sa dostepne jakies dane */
								{
								    printf("ERROR: Blad pobierania danych!\n");     /* Obslugujemy blad pobrania danych */
									zamknij(ilosc_polaczen, deskryptory);           /* Wywolujemy funkcje czyszczace */
									return -1;
								}
                                else
								{
									deskryptory[k].revents = 0;     /* Zerujemy zdarzenia powrotne dla deskryptora */
									continue;
								}
							}
							buf[ilosc_danych] = '\0';     /* Doklejamy znak konca napisu */
							if(k % 2 == 0)          /* Wysylamy odpowiednio do docelowego lub zrodlowego */
                            {
								send(deskryptory[k - 1].fd, buf, ilosc_danych, 0);
							}
							else
                            {
								send(deskryptory[k + 1].fd, buf, ilosc_danych, 0);
							}
						}
					}
					if((deskryptory[k].revents & POLLRDHUP) == POLLRDHUP)   /* Sprawdzamy czy polaczenie zostalo zakonczne */
                    {
						close(deskryptory[k].fd);   /* Zamykamy odpowiednio docelowy i zrodlowy host */
						if(k % 2 != 0)
                        {
                            close(deskryptory[k + 1].fd);   /* Zamykamy deskryptor */
							deskryptory = polacz_zamknij(ilosc_polaczen, k, k + 1, deskryptory);    /* Konczymy polaczenie dla tego deskryptora */
							k++;    /* Pomijamy nastepne polaczenie w zbiorze */
						}
                        else
                        {
							close(deskryptory[k - 1].fd);   /* Zamykamy deskryptor */
							deskryptory = polacz_zamknij(ilosc_polaczen, k, k - 1, deskryptory);    /* Konczymy polaczenie dla tego deskryptora */
						}
						ilosc_polaczen = ilosc_polaczen - 2;    /* Zmniejszamy ilosc polaczen o zamkniete deskryptory */
						continue;
					}
					deskryptory[k].revents = 0; /* Zerujemy zdarzenia powrotne dla deskryptora (brak ruchu) */
				}
            }
			zamknij(ilosc_polaczen, deskryptory);   /* Wywolujemy funkcje czyszczace */
			return 0;   /* Pomyslnie konczymy program */
		}
	}
	for(k = 1; k < ile_portow; k++)
    {
		wait(NULL); /* Czekamy aby kazdy potomek zakonczyl dzialanie */
	}
    return 0;       /* Pomyslnie konczymy program */
}
