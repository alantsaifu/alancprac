#include <stdio.h>
#include <sys/types.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <errno.h>
#include <unistd.h>

#define SUM(a,b) a+b

void func_static_var(void){
  static int i=0;
  i++;
  printf("i=%d\n", i);
}

void func_plus_var(void){
 int a=1;
 int b=5;
 int c;

 c=a+++b;
 printf("a=%d, b=%d, c=%d\n",a,b,c);
}

void main()
{
  char **a[40];
  char **b=malloc(40*sizeof(char));
  char c[40];
  char *d[40];
  int *e;
  int i;

  printf("%ld\n", sizeof(char));

  usleep(1000000);

  printf("%ld\n", sizeof(a));
  printf("%ld\n", sizeof(*a));
  printf("%ld\n", sizeof(**a));
  printf("%ld\n", sizeof(b));
  printf("%ld\n", sizeof(**b));
  printf("%ld\n", sizeof(c));
  printf("%ld\n\n", sizeof(*c));
  printf("%ld\n", sizeof(d));
  printf("%ld\n", sizeof(*d));
  printf("%ld\n", sizeof(*d));

  printf("%ld\n", sizeof(*b));
  printf("%ld\n", sizeof(e));
  printf("%d\n", SUM(3,8)*100);

  for(i=0;i<10;i++){
    func_static_var();   
  }

  func_plus_var();
}
