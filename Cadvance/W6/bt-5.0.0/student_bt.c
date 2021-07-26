#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include "inc/bt.h"
#include "inc/btree_int.h"
#include "inc/btree.h"
int main()
{
  int i,n,size;
  double  diem;
  char name[80];
  BTA *book;
  btinit();
  book = btopn("my book", 0, 0);
  if(!book)
    {
      printf("Create my book\n");
      book = btcrt("my book", 0, 0);
      printf("Insert data\n");
      diem = 8.5;
      if(btins(book, "Dung", (char*)&diem, sizeof(double)))
	printf("Error, can not insert Dung\n");
       diem = 8;
      if(btins(book, "Thang", (char*)&diem, sizeof(double)))
	printf("Error, can not insert Dung\n");
       diem = 7.25;
      if(btins(book, "Huong", (char*)&diem, sizeof(double)))
	printf("Error, can not insert Dung\n");
       diem = 9.5;
      if(btins(book, "Diem", (char*)&diem, sizeof(double)))
	printf("Error, can not insert Dung\n");
    }
  do
    {
      printf("1.Add student\n2.Search student\n3.Printf list\n4.Change scores\n5.Exit\nYour choice:");
      scanf("%d",&n);
      // while(getchar()!= '\n');
      switch(n)
	{
	case 1:
	  printf("Name:");
	  //fflush(stdin);
	  getchar();
	  scanf("%[^\n]s",name);
	  printf("Scores:");
	  scanf("%lf",&diem);
	  while(getchar()!= '\n');
	  btins(book, name, (char*)&diem, sizeof(double));  
	  break;
	case 2:
	  printf("Name:");
	  //fflush(stdin);
	  getchar();
	  scanf("%[^\n]s",name);
	  if(btsel(book, name, (char*)&diem, sizeof(double), &size))
	    printf("Not found student %s\n", name);
	  else
	    printf("Scores of student %s is %.2lf\n", name,diem);
	  break;
	  case 3:
	    btsel(book, "", (char*)&diem, sizeof(double), &size);
	    while(btseln(book, name, (char*)&diem, sizeof(double), &size)==0)
	      printf("Scores of student %s is %.2lf\n", name, diem);
	    
	  break;
	case 4:
	  printf("Name:");
	  //fflush(stdin);
	  getchar();
	  scanf("%[^\n]s",name);
	  printf("New scores:");
	  scanf("%lf",&diem);
	  btupd(book, name, (char*)&diem, sizeof(double));  
	  break;
	case 5:
	  btcls(book);
	  break;
	}
    }while(n!=5);

  return 0;
}
