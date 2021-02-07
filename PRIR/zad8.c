#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <time.h>
#include <string.h>
#include <mpi.h>
#include <omp.h>

#define N 8
#define NUM_THREADS 4
#define MIN(a,b) (((a)<(b))?(a):(b))

int main(int argc,char **argv){
	int i,j,k,size,rank,step;
	int *K;
	int *I_loc,*J_loc;
	int* I;

	MPI_Init(&argc,&argv);
	MPI_Comm_rank(MPI_COMM_WORLD,&rank);
    MPI_Comm_size(MPI_COMM_WORLD,&size);
	step=N/size;

	K = malloc(N*sizeof(int));
	I_loc = malloc(step*N*sizeof(int));
	J_loc = malloc(step*N*sizeof(int));

	if(rank==0)
    {
		I = malloc(N*N*sizeof(int));
        srand((unsigned int)time((time_t*)NULL));

		for(i=0;i<N;i++)for(j=0;j<N;j++)
		{
            if(i==j){*(I+i*N+j)=0;continue;}
            *(I+i*N+j)=(rand()/100000000);
            if(*(I+i*N+j)>9)*(I+i*N+j)=1000000;
		}
		for(i=0;i<N;i++)
        {
			for(j=0;j<N;j++)printf("\t%d",*(I+i*N+j));
			printf("\n");
		}
        printf("\n");
	}

	MPI_Scatter(I,step*N,MPI_INT,I_loc,step*N,MPI_INT,0,MPI_COMM_WORLD);

    for(k=0;k<N;k++)
    {
        //#pragma omp parallel num_threads(NUM_THREADS) private(i,j) firstprivate(k)
		if(rank==(k/step))memcpy(K,I_loc+(k%step)*N,sizeof(int)*N);
		MPI_Bcast(K,N,MPI_INT,k/step,MPI_COMM_WORLD);

		#pragma omp for private(j)//schedule(dynamic)
        for(i=0;i<step;i++)
            for(j=0;j<N;j++)*(J_loc+i*N+j)=MIN(*(I_loc+i*N+j),*(I_loc+i*N+k)+*(K+j));

        #pragma omp for //schedule(dynamic)
        for(i=0;i<step;i++)memcpy(I_loc+i*N,J_loc+i*N,N*sizeof(int));
	}

	MPI_Gather(I_loc,step*N,MPI_INT,I,step*N,MPI_INT,0,MPI_COMM_WORLD);

	if(rank==0)
	{
		for(i=0;i<N;i++)
		{
			for(j=0;j<N;j++)printf("\t%d",*(I+i*N+j));
			printf("\n");
		}
		free(I);
	}

	free(I_loc);
	free(J_loc);
	free(K);
	MPI_Finalize();
	return EXIT_SUCCESS;
}

