#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>
#include <sched.h>
#include <linux/unistd.h>
#include <sys/syscall.h>
#include <errno.h>
#include <sys/wait.h>

//pthread_spinlock_t spinlock;
//volatile int global = 0;
//int global = 0;
//int fd[2];

 
/*static void *slave(void *arg)*/
static void slave(void)
{
    int i;
    FILE *fd = NULL;
    int set_motor_exe = 0;
 
    for (i = 0; i < 10; i++) {
        //pthread_spin_lock(&spinlock);
        sleep(1);
        set_motor_exe++;
        if ((fd = fopen("/run/spi_motor", "wb+")) != NULL){
          fwrite(&set_motor_exe, 1, sizeof(set_motor_exe), fd);   
        }
        fclose(fd); 
        fd = NULL; 
        //pthread_spin_unlock(&spinlock);
    }
     
    set_motor_exe = 0; 
    if ((fd = fopen("/run/spi_motor", "wb+")) != NULL){
      fwrite(&set_motor_exe, 1, sizeof(set_motor_exe), fd);   
    }
    fclose(fd); 
    fd = NULL;   
      
    /*return NULL;*/
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

    pgmexe = &get_motor_exe;
    
      if ((fd = fopen("/run/spi_motor", "rb")) != NULL){
        fread(&get_motor_exe, sizeof(get_motor_exe), 1, fd);   
      }else{
        if ((fd = fopen("/run/spi_motor", "wb+")) == NULL){
          return -1;
        }     
      }
      fclose(fd); 
      fd = NULL;            
      printf("Set_Motor : get_motor_exe = %d\n", get_motor_exe);
      
    if(get_motor_exe > 0)
      return 0;
    
    //pthread_spin_init(&spinlock, PTHREAD_PROCESS_PRIVATE);
    
    pid = fork();
    if (pid == 0){
      slave();
    }else if(pid > 0) {
      if ((fd = fopen("/run/spi_motor", "rb")) != NULL){
        fread(&get_motor_exe, sizeof(get_motor_exe), 1, fd);   
      }
      fclose(fd); 
      fd = NULL;   
      printf("parent : get_motor_exe = %d\n", get_motor_exe);          
    } else {
      printf("Fork fail\n");
      return -1;
    } 
   
    //pthread_spin_destroy(&spinlock);
 
    return 0;
}
