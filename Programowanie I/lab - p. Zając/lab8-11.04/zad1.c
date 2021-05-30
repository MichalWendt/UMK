#include <stdio.h>

int silnia_rek(int num){
	if(num == 0) return 1;
	if(num == 1) return 1;
	else
		return num*(silnia_rek(num-1));
}

int silnia_iter(int num){
	if(num == 0) return 1;
	else{
		int i;
		int suma = num;
		for(i = 1; i < num; i++){
			suma = suma * i;
		}
		return suma;
	}
}

int main(int argc, char **argv)
{
	int num;
	int silnia1;
	int silnia2;
	sscanf(argv[1], "%d", &num);
	
	silnia1 = silnia_rek(num);
	silnia2 = silnia_iter(num);
	
	printf("Rekurencyjnie: %d", silnia1);
	printf("Iteradcyjnie: %d", silnia2); 
	
	return 0;
}

