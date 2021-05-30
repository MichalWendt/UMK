/*myls - Michal Wendt*/
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <time.h>
#include <pwd.h>
#include <grp.h>
#include <string.h>
#include <limits.h>
#include <fcntl.h>

/*Definicja porownujaca*/
#define max(a, b) \
   ({ __typeof__ (a) _a = (a); \
       __typeof__ (b) _b = (b); \
     _a > _b ? _a : _b; })

/*Zmienne okreslajace szerokosc poszczegolnych kolumn oraz ilosci blokow pamieci */
int ile_dowiazan = 0;
int Max_nazwa_wlasciciela = 0;
int Max_nazwa_grupy = 0;
long Max_rozmiar = 0;
long ile_blokow = 0;

/*Funkcja wyrownojaca tekst przy uzyciu spacji*/
char *przesuniecie(long ile)
{
    if (ile > 0)
    {
        char *wyrownanie = malloc(ile + 1);
        int i;
        for (i = 0; i < ile; ++i)
        {
            wyrownanie[i] = ' ';
        }
        wyrownanie[ile] = '\0';
        return wyrownanie;
    }
    else
    {
        char *wyrownanie = malloc(2);
        wyrownanie[0] = '\0';
        return wyrownanie;
    }
}

/*Funkcja okreslajaca uprawniena dla konkretnych plikow*/
void *uprawnienia(int mode)
{
    char *upr = malloc(10 * sizeof(char));
	strcpy(upr, "----------");      /*Domyslna tablica z brakiem uprawnien*/

	if(mode & S_IRUSR) upr[1] = 'r';	/*3 bity uzytkownika*/
	if(mode & S_IWUSR) upr[2] = 'w';
	if(mode & S_IXUSR) upr[3] = 'x';

	if(mode & S_IRGRP) upr[4] = 'r';	/*3 bity grup*/
	if(mode & S_IWGRP) upr[5] = 'w';
	if(mode & S_IXGRP) upr[6] = 'x';

	if(mode & S_IROTH) upr[7] = 'r';	/*3 bity innych uzytkownikow*/
	if(mode & S_IWOTH) upr[8] = 'w';
	if(mode & S_IXOTH) upr[9] = 'x';
	return upr;
}

/*Funckja wypisujaca czasy*/
char *okresl_czas(const long int czas)
{
    char *data = malloc(40 * sizeof(char));
    time_t timeA;
    struct tm *aktualna;       /*Struktura czasowa*/
    /*Tablica z nazwami miesiaca*/
	char miesiace[12][4]={{"sty\0"},{"lut\0"},{"mar\0"},{"kwi\0"},{"maj\0"},{"cze\0"},{"lip\0"},{"sie\0"},{"wrz\0"},{"paz\0"},{"lis\0"},{"gru\0"}};
    time(&timeA);                        /*Przypisanie czasow do struktur*/
    aktualna = localtime(&czas);

    if (difftime(timeA, czas) > 15778463)
    {
        sprintf(data,"%2d %3s %5d",aktualna->tm_mday, miesiace[aktualna->tm_mon], aktualna->tm_year + 1900);
    }
    else
    {
        sprintf(data,"%2d %3s %02d:%02d",aktualna->tm_mday, miesiace[aktualna->tm_mon], aktualna->tm_hour, aktualna->tm_min);
    }
    return data;
}

char *upra_typ(int mode)
{
    char *upraw;
    char *pelneUpr = malloc(12);
    char typ;
    switch (mode & S_IFMT)
    {
        case S_IFDIR:
            typ = 'd';
            break;
        case S_IFLNK:
            typ = 'l';
            break;
        case S_IFBLK:
            typ = 'b';
            break;
        case S_IFCHR:
            typ = 'c';
            break;
        case S_IFIFO:
            typ = 'p';
            break;
        case S_IFSOCK:
            typ = 's';
            break;
        default:
            typ = '-';
            break;
    }
    upraw = uprawnienia(mode); /*Pobieramy uprawnienia*/
    sprintf(pelneUpr, "%c%s", typ, upraw);  /*Wpisujemy typ i uprawnienia do zmiennej pelneUpr*/
    free(upraw);
    return pelneUpr;
}

