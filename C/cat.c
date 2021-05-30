#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
    int plik, kopia, n;
    char bufor[100];

    plik  = open(argv[1], O_RDONLY);
    kopia = open(argv[2], O_CREAT| O_WRONLY | O_TRUNC, S_IRWXU);

    while ((n = read(plik, bufor, sizeof(bufor))) != 0)
        write(kopia, bufor, n);

    close(plik);
    close(kopia);

}
