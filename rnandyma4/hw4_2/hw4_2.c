#include <omp.h>
#include <stdio.h>
#include <stdlib.h>

int add(int n)
{int sum = 0;
for(int i =1;i<=n;i++)
sum = sum+=i;
return sum;
}
int main (int argc, char *argv[]) {
int sum_critical;
int sum_master;
int sum_single;
  #pragma omp parallel   
  {
	#pragma omp critical
	{
	sum_critical = add(omp_get_thread_num());
	printf("the sum insde the CRITICAL block is %d\n",sum_critical);
//	b++;
	}
	#pragma omp single
        {
	sum_single = add(omp_get_thread_num());
	//a++;
         printf("the sum insde the SINGLE block is %d\n",sum_single);

        }
	
	 #pragma omp master
        {
        //c++;
        sum_master = add(omp_get_thread_num());
        printf("the sum inside the MASTER block is %d\n",sum_master);
        }

      
  }
      //  printf("the value of a and b are  %d and %d and  %d\n",a,b,c);
   
}

