/*
------------------------------------------------
費伯納基係數
所謂費伯納基係數是指一個數列，它的任意一項是前兩項的和。
數列如下：0, 1, 1, 2, 3, 5, 8, 13, ....
寫一程式，求出費伯納基係數的第N項。
輸入：N。
輸出：f(N)  
------------------------------------------------
date:5-Nov.-07
author:WenChen
version:1105071818
*/
#include <stdio.h>

int do_fibonacci()
{
    int tmp,f=1,j=0,i;
    printf("fibonacci : \n\n");
    printf("%d,%d,",j,f); // First of all,the first tow numerical printed in the screen.
	for (i=2;i<20;i++)    // 0 1 1 2 3 5 8 13
	                      // t f
	                      //   t f
	                      //     t f
	{
	    tmp=f;
	    f=f+j;
	    j=tmp;

	    printf("%d,",f);
	}
    printf("\n\n");
	//system("pause");
    return 0;
	
}
