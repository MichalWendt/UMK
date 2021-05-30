#include <stdio.h>
#include <string.h>

int main(int argc, char **argv)
{
	char a[100];
	int n;
	int i;
	int wynik = 0;
	int m = 0;
	printf("Podaj liczbe: ");
	scanf("%s" , a);
	n = strlen(a);
	for( i = n ; i > 0 ; i--)
	{
		if(a[i - 1] == '1')
		{
			wynik = wynik | (1 << m); 
		}
		m++;
	}
	printf("%d\n" , wynik);
	printf("%d\n" , wynik<<3);
	printf("%d\n" , wynik>>2);
	return 0;
}

