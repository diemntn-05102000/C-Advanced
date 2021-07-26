#include <stdio.h>
#include <stdlib.h>

int int_compare(void const *x,void const *y)
{
  int m,n;
  m = *((int*)x);
  n = *((int*)y);
  if(m==n) return 0;
  return (m>n)?1:-1;
  
}
int Search(void *buf, int size, int l, int r, void *item, int (*compare)(void const*,void const*))
{
  if (r < l) return -1;
  int i = (l+r)/2;
  int res = compare(item, (char*)buf + (size*i));
  if(res==0) return i;
  else if(res < 0) return Search(buf,sizeof(int), l, i-1, item, compare);
  else return Search(buf,sizeof(int), i+1, r, item, compare);
}
int main()
{
  int n=100;
  int *A = (int*)malloc(n*sizeof(int));
  int r,i;
  for(i=0; i<n; i++)
    {
      r=rand()%100;
      A[i] = r;
    }
  qsort(A, n, sizeof(int), int_compare);
  for(i=0; i<n; i++)
    {
      printf("%d  ",A[i]);
    }
  printf("\n");
  int item;
  printf("nhap so can tim: ");
  scanf("%d",&item);
  printf("Vi tri la: %d\n", Search(A, sizeof(int), 0, n-1, &item, int_compare));
  return 0;
}
