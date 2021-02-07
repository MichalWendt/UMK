#include <pthread.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int N = 8;
int i;

void* mini(void* B)
{
    float *tab = (float*)B;
    float *min = malloc(sizeof(float));
    *min = tab[0];

    for (i=1 ; i< N/4 ; i++)
    {
        if(tab[i] < *min)
        {
            *min = tab[i];
        }
    }
    return min;
}

int main()
{
    float *A = malloc(sizeof(float)*N);
    printf("Zawartosc tablicy to:\n");
    srand(time(NULL));
    for(i = 0; i < N; ++i)
    {
        *(A + i) = ((float)(rand()%50 / 3))*1.13232;
        printf("%f, ",*(A + i));
    }
    float wynik;
	pthread_t thread1,thread2,thread3,thread4;
	float wynikowa[4];
	void *pomwynikowa1,*pomwynikowa2,*pomwynikowa3,*pomwynikowa4;
	float *pom = A, *pom2 = pom + (N / 4), *pom3 = pom + 2*(N / 4), *pom4 = pom + 3*(N / 4);

    pthread_create(&thread1, NULL, &mini, (void*)(pom));
    pthread_create(&thread2, NULL, &mini, (void*)(pom2));
    pthread_create(&thread3, NULL, &mini, (void*)(pom3));
    pthread_create(&thread4, NULL, &mini, (void*)(pom4));

    pthread_join(thread1, &pomwynikowa1);
    pthread_join(thread2, &pomwynikowa2);
    pthread_join(thread3, &pomwynikowa3);
    pthread_join(thread4, &pomwynikowa4);

    wynikowa[0] = *(float*)pomwynikowa1;
    wynikowa[1] = *(float*)pomwynikowa2;
    wynikowa[2] = *(float*)pomwynikowa3;
    wynikowa[3] = *(float*)pomwynikowa4;

    wynik = wynikowa[0];
    for (i=1 ; i< 4 ; i++)
    {
        if(wynikowa[i] < wynik)
        {
            wynik = wynikowa[i];
        }
    }
    printf("minimum z tablicy to: %f\n",wynik);
	return EXIT_SUCCESS;
}
