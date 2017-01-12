#if 0
#include <stdint.h>
#include <string.h>
#include <stdio.h> 
#include <stdlib.h>  
#endif

//(*(void(*)())0)();
typedef void (*funcptr)();

//float *g();
//声明g是一个返回float指针的函数，所以(float *())就是它的模型。

//(*(void(*)())0)();硬件会调用地址为0处的子程序
//(*0)(); 但这样并不行，因为*运算符要求必须有一个指针作为它的操作数。

// typedef funcptr void (*)();指向返回void的函数的指针
//typedef void (*funcptr)();
//(*(funcptr)0)();//调用地址为0处的子程序

int a[3];

struct{ 
  double v[3]; 
  double length; 
} b[17];

int calendar[12][31];

int main(){
  //(*(funcptr)0)();
  return 0;
}
