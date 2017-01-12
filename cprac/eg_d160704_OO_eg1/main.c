#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <error.h>

struct B { 
    int x; 
    int y; 
    int z; 
}; 

struct C { 
    struct B objB; 
    float f; 
    char s[10]; 
};

/*
要想訪問父類的成員x，有兩種方法，
一種是objC.objB.x；
另一種是((struct B*)&objC)->x = 10。
這兩種方式都看起來不夠直接。而在子類方法中訪問父類成員是非常頻繁的。
*/

void c_member_method(struct C* pObjC) { 
    pObjC->objB.x = 20; /* 訪問父類成員 */ 
    pObjC->f = 0.23f; /* 訪問自身成員 */ 
}

int main(){
    
    struct C objC; 
    objC.objB.x = 10; 
    ((struct B*)&objC)->x = 10;

    OO_define();
    OO_define_eg1();
    OO_define_eg2();
    
    return 0;
}