#include <stdio.h>

int silnia(int a){
	if(a == 0) return 1;
	if(a == 1) return 1;
	else 
		return silnia(a - 1) * a; 
}

int main(int argc, char **argv)
{
	int a = 0;
/*(if(argc != 2){
		printf("Bledna liczba argumentow\n");
		return -1;
	}
	sscanf(argv[1], "%d", &a); */
	while(silnia(a + 1) < silnia(a))
	{
		a++;
		printf("%d", a);
	
	}
	
	return 0;
}

