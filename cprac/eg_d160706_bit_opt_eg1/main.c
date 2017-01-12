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

#define SET_BIT(x, n) ( (x) |= (1<< (n)) )
#define CLR_BIT(x, n) ( (x) &= (~(1<< (n))))
#define CHK_BIT(x, n) ( ((x) & (1<< (n)))!=0 )
#define FLIP_BIT(x, n) ( (x) ^= (1<< (n)) )

void show_binary(unsigned x)
{
    int i;
    unsigned mask=0xf0000000;
    char *table[] = {
        "0000","0001","0010","0011","0100","0101","0110","0111",
        "1000","1001","1010","1011","1100","1101","1110","1111"
    };
    for(i=7; i>=0; --i, mask>>=4)
        printf("%s ", table[ (x&mask) >> (i*4) ]);
    puts("");
}

int main(){
    show_binary(0x33);
	return 0;
}
