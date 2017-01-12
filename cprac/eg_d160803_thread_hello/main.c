#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

void *PrintHello(void)
{
    pthread_detach(pthread_self());
    int stack[1024 * 20] = {0,};
    long tid = 0;
}

int main (int argc, char *argv[])
{
    pthread_t pid;
    int rc;
    long t;

    while (1) {
        printf("In main: creating thread %ld\n", t);
        rc = pthread_create(&pid, NULL, PrintHello, NULL);
        
        if (rc){
            printf("ERROR; return code from pthread_create() is %d\n", rc);
        }
        sleep(1);
    }

    printf("\n main End \n");
    pthread_exit(NULL);
}