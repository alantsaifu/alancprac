#ifndef _OOP_H_
#define _OOP_H_
#include <stdint.h>
#include <string.h>
#include <stdio.h> 
#include <stdlib.h>  

typedef struct object Object;
typedef int (*func_t)(Object *);

struct object{
	int a, b;
	func_t add, sub;
};
#endif