#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
//#include <conio.h>
#define INITIAL_SIZE 10
#define INCREMENTAL_SIZE 5
typedef struct
{
  void *key;
  void *value;
}Entry;
typedef struct
{
  Entry *entries;
  int total;
  int size;
  Entry (*makeNode)(void*, void*);
  int (*compare)(void*,void*);
}SymbolTable;
void dropSymbolTable(SymbolTable *table)
{
  int i;
  for(i=0; i< table->total; i++)
    {
      free(table->entries[i].key);
      free(table->entries[i].value);
    }
  free(table->entries);
  table->total = 0;
  table->size =0;
}
SymbolTable createSymbolTable(Entry (*makeNode)(void*, void*),int (*compare)(void*,void*))
{
  SymbolTable tab;
  tab.total =0;
  tab.size = INITIAL_SIZE;
  tab.entries = (Entry*)malloc(INITIAL_SIZE*sizeof(Entry));
  tab.makeNode = makeNode;
  tab.compare = compare;
  return tab;
}
 int binarySearch(Entry *entries, int l, int r, char *key, int *found,int (*compare)(void*,void*))
{
  int i, res;
  if(r < l)
    {
      *found = 0;
      return l;
    }
  i = (l+r)/2;
  res = compare(key, entries[i].key);
  if(res == 0)
    {
      *found =1;
      return i;
    }
  else if(res < 0)
    {
      return binarySearch(entries, l, i-1,key, found, compare) ;
    }
  else
    {
      return binarySearch(entries, i+1, l,key, found, compare) ;
    }
}
void addEntry(void *key, void* value, SymbolTable *book)
{
  int found, pos;
  if(book->total > 0)
    {
      pos = binarySearch(book->entries, 0, book->total-1, key, &found, book -> compare);
    }
  else
    {
      pos =0;
      found =0;
    }
  if(found)
    {
      free(book->entries[pos].key);
      free(book->entries[pos].value);
      book -> entries[pos] = book->makeNode(key, value);
    }
  else
    {
      if(book->total >= book->size)
	{
	  Entry *p;
	  book->size += INCREMENTAL_SIZE;
	  (book->entries) = (Entry*)realloc(book->entries, sizeof(Entry)*( book->size));
	}
      if(pos < book->total)
	{
	  memcpy(&(book->entries[pos+1]),&(book->entries[pos]), (book->total-pos)*sizeof(Entry));
	}
      book->entries[pos] = book->makeNode(key, value);
      book->total++;
    }
}
Entry *getEntry(void *key, SymbolTable book)
{
  int found, pos;
  pos = binarySearch(book.entries, 0, book.total-1,key, &found, book.compare);
  if(found)
    {
      return &(book.entries[pos]);
    }
  else return NULL;
}
Entry makePhone(void *name, void *phone)
{
  Entry res;
  res.key = strdup((char*)name);
  res.value = malloc(sizeof(long));
  memcpy(res.value, phone, sizeof(long));
  return res;
}
int compare(void *key1, void *key2)
{
  return strcmp((char*)key1,(char*)key2 );
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
void way3(Entry *a, int size, int l, int r, int (*compare)(void*, void*))
{
  if(r <= l) return;
  int i = l-1, j = r;
  int p = l-1, q = r;
  while(1)
    {
      while(compare((char*)a[++i].key, (char*)a[r].key)<0);
      while(compare((char*)a[r].key, (char*)a[--j].key)<0) if(j==l) break;
      if(i >= j) break;
      exchn(a, size, i, j);
      if(compare((char*)a[i].key, (char*)a[r].key)==0) exchn(a, size, ++p,i);
      if(compare((char*)a[j].key, (char*)a[r].key)==0) exchn(a, size, --q,j);
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
  int i,n;
  long  sdt;
  char name[80];
  Entry *entries;
  Entry *a;
  SymbolTable book = createSymbolTable(makePhone,compare);
  sdt = 385384674;
  addEntry("Dung", &sdt, &book);
  sdt = 755384674;
  addEntry("Anh", &sdt, &book);
  sdt = 192834674;
  addEntry("Thang", &sdt, &book);
  sdt = 432645634;
  addEntry("Huong", &sdt, &book);
  
  do
    {
      //system("cls");
      printf("1.Add phone\n2.Search phone\n3.Printf list\n4.Sort 3 way\n5.Exit\nYour choice:");
      scanf("%d",&n);
      switch(n)
	{
	case 1:
	  printf("Name:");
	  //fflush(stdin);
	  getchar();
	  scanf("%[^\n]s",name);
	  printf("Number:");
	  scanf("%ld",&sdt);
	  addEntry(name,&sdt, &book);
	  break;
	case 2:
	  printf("Name:");
	  //fflush(stdin);
	  getchar();
	  scanf("%[^\n]s",name);
	  Entry *s;
	  if(getEntry(name,book)==NULL)
	    printf("Khong tim thay!!!\n");
	  else
	    {
	    s=getEntry(name,book);
	    printf("Tim thay %s - %ld\n",name,*((long*)s->value));
	    //getch();
	    }
	  break;
	case 3:
	  for(int i=0; i< book.total; i++)
	    {
	      printf("%-15s%10ld\n",((char*)book.entries[i].key),*((long*)book.entries[i].value));
	      //getch();
	    }
	  break;
	  case 4:
	    a=(Entry*)malloc(book.total*sizeof(Entry));
	    memcpy(a,book.entries, book.total*sizeof(Entry));
	    int t = book.total;
	    way3(a,sizeof(Entry) ,0,book.total-1,book.compare);
	   for(int i=0; i< t; i++)
	    {
	      printf("%-15s%10ld\n",((char*)a[i].key),*((long*)a[i].value));
	      //getch();
	    }
	  break;
	case 5:
	  dropSymbolTable(&book);
	  free(a);
	  break;
	}
    }while(n!=5);

  return 0;
}
