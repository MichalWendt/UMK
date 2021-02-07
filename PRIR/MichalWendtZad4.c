#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main ()
{
    int i;
    long iloczyn = 1;
    float N;
    printf("prosze podac N: ");
    scanf("%f",&N);
    #pragma omp for reduction(*: iloczyn)
    for (i=1; i <= N; i++)
    {
        iloczyn = iloczyn * i;
    }
    printf("%f! = %ld\n",N,iloczyn);
    return EXIT_SUCCESS;
}
