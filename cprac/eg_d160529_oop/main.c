
#include "oop.h"

int main(int argc, char *argv[]){
  Object *o = NULL;
  init_object(&o);
  o->a = 9922; 
  o->b = 5566;
  printf("add = %d, sub = %d\n", o->add(o), o->sub(o));

  return 0;
}