/*Funkcja obliczajaca ilosc cyfr*/
int ile_cyfr(long liczba)
{
    int dlugosc = 0;
    if (liczba == 0)
    {
        return 1;
    }
    while (liczba > 0)
    {
        liczba = liczba / 10;
        dlugosc++;
    }
    return dlugosc;
}

/*Funckja wypisujaca dane o wszystkich plikach*/
char *dane_ls(struct stat info)
{
    char *dane = malloc(50 * sizeof(char));
	struct passwd *user;    /*Struktura uzytkownika*/
	struct group *grupy;    /*Struktura grup*/

	grupy = getgrgid(info.st_gid);  /*Pobieranie inforamcje o grupie */
	if(grupy == NULL)
    {
		perror("Brak dostepu do danych grupy uzytkownika\n"); /*Obsluga bledu dostepu*/
		exit(-1);
	}
	user = getpwuid(info.st_uid);   /*Pobieranie informacje o uzytkowniku */
	if(user == NULL)
    {
		perror("Brak dostepu do danych uzytkownika\n");   /*Obsluga bledu dostepu*/
		exit(-1);
	}

	char *przesuniecie_dowiazania = przesuniecie(ile_dowiazan - ile_cyfr((int) info.st_nlink));
    char *przesuniecie_nazwa = przesuniecie(Max_nazwa_wlasciciela - strlen(user->pw_name));
    char *przesuniecie_grupa = przesuniecie(Max_nazwa_grupy - strlen(grupy->gr_name));
    sprintf(dane, "%s%d %s%s  %s%s", przesuniecie_dowiazania, (int) info.st_nlink, przesuniecie_nazwa, user->pw_name, przesuniecie_grupa, grupy->gr_name);
    free(przesuniecie_dowiazania);
    free(przesuniecie_nazwa);
    free(przesuniecie_grupa);
    return dane;
}

/*Funkcja wypisujaca informacje pliku w formie wierszowej*/
void wypiszLs(struct stat sb, char *nazwa)
{
    char *upr = upra_typ(sb.st_mode);
    char *info = dane_ls(sb);
    char *data = okresl_czas(sb.st_mtime);
    char *przesuniecie_rozmiar = przesuniecie(Max_rozmiar - ile_cyfr((long long) sb.st_size));   /*Pobieramy ilosc spacji potrzebnych do przesuniecia*/

    printf("%s  %s  %s%lld %s ", upr, info, przesuniecie_rozmiar, (long long) sb.st_size, data);
    /*Wypisujemy nazwe w odpowiednim formacie i kolorze*/
    if (S_ISDIR(sb.st_mode))   /*Jezeli katalog*/
    {
        printf("\x1B[34m" "%s\n" "\x1B[0m", nazwa);
    }
    else if (S_ISLNK(sb.st_mode)) /*Jezeli link symboliczny*/
    {
        char *slink = malloc(sb.st_size + 1);
        int wielkosc = readlink(nazwa, slink, sb.st_size + 1);
        if (wielkosc < 1)
        {
            perror("Blad odczytania linku\n");
            exit(-1);
        }
        slink[wielkosc] = '\0';
        printf("\x1B[36m" "%s " "\x1B[0m" "-> %s\n", nazwa, slink);
        free(slink);
    }
    else if (sb.st_mode & (S_IXUSR | S_IXGRP | S_IXOTH))   /*Jezeli plik wykonywalny*/
    {
        printf("\x1B[32m" "%s\n" "\x1B[0m", nazwa);
    }
    else
    {
        printf("%s\n", nazwa);
    }
    free(upr);
    free(info);
    free(data);
    free(przesuniecie_rozmiar);
}

/*Funkcja sprawdzajaca maksymalny rozmiar kolumny oraz zajmowanych ilosc blokow pamieci*/
void dopasowanie_kolumn(struct stat sb, struct dirent **glowny_tab, int n)
{
    int i;
    for (i = 0; i < n; ++i)
    {
        if (lstat(glowny_tab[i]->d_name, &sb) < 0)
        {
            perror("Brak pliku lub brak uprawnien ");
            exit(-1);
        }
        ile_dowiazan = max(ile_dowiazan, ile_cyfr(sb.st_nlink));
        struct group *group = getgrgid(sb.st_gid);
        if (group == NULL)
        {
            perror("Nie mozna pobrac danych grupy uzytkownika");
            exit(-1);
        }
        struct passwd *passwd = getpwuid(sb.st_uid);
        if (passwd == NULL)
        {
            perror("Nie mozna pobrac danych uzytkownika");
            exit(-1);
        }
        Max_nazwa_wlasciciela = max(Max_nazwa_wlasciciela, strlen(passwd->pw_name));
        Max_nazwa_grupy = max(Max_nazwa_grupy, strlen(group->gr_name));
        Max_rozmiar = max(Max_rozmiar, ile_cyfr(sb.st_size));
        ile_blokow = ile_blokow + sb.st_blocks / 2; /*Obliczamy liczbe blokow pamieci*/
    }
}

