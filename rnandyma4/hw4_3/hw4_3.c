#include <omp.h>
#include <stdio.h>
#include <stdlib.h>

int sum_of_n_number (int n)
{
int result;
for (int i=1; i<=n; i++)
{
result +=i;
}
return result;
}

long int product_of_n_number(int n)
{
long int product;
for(int i=1; i<=n;i++)
{
product*=i;
}
printf("the value of prooduct is %ld\n", product);
return product;
}
int main(int argc, char *argv[])
{
int n = 20;
int v;
long int w;
#pragma omp parallel sections
{
#pragma omp section
{
v=sum_of_n_number(n);
printf("the thread id for this section 1 is %d\n",omp_get_thread_num());
printf("the sum is %d\n",v);
}
#pragma omp section
{
w=product_of_n_number(n);
printf("the thread id for this section 2 is %d\n",omp_get_thread_num());
printf("the product is %ld\n",w);
}
}
}

