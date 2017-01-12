#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>
#include <sched.h>
#include <linux/unistd.h>
#include <sys/syscall.h>
#include <errno.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>

int above_opt(){
    int ref[] = {8, 4, 5, 9};
    int *ptr;
    int index;

    for(index = 0, ptr = ref; index <2; index++, ptr++)
        printf("%d %d\n", ref[index], *ptr);

    (*ptr)++;
    printf("%d %d\n", ref[index], *ptr);
}