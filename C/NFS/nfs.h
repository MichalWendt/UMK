struct rezultaty{
	int nazwa_pliku;
	int czy_pusty;
};
struct polaczenie{
	int tryb;
	char nazwa[4098];
};
struct pobieranie{
	int nazwa_pliku;
	int pozycja;
	int przesun;
};
struct zwracanie{
	int liczba;
	char buf[4098];
};
struct wysylanie{
	int nazwa_pliku;
	char buf[4098];
};
program NFS{
	version NFS_1{
		rezultaty start(polaczenie) = 1;
		zwracanie pull(pobieranie) = 2;
		int push(wysylanie) = 3;
		int koniec(int) = 4;
	} = 1;
} = 0x2d24ffa2;
