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
      wA[i] = (int) rand( )%2*i/(n/10);
   }
   return wA;
}

int main (int argc, char *argv[]) {
int *w = initWork(100);
//int i;
double start, end;
start = omp_get_wtime();
for(int j =0;j<100;j++)
{
doWork(w[j]);
}
end = omp_get_wtime();
printf("the time is %lf\n", end - start);
}




