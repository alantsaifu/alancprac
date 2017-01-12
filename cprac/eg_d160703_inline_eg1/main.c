#include <stdio.h>
#include <unistd.h>
#include "inline.h"

int main(int argc, char *argv[]){

	volatile int i = 0;
	inc_inline(&i);
	printf("i:%d\n", i);

	return 0;
}
