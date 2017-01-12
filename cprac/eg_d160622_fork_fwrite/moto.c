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

 
/*static void *slave(void *arg)*/
static int slave(void)
{
    int i;
    FILE *fd = NULL;
    int set_motor_exe;
    size_t filerws;
 
    //for (i = 0; i < 10000; i++) {
        //pthread_spin_lock(&spinlock);
        if ((fd = fopen("/run/spi_motor", "rb")) != NULL){
            //do{
              filerws = fread(&set_motor_exe, sizeof(set_motor_exe), 1, fd);
              //printf("read filerws : %ld\r\n", filerws);
            //}while(filerws != 1);   
        }else{
            //printf("open error\r\n");
            return -1;
        }
        fclose(fd); 
        fd = NULL;

        
        if(set_motor_exe != 0){
            return -1;
        }
        
        if ((fd = fopen("/run/spi_motor", "wb+")) != NULL){    
          //do{
            set_motor_exe = 1;
            filerws = fwrite(&set_motor_exe, 1, sizeof(set_motor_exe), fd);
            //printf("write filerws : %ld\r\n", filerws);
          //}while(filerws != 4);  
        }else{
          //printf("open error\r\n");
          return -1;
        }
        fclose(fd); 
        fd = NULL; 

        usleep(10000);

        if ((fd = fopen("/run/spi_motor", "wb+")) != NULL){    
          //do{
            set_motor_exe = 0;
            filerws = fwrite(&set_motor_exe, 1, sizeof(set_motor_exe), fd);
            //printf("write filerws : %ld\r\n", filerws);
          //}while(filerws != 4);  
        }else{
          //printf("open error\r\n");
          return -1;
        }
        fclose(fd); 
        fd = NULL; 
        //pthread_spin_unlock(&spinlock);
    //}     
    return 0;
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

#if 0
      get_motor_exe = 0;

      if ((fd = fopen("/run/spi_motor", "wb+")) != NULL){
        fwrite(&get_motor_exe, 1, sizeof(get_motor_exe), fd);   
      }
      fclose(fd); 
      fd = NULL; 
#endif

      printf("Set_Motor : get_motor_exe = %d\n", get_motor_exe);

    if(get_motor_exe){
        printf("motor busy\r\n");
        return 0;
    }    
    
    //pthread_spin_init(&spinlock, PTHREAD_PROCESS_PRIVATE);
    
    pid = fork();
    if (pid == 0){
      slave();
      if ((fd = fopen("/run/spi_motor", "rb")) != NULL){
        fread(&get_motor_exe, sizeof(get_motor_exe), 1, fd);   
      }
      fclose(fd); 
      fd = NULL;   
      printf("\r\nchild : get_motor_exe = %d\n", get_motor_exe);   
    }else if(pid > 0) {
      return 0;
      slave();
      if ((fd = fopen("/run/spi_motor", "rb")) != NULL){
        fread(&get_motor_exe, sizeof(get_motor_exe), 1, fd);   
      }
      fclose(fd); 
      fd = NULL;   
      printf("\r\nparent : get_motor_exe = %d\n", get_motor_exe);          
    } else {
      printf("Fork fail\n");
      return -1;
    } 
   
    //pthread_spin_destroy(&spinlock);
 
    return 0;
}
