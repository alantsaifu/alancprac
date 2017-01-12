#include "oop.h"

static int add_impl(Object *self){
	return self->a + self->b;
}

static int sub_impl(Object *self){
	return self->a - self->b;
}

int init_object(Object **self){
	if(NULL == (*self = malloc(sizeof(Object))))
		return -1;
	(*self)->a = 0;
	(*self)->b = 0;
	(*self)->add = add_impl;
	(*self)->sub = sub_impl;
	return 0;
}