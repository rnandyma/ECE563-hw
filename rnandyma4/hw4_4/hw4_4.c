#include  <stdio.h>
#include  <omp.h>

int main(int argc, char *argv[]) {
int n = 0;
int m = 0;
#pragma omp parallel
{
for(int i = 0; i<25; i++)
{
//printf("the thread number is %d\n", omp_get_thread_num());
#pragma omp critical
n++;
//printf("the number of loop interation = %d\n",n++);
}
}
printf ("the number of loop iteration with just parallel is =%d\n",n);

#pragma omp parallel for
for(int j = 0; j<25; j++)
{m++;
//printf("the number of the loop interation = %d\n",m++);
}
printf("the number of the loop iteration = %d\n",m);
return 0;
}
