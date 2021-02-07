#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>

int N = 8;
int i;
float minimum;
float *A;


pthread_mutex_t mutex=PTHREAD_MUTEX_INITIALIZER;

void* mini(void* B)
{
    int *iter = (int*)B;
    float *min = malloc(sizeof(float));
    *min = A[*iter];

    for (i=1+*iter ; i< N/4 + *iter ; i++)
    {
        if(A[i] < *min)
        {
            *min = A[i];
        }
    }

    pthread_mutex_lock(&mutex);
	if(minimum > *min){
		minimum = *min;
	}
	sleep(1);
	pthread_mutex_unlock(&mutex);
	return NULL;
}

int main()
{
	pthread_t thread[4];
	int pom[4];
	A = malloc(sizeof(float)*N);
    printf("Zawartosc tablicy to:\n");
    srand(time(NULL));
    for(i = 0; i < N; ++i)
    {
        *(A + i) = ((float)(rand()%50 / 3) + 1)*1.13232;
        printf("%f, ",*(A + i));
    }
    minimum = *(A + 0);
    for(i=0;i<4;i++)
    {
        pom[i]=i*(N/4);
    }
    float wynik;
	float wynikowa[4];
	for(i=0;i<4;i++)
    {
        pthread_create(&thread[i],NULL,&mini,(void*)&pom[i]);
    }
    for(i=0;i<4;i++)
    {
        pthread_join(thread[i], NULL);
    }
    pthread_mutex_destroy(&mutex);

    printf("Minimum z tablicy to: %f\n",minimum);
    return EXIT_SUCCESS;
}
