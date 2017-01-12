/*
[技術] Linux Shared Memory程式
要運行程式，需要在當前目錄下建立一個share檔案，
share是一個空檔案，沒有任何意義，只是函數ftok需要一個檔案名作參數，
ftok另一個參數可以為任何數字。

程式執行後，分為父子程序，子程序申請Shared Memory，
然後等待父程序繼續執行，父程序首先等待子程序申請到Shared Memory區段(segment)，
然後輸出Shared Memory中的內容，為了演示Shared Memory可以隨時更新，
程序中在子程序裡產生隨機數寫入Shared Memory供父程序讀取。
*/
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

#include <time.h>
#include <signal.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/types.h>

int shmID;
char * buf;
 
void finalize(int signo){
 shmctl(shmID,IPC_RMID,NULL);
 exit(0);
}

int main(){
 int i = 1;  
 key_t shmKey;
 
 signal(SIGINT,finalize);
 signal(SIGTERM,finalize);
 
 if(fork() == 0) //子程序
 {  
 	shmKey = ftok("share",16);  //可以使用任何大於0的數字，如果名字和數相同，則產生的key相同。
  	if(shmKey == -1)
  	{
   		printf("make key error\n");
   		exit(-1);
  	}
  
  	shmID = shmget(shmKey,20,IPC_CREAT | IPC_EXCL | 0666);
  	if(shmID == -1)
  	{
   		printf("make Shared Memory Segment error\n");
   		exit(-1);
  	}
  
  	sleep(2); //等待父程序執行，好顯示第一行為空。
  	while(1)
  	{
   		buf = (char *)shmat(shmID,NULL,0);
   		srandom(time(NULL));
   		sprintf(buf,"%ld",random()); 
   		shmdt(buf);  
  	}
 }
 else  //父程序
 {
  	sleep(1); //讓子程序先執行，以建立Shared Memory Segment。
  
  	shmKey = ftok("share",16);  //可以使用任何大於0的數字，如果名字和數相同，則產生的key相同。
  	if(shmKey == -1){
   		printf("make key error\n");
   		exit(-1);
  	}
  
  	shmID = shmget(shmKey,20,0); //0表示如果shmKey映射的不存在則報錯。
  	if(shmID == -1){
   		printf("Direct Segment id error\n");
   		exit(-1);
  	}
  
  	while(1)
  	{ 
   		buf = (char *)shmat(shmID,NULL,0);
   		printf("%d. Content of Shared Memory now ：%s\n",i++,buf);
   		shmdt(buf);
   		sleep(1);
  	}
 } 

 return 0;
}