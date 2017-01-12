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

#define LBJSTRING "LeBron_James"

void reversev2(char *str)
{
    char* slow = str;
    char* fast = str;
    char* bslow = NULL;
  
    while(*(fast+1) && *(fast+2))
    {
        fast += 2;
        slow++;
    }
    bslow = slow++;
    if (*(fast+1))
        fast++;
    else
        bslow--;
  
    while(slow <= fast)
    {
        *str ^= *fast;
        *fast ^= *str;
        *str++ ^= *fast--;
  
        if (slow < fast)
        {
            *slow ^= *bslow;
            *bslow ^= *slow;
            *slow++ ^= *bslow--;
        }
    }
}

int main(){
	char *str = LBJSTRING; //in stack
	char *mod_str;
	int len = sizeof(LBJSTRING);

	mod_str = (char *)malloc(sizeof(len)); // in memory heap
	memcpy(mod_str, str, len);
	reversev2(mod_str);
	
	printf("string : %s\n", str);
	printf("reverse string : %s\n", mod_str);

    above_opt();
	
	return 0;
}