#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char **argv)
{
	int deskr;
	int i;
	char tmp[255];
	int linie  = 0;
	deskr = open("dane.txt", O_RDONLY);

	while((read(deskr, tmp, 255))!=0){
		for(i = 0;  i < strlen(tmp); i++){
			if(tmp[i] == '\n'){
				linie++;
			}
		}
		
	}
	printf("Liczba lini w pliku %d", linie);
	
	close(deskr);
	return 0;
}

