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

/*Funkcja okreslajaca uprawniena dla konkretnych plikow*/
void uprawnienia(int mode, char upr[])
{
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
}
/*Funckja wypisujaca czasy*/
void okresl_czas(struct tm *czas1)
{
    time_t timeA, timeB;
    struct tm aktualna, czas;       /*Struktury czasowe*/
    double difference;              /*Zmienna roznicy czasu*/
    /*Tablica z nazwami miesiaca*/
	char miesiace[12][4]={{"sty\0"},{"lut\0"},{"mar\0"},{"kwi\0"},{"maj\0"},{"cze\0"},{"lip\0"},{"sie\0"},{"wrz\0"},{"paz\0"},{"lis\0"},{"gru\0"}};
    time(&timeB);                           /*Przypisanie czasow do struktur*/
    czas = *czas1;
    czas1 = localtime(&timeB);
    aktualna = *czas1;

	printf("%2d ", czas.tm_mday);           /*Drukowanie dnia*/
    printf("%s ", miesiace[czas.tm_mon]);   /*Drukowanie miesiaca*/

    timeA = mktime(&czas);                  /*Konwersja typu czasowego*/
    timeB = mktime(&aktualna);
    difference = difftime(timeB,timeA);     /*Okreslanie roznicy czasu*/
    difference = difference/2629743;
    if(difference >= 6)
    {
        printf("%5d ",czas.tm_year+1900);   /*Drukowanie roku dla dat starszych niz 6 miesiecy*/
    }
    else
    {
        printf("%02d:", czas.tm_hour);      /*Drukowanie godziny*/
        printf("%02d ", czas.tm_min);       /*Drukowanie minuty*/
    }
}
/*Funckja wypisujaca dane o wszystkich plikach*/
void dane_ls(struct stat info)
{
	struct passwd *user;    /*Struktura uzytkownika*/
	struct group *grupy;    /*Struktura grup*/
	struct tm *czas;        /*Struktura czasowa*/
	char upr[11];           /*Tablica z uprawnieniami*/

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

	czas = localtime(&info.st_mtime);   /*Okreslanie czasu dla pliku*/
	/*Sprawdzanie poszczegolnych uprawnien*/
	uprawnienia(info.st_mode, upr);
    switch (info.st_mode & S_IFMT) /*Sprawdzenie jaki to typ pliku*/
	{
        case S_IFREG:       /*zwykly plik*/
            upr[0] = 'f';
            break;
        case S_IFDIR:       /*katalog*/
            upr[0] = 'd';
            break;
        case S_IFLNK:       /*link/lacze symboliczne*/
            upr[0] = 'l';
            break;
        case S_IFBLK:       /*plik specjalny przypisany/urzadzenie blokowe*/
            upr[0] = 'b';
            break;
        case S_IFCHR:       /*plik specjalny/urzadzenie*/
            upr[0] = 'c';
            break;
        case S_IFIFO:       /*lacze nazwane/fifo*/
            upr[0] = 'p';
            break;
        case S_IFSOCK:      /*gniazdo/socket*/
            upr[0] = 's';
            break;
        default:            /*domyslna opcja*/
            upr[0] = '-';
            break;
    }
	/*Wypisanie uprawnien*/
    printf("%s",upr);
	/*Wypisanie ilosci twardych dowiazan */
	printf("%5d", (int)info.st_nlink);
	/*Wypisanie nazwy uzytkownika */
	printf("%10s", user->pw_name);
	/*Wypisanie grupy uzytkownika */
	printf("%10s", grupy->gr_name);
	/*Wypisanie rozmiaru pliku */
	printf("%8ld ", info.st_size);
	/*Funckja okreslajaca czasy dla poszczegolnych plikow*/
	okresl_czas(czas);
	return;
}
/*Funkcja obslugujaca ls bez parametru*/
void ls(char mydir[])
{
    DIR	*dir_ptr;	         /*Zmienna sciezki pliku*/
	struct dirent *direntp;
	struct stat info;        /*Struktura zawierajaca informacje o pliku*/
	int rozmiar;             /*Wielkosc linku*/
	char *link;              /*Zmienna do linkow*/
	dir_ptr = opendir(mydir);    /*Otwieranie pliku*/
	if(dir_ptr == NULL)
    {
        fprintf(stderr, "ls: Blad otwarcia sciezki lub odmowa dostepu %s\n", mydir);     /*Obsluga bledu otwarcia pliku*/
        exit(-1);
    }
	else
	{
		while(1)
		{
		    direntp = readdir(dir_ptr);     /*Odczytanie sciezki do pliku*/
		    if(direntp == NULL)
            {
                break;
            }
			if(stat(direntp->d_name, &info) < 0)    /* Pobieramy inforacje o pliku */
            {
				perror("Nie ma takiego pliku/katalogu lub odmowa dostepu\n");     /*Obsluga bledu sciezki*/
				exit(-1);
			}
			/* Jezeli byl to link to o nim, a nie o pliku na ktory wskazuje */
			if((S_IFLNK & info.st_mode) && lstat(direntp->d_name, &info) < 0)
            {
				perror("Nie ma takiego pliku/katalogu lub odmowa dostepu\n");     /*Obsluga bledu sciezki*/
				exit(-1);
			}
            dane_ls(info);  /*Wywolanie funkcji wypisujacej dane o wszystkich plikach*/
			printf("%s", direntp->d_name);
			if(S_IFLNK == (S_IFLNK & info.st_mode))     /*Jezeli byl to link, wypisujemy na co wskazuje*/
            {
				link = malloc(info.st_size + 1);
				rozmiar = readlink(direntp->d_name, link, info.st_size + 1);
				link[rozmiar] = '\0';
				printf(" -> %s", link);
            }
			printf("\n");
		}
		closedir(dir_ptr);  /*Zamkniecie pliku*/
		free(link);
	}
	return;
}