/*Funkcja obslugujaca ls bez parametru*/
void ls(char mydir[])
{
    int n;
	struct dirent **glowny_tab;
	struct stat info;        /*Struktura zawierajaca informacje o pliku*/
	if((n = scandir(".", &glowny_tab, NULL, alphasort)) < 0) /*Pobieramy zawartosc katalogu, posortowana alfanumeryczie po nazwach plikow(katalogow itp)*/
    {
        fprintf(stderr, "ls: Blad otwarcia sciezki lub odmowa dostepu %s\n", mydir);     /*Obsluga bledu otwarcia pliku*/
        exit(-1);
    }
	else
	{
        dopasowanie_kolumn(info, glowny_tab, n);
        printf("total: %ld\n", ile_blokow);
        int i;
		for (i = 0; i < n; ++i)
        {
			/* Jezeli byl to link to o nim, a nie o pliku na ktory wskazuje */
			if(lstat(glowny_tab[i]->d_name, &info) < 0)
            {
				perror("Nie ma takiego pliku/katalogu lub odmowa dostepu\n");     /*Obsluga bledu sciezki*/
				exit(-1);
			}
            wypiszLs(info,glowny_tab[i]->d_name);  /*Wywolanie funkcji wypisujacej dane o wszystkich plikach*/
			free(glowny_tab[i]);
		}
		free(glowny_tab);
	}
	return;
}

/*Funkcja wypisujaca dokladniejsza date*/
char *okresl_czas_2(const long int czas)
{
    char *data = malloc(40 * sizeof(char));
    struct tm *time = localtime(&czas);
	/*Tablica z nazwami miesiaca*/
	char miesiace[12][14]={"stycznia\0","lutego\0","marca\0","kwietnia\0","maja\0","czerwca\0","lipca\0","sierpnia\0","wrzesnia\0","pazdziernika\0","listopada\0","grudnia\0"};

	sprintf(data, "%2d %s %d roku o %02d:%02d:%02d", time->tm_mday, miesiace[time->tm_mon], time->tm_year + 1900,
            time->tm_hour, time->tm_min, time->tm_sec);
    return data;
}

