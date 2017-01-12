#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <memory.h>
#include <sys/time.h>
#include <signal.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <stdint.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/socket.h>
#include <net/if.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include "helper.h"

unsigned char num_buf[10] ={0x61,0x62,0x63,0x64,0x65,0x66,0x67,0x68,0x69,0};
unsigned char* rawdata_buf = NULL;

void get_rawdata(void){
    rawdata_buf = &num_buf[0];
}

THREAD_PROC(thread_ltthm_rc, thread_context){    
    unsigned char* rawdata16bit_buf_rc = NULL;
    //unsigned char* rawdata_buf = (unsigned char *)thread_context;
    rawdata16bit_buf_rc = rawdata_buf;
    printf("thread_ltthm_rc str=%s\n", rawdata16bit_buf_rc);
}

THREAD_PROC(thread_leptionencode, thread_context){
    //unsigned char* rawdata_buf = (unsigned char *)thread_context;
    //rawdata_buf = &num_buf[0];
    get_rawdata();
}

int main(int argc, char **argv)
{
    int rdbufcnt = 0;
    //unsigned char* rawdata_buf = NULL;
    THREAD_OBJECT( pt_leptionencode );
    THREAD_OBJECT( pt_ltthm_rc );

    // create lepton-encode thread, read Lepton raw data from spi-rx fifo, compress it, and push to spi-tx & network-tx fifo
    if(!THREAD_CREATE(pt_leptionencode, thread_leptionencode, rawdata_buf)){
    }
        
    do{
        printf("get rawdata_buf = %d\n", rdbufcnt++);       
    }while(rawdata_buf == NULL);
        
    if(!THREAD_CREATE(pt_ltthm_rc, thread_ltthm_rc, rawdata_buf)){
    }

    // close threads
    THREAD_CLOSE(pt_leptionencode);
    THREAD_CLOSE(pt_ltthm_rc);

    return 0;
}