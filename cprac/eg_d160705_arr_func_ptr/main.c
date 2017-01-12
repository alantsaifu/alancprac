#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>
#include <sched.h>
#include <linux/unistd.h>
#include <sys/syscall.h>
#include <errno.h>

/*
int a[5] ={1,2,3,4,5};
int *p = (int *)(&a+1);
ask: the value of *(a+1), (*p-1)?
*/

//void (*(*papf)[3])(char *);
typedef void (*pf)(char *);
//pf(*papf)[3];

void prun(char *run) {
    printf("start\r\n");
}

void pstop(char *stop) {
    printf("stop\r\n");
}

void pexit(char *exit) {
    printf("exit\r\n");
}

int OnStateChange(int state, pf *fpapf) {
       
    if (state > 2) { 
        printf("Wrong state!\n");
        return -1;
    }

    fpapf[state]("func_ptr_eg");
    return 0;
}

int main()
{
    int a[5] ={1,2,3,4,5};
    int *p = (int *)(&a+1);

    pf papf[3]  = {prun, pstop, pexit};

    OnStateChange(0, &papf[0]);
    OnStateChange(1, &papf[0]);
    OnStateChange(2, &papf[0]);
    
    pf _papf1a = prun;
    pf _papf1b = pstop;
    pf _papf1c = pexit;
    pf *papf1[3] = {&_papf1a, &_papf1b, &_papf1c};
    
    pf (*papf2)[3] = &papf;

    OnStateChange(0, (papf2)[0]);
    OnStateChange(1, (papf2)[0]);
    OnStateChange(2, (papf2)[0]);

	return 0;
}
