#include <stdio.h>
#include <math.h>

int pobierzioblicz(){
	int a,b,c;
	printf("podaj a=");
	scanf("%d", &a);
	printf("podaj b=");
	scanf("%d", &b);
	c=pow(a,b);
	return c;
}

int main(int argc, char **argv)
{
	
	printf("%d/n", pobierzioblicz());
	return 0;
}

