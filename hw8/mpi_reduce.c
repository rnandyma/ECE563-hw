/*  C  */

#include <stdio.h>
#include <mpi.h>
#include <stdlib.h>

int main (int argc, char *argv[]) {

    /* MPI Parameters */
    int pid;
    int numP;
     int N;
     N = atoi(argv[1]);
     //printf("the value of N is %d\n", N);
     int a[N];
     //int a_per_proc[N/16];
     int *a_per_proc;
     int *res_per_proc;
    //char name[MPI_MAX_PROCESSOR_NAME];
    int LB = pid*N/16;
    int UB = ((pid+1)*N/16)-1;
    int size  = UB-LB+1;
    int result;
    int sum;
    double time1, time2;
    /* All ranks initiate the message-passing environment. */
    /* Each rank obtains information about itself and its environment. */
    MPI_Init(&argc, &argv);                 /* start MPI           */
    MPI_Comm_size(MPI_COMM_WORLD, &numP);   /* get number of processes */
    MPI_Comm_rank(MPI_COMM_WORLD, &pid);   /* get pid           */
    a_per_proc = malloc(sizeof(int)*(UB-LB+1));
    res_per_proc = malloc(sizeof(int)*(UB-LB+1));
    //MPI_Get_processor_name(name, &len);     /* get run-host name   */

    //printf("Runhost:%s   Rank:%d of %d ranks   hello, world\n", name,rank,size);
    if(a_per_proc == NULL)
printf("ERROR: memory not allocated by malloc");
    for(int i = 0; i<size; i++)
	a_per_proc[i] = 1;
    
    MPI_Barrier(MPI_COMM_WORLD);
    time2 = MPI_Wtime();
   MPI_Barrier(MPI_COMM_WORLD);   
 for(int l=0;l<1000;l++)
{ sum = 0;
  result = 0;
  MPI_Reduce(a_per_proc,res_per_proc,size, MPI_INT, MPI_SUM, 0,MPI_COMM_WORLD);
    if(pid == 0){
	       for(int j = 0; j<size; j++)
         result = result+res_per_proc[j];
         sum = result;}}
MPI_Barrier(MPI_COMM_WORLD);   
   time1 = (MPI_Wtime() - time2)/1000;
	//printf("the sum is %d\n", sum);}
   
    //printf("the sum is %d\n", sum);
   if(pid == 0) printf("(MPI_Reduce) Time Elapsed (averaged over 1000 runs) for %d size : %f\n", N, time1);
   if(pid == 0) printf("pid : %02d,   sum : %03d\n", pid, sum);


    MPI_Finalize();                         /* terminate MPI       */
    return 0;
}
