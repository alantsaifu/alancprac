/*
------------------------------------------------
�������D
�����b�ƾǤW���w�q���G
N! = 1 x 2 x 3 x ......x N
�H�U��1��10��������:
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
�ڭ̵o�{�A�����V�j�A�᭱���s�V�h�C
���D�O�Ʊ�g�@�ӵ{���A��X�q�Ӧ�ư_�A�Ĥ@�ӫD�s���Ʀr�O����C
��J�G�@�ӥ����N
��X�GN! ���Ĥ@�ӫD�s�Ʀr��
�d�ҡGN=9, 9! ���Ĥ@�ӫD�s�Ʀr��8
N=8, 8! ���Ĥ@�ӫD�s�Ʀr��2
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
