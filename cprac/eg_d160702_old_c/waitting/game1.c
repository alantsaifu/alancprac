/*
------------------------------------------------
¤«¦r¹CÀ¸ 
------------------------------------------------
date:6-Nov.-07
author:WenChen
version:1106072150
*/
#include <stdio.h>
#include <windows.h>
void gotoxy(int xpos, int ypos);
void clrscr(void);

void gotoxy(int xpos, int ypos)
{
  COORD scrn;

  HANDLE hOuput = GetStdHandle(STD_OUTPUT_HANDLE);

  scrn.X = xpos; scrn.Y = ypos;

  SetConsoleCursorPosition(hOuput,scrn);

}
void clrscr(void)
{
    CONSOLE_SCREEN_BUFFER_INFO sbinf;
    int size;
    COORD scrn = {0, 0};
    HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
    GetConsoleScreenBufferInfo(hStdOut, &sbinf);
    size = (sbinf.srWindow.Right-sbinf.srWindow.Left+1)*
        (sbinf.srWindow.Bottom-sbinf.srWindow.Top+1);
    FillConsoleOutputCharacter(hStdOut, 32, size, scrn, NULL);
}

int chess[9];int n;int game=1;

void initial()
{
     int i;
     for(i=0;i<9;i++)
     {
      chess[i]=i+1;                  
     }
     gotoxy(3,2);
     printf(" %d |",chess[6]);printf(" %d |",chess[7]); printf(" %d ",chess[8]);
     gotoxy(3,3);
     printf(" ---------- ");
     gotoxy(3,4);
     printf(" %d |",chess[3]);printf(" %d |",chess[4]); printf(" %d ",chess[5]);
     gotoxy(3,5);
     printf(" ---------- ");
     gotoxy(3,6);
     printf(" %d |",chess[0]);printf(" %d |",chess[1]); printf(" %d ",chess[2]);
     
     
     gotoxy(30,9);
     printf("   |");printf("   |"); printf("  ");
     gotoxy(30,10);
     printf(" --------- ");
     gotoxy(30,11);
     printf("   |");printf("   |"); printf("  ");
     gotoxy(30,12);
     printf(" --------- ");
     gotoxy(30,13);
     printf("   |");printf("   |"); printf("  ");   
     
}

void goon()
{
     gotoxy(22,17);
     printf("please sign the site you want");
     gotoxy(22,18);
     scanf("%d",&n);
     gotoxy(22,16);
     printf("      "); 
     
     switch(n)
     {
       case(7) :
               gotoxy(30,9);
               printf(" %c |",'O');
               chess[6]=10;
               break;
       case(8) :
               gotoxy(34,9);
               printf(" %c |",'O');
               chess[7]=10;
               break;
       case(9) :
               gotoxy(38,9);
               printf(" %c ",'O');
               chess[8]=10;
               break;
       case(4) :
               gotoxy(30,11);
               printf(" %c |",'O');
               chess[3]=10;
               break;
       case(5) :
               gotoxy(34,11);
               printf(" %c |",'O');
               chess[4]=10;
               break;
       case(6) :
               gotoxy(38,11);
               printf(" %c ",'O');
               chess[5]=10;
               break; 
       case(1) :
               gotoxy(30,13);
               printf(" %c |",'O');
               chess[0]=10;
               break;
       case(2) :
               gotoxy(34,13);
               printf(" %c |",'O');
               chess[1]=10;
               break;
       case(3) :
               gotoxy(38,13);
               printf(" %c ",'O');
               chess[2]=10;
               break;
       default :
               gotoxy(20,16);
               printf("error!"); 
               goon();
     }
     
}

void check ()
{
     if ( (chess[0]==10) && (chess[1]==10) && (chess[2]==10) || 
          (chess[3]==10) && (chess[4]==10) && (chess[5]==10) ||
          (chess[6]==10) && (chess[7]==10) && (chess[8]==10) || 
          (chess[0]==10) && (chess[3]==10) && (chess[6]==10) ||
          (chess[1]==10) && (chess[4]==10) && (chess[7]==10) ||
          (chess[2]==10) && (chess[5]==10) && (chess[8]==10) ||
          (chess[2]==10) && (chess[4]==10) && (chess[6]==10) ||
          (chess[0]==10) && (chess[4]==10) && (chess[8]==10) )
          {
          gotoxy(22,16);
          printf ("player won the game !");
          game=0;
          }
     else
         {   
         game=1;
         }
}


int main()
{
    initial();
     while (game!=0)
     {
     goon();
     check();
     }
    printf("\n");
    gotoxy(20,21);
    system("pause");
    return 0;
}
