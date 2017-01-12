#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>
#include <sched.h>
#include <linux/unistd.h>
#include <sys/syscall.h>
#include <errno.h>
#include <math.h>
#include <string.h>

#include <stdarg.h>
// or #include <sys/varargs.h>
void minprintf(char *fmt, ...) {
    va_list ap; /* pointer to each unnamed arg in turn */
    char *p, *sval;
    int ival;
    double dval;
    va_start(ap, fmt); /* make ap point to 1st unnamed arg */
    for (p = fmt; *p; p++) { // check each character
        if (*p != '%') { // 不是特殊字元,直接輸出即可
            putchar(*p);
            continue;
        }
        switch(*++p) { // 檢查%的下一個字元是甚麼
        case 'd':
            ival = va_arg(ap, int);
            printf("%d", ival);
            break;
        case 'f':
            dval = va_arg(ap, double);
            printf("%f", dval);
            break;
        case 's':
            for (sval = va_arg(ap, char *); *sval; sval++) { // 印出sval所指到的所有字元
                putchar(*sval);
            }
            break;
        default :
            putchar(*p);
            break;
        }
    }
    va_end(ap); // clean up when done */
}

int main() {
    int i = 0;
    i++;    
    minprintf("printf test i : %d\r\n", i);
    return 0;
}
