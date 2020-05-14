#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
void doWork(int t) {
   sleep(t);
}

int* initWork(int n) {
   int i;
   double r;
   int* wA = (int *) malloc(sizeof(int)*n);   
   for (i = 0; i < n; i++) {
      wA[i] = rand( )%2*i/(n/10);
   }
   return wA;
}

int main (int argc, char *argv[]) {
   int i;
   int *w = initWork(100);
   double start_time = 0.0; double end_time = 0.0;
   start_time = omp_get_wtime();
#pragma omp parallel for schedule(dynamic,1)
  for (i = 0; i < 100; i+=1) {
      doWork(w[i]);
      //printf("w[i] has the value= %d, tid=%d\n",w[i], omp_get_thread_num());
   }
//printf("the number of threads are %d\n", omp_get_num_threads());
    end_time = omp_get_wtime();
    printf("the computed time is for dyn %lf\n", end_time - start_time);
}

