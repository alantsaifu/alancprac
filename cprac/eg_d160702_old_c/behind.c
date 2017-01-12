/******************************************
請使用C語言寫出一個程式輸入後序排序後的算式
計算出其答案,其輸入方式可以由按鍵輸入或者是
檔案輸入請自行決定,輸出方式亦然

作者：黃國銘
******************************************/
#include <stdio.h>
#include <math.h>
#define size 50
#define true 1
#define false 0
int stack[size];
int top=-1;
int full(void)
{
        if(top==size-1)
                return true;
        else
                return false;
}
int empty(void)
{
        if(top==-1)
                return true;
        else
                return false;
}
void push(int n)
{
        stack[++top]=n;
}
int pop()
{
        return stack[top--];
}

do_postfix()
{
        int i=0,ans=0,temp;
        char x,postfix[80];
        printf("Input the postfix:");
        //fgets(postfix, sizeof(postfix), stdin);
        if ( (fgets(postfix, sizeof(postfix), stdin)) != NULL ){
            while((x=postfix[i++])!='\0')
            {
                if(x>='0' && x<='9')
                        push((int)(x-'0'));
                else
                {
                        temp=pop();
                        switch(x)
                        {
                          case '+':
                                ans=(pop()+temp);
                                break;
                          case '-':
                                ans=(pop()-temp);
                                break;
                          case '*':
                                ans=(pop()*temp);
                                break;
                          case '/':
                                ans=(pop()/temp);
                                break;
                          case '^':
                                ans=(pow(pop(),temp));
                                break;
                        }
                        push(ans);
                }
            }
        }    
        printf("result = %d\n",pop());

}

