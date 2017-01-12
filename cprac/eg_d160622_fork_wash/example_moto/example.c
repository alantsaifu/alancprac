#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>
#include <sched.h>
#include <linux/unistd.h>
#include <sys/syscall.h>
#include <errno.h>

#define SUCCESS   (0)
#define WRONG_PAR (-1)
#define WRONG_DEV (-2)
#define WRONG_BZ (-3)

int main(int argc, char *argv[])
{
  int status;
  status = Set_Motor(0, 0, 0, 0, 0, 0);
  if(status == SUCCESS)
    printf("\r\ndo_motor done\n");
  else if(status == WRONG_PAR)
    printf("\r\nfork fail\n");
  else if(status == WRONG_DEV)
    printf("\r\ndevice open fail\n");
  else if(status == WRONG_BZ)
    printf("\r\ndevice busy\n");
  return 0;
}
