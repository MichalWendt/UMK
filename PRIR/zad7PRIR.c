#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <omp.h>

#define N 8
#define MIN(a,b) (((a)<(b))?(a):(b))

int I[N][N] = {0};

int main(int argc, char *argv[])
{
    int nthreads;
    int i, j, k;

    for (i = 0; i < N; i++)
    {
        for (j = 0; j < N; j++)
        {
            if(i != j)
            {
                if(i==j){I[i][j]=0;continue;}
                I[i][j]=(rand()/100000000);
                if(I[i][j]>9)I[i][j]=1000000;
            }
        }
    }

    for(i=0;i<N;i++)
    {
		for(j=0;j<N;j++)printf("\t%d",I[i][j]);
		printf("\n");
	}
	printf("\n");
/* TUTAJ SKONCZYLEM*/

    for (k = 0; k < N; k++)
    {
        int * dm = I[k];
        for (i = 0; i < N; i++)
        {
            int * ds = I[i];
            for (j = 0; j < N; j++)
            {
                ds[j] = MIN(ds[j],ds[k] + dm[j]);
            }
        }
    }

    for(nthreads=1; nthreads <= 10; nthreads++)
    {
        omp_set_num_threads(nthreads);

        #pragma omp parallel shared(I)
        for (k = 0; k < N; k++)
        {
            int * dm = I[k];
            #pragma omp parallel for private(i, j) schedule(dynamic)
            for (i = 0; i < N; i++)
            {
                int * ds = I[i];
                for (j = 0; j < N; j++)
                {
                    ds[j] = MIN(ds[j],ds[k] + dm[j]);
                }
            }
        }
    }

   for(k=0;k<N;k++){
        #pragma omp parallel for private(j)
        for(i=0;i<N;i++)
            for(j=0;j<N;j++)
                J[j]=MIN(I[j],I[k]+I[k][j]);
        #pragma omp parallel for
        for(i=0;i<N;i++)memcpy(&(I[0]),&(J[0]),N*sizeof(int));
    }
  return 0;
}
