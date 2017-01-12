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

typedef struct C CSTUT; 
#if 0
static void c_member_function(C* pobjC) /* 類C的成員函數 */ { 
}    
#endif    

#define C_STRUCT \
    B_STRUCT; \
    float f; \
    char s[10];\
    void (*pc_member_function1)(CSTUT*); 

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

static void c_member_function(CSTUT* pobjC) { 
    pobjC->x = 70; /* 訪問父類成員 */ 
    b_member_function((B*)pobjC); /* 子類成員函數內部調用父類成員函數 */ 
} 

static void c_member_function1(CSTUT* pobjC) { 
    pobjC->x = 99; /* 訪問父類成員 */ 
    //b_member_function((B*)pobjC); /* 子類成員函數內部調用父類成員函數 */ 
} 

static void c_member_method(struct C* pObjC) { 
    pObjC->x = 50; /* 訪問父類成員 */ 
    pObjC->f = 0.23f; /* 訪問自身成員 */ 
}

static int OO_define_ptr () { 
   
    CSTUT *pObjC;
    pObjC = (CSTUT *) malloc (sizeof(CSTUT)); 
    b_member_function((B*)pObjC); /* 外部代碼調用成員函數 */ 
    free(pObjC);

    return 0;
}

#if 0
/*
這兩種情況都需要對實參進行強制類型轉換為父類型。
C編譯器對類型繼承關係一無所知，無法從語法上對繼承進行自動支持，
所以只能手動強制類型轉換了。 

有些人喜歡更進一步模擬成員函數，
把所有成員函數的地址作為指針類型的成員變量存儲到結構體內部。如下：
*/
#define B_STRUCT \
    int x; \
    int y; \
    int z; \
    void (*pb_member_function1)(B*); \
    void (*pb_member_function2)(B*, int arg); 

    struct B { 
        B_STRUCT; 
    }; /* 初始化B對象的同時初始化 */ 

    B* b = malloc(sizeof(B)); 
    b->pb_member_function1 = b_member_function1; 
    b->pb_member_function2 = b_member_function2; /* 調用 */ 
    b->b_member_function1(b);

/*
這樣形式上更加接近「成員函數」，但同時也帶來了額外的內存開銷和代碼量。
為了減小內存消耗，有人提出不再在對象中完全存放所有成員函數指針，
而是只存放一個指向成員函數地址列表的指針。

畢竟，同一類型的所有實例（對象）共享相同的一組成員函數。
*/
/* B類型的成員方法表 */ 
const struct B_MethodTable { 
    void (*pb_member_function1)(B*); 
    void (*pb_member_function2)(B*, int arg); 
}

b_method_table{ 
    b_member_function1, 
    b_member_function2 
}; 

#define B_STRUCT \
    int x; \
    int y; \
    int z; \
    struct B_MethodTable * pMethodTable; 

    struct B { 
        B_STRUCT; 
    }; /* 初始化B對象的同時初始化 */ 

    B* b = malloc(sizeof(B)); 
    b->pMethodTable = &b_method_table; /* 調用 */ 
    b->pMethodTable->pb_member_function1(b);
/*
這樣在一定程度上減小了內存占用量和代碼量，
但是隊成員函數的調用寫法卻變得非常繁瑣不自然。 
使用C語言做OO開發時，要掌握好一個度。
不要過分追求對OO語言C++的模擬，完全模擬C++的話，還不如乾脆直接使用C++。 
有些語言特性無法模擬，如C++中private,protected等訪問限定符，
成員函數的this指針。更應該注重意義上的模擬，通過一些命名規則和約定來達到OO。 

永遠不要違背C語言的設計哲學：程式設計師控制一切，直接簡明。 
這個度的把握需要根據具體的項目規模和需求，是實踐中摸索出來的，
無法給出理論上的最優值。
*/
#endif

int OO_define_eg1(){
    
    struct C objC; 
    objC.x = 10; 
    ((struct B*)&objC)->x = 20;
    objC.pc_member_function1 = c_member_function1;
    c_member_method(&objC);
    c_member_function(&objC);

    objC.pc_member_function1(&objC);

    return 0;
}

int OO_define_eg2(){
    
    CSTUT *pobjC;
    pobjC = (CSTUT*)malloc(sizeof(CSTUT)); 
    
    pobjC->x = 10; 
    ((struct B*)pobjC)->x = 20;
    pobjC->pc_member_function1 = c_member_function1;
    c_member_method(pobjC);
    c_member_function(pobjC);

    pobjC->pc_member_function1(pobjC);

    return 0;
}