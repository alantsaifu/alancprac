#include <stdint.h>
#include <string.h>
#include <stdio.h>

int main(void){   
    int a = 100;
    int *p = &a;

    int array[10]={11,22,33,44,55,66,77,88,99,0};
    int *ptr;
    ptr = &array[0];
    
    printf("&p = %p\n",(void*)p);
    ++(*p++);
    printf("++(*p++) = %p\n",(void*)p);
    printf("a = %d\n",a);    

    //ptr++;    // Pointer moves to the next int position (as if it was an array)
    printf("ptr++ = %p\n",(void*)ptr++);
    //++ptr;    // Pointer moves to the next int position (as if it was an array)
    printf("++ptr = %p\n",(void*)++ptr);

    //++*ptr;   // The value of ptr is incremented
    printf("++*ptr = %d\n", ++*ptr);
    //++(*ptr); // The value of ptr is incremented
    printf("++(*ptr) = %d\n", ++(*ptr));
    //++*(ptr); // The value of ptr is incremented
    printf("++*(ptr) = %d\n", ++*(ptr));
    //*ptr++;   // Pointer moves to the next int position (as if it was an array). But returns the old content
    printf("*ptr++ = %d\n", *ptr++);
    printf("&ptr = %p\n",(void*)ptr);

    //(*ptr)++; // The value of ptr is incremented
    printf("(*ptr)++ = %d\n", (*ptr)++);
    //*(ptr)++; // Pointer moves to the next int position (as if it was an array). But returns the old content
    printf("*(ptr)++ = %d\n", *(ptr)++);
    printf("&ptr = %p\n",(void*)ptr);

    //*++ptr;   // Pointer moves to the next int position, and then get's accessed, with your code, segfault
    printf("*++ptr = %d\n", *++ptr);

    //*(++ptr); // Pointer moves to the next int position, and then get's accessed, with your code, segfault
    printf("*(++ptr) = %d\n", *(++ptr));

#if 0
    ptr++;    // use it then move to next int position
    ++ptr;    // move to next int and then use it
    ++*ptr;   // increments the value by 1 then use it 
    ++(*ptr); // increments the value by 1 then use it
    ++*(ptr); // increments the value by 1 then use it
    *ptr++;   // use the value of p then moves to next position
    (*ptr)++; // use the value of p then increment the value
    *(ptr)++; // use the value of p then moves to next position
    *++ptr;   // moves to the next int location then use that value
    *(++ptr); // moves to next location then use that value
#endif

    return 0;   
}


