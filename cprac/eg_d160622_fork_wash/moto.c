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
#define WRONG_NONE (-4)

#define MOTOR_BZ (1)
#define MOTOR_AVLBL (0)

#define BUS_MOTOR_CREATE(fd, fd_status) do {\
    if ((fd = fopen("/run/spi_motor", "rb")) != NULL){\
        fd_status = SUCCESS;\
        fclose(fd);\
        fd = NULL;\
    }else{\
      if ((fd = fopen("/run/spi_motor", "wb+")) != NULL){\
        fd_status = SUCCESS;\
      }else{\
        fd_status = WRONG_DEV;\
      }\
    }\
  } while (0) 

#define BUS_MOTOR_READ(fd, get_motor_exe, fd_status) do {\
      if ((fd = fopen("/run/spi_motor", "rb")) != NULL){\
        fread(&get_motor_exe, sizeof(get_motor_exe), 1, fd);\
        fd_status = SUCCESS;\
        fclose(fd);\
        fd = NULL;\
      }else{\
        fd_status = WRONG_DEV;\
      }\
  } while (0)

#define BUS_MOTOR_WRITE(fd, set_motor_exe, fd_status) do {\
        if ((fd = fopen("/run/spi_motor", "wb+")) != NULL){\
            fwrite(&set_motor_exe, sizeof(set_motor_exe), 1, fd);\
            fd_status = SUCCESS;\
            fclose(fd);\
            fd = NULL;\
        }else{\
            fd_status = WRONG_DEV;\
        }\
    } while (0)

    
static int do_motor(void)
{
    int i;
    FILE *fd = NULL;
    int set_motor_exe;
    int get_motor_exe;
    int fd_status = SUCCESS;

        BUS_MOTOR_READ(fd, get_motor_exe, fd_status);
        if(fd_status == WRONG_DEV)
            return WRONG_DEV;
           
        if(get_motor_exe){
            return WRONG_BZ;
        }

        set_motor_exe = MOTOR_BZ;
        BUS_MOTOR_WRITE(fd, set_motor_exe, fd_status);
        if(fd_status == WRONG_DEV)
            return WRONG_DEV;

        usleep(10000);

        set_motor_exe = MOTOR_AVLBL;
        BUS_MOTOR_WRITE(fd, set_motor_exe, fd_status);
        if(fd_status == WRONG_DEV)
            return WRONG_DEV;

    return SUCCESS;
}
 
int Set_Motor( int moto_n, 
               int action, 
               int mode, 
               int position, 
               int speed, 
               int Acc ) {
    pid_t pid;
    FILE *fd = NULL;

    int *pgmexe;
    int get_motor_exe = 0;
    int status;
    int fd_status = SUCCESS;

    pgmexe = &get_motor_exe;
    
    BUS_MOTOR_CREATE(fd, fd_status);
    if(fd_status != SUCCESS)
        return WRONG_DEV;

    BUS_MOTOR_READ(fd, get_motor_exe, fd_status);
    if(fd_status != SUCCESS)
        return WRONG_BZ;

    if(get_motor_exe){
        return WRONG_BZ;
    }    
    
    pid = fork();
    if (pid == 0){     
      status = do_motor();
      if(status != SUCCESS)
        return status;
      BUS_MOTOR_READ(fd, get_motor_exe, fd_status);
    }else if(pid > 0) {
      return WRONG_NONE;
      status = do_motor();
      if(status != SUCCESS)
        return status;
      BUS_MOTOR_READ(fd, get_motor_exe, fd_status);
    } else {
      return WRONG_PAR;
    } 
   
    return SUCCESS;
}
