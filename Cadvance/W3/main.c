#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "jval.h"
Jval *create_array_i(int n)
{
  Jval *A = (Jval*)malloc(sizeof(Jval)*n);
  return A;
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
int Search(void *buf, int size, int l, int r, void *item, int (*compare)(void *,void*))
{
  if (r < l) return -1;
  int i = (l+r)/2;
  int res = compare(item, (char*)buf + (size*i));
  if(res==0) return i;
  else if(res < 0) return Search(buf,sizeof(int), l, i-1, item, compare);
  else return Search(buf,sizeof(int), i+1, r, item, compare);
}

int jval_compare_int(void *x,void *y)
{
  Jval m,n;
  m = *((Jval*)x);
  n = *((Jval*)y);
  if(jval_i(m)==jval_i(n)) return 0;
  return (jval_i(m)>jval_i(n))?1:-1;
  
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

  int n=10,a;
  Jval *A = create_array_i(n);
  int r, i;
  for(i=0; i<n; i++)
    {
      a=rand()%100;
      A[i] = new_jval_i(a);
    }
  way3(A,sizeof(*A),0,n-1,jval_compare_int);
  for(i=0; i<n; i++)
    {
      printf("%d  ",jval_i(A[i]));
    }
    printf("\n");
   int item;
   printf("Nhap so can tim: ");
   scanf("%d",&item);
   Jval x= new_jval_i(item);
   printf("vi tri tim thay:%d\n",Search(A, sizeof(*A),0,n-1,&x,jval_compare_int ));
  return 0;
}
