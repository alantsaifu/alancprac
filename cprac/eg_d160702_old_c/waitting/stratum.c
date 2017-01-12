/*
------------------------------------------------
階乘問題
階乘在數學上的定義為：
N! = 1 x 2 x 3 x ......x N
以下為1到10階乘的值:
1! = 1
2! = 2
3! = 6
4! = 24
5! = 120
6! = 720
7! = 5040
8! = 40320
9! =362880
10!=3628800
我們發現，當階乘越大，後面的零越多。
本題是希望寫一個程式，算出從個位數起，第一個非零的數字是什麼。
輸入：一個正整數N
輸出：N! 的第一個非零數字為
範例：N=9, 9! 的第一個非零數字為8
N=8, 8! 的第一個非零數字為2
------------------------------------------------
date:5-Nov.-07
author:WenChen
version:1105071818
*/
#include <stdio.h>

int main()
{
    int i=0,mul=1,judgment=0;
    printf("\n10! = ");
    for(i=1;i<=10;i++)
     {
      mul=mul*i;
     }
      printf("%d \n",mul);
     
     while(mul%10==0)        //Excluding zero character
     {
      mul=mul/10;
     }
      printf("The first non-zero figures : ");
      printf("%d \n\n",mul%10);
      
      system("pause");
      return 0;
	
}
