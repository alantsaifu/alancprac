
#include <stdint.h>
#include <string.h>
#include <stdio.h> 
#include <stdlib.h>  

typedef union {
    char ch;
    float f;
} Data;

union unionType
{
    char a[2];
    short b;
};

typedef union _data {
    int a;
    double b;
} u_data;

int main()
{
    Data d;
    d.ch = 'A';
    Data d2 = d; // initialize one union to another
    Data d3 = {'B'}; // initialize first member of union
    printf("%c, %c, %c\n", d.ch, d2.ch, d3.ch);

    union unionType u;
    u.b=20;
    printf("sizeof=%ld u.b=%d, u.a[1]=%d, u.a[0]=%d\n", 
    	sizeof(u), u.b, u.a[1], u.a[0]);

    u_data udata;
    udata.a = 1;
    udata.b = 0.5;
    printf("%d\t%f\n", udata.a, udata.b);
    
    return 0;
}
