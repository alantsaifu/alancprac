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
  if(key == -1){
    perror("ftok");
  }
  
  /*創建共用記憶體*/
  shmid = shmget(key, BUFSZ, SHM_R|SHM_W|IPC_CREAT);
  if(shmid < 0){
    perror("shmget");
    printf("[Debug]shmget error\n");
    exit(-1);
  }

  /*映射*/
  shmadd = shmat(shmid, NULL, 0);
  if(shmadd < 0){
    perror("shmat");
    _exit(-1);
  }

  /*拷貝資料至共用記憶體區*/
  printf("copy data to shared-memory\n");
  bzero(shmadd, BUFSZ);
  strcpy(shmadd, "data in shared memory\n");
  return 0;
}