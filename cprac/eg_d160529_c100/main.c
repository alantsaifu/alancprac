#include <stdint.h>
#include <string.h>
#include <stdio.h> 
#include <stdlib.h>  

main(){
  int i;
  int j;
  int k;
  int result;

  long f1,f2;

for(i=0;i<8;i++)  
    {  
                for(j=0;j<8;j++)  
                if((j+i)%2==0)printf("%c",219);  
                else printf(" ");  
                  
                printf("\n");  
                  
    }  
    
  for(i=0;i<128;i++)  
    printf("%c ",i);
  printf("\r\n");

    for(i=1;i<5;i++)  
      for(j=1;j<5;j++)  
        for(k=1;k<5;k++)  
          if(i!=j&&i!=k&&j!=k)  
            printf("%d%d%d ",i,j,k);  
    printf("\r\n");

  f1=f2=1;
  for(i=1;i<=20;i++){
    printf("%12ld %12ld",f1,f2);
    if(i%2==0) printf("\n");/*控制輸出，每行四個*/
      f1=f1+f2;/*前兩個月加起來賦值給第三個月*/
      f2=f1+f2;/*前兩個月加起來賦值給第三個月*/
  }

  printf("\n");
  for (i=1;i<10;i++){
     for(j=1;j<10;j++){
        result=i*j;
        printf("%d*%d=%-3d", i, j, result);
     }
     printf("\n");
  }
}
