#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#define MAX 1000000
int int_compare(void *x,void *y)
{
  int m,n;
  m = *((int*)x);
  n = *((int*)y);
  if(m==n) return 0;
  return (m>n)?1:-1;
  
}
void swap(void *a, void *b, int size)
{
  void *temp = (void*)malloc(size*sizeof(char));
  void *result1 = a;
  void *result2 = b;
  for(int i = 0; i<size; i++)
    {
      *((char*)temp+i) = *((char*)result1+i);
      *((char*)result1+i) = *((char*)result2+i);
      *((char*)result2+i) = *((char*)temp+i);
    }
}
void exchn(void *buf, int size, int i, int j)
{
  void *a, *b;
  a = (char*)buf + (i*size);
  b = (char*)buf + (j*size);
  swap(a,b,size);
}
void way3(void *a, int size, int l, int r, int (*compare)(void*, void*))
{
  if(r <= l) return;
  int i = l-1, j = r;
  int p = l-1, q = r;
  while(1)
    {
      while(compare((char*)a+ (++i)*size, (char*)a+ r*size)<0);
      while(compare((char*)a+ r*size, (char*)a+ (--j)*size)<0) if(j==l) break;
      if(i >= j) break;
      exchn(a, size, i, j);
      if(compare((char*)a+ i*size, (char*)a+ r*size)==0) exchn(a, size, ++p,i);
      if(compare((char*)a+ j*size, (char*)a+ r*size)==0) exchn(a, size, --q,j);
    }
  exchn(a, size, i, r);
  j = i-1;
  i = i+1;
  for(int k = l ; k <= p; k++) exchn(a, size, k, j--);
  for(int k = r-1 ; k >= q; k--) exchn(a, size, k, i++);
  way3(a, size, l, j, compare);
  way3(a, size, i, r, compare);
}
int main()
{
  int n=100;
  int l=0, r=n-1;
  int *A = (int*)malloc(n*sizeof(int));
  int a,i;
  for(i=0; i<n; i++)
    {
      a=rand()%100;
      A[i] = a;
    }
  clock_t start_t, end_t;
  volatile long unsigned t;
  start_t = clock();
  way3(A,sizeof(int),l,r,int_compare);
  
   end_t = clock();
   printf("3 way partitioning run in %f seconds.\n",(double)(end_t - start_t) / CLOCKS_PER_SEC );
  for(i=0; i<n; i++)
    {
      printf("%d  ",A[i]);
    }
    printf("\n");
   free(A);
 return 0;
}
 
