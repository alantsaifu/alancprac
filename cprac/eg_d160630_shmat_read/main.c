#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>

#define BUFSZ 2048

int main(int argc, char *argv[]){
  int shmid;
  int ret;
  key_t key;
  char *shmadd;

  key = ftok(".", 2012);
  if(key==-1){
    perror("ftok");
  }
  
  system("ipcs -m");
  /*打開共用記憶體*/
  shmid = shmget(key, BUFSZ, SHM_R|SHM_W);
  if(shmid < 0){
    perror("shmget");
    printf("[Debug] shmget error\n");
    exit(-1);
  }

  /*映射*/
  shmadd = shmat(shmid, NULL, 0);
  if(shmadd < 0){
    perror("shmat");
    exit(-1);
  }

  /*讀共用記憶體區資料*/
  printf("copy data from shared-memory\n");
  printf("data = [%s]\n", shmadd);
  
  /*分離共用記憶體和當前進程*/
  ret = shmdt(shmadd);
  if(ret < 0){
    perror("shmdt");
    exit(1);
  }else{
    printf("deleted shared-memory\n");
  }

  /*刪除共用記憶體*/
  shmctl(shmid, IPC_RMID, NULL);
  system("ipcs -m");
  return 0;
}