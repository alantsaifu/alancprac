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

/*
Set Specific Bit
value = value | (1 << bit)
*/
#define SET_BIT(x, y) ((x) = (x) | ((1)<<(y)))

/*
Clear Specific Bit
value = value & ~(1 <<bit)
*/
#define CLEAR_BIT(x, y) ((x) = (x) & ~((1)<<(y)))

/*
Inverse Specific Bit
value = value ^ (1 << bit)
*/
#define INVERSE_BIT(x, y) ((x) = (x) ^ ((1)<<(y)))

/*
Get Specific Bit
ret = (value >> bit) & 1
*/
#define GET_BIT(x, y) ((x)>>(y) & 1)

//Bit Count
#if 0
int counter = 0;
while ( input ) {
    counter++;
    input &= (input - 1);
}
#endif

int main(){
    unsigned long v1 = 0x00001111;
    unsigned long v2 = 0x00001202;
    unsigned long v;

    v = v1 & (~v2);
    v = v | v2;
    printf("v:0x%lx\n", v);
	return 0;
}
