#include <stdint.h>
#include <string.h>
#include <stdio.h>

int main(){
    int a[2][3];
    int (*ptr) [3];

    //ptr = a[0];
    ptr = &a[0];

    return 0;
}

