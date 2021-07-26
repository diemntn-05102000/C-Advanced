#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "fields.h"
#include "jrb.h"
int main()
{
  JRB b, bn;
  IS is;
  is = new_inputstruct(NULL);
  b = make_jrb();
  int a=0;
  while ((get_line(is) >=0)&&(a<5))
    {
      jrb_insert_int(b, atoi(is->text1), new_jval_s(strdup(is->text1)));
      a++;
    }
  printf("Mang:\n");
  jrb_traverse(bn,b)
    {
      printf("%s", jval_s(bn->val));
    }
  return 0;
}
