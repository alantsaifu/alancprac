/*
------------------------------------------------
��ƪ��w�q�����G�@�Ӥj��1���۵M�ơA���F1�P���ۨ��~�A
�A�S���䥦�������ƤF�A�o�˪��۵M�ƥs����ơC  
------------------------------------------------
date:5-Nov.-07
author:WenChen
version:1105071818
*/

#include <stdio.h>
int main()
{
 int i=2,j=0;
 printf(" The prime is : \n\n");
 printf(" %3d",i);   
 for (i=1;i<=400;i++)
     {
      for(j=2;j<i;j++)
       {
        if(i%2==0)     //if n mod 2==0 ,be eliminate from line.
        {
         break;
        }
        if(i%j==0)     //if n mod line_NO.==0 ,be eliminate from line.
        {
         break;
        }
         if(j==i-1)    //if n mod line_NO.!=0,it is prime.
         {
          printf(" %3d",i);
         }
       }
     }
     printf("\n\n");
     system("pause");
}
