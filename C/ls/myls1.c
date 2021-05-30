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
void okresl_czas(struct tm *czas)
{
	/*Tablica z nazwami miesiaca*/
	char miesiace[12][4]={{"sty\0"},{"lut\0"},{"mar\0"},{"kwi\0"},{"maj\0"},{"cze\0"},{"lip\0"},{"sie\0"},{"wrz\0"},{"paz\0"},{"lis\0"},{"gru\0"}};

	printf("%2d ", czas->tm_mday);      /*Drukowanie dnia*/
    printf("%s ", miesiace[czas->tm_mon]);  /*Drukowanie miesiaca*/
	printf("%2d:", czas->tm_hour);  /*Drukowanie godziny*/
	if(czas->tm_min >= 10)
    {
        printf("%d ", czas->tm_min);    /*Drukowanie minuty*/
	}
	else
	{
		printf("0%d ", czas->tm_min);   /*Drukowanie minuty mniejszej niz 10*/
	}
}
/*Funckja wypisujaca dane o wszystkich plikach*/
void dane_ls(struct stat info)
{
	struct passwd *user;    /*Struktura uzytkownika*/
	struct group *grupy;   /*Struktura grup*/
	struct tm *czas;    /*Struktura czasowa*/
	char upr[11];       /*Tablica z uprawnieniami*/

	grupy = getgrgid(info.st_gid);  /*Pobieranie inforamcje o grupie */
	if(grupy == NULL)
    {
		perror("Brak dostepu do danych grupy uzytkownika"); /*Obsluga bledu dostepu*/
		exit(-1);
	}
	user = getpwuid(info.st_uid);   /*Pobieranie informacje o uzytkowniku */
	if(user == NULL)
    {
		perror("Brak dostepu do danych uzytkownika");   /*Obsluga bledu dostepu*/
		exit(-1);
	}

	czas = localtime(&info.st_mtime);   /*Okreslanie aktualnego czasu*/
	/* Sprawdzenie jaki to typ pliku */
    if(S_IFREG == (S_IFREG & info.st_mode)) upr[0] = 'f';           /*zwykly plik*/
    else if(S_IFDIR == (S_IFDIR & info.st_mode)) upr[0] = 'd';		/*katalog*/
	else if(S_IFCHR == (S_IFCHR & info.st_mode)) upr[0] = 'c';		/*plik specjalny/urzadzenie*/
	else if(S_IFBLK == (S_IFBLK & info.st_mode)) upr[0] = 'b';		/*plik specjalny przypisany/urzadzenie blokowe*/
	else if(S_IFIFO == (S_IFIFO & info.st_mode)) upr[0] = 'p';      /*lacze nazwane/fifo*/
    else if(S_IFLNK == (S_IFLNK & info.st_mode)) upr[0] = 'l';      /*link/lacze symboliczne*/
    else if(S_IFSOCK == (S_IFSOCK & info.st_mode)) upr[0] = 's';    /*gniazdo/socket*/
    else upr[0] = '-';
    /*Sprawdzanie poszczegolnych uprawnien*/
	uprawnienia(info.st_mode, upr);
	/*Wypisanie uprawnien*/
    printf("%s",upr);
	/*Wypisanie ilosci twardych dowiazan */
	printf("%4d", (int)info.st_nlink);
	/*Wypisanie nazwy uzytkownika */
	printf("%10s", user->pw_name);
	/*Wypisanie grupy uzytkownika */
	printf("%10s", grupy->gr_name);
	/*Wypisanie rozmiaru pliku */
	printf("%7ld ", info.st_size);
	/*Funckja okreslajaca czasy dla poszczegolnych plikow*/
	okresl_czas(czas);
	exit(0);
}
/*Funkcja obslugujaca ls bez parametru*/
void ls(char mydir[])
{
    DIR	*dir_ptr;	/*Zmienna sciezki pliku*/
	struct dirent *direntp;
	struct stat info;   /*Struktura zawierajaca informacje o pliku*/
	int rozmiar;    /*Wielkosc linku*/
	char *link;     /*Zmienna do linkow*/
	if((dir_ptr = opendir(mydir)) == NULL)  /*Otwieranie pliku*/
    {
        fprintf(stderr, "ls: Blad otwarcia sciezki lub odmowa dostepu %s\n", mydir);     /*Obsluga bledu otwarcia pliku*/
        exit(-1);
    }
	else
	{
	    direntp = readdir(dir_ptr);
		while(direntp != NULL)
		{
			if(stat(direntp->d_name, &info) < 0)    /* Pobieramy inforacje o pliku */
            {
				perror("Nie ma takiego pliku/katalogu lub odmowa dostepu");     /*Obsluga bledu sciezki*/
				exit(-1);
			}
			/* Jezeli byl to link to o nim, a nie o pliku na ktory wskazuje */
			if((S_IFLNK & info.st_mode) && lstat(direntp->d_name, &info) < 0)
            {
				perror("Nie ma takiego pliku/katalogu lub odmowa dostepu");     /*Obsluga bledu sciezki*/
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
		closedir(dir_ptr);
	}
	exit(0);
}

/*Funkcja wypisujaca dokladniejsza date*/
void okresl_czas_2(struct tm *czas)
{
	/*Tablica z nazwami miesiaca*/
	char miesiace[12][14]={"stycznia\0","lutego\0","marca\0","kwietnia\0","maja\0","czerwca\0","lipca\0","sierpnia\0","wrzesnia\0","pazdziernika\0","listopada\0","grudnia\0"};

	printf("%2d ", czas->tm_mday);
	printf("%13s", miesiace[czas->tm_mon]);
	printf("%5d roku o ", czas->tm_year + 1900);
	printf("%2d:", czas->tm_hour);
	if(czas->tm_min >= 10)      /*Wyswietlanie minut*/
    {
		printf("%d:", czas->tm_min);
	}
	else                        /*Wyswietlanie minut mniejszych niz 10*/
	{
	    printf("0%d:", czas->tm_min);
	}
	if(czas->tm_sec >= 10)      /*Wyswietlanie sekund*/
    {
        printf("%d", czas->tm_sec);
	}
	else                        /*Wyswietlanie sekund mniejszych niz 10*/
	{
		printf("0%d", czas->tm_sec);
	}
}

/*Funcka do wypisania szczegolowych informacji o konkretnym pliku*/
void dane_lspar(struct stat info, char *nazwa)
{
	struct tm *czas;
	char zawar;
	int zwykly = 0;
	char *link;
	char upr[11];
	FILE *plik;

	printf("Informacje o %s:\n", nazwa);
	printf("Typ pliku:   ");
    if(S_IFREG == (S_IFREG & info.st_mode))       /*Sprawdzenie jaki to typ pliku*/
	{
		printf("zwykly plik\n");
		zwykly = 1;
	}
	else if(S_IFDIR == (S_IFDIR & info.st_mode))
    {
		printf("katalog\n");
	}
	else if(S_IFCHR == (S_IFCHR & info.st_mode))
	{
		printf("urzadzenie\n");
	}
	else if(S_IFBLK == (S_IFBLK & info.st_mode))
	{
		printf("urzadzenie blokowe\n");
	}
	else if(S_IFIFO == (S_IFIFO & info.st_mode))
	{
		printf("fifo\n");
	}
	else if(S_IFLNK == (S_IFLNK & info.st_mode))
	{
		printf("link symboliczny\n");
	}
	else if(S_IFSOCK == (S_IFSOCK & info.st_mode))
	{
		printf("socket\n");
	}
	else
	{
		printf("typ nieokreslony\n");
	}

	printf("Sciezka:     ");        /*Sprawdzenie sciezki do pliku*/
	if(!((S_IFLNK & info.st_mode) == S_IFLNK))     /*Jezeli to nie link*/
    {
		link = realpath(nazwa, NULL);
		printf("%s\n", link);
	}
	else    /*Jezeli to link*/
	{
		link = realpath(".", NULL);
		printf("%s/%s\n", link, nazwa);
		printf("Wskazuje na: ");
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

	if(zwykly)   /*Jezeli byl to zwykly plik wypisujemy 80 pierwszych znakow*/
    {
		printf("Poczatek zawartosci:\n");
		if((plik = fopen(nazwa,"r")) == NULL)
		{
			perror("Nie udalo sie otworzyc pliku");     /*Obsluga bledu otwarcia pliku*/
			exit(-1);
		}
		for(int i = 0; i < 80; ++i)
		{
			fscanf(plik, "%c" , &zawar);            /*Wypisanie zawartosci pliku*/
			printf("%c", zawar);
		}
		printf("\n");
		fclose(plik);           /*Zamkniecie pliku*/
	}
	exit(0);
}

void lspar(char mydir[], struct stat info)
{
    if(stat(mydir, &info) < 0)  /*Pobieramy inforacje o pliku*/
    {
        perror("Nie ma takiego pliku/katalogu lub odmowa dostepu"); /*Obsluga bledu sciezki*/
        exit(-1);
    }
    if((S_IFLNK & info.st_mode) && lstat(mydir, &info) < 0) /*Jezeli byl to link to o nim, a nie o pliku na ktory wskazuje*/
    {
        perror("Nie ma takiego pliku/katalogu lub odmowa dostepu"); /*Obsluga bledu sciezki*/
        exit(-1);
    }
    dane_lspar(info, mydir);    /*Wywolanie funkcji wypisujacej dane o konkretnym pliku*/
    exit(0);
}

int main(int argc, char *argv[])
{
    struct stat info;   /*Struktura zwracajaca informacje o pliku*/
    if(argc == 1)
    {
        ls(".");    /*Funkcja bez argumentu*/
    }
    else if(argc == 2)
    {
        lspar(argv[1],info);   /*Funkcja z argumentem*/
    }
    else
    {
        printf("Za duzo argumentow");   /*Obsluga bledu ilosci argumentow*/
        return -1;
    }
    return 0;   /*Program zakonczyl sie powodzeniem*/
}

