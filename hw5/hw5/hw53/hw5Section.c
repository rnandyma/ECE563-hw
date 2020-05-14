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
#pragma omp parallel sections
{
#pragma omp section
{
for(int i=0; i<=4;i++)
doWork(w[i]);
}
#pragma omp section
{
for(int i=5; i<=9;i++)
doWork(w[i]);
}
#pragma omp section
{
for(int i=10; i<=14;i++)
doWork(w[i]);
}
#pragma omp section
{
for(int i=15; i<=19;i++)
doWork(w[i]);
}
#pragma omp section
{
for(int i=20; i<=24;i++)
doWork(w[i]);
}
#pragma omp section
{
for(int i=25; i<=29;i++)
doWork(w[i]);
}
#pragma omp section
{
for(int i=30; i<=34;i++)
doWork(w[i]);
}
#pragma omp section
{
for(int i=35; i<=39;i++)
doWork(w[i]);
}
#pragma omp section
{
for(int i=40; i<=44;i++)
doWork(w[i]);
}
#pragma omp section
{
for(int i=45; i<50;i++)
doWork(w[i]);
}
#pragma omp section
{
for(int i=50; i<55;i++)
doWork(w[i]);
}
#pragma omp section
{
for(int i=55; i<60;i++)
doWork(w[i]);
}
#pragma omp section
{
for(int i=60; i<65;i++)
doWork(w[i]);
}
#pragma omp section
{
for(int i=65; i<70;i++)
doWork(w[i]);
}
#pragma omp section
{
for(int i=70; i<75;i++)
doWork(w[i]);
}
#pragma omp section
{
for(int i=75; i<80;i++)
doWork(w[i]);
}
#pragma omp section
{
for(int i=80; i<85;i++)
doWork(w[i]);
}
#pragma omp section
{
for(int i=85; i<90;i++)
doWork(w[i]);
}
#pragma omp section
{
for(int i=90; i<95;i++)
doWork(w[i]);
}
#pragma omp section
{
for(int i=95; i<100;i++)
doWork(w[i]);
}


}
end = omp_get_wtime();
printf("the time is %lf\n", end - start);
}




