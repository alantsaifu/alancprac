/*
------------------------------------------------
(先將0! , 1!, 2! ~9! 的值存入陣列，再將數子的各個位數取出)
找出所有小於50000 之正整數，其值等於其各個數字之階乘和。
例：4!＋0!＋5!＋8!＋5!           (remove a ! , the series is 40585)
    = 24＋1＋120＋40320＋120
    = 40585
輸入：不用輸入
輸出：由小而大依序輸出50000以下之符合題目要求之正整數, 數字之間以逗點間隔。
------------------------------------------------
date:6-Nov.-07
author:WenChen
version:1106071050
*/
#include <stdio.h>

int main()
{
    int push[50];
    int stair[10];
    int sum=0,i,j,i_tmp,tmp;
    stair[0]=1;
    stair[1]=1;
     for (i=2;i<=9;i++)
     {
         stair[i]=stair[i-1]*i;
     }
     
     /*
     design skills
     concept
     while (the NO. of one digit is decreased)!= 0
     {
     then
     tmp=(the NO. of one digit is decreased)%10
     (the NO. of one digit is decreased) = (the NO. of one digit is decreased)/10
     sum = sum + array[tmp]
     }
     eventually,don't forget to have one last bit need to be addressed
     sum = sum + array[last bit%10]
     */
    for(i=1;i<50000;i++)
    {
     tmp=0;sum=0;                   
     i_tmp=i;
     while((i_tmp/10)!=0)           //Decomposition of the numbers-bit computing
     {
     tmp=i_tmp%10;
     i_tmp=(i_tmp/10);
     sum=sum+stair[tmp];
     }
     sum=sum+stair[i_tmp%10];
     
     i_tmp=i;
     tmp=0;
     if(i==sum)                     //Decomposition of the numbers-bit,being printed
     {
      while((i_tmp/10)!=0)
      {
       push[tmp]=(i_tmp%10);
       tmp=tmp+1;
       i_tmp=(i_tmp/10);
      }
     push[tmp]=(i_tmp%10);
     tmp=tmp+1;
     
      for(j=tmp-1;j>=0;j--)
       {
        printf(" %d! ",push[j]);
        
        if(j==0)
        break;
        printf("+");
       }
       printf("= %d\n\n",i);
     }
     
    }
     
     system("pause");
    return 0;
	
}
