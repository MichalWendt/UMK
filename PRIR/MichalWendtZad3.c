#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int N = 8;
int i;

int main()
{
    float *a = malloc(sizeof(float)*N);
    float *b = malloc(sizeof(float)*N);
    float *c = malloc(sizeof(float)*N);
    printf("Tablica a: ");
    for(i = 0; i < N; ++i)
    {
        *(a + i) = ((float)(rand()%50 / 3) + 1)*1.13232;
        printf("%f, ",*(a + i));
    }
    printf("\nTablica b: ");
    for(i = 0; i < N; ++i)
    {
        *(b + i) = ((float)(rand()%50 / 3) + 1)*1.13232;
        printf("%f, ",*(b + i));
    }
    #pragma omp for
    for(i = 0; i < N; ++i)
    {
        *(c + i) = *(a + i) * *(b + i);
    }
    #pragma omp barrier
    int p = N/2;
    while(p > 0)
    {
    #pragma omp for
        for(i = 0; i < p-1; ++i)
        {
            *(c + i) = *(c + i) + *(c + i + p);
        }
        p = p/2;
    }
    #pragma omp barrier
    printf("\nWynik to: %f\n",*(c + 0));
    return EXIT_SUCCESS;
}
