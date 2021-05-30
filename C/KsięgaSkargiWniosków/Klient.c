/* Michal Wendt - klient skarg i wnioskow */
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <sys/ipc.h>
#include <sys/types.h>

struct pamiec      /* Struktura do przechowywania informacji o wiadomosci */
{
    int typ;
    int login;
	char wiad[200];  /* Maksymalna wielkosc wiadomosci */
} *pamiec_wspo;

int main(int argc, char **argv)
{
	struct shmid_ds wyniki;    /* Zmienna strukturalna zawierajaca inforacje o pamieci wspoldzielonej */
    key_t klucz;    /* Klucz utworzony z pliku*/
    int shmid;      /* ID segmentu */
    int ilosc;      /* Pomocniczy licznik ilosci wolnych wpisow */
    int pom;        /* Pomocnicza do przechowywania dancyh pamieci */
    int i = 0;      /* Licznik pomocniczy */
	int semafor;    /* Semafor */
	int rekordy;    /* Ilosc rekordow w ksiedze*/
	size_t wiel_wiado = 200;   /* Wielkosci wiadomosci */
	int wolny_sem = -1;      /* Zmienna okreslajaca czy semafor jest wolny */
	int wartosc = 0;/* Wartosc semafora */

    if(argc != 2)   /* Obslugujemy blad zlej ilosci argumentow */
    {
		printf("ERROR: Podano bledna ilosc argumentow!\n");
		printf("Prawidlowa skladnia: %s [nazwa pliku zrodlowego serwera].c\n", argv[0]);
		exit(-1);
	}

	klucz = ftok(argv[1], 1);  /* Tworzymy klucz */
	if(klucz == -1)   /* Obslugujemy blad utworzenia klucza */
    {
		printf("ERROR: Blad podczas tworzenia klucza!\n");
		exit(-1);
	}

	shmid = shmget(klucz, 0, 0);    /* Wyciagamy adres pamieci z klucza */
	if(shmid  == -1 )  /* Obslugujemy blad adresu */
	{
		printf("ERROR: Nie udalo sie polaczyc z serwerem lub uzyskac dostepu do pamieci!\n");
		exit(-1);
	}

    if(shmctl(shmid, IPC_STAT, &wyniki) == -1)   /* Sprawdzamy dostepnosc informacje o pamieci */
	{
		printf("ERROR: Brak dostepu do inforamcji o pamieci!\n");    /* Oblusgujemy blad shmctl(operacji kontroli pamieci wspoldzielonej) */
		exit(-1);
	}

    pamiec_wspo = (struct pamiec *) shmat(shmid, (void *)0, 0);    /* Zapisujemy wskaznik na 1 element */
	if(pamiec_wspo == (struct pamiec *)-1)     /* Obslugujemy blad wskaznika */
	{
		printf("ERROR: Nie udalo sie odnalezc wskazywanej pamieci!\n");
		exit(-1);
	}

    semafor = semget(klucz, 1, 0);  /* Sprawdzamy dostepnosc informacji o semaforach */
	if(semafor == -1)  /* Obslugujemy blad semafora */
	{
		printf("ERROR: Nie udalo sie uzyskac dostepu do semafora!\n");
		exit(-1);
	}

	rekordy = wyniki.shm_segsz / sizeof(struct pamiec);   /* Zliczamy sume wszystkich rekordow */
	while(i < rekordy)    /* Szukamy dostepnych do pisania semaforow */
	{
		if(!((i + pamiec_wspo)->typ))
		{
		    wartosc = semctl(semafor, i, GETVAL);   /* Pobieramy wartosc w semaforze */
			if(wartosc == 1)        /* Znalezlismy wolny */
            {
				wolny_sem = i;      /* Zapamietujemy jego pozycje */
				if(semctl(semafor, wolny_sem, SETVAL, 0) == -1)         /* Blokujemy semafor */
				{
					printf("ERROR: Nie udalo sie zablokowac semafora!\n");     /* Obslugujemy blad zmiany stanu semafora */
					exit(-1);
				}
				break;      /* Kontynuujemy ze znalezionym semaforem */
			}
			else if (wartosc == -1)          /* Obslugujemy blad wartosci w semaforze */
			{
				printf("ERROR: Nie udalo sie pobierac wartosci semafora!\n");
				exit(-1);
			}
		}
		i++;
	}
    ilosc = rekordy - wolny_sem;
	if(wolny_sem == -1)             /* Sprawdzamy dostepnosc wolnych miejsc */
	{
		printf("Brak wolnych wpisow!\n");       /* Oblusgujemy blad braku miejsca */
		exit(0);
	}
	printf("Klient ksiegi skarg i wnioskow wita!\n");   /* Wypisujemy przywitanie */

	if(ilosc == 1)                      /* Wypisujemy ilosc wolnych wpisow */
	{
		printf("[Wolny %d wpis", ilosc);
	}
	else if((ilosc % 10 < 5) && (ilosc % 10 > 1) && (ilosc > 20 || ilosc < 10))
	{
		printf("[Wolne %d wpisy", ilosc); /* Z prawidlowa odmiana */
	}
	else
	{
		printf("[Wolnych %d wpisow", ilosc);
	}
	printf(" (na %d)]\n", rekordy);       /* Wypisujemy maksymalna ilosc miejsc */

	printf("Napisz co ci lezy na watrobie:\n");     /* Prosimy uzytkownika o wpis */

	(pamiec_wspo + wolny_sem)->typ = 1;             /* Zmieniamy stan obslugiwanego obszaru na zajety */

	(pamiec_wspo + wolny_sem)->login = getuid();    /* Dodajemy id uzytkownika zeby serwer mogl rozpoznac klienta */

	pom = read(0, (pamiec_wspo + wolny_sem)->wiad, wiel_wiado);  /* Zapamietujemy wiadomosc w pamieci */

	(pamiec_wspo + wolny_sem)->wiad[pom-1] = '\0';               /* Dopisujemy znak konca zdania */



	shmdt(pamiec_wspo + wolny_sem);

	if(semctl(semafor, wolny_sem, SETVAL, 1) == -1)         /* Odblokowujemy semafor */
    {
		printf("ERROR: Nie udalo sie odblokowac semafora!\n"); /* Oblusgujemy blad odbkowania semafor */
		exit(-1);
	}

	printf("Dziekuje za dokonanie wpisu do ksiegi\n");  /* Dziekujemy za wpis */

    return 0;       /* Zwracamy wartosc poprawnego zakonczenia programu */
}
