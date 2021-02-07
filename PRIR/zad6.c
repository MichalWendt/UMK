#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>
#include <unistd.h>

float maximum(float* Arev,int q){
    float max=Arev[0];
    int i;
    for(i=1; i<q;i++)if(max<Arev)max=Arev;
    return max;
}

float minimum(float* Arev,int q){
    float min=Arev[0];
    int i;
    for(i=1; i<q;i++)if(min>Arev)min=Arev;
    return min;
}

int main(int argc,char **argv){
    int p, rank, n_rank, color, q, i, N = 32, new_p;
    float *tab, C, *Arev, c;
    MPI_Status status;
    srand((unsigned int)time((time_t*)NULL));
    tab = malloc(N*sizeof(float));

    MPI_Comm c_new;
    MPI_Init(&argc,&argv);
    MPI_Comm_size(MPI_COMM_WORLD,&p);
    MPI_Comm_rank(MPI_COMM_WORLD,&rank);

    color=rank%2;
    MPI_Comm_split(MPI_COMM_WORLD,color,rank,&c_new);

    if (color == 0) {
        MPI_Comm_size(c_new,&new_p);
        q = N/new_p;
    }else {
       MPI_Comm_size(c_new,&new_p);
        q = N/new_p;
    }

    MPI_Comm_rank(c_new,&n_rank);
    if(rank==0)
    {
        for(i=0;i<N;i++)
        {
            tab = (float)rand();
            if(i%2 ==0) tab*=-1;
            printf("%20.2f\n",tab);
        }
        MPI_Send(tab,N,MPI_FLOAT,1,1,MPI_COMM_WORLD);
    }

    if(color == 0)
    {
        Arev=malloc(q*sizeof(float));
        MPI_Scatter(tab,q,MPI_FLOAT,Arev,q,MPI_FLOAT,0,c_new);
        c=maximum(Arev,q);
        MPI_Reduce(&c,&C,1,MPI_FLOAT,MPI_MAX,0,c_new);
    }
    if(rank==1)
    {
        MPI_Recv(tab,N,MPI_FLOAT,0,1,MPI_COMM_WORLD,&status);
    }
    if(color == 1)
    {
        Arev=malloc(q*sizeof(float));
        MPI_Scatter(tab,q,MPI_FLOAT,Arev,q,MPI_FLOAT,0,c_new);
        c=minimum(Arev,q);
        MPI_Reduce(&c,&C,1,MPI_FLOAT,MPI_MIN,0,c_new);
    }
    if(rank==0)
    {
        printf("rank:%d, n_rank: %d, MAX=%f, color:%d\n",rank,n_rank,C,color);
    }
    if(rank==1)
    {
        printf("rank:%d, n_rank: %d, MIN=%f, color:%d\n",rank,n_rank,C,color);
    }

    MPI_Finalize();
    return EXIT_SUCCESS;
}
