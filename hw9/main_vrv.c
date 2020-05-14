#include <stdlib.h>
#include <stdio.h>
//#include <omp.h>
#include <mpi.h>
struct node {
   float val;
   int node_num;
   struct node* l;
   struct node* r;
} nodeT;

#define MAXLEVEL 18


struct node* build_s(int level) {

   if (level < MAXLEVEL) {
      struct node* p = (struct node*) malloc(sizeof(nodeT));
      p->val = (float)rand()/RAND_MAX;
      p->node_num = level;
      //printf("the level is %d\n", p->node_num);
      //p->val = 1;

      p->l = build_s(level+1);
      p->r = build_s(level+1);

      return p;
   } else {
      return NULL;
  }
}

int traverse_reverse(struct node* root, int depth)
{
   int lcount;
   int rcount;

   lcount = 0;
   rcount = 0;
   //printf("in the transverse_reverse fn the level of the root is %d\n", root->node_num);
	if(depth == 0) return 0;

   if(root->l) lcount = traverse_reverse(root->l, depth-1);

   if(root->r) rcount = traverse_reverse(root->r, depth-1);

  
	if(root->val < 0.50)
	{
		return (lcount + rcount + 1);
	}
	else
	{
		return (lcount + rcount);
   }
}
	
struct node* findSubroot(struct node* root, int depth, int p)
{
	struct node* subroot = root;
	int mid = depth/2;
     

	if(depth == 1)
	{
		
		return subroot;
	}

	if( mid > p)
	{
		
		subroot = findSubroot(root->l, (depth/2), p);
	}
	else
	{
		
		if(p >= mid ) p = p - mid;
		subroot = findSubroot(root->r, (depth/2), p);
	}
	
	return subroot;
}



int main (int argc, char *argv[])
{
   int p, numP, i, j;
   double time1, time2;
	int rc, depth, sum;

   struct node* root1 = NULL;
   struct node* root2 = NULL;

	MPI_Init(&argc, &argv);

	MPI_Comm_rank(MPI_COMM_WORLD, &p);
	MPI_Comm_size(MPI_COMM_WORLD, &numP);

	i = 0;

	
   // Initialize the random seed.
   srand(2);

	// Create the subtree locally (sequential). 
	root1 = build_s(0);

	if(p == 10)
	{
		time2 = MPI_Wtime();
		j = traverse_reverse(root1, MAXLEVEL);
		time2 = MPI_Wtime() - time2;
		
	}

   
	MPI_Barrier(MPI_COMM_WORLD);

	// Find the item count (value < 0.50) recursively.
	root2 = findSubroot(root1, 16, p);
        time1 = MPI_Wtime();
	i = traverse_reverse(root2, MAXLEVEL-4);
        time1 = MPI_Wtime() - time1;
	if(p == 10) i = i + traverse_reverse(root1, 4);
        
   if(p == 10) MPI_Reduce(MPI_IN_PLACE, &i, 1, MPI_INT, MPI_SUM, 10, MPI_COMM_WORLD);
	else MPI_Reduce(&i, NULL, 1, MPI_INT, MPI_SUM, 10, MPI_COMM_WORLD);

	MPI_Barrier(MPI_COMM_WORLD);
	
   if(p == 10) printf("\n%02d : Elapsed Time (COUNT MPI_Reduce) = %0f\n", p, time1);
   if(p == 10) printf("%02d : MPI_Reduce (subtrees at depth==5) COUNT(elements < 0.50) = %d\n", p, i);

	if(p == 10) printf("\n%02d : SPEEDUP MPI vs OpenMP %0.2f\n", p, 0.000227/time1);

	MPI_Barrier(MPI_COMM_WORLD);
	MPI_Finalize();

   return 0;
}