/*Funcka do wypisania szczegolowych informacji o konkretnym pliku*/
void dane_lspar(struct stat info, char *nazwa)
{
	char zawar;     /*Pomocnicza do zawartosci*/
	int zwykly = 0, symb = 0;   /*Pomocnicze do typu pliku*/
	char *link;     /*Sciezka do pliku*/
	FILE *plik;     /*Obslugiwany plik*/
    char *upra = uprawnienia(info.st_mode);         /*Tablica uprawnien*/
    char *czas_uzywania = okresl_czas_2(info.st_atime);
    char *czas_modyfikacji = okresl_czas_2(info.st_mtime);
    char *czas_zmiany_stanu = okresl_czas_2(info.st_ctime);
	printf("Informacje o %s:\n", nazwa);    /*Podanie nazwy pliku*/
	printf("Typ pliku:   \t");
	switch (info.st_mode & S_IFMT) /*Sprawdzenie jaki to typ pliku*/
	{
        case S_IFREG:
            printf("zwykly plik\n");
            zwykly = 1;
            break;
        case S_IFDIR:
            printf("katalog\n");
            break;
        case S_IFLNK:
            printf("link symboliczny\n");
            symb = 1;
            break;
        case S_IFBLK:
            printf("urzadzenie blokowe\n");
            break;
        case S_IFCHR:
            printf("urzadzenie\n");
            break;
        case S_IFIFO:
            printf("fifo/pipe\n");
            break;
        case S_IFSOCK:
            printf("socket\n");
            break;
        default:
            printf("nieznay typ\n");
            break;
    }
	printf("Sciezka:     \t");        /*Sprawdzenie sciezki do pliku*/
	if(symb == 1)     /*Jezeli to link*/
    {
        if((link = realpath(".", NULL)) == NULL)
        {
            perror("Odczytywanie sciezki nie powiodlo sie ");
            exit(-1);
        }
		printf("%s/%s\n", link, nazwa);
		free(link);
		printf("Wskazuje na: \t");
		if((link = realpath(nazwa, NULL)) == NULL)
        {
            perror("Odczytywanie sciezki nie powiodlo sie ");
            exit(-1);
        }
		printf("%s\n", link);
		free(link);
	}
	else    /*Jezeli to nie link*/
	{
		if((link = realpath(nazwa, NULL)) == NULL)
        {
            perror("Odczytywanie sciezki nie powiodlo sie ");
            exit(-1);
        }
		printf("%s\n", link);
		free(link);
	}

	printf("Rozmiar:\t%lld ", (long long) info.st_size); /*Wypisanie rozmiaru*/
	if(info.st_size == 1)
    {
		printf("bajt\n");
	}
	else if((info.st_size % 10 < 5) && (info.st_size % 10 > 1) && (info.st_size > 20 || info.st_size < 10))
    {
		printf("bajty\n");
	}
	else
    {
		printf("bajtow\n");
	}

	printf("Uprawnienia: ");
	printf("\t%s",upra+1);
	printf("\n");
    printf("Ostatnio uzywany     \t%s\n", czas_uzywania);       /*Wypisanie ostatniego czasu dostepu*/
    printf("Ostatnio modyfikowany\t%s\n", czas_modyfikacji);    /*Wypisanie ostatniego czasu modyfikacji*/
    printf("Ostatnio zmieniany stan\t%s\n", czas_zmiany_stanu); /*Wypisanie ostatniego czasu zmiany*/

	if(zwykly)         /*Jezeli byl to zwykly plik wypisujemy 80 pierwszych znakow*/
    {
        int i;
		printf("Poczatek zawartosci:\n");
		plik = fopen(nazwa,"r");    /*Otwarcie pliku*/
		if(plik == NULL)
		{
			perror("Nie udalo sie otworzyc pliku\n");     /*Obsluga bledu otwarcia pliku*/
			exit(-1);
		}
		for(i = 0; i < 80; ++i)
		{
		    zawar = getc(plik);     /*Pobieranie zawartosci po znaku*/
		    if(zawar == EOF)        /*Do konca pliku jezeli jest szybciej niz 80 znakow*/
            {
                break;
            }
			printf("%c", zawar);    /*Wypisanie zawartosci pliku*/
		}
		printf("\n");
		fclose(plik);           /*Zamkniecie pliku*/
	}
	free(upra);
    free(czas_uzywania);
    free(czas_modyfikacji);
    free(czas_zmiany_stanu);
	return;
}

void lspar(char mydir[])
{
    struct stat info;   /*Struktura zwracajaca informacje o pliku*/
    if(lstat(mydir, &info) < 0)  /*Pobieramy inforacje o pliku*/
    {
        perror("Nie ma takiego pliku/katalogu lub odmowa dostepu\n"); /*Obsluga bledu sciezki*/
        exit(-1);
    }
    if((S_IFLNK & info.st_mode) && lstat(mydir, &info) < 0) /*Jezeli byl to link to o nim, a nie o pliku na ktory wskazuje*/
    {
        perror("Nie ma takiego pliku/katalogu lub odmowa dostepu\n"); /*Obsluga bledu sciezki*/
        exit(-1);
    }
    dane_lspar(info, mydir);    /*Wywolanie funkcji wypisujacej dane o konkretnym pliku*/
    exit(0);
}

int main(int argc, char *argv[])
{

    if(argc == 1)   /*Funkcja bez argumentu*/
    {
        ls(".");
    }
    else if(argc == 2)
    {
        lspar(argv[1]);   /*Funkcja z argumentem*/
    }
    else
    {
        printf("Za duzo argumentow!\n");   /*Obsluga bledu ilosci argumentow*/
        return -1;
    }
    return 0;   /*Program zakonczyl sie powodzeniem*/
}
