/*
------------------------------------------------
完整數的問題
所謂完整數是一個正整數等於它除了自己以外之所有因數之和，
如6的因數有1, 2, 3，而6=1+2+3，所以6是完整數。
但8的因數有1, 2, 4, 但8 不等於1+2+4，所以8不是完整數，
又如12不等於1+2+3+4+6，所以12也不是完整數。
寫一程式，找出10000(含)以下之所有完整數(1除外)。
------------------------------------------------
date:5-Nov.-07
author:WenChen
version:1105071800
*/

#include <stdio.h>

int do_completed2()
{
 int i=0,tmp=0;
 int sum;
 
 printf(" The completeness is : \n\n");
  
 for (i=2;i<=10000;i++)    //line
     {
      sum=1;
      tmp=i;
      while(tmp%2==0)
      {
       tmp=tmp/2;            //eg.496/2=248,496/4=124,496/8=62,496/16=31    
       sum=sum+tmp+i/tmp;    //   496's factor = 1,2,4,8,16,31,62,124,248      
       if(i%3==0)            //   496=1+2+4+8+16+31+62+124+248=496
       break;                //but a factor theree is one of the line,being refused
      }      
        if (sum == i)        //if it is balanced all factor value and line equally,printed in the screen
        {
          printf(" %3d",i);
        }
       
     }
     printf("\n\n");
     //system("pause");
     return 0;
}
