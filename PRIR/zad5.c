#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>
#include <unistd.h>

#define N 100

int main(int argc,char **argv){
    float *A,*B,*Arev,min;
	int rank,i,p,q;
	srand(time(NULL));
	MPI_Init(&argc,&argv);
	MPI_Comm_rank(MPI_COMM_WORLD,&rank);
	MPI_Comm_size(MPI_COMM_WORLD,&p);
    /*dla N niepodzielnego przez p
    r=N%(p);
    if(r==0)q=N/p;
    else q=(N+p-r)/(p);*/
    q=N/p;
    Arev=malloc(q*sizeof(float));
    if(rank==0){
		A=calloc(q*p,sizeof(float));
		B=calloc(p,sizeof(float));
		for(i=0;i<N;i++)
		{
		    A[i]=(float)rand()%100;
        }
	}

	MPI_Scatter(A,q,MPI_FLOAT,Arev,q,MPI_FLOAT,0,MPI_COMM_WORLD);
	min = Arev[0];
	for(i=0;i<q;i++)
    {
        if(Arev[i] < min)
        min = Arev[i];
    }
    MPI_Gather(&min,1,MPI_FLOAT,B,1,MPI_FLOAT,0,MPI_COMM_WORLD);
    if(rank==0){
        min = B[0];
        for(i=1;i<p;i++)
		{
		    if(B[i] < min)
		    {
		        min = B[i];
		    }
        }
		free(A);
		free(B);
        printf("min = %f\n",min);
	}
	free(Arev);
    MPI_Finalize();
}
