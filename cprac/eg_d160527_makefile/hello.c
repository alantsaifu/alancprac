#include <stdio.h>
 
typedef struct{
    int blobsize;
    int *blob;
}cpt_hdl;

int disp_pkey(const int **blob){
    printf("blob = %d\n", **blob);  
}

int main(void){   
    cpt_hdl *pkey;
    cpt_hdl pkey_mem;
    int *keybuf;
    int *keybuf_addr;
    int *keybuf_addr_addr;
    int keybuf_addr_mem;
    int **keybufa1;
    int keybufa2;
    int a1 = 88;
    int *a1_ptr;
    
    pkey_mem.blobsize = 99;
    pkey_mem.blob = &a1;

    pkey = &pkey_mem;
    a1_ptr = &a1;

    keybuf_addr=(int*)&pkey; 
    printf("keybuf_addr = 0x%x\n", *keybuf_addr); //0xf18944f0
    
    keybuf_addr_addr = (int*)&keybuf_addr;
    printf("keybuf_addr_addr = 0x%x\n", *keybuf_addr_addr);

    keybuf_addr=(int*)&a1_ptr; 
    printf("keybuf_addr = 0x%x\n", *keybuf_addr); //0xf189452c

    keybuf=pkey->blob; 
    printf("keybuf = %d\n", *keybuf); //88

    keybuf=(int*)pkey->blob; 
    printf("keybuf = %d\n", *keybuf); //88

    keybufa1=(int**)&pkey->blob; 
    printf("keybuf = %d\n", **keybufa1); //88

    keybuf_addr=(int*)&pkey->blob; 
    printf("keybuf_addr = 0x%x\n", *keybuf_addr); //0xf189452c
    
    disp_pkey((const int**)&pkey->blob); //88

    return 0; 
}
