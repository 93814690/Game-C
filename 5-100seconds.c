#include "stdio.h"
#include "stdlib.h"
#include "windows.h"
#include "conio.h"
#include "time.h"


int a[100][100];
int i,j,k;
int top = 0,bottom,right,left = 0;
int player_x,player_y;
int con = 1;

//清屏函数
void Cls(int x,int y)
{
    HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD pos;
    pos.X = x;
    pos.Y = y;
    SetConsoleCursorPosition(handle,pos);
}

//隐藏光标
void HideCursor()
{
	CONSOLE_CURSOR_INFO cursor_info = {1, 0}; 
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor_info);
}

// 数据初始化
void startup()
{
	printf("请输入地图宽，长\n");
	scanf("%d%d",&bottom,&right);
	for (i = top; i < bottom; i++)
	{
		for (j = left; j < right; j++)
		{
			if (i == 0 || i == bottom - 1)
				a[i][j] = 3;
			else
			{
				if (j == 0 || j == right - 1)
					a[i][j] = 4;
			}
		}
	}
	player_x = rand() % (bottom - 1) + 1;
	player_y = rand() % (left - 1) + 1;
	HideCursor();
	system("cls");
}

// 显示画面
void show()
{
	Cls(0,0);
	for ( i = 0; i < bottom; i++)
	{
		for (j = 0; j < right; j++)
		{
			if (a[i][j] == 0)
				printf(" ");
			else if (a[i][j] == 1)
				printf("@");
			else if (a[i][j] == 3)
				printf("-");
			else if (a[i][j] == 4)
				printf("|");
		}
		printf("\n");
	}
}

// 与用户输入无关的更新
void updateWithoutInput()
{
	for (i = top + 1; i < bottom - 1; i++)
	{
		for (j = left + 1; j < right - 1; j++)
		{
			a[i][j] = 0;
		}
	}
	a[player_x][player_y] = 1;
}

// 与用户输入有关的更新
void updateWithInput()
{
	char input;
	if (kbhit())
	{
		input = getch();
		if (input == 'a')
			player_y -= 2;
		if (input == 'd')
			player_y += 2;
		if (input == 'w')
			player_x -= 2;
		if (input == 's')
			player_x += 2;
	}
	FlushConsoleInputBuffer(GetStdHandle(STD_INPUT_HANDLE));
	fflush(stdin);
}

int main()
{
   startup();
   while(1)
   {
        show();
        updateWithoutInput();
        updateWithInput();
    }

    return 0;
}
