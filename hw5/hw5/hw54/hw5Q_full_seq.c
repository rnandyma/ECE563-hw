#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

typedef struct Q {
   int* q;
   int pos;
   int size;
} Q;

struct Q* initQ(int n) {
   int i;
   struct Q *newQ = (struct Q *) malloc(sizeof(Q));   
   newQ->q = (int*) malloc(sizeof(int)*n);
   newQ->pos = -1;
   newQ->size = n-1;
   return newQ;
}

void putWork(struct Q* workQ) {
   if (workQ->pos < (workQ->size)) {
      workQ->pos++;
      workQ->q[workQ->pos] = (int) (rand( )%2*(workQ->pos/1000));
   } else printf("ERROR: attempt to add Q element%d\n", workQ->pos+1);
}

int getWork(struct Q* workQ) {
   if (workQ->pos > -1) {
      int w = workQ->q[workQ->pos];
      workQ->pos--;
      return w;
   } else printf("ERROR: attempt to get work from empty Q%d\n", workQ->pos);
}
 void doWork(int t)
{
sleep(t);
}

int main(int argc, char*argv[])
{double start, end;
Q *workQ = initQ(100); //initializes the work queue
for(int j=0;j<100;j++)
{
putWork(workQ);
}

printf("the time of computation in series is %lf\n", end-start);

int work_value;
start = omp_get_wtime();
for(int i=0; i<100; i++)
{work_value = getWork(workQ);
doWork(work_value);
}
end = omp_get_wtime();
printf("the time of computation in series is %lf\n", end-start);
return 0;
}