/*Funkcja wypisujaca dokladniejsza date*/
void okresl_czas_2(struct tm *czas)
{
	/*Tablica z nazwami miesiaca*/
	char miesiace[12][14]={"stycznia\0","lutego\0","marca\0","kwietnia\0","maja\0","czerwca\0","lipca\0","sierpnia\0","wrzesnia\0","pazdziernika\0","listopada\0","grudnia\0"};

	printf("%2d ", czas->tm_mday);          /*Wyswietlanie dnia*/
	printf("%13s", miesiace[czas->tm_mon]); /*Wyswietlanie miesiaca*/
	printf("%5d roku o ", czas->tm_year + 1900);    /*Wyswietlanie roku*/
    printf("%2d:", czas->tm_hour);          /*Wyswietlanie godzin*/
    printf("%02d:", czas->tm_min);          /*Wyswietlanie minut*/
    printf("%02d", czas->tm_sec);           /*Wyswietlanie sekund*/
}

/*Funcka do wypisania szczegolowych informacji o konkretnym pliku*/
void dane_lspar(struct stat info, char *nazwa)
{
	struct tm *czas;    /*Pomocnicza czasowa*/
	char zawar;     /*Pomocnicza do zawartosci*/
	int zwykly = 0, symb = 0;   /*Pomocnicze do typu pliku*/
	char *link;     /*Sciezka do pliku*/
	char upr[11];   /*Tablica uprawnien*/
	FILE *plik;     /*Obslugiwany plik*/

	printf("Informacje o %s:\n", nazwa);    /*Podanie nazwy pliku*/
	printf("Typ pliku:   ");
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
	printf("Sciezka:     ");        /*Sprawdzenie sciezki do pliku*/
	if(symb == 1)     /*Jezeli to link*/
    {
        link = realpath(".", NULL);
		printf("%s/%s\n", link, nazwa);
		printf("Wskazuje na: ");
		link = realpath(nazwa, NULL);
		printf("%s\n", link);
	}
	else    /*Jezeli to nie link*/
	{
		link = realpath(nazwa, NULL);
		printf("%s\n", link);
	}

	printf("Rozmiar:     %ld ", info.st_size); /*Wypisanie rozmiaru*/
	if(info.st_size == 1)
    {
		printf("bajt\n");
	}
	else if((info.st_size%10) < 4)
    {
		printf("bajty\n");
	}
	else
    {
		printf("bajtow\n");
	}

	printf("Uprawnienia: ");
	uprawnienia(info.st_mode, upr);
	printf("%s",upr+1);
	printf("\n");

	czas = localtime(&info.st_atime);      /*Wypisanie ostatniego czasu dostepu*/
	printf("Ostatnio uzywany:        ");
	okresl_czas_2(czas);
	printf("\n");

	czas = localtime(&info.st_mtime);      /*Wypisanie ostatniego czasu modyfikacji*/
	printf("Ostatnio modyfikowany:   ");
	okresl_czas_2(czas);
	printf("\n");

	czas = localtime(&info.st_ctime);      /*Wypisanie ostatniego czasu zmiany*/
	printf("Ostatnio zmieniany stan: ");
	okresl_czas_2(czas);
	printf("\n");

	if(zwykly)         /*Jezeli byl to zwykly plik wypisujemy 80 pierwszych znakow*/
    {
		printf("Poczatek zawartosci:\n");
		plik = fopen(nazwa,"r");    /*Otwarcie pliku*/
		if(plik == NULL)
		{
			perror("Nie udalo sie otworzyc pliku\n");     /*Obsluga bledu otwarcia pliku*/
			exit(-1);
		}
		for(int i = 0; i < 80; ++i)
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
	free(link);
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
    if(argc == 1)
    {
        ls(".");    /*Funkcja bez argumentu*/
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
