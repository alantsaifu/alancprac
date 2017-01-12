#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <error.h>

#define B_STRUCT \
    int x; \
    int y; \
    int z 

    struct B { 
        B_STRUCT; 
    }; 

#define C_STRUCT \
    B_STRUCT; \
    float f; \
    char s[10] 

    struct C { 
        C_STRUCT; 
    }; 

#define D_STRUCT \
    C_STRUCT; \
    double d 

    struct D { 
        D_STRUCT; 
    };

typedef struct B B; 
static void b_member_function(B* pobjB) /* 類B的成員函數 */ { 
    pobjB->x = 60;
} 

typedef struct C CSTUT; 
#if 0
static void c_member_function(C* pobjC) /* 類C的成員函數 */ { 
}    
#endif

#if 1
static void c_member_function(CSTUT* pobjC) { 
    pobjC->x = 70; /* 訪問父類成員 */ 
    b_member_function((B*)pobjC); /* 子類成員函數內部調用父類成員函數 */ 
} 
#endif

#if 1
static void c_member_method(struct C* pObjC) { 
    pObjC->x = 50; /* 訪問父類成員 */ 
    pObjC->f = 0.23f; /* 訪問自身成員 */ 
}
#endif

typedef struct rec{
    int i;
    float PI;
    char A;
}RECORD;


int OO_define_ptr () { 

#if 0
    RECORD *ptr_one;
    ptr_one = (RECORD *) malloc (sizeof(RECORD));
    free(ptr_one);
#endif

#if 1    
    CSTUT *pObjC;
    pObjC = (CSTUT *) malloc (sizeof(CSTUT)); 
    b_member_function((B*)pObjC); /* 外部代碼調用成員函數 */ 
    free(pObjC);
#endif

    return 0;
}

int OO_define(){
    
    struct C objC; 
    objC.x = 10; 
    ((struct B*)&objC)->x = 20;
    c_member_method(&objC);
    c_member_function(&objC);

    return 0;
}