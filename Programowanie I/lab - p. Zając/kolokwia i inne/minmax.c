#include <stdio.h>

int main(int argc, char **argv)
{
	int min;
	int max;
	int a, i;
	if(argc>1){
		for(i = 1; i < argc; i++){
			sscanf(argv[i], "%d", &a);
			if(a > max) max = a;
			if(a < min) min = a; 
		}
		printf("Minimum %d, maksimum %d", min, max);
	}
	else{
		printf("Bledna liczba argumnetow");
		return -1;
	}
	
	return 0;
}

