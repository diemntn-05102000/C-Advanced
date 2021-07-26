#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#define MAX 1000000
void swap(int a,int b)
{
  int tmp=a;
  a=b;
  b=tmp;
}
void way2(int list[],int left,int right)
{
  int pivot, i, j;
  int temp;
  if(left<right)
    {
      i = left;
      j = right+1;
      pivot = list[left];
      do
	{
	  do i++; while (list[i]<pivot);
	  do j--; while (list[j]>pivot);
	  if(i<j)
	    {
	      temp=list[i];
	      list[i]=list[j];
	      list[j]=temp;
	    } 
	} while(i<j);
        temp=list[left];
        list[left]=list[j];
        list[j]=temp;
	way2(list, left,j-1);
	way2(list,j+1,right);
    }
}
void way3(int a[], int l, int r)
{
  if(r <= l) return;
  int i = l-1, j = r;
  int p = l-1, q = r;
  while(1)
    {
      while(a[++i] < a[r]);
      while(a[r] < a[--j]) if(j==l) break;
      if(i >= j) break;
      swap(a[i],a[j]);
      if(a[i] == a[r]) swap(a[++p],i);
      if(a[j] == a[r]) swap(a[--q],j);

    }
  swap(a[i],a[r]);
  j = i-1;
  i = i+1;
  for(int k = 1 ; k <= p; k++) swap(a[k],a[j--]);
  for(int k = r-1 ; k >= p; k--) swap(a[k],a[i++]);
  way3(a, l, j);
  way3(a, i, r);
  
}
int main()
{
  int l=0, r=MAX-1;
  int a[MAX],b[MAX];
  srand((int)time(0));
  for(int i=0;i< MAX;i++)
    {
      a[i]=b[i]=rand()%11;
    }
  clock_t start_t, end_t;
  volatile long unsigned t;
  start_t = clock();
  way3(a,l,r);
   end_t = clock();
  printf("3 way partitioning run in %f seconds.\n",(double)(end_t - start_t) / CLOCKS_PER_SEC );
  start_t = clock();
  way2(b,l,r);
   end_t = clock();
  printf("2 way partitioning run in %f seconds.\n",(double)(end_t - start_t) / CLOCKS_PER_SEC );
 return 0;
}
 
