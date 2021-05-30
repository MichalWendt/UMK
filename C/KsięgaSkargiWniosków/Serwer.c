/* Michal Wendt - serwer skarg i wnioskow */
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <pwd.h>
#include <signal.h>
#include <sys/shm.h>
#include <sys/ipc.h>
#include <sys/types.h>
#include <sys/msg.h>
#include <sys/sem.h>

struct pamiec   /* Informacje o wiadomosci */
{
	int typ;
	int login;       /* Login nadawcy */
	char wiad[200];  /* Maksymalna wielkosc wiadomosci */
} *pamiec_wspo;

int shmid;           /* ID segmentu */
int ilosc_wpis = 0;  /* Ilosc wszystkich wpisow */
int semafor;         /* Semafor */

void czyszczenie(int co)      /* Funckja usuwajaca bledne segmenty i semafory */
{
    if(co == 1)
    {
        printf("odlaczenie: %s\n",(shmdt(pamiec_wspo) == 0) ? "OK" : "blad shmdt");             /* Odlaczanie pamieci */
    }
    if(co == 2)
    {
        printf("usuniecie: %s\n",(shmctl(shmid, IPC_RMID, 0) == 0) ? "OK" : "blad shmctl");     /* Kontrolwoanie pamieci */
    }
    if(co == 3)
    {
        printf("semafory : %s\n", (semctl(semafor, 0, IPC_RMID) == 0)? "OK" : "blad semctl");   /* Kontrolwoanie semafora */
    }
}
void wypisywanie(int signal)/* Obslugujemy sygnal wypisywania informacji o zawartosci ksiegi */
{
    struct passwd *nazwa;   /* Zmienna strukturalna z informacjami o kliencie */
	int i = 0;              /* Licznik pomocniczy */
	int wpisy = 0;          /* Licznik wpisow */
	while(i < ilosc_wpis)   /* Sprawdzamy zawartosc ksiegi */
    {
		if(semctl(semafor, i, GETVAL) != 0 && pamiec_wspo[i].typ != 0)  /* Sumujemy ilosc wpisow */
		{
			wpisy++;
		}
		i++;
	}
	i = 0;
	if(wpisy < 1)    /* Obslugujemy brak wpisow */
    {
		printf("\nKsiega skarg i wnioskow jest jeszcze pusta\n");
		return;
	}
	printf("\n___________  Ksiega skarg i wnioskow:  ___________\n");
	while(i < ilosc_wpis)    /* Przeszukujmey zawartosc ksiegi w poszukiwaniu zapisow */
    {
		if(semctl(semafor, i, GETVAL) != 0 && pamiec_wspo[i].typ != 0)  /* Jezeli w pamieci jest zapis i obszar nie jest uzywany */
        {
            nazwa = getpwuid(pamiec_wspo[i].login);  /*Pobieramy login klienta */
			if(nazwa == NULL)
            {
				printf("ERROR: Niepoprawny login!\n");    /* Obslugujemy nieprawidlowy login */
				czyszczenie(1);    /* Usuwamy bledne segmenty pamieci i semafory */
				czyszczenie(2);
				czyszczenie(3);
				exit(-1);
			}
            printf("[%s]: %s\n", nazwa->pw_name, pamiec_wspo[i].wiad);
		}
		i++;
	}
}

void konczenie(int signal)  /* Obslugujemy sygnal zakonczenia procesu serwera */
{
	printf("\n[Serwer]: dostalem SIGINT => koncze i sprzatam... ");
	printf("(odlaczenie: %s, semafory: %s, usuniecie: %s)\n",(shmdt(pamiec_wspo) == 0)? "OK" : "ERROR: Nie odlaczono pamieci wspoldzielonej",         /* Sprawdzajac prawidlowosc kontroli */
    (semctl(semafor, 0, IPC_RMID) == 0)? "OK" : "ERROR: Nie usunieto semaforow",(shmctl(shmid, IPC_RMID, 0) == 0)? "OK" : "ERROR: Nie usunieto segmentu");
    exit(0);
}

