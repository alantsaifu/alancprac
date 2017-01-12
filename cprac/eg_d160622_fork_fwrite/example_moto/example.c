#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>
#include <sched.h>
#include <linux/unistd.h>
#include <sys/syscall.h>
#include <errno.h>

int main(int argc, char *argv[])
{
  Set_Motor(0, 0, 0, 0, 0, 0);
  printf("close main\r\n");
  return 0;
}
