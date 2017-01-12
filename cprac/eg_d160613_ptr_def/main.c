#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>
#include <sched.h>
#include <linux/unistd.h>
#include <sys/syscall.h>
#include <errno.h>

int do_math(float arg1, int arg2) {
    return arg2;
}
int call_a_func(int (*call_this)(float, int)) {
    int output = call_this(5.5, 7);
    return output;
}


typedef int (*MathFunc)(float, int);
int do_math_ptr(float arg1, int arg2) {
    return arg2;
}
int call_a_func_ptr(MathFunc call_this) {
    int output = call_this(5.5, 7);
    return output;
} 

int main()
{
	int final_result = call_a_func(do_math);
	int final_result_ptr = call_a_func_ptr(do_math);

	printf("%d\n", final_result);
	printf("%d\n", final_result_ptr);

	return 0;
}