int main(int argc, char ** argv)
{
	struct shmid_ds pom;    /* Pomocnicza struktura z inforacjami o pamieci wspoldzielonej */
	key_t klucz;    /* Klucz utworzony z pliku */
	int i = 0;

	signal(SIGTSTP, wypisywanie);   /* Przekazanie obslugi sygnalow Ctrl^Z */
	signal(SIGINT, konczenie);      /* i Ctrl^C do wlasnych funckji */

	if(argc != 2)   /* Obslugujemy blad zlej ilosci argumentow */
    {
		printf("ERROR: Podano bledna ilosc argumentow!\n");
		printf("Prawidlowa skladnia: %s [ilosc wpisow]\n", argv[0]);
		exit(-1);
	}
	else
    {
        sscanf(argv[1], "%d", &ilosc_wpis);   /* Pobieramy maksymalna ilosc wpisow (mialo byc n ale nazwa jest czytelniejsza) */
        if(ilosc_wpis < 1)
        {
            printf("ERROR: Prosze o wiecej pamieci!(%s to za malo)\n", argv[1]);       /* Obslugujemy blad ilosci pamieci */
            exit(-1);
        }
    }

    printf("[Serwer]: ksiega skarg i wnioskow (WARIANT A)\n");

    printf("[Serwer]: tworze klucz na podstawie pliku %s...", argv[0]);     /* Tworzymy klucz z pliku */
	klucz = ftok(argv[0], 1);
	if(klucz == -1)
    {
		printf("ERROR: Blad podczas tworzenia klucza!\n");        /* Obslugujemy blad utworzenia klucza */
		exit(-1);
	}
	printf(" OK (klucz: %ld)\n", klucz);    /* Wypisujemy numer klucza */

	printf("[Serwer]: tworze semafory...");
	semafor = semget(klucz, ilosc_wpis, 0666 | IPC_CREAT | IPC_EXCL);     /* Tworzymy semafory */
	if(semafor == -1)
    {
		printf("ERROR: Nie udalo sie utworzyc semaforow!\n");        /* Obslugujemy blad utworzenia semafora */
		exit(-1);
	}
	printf(" OK\n");

	while(i < ilosc_wpis)    /* Blokujemy dostep do semaforow */
	{
		if(semctl(semafor, i, SETVAL, 0) == -1)
        {
			printf("ERROR: Nie udalo sie zablokowac semafora nr: %i!\n", i + 1);  /* Obslugujemy blad wartosci semafora */
			czyszczenie(3);    /* Usuwamy bledne semafory */
			exit(-1);
		}
		i++;
	}
    i = 0;

    printf("[Serwer]: tworze segment pamieci wspolnej dla ksiegi na %d ", ilosc_wpis);
	if(ilosc_wpis == 1)
    {
		printf("wpis...");          /* Wypisujemy ilosc wszystkich wpisow */
	}
	else if((ilosc_wpis % 10 < 5) && (ilosc_wpis % 10 > 1) && (ilosc_wpis > 20 || ilosc_wpis < 10))
    {
		printf("wpisy...");         /* Z prawidlowa odmiana */
	}
	else
    {
		printf("wpisow...");
	}

	shmid = shmget(klucz, ilosc_wpis * sizeof(struct pamiec), 0666 | IPC_CREAT | IPC_EXCL);  /* Tworzymy obszar pamieci */
	if(shmid == -1)
    {
		printf("ERROR: Blad tworzenia pamieci!\n");      /* Oblusgujemy blad uworzenia pamieci */
		czyszczenie(3);    /* Usuwamy bledne semafory */
		exit(-1);
	}

	if(shmctl(shmid, IPC_STAT, &pom) == -1)     /* Sprawdzamy dostepnosc informacje o pamieci */
    {
		printf("ERROR: Blad shmctl!\n");        /* Oblusgujemy blad shmctl(operacji kontroli pamieci wspoldzielonej) */
		czyszczenie(2);      /* Usuwamy bledne segmenty pamieci i semafory */
		czyszczenie(3);
		exit(-1);
	}
	printf(" OK (id: %d, rozmiar: %zub)\n", shmid, pom.shm_segsz);

	printf("[Serwer]: dolaczam pamiec wspolna...");
	pamiec_wspo = (struct pamiec *) shmat(shmid, (void *)0, 0);    /* Zapisujemy wskaznik na 1 element */
	if(pamiec_wspo == (struct pamiec *)-1)
    {
		printf("ERROR: Nie udalo sie odnalezc wskazywanej pamieci!\n");        /* Oblusgujemy blad wskaznika */
		czyszczenie(2);      /* Usuwamy bledne segmenty pamieci i semafory */
		czyszczenie(3);
		exit(-1);
	}
	printf(" OK (adres: %lX)\n", (long int)pamiec_wspo);

	while(i < ilosc_wpis)
    {
		pamiec_wspo[i].login = 0;       /* Oznaczamy brak wiadomosci w konkretnych wpisach*/
        pamiec_wspo[i].typ = 0;

		if(semctl(semafor, i, SETVAL, 1) == -1)  /* Odblokowujemy semafory */
		{
			printf("ERROR: Nie udalo sie odblokowac semafora nr: %i!\n", i + 1);       /* Znowu obslugujemy blad wartosci semafora */
			czyszczenie(1);        /* Usuwamy bledne segmenty pamieci i semafory */
			czyszczenie(2);
			czyszczenie(3);
			exit(-1);
		}
        i++;
	}

	printf("[Serwer]: nacisnij Ctrl^Z by wyswietlic stan ksiegi\n");        /* Komunikujemy sie z klientem */
    printf("[Serwer]: nacisnij Ctrl^C by zakonczyc program\n");
	while(1)    /* Przechodzimy w stan oczekiwania na sygnaly */
    {
		pause();
	}
	return 0;   /* Zwracamy wartosc poprawnego zakonczenia programu */
}
