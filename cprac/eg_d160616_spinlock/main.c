#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>
#include <sched.h>
#include <linux/unistd.h>
#include <sys/syscall.h>
#include <errno.h>

pthread_spinlock_t spinlock;
volatile int global = 0;
 
void *slave(void *arg)
{
    int i;
 
    for (i = 0; i < 100 * 100 * 100; i++) {
        pthread_spin_lock(&spinlock);
        global++;
        pthread_spin_unlock(&spinlock);
    }
 
    return NULL;
}
 
int main()
{
    int i;
    pthread_t tids[3];
 
    pthread_spin_init(&spinlock, PTHREAD_PROCESS_PRIVATE);
    for (i = 0; i < 3; i++)
        pthread_create(&tids[i], NULL, slave, NULL);
 
    for (i = 0; i < 3; i++)
        pthread_join(tids[i], NULL);
    pthread_spin_destroy(&spinlock);
 
    printf("global = %d\n", global);
    return 0;
}
