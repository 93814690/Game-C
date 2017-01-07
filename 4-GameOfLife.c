#include "stdio.h"
#include "stdlib.h"
#include "conio.h"
#include "windows.h"
#include "time.h"

#define High 30
#define Width 60

int cells[High][Width];
int speed = 70;

//隐藏光标
void HideCursor()
{
	CONSOLE_CURSOR_INFO cursor_info = {1, 0}; 
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor_info);
}


//清屏函数
void cls(int x,int y)
{
    HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD pos;
    pos.X = x;
    pos.Y = y;
    SetConsoleCursorPosition(handle,pos);
}

void startup()
{
	int i,j;
	srand((unsigned)time(0));
	for (i = 0;i < High;i++)
		for (j = 0;j < Width;j++)
		{
			cells[i][j] = 0;
		}
	for (i = 1;i < High-1;i++)
		for (j = 1;j < Width-1;j++)
		{
			cells[i][j] = rand() % 2;
		}
}

void show()
{
	HideCursor();
	cls(0,0);
	int i,j;
	for (i = 1; i < High-1; i++)
	{
		for (j = 1; j < Width-1; j++)
		{
			if (cells[i][j] == 1)
				printf("*");
			else
				printf(" ");
		}
		printf("\n");
	}
	printf("操作说明：按+加速、按-减速\n");
	Sleep(speed);
}

void updateWithoutInput()
{
	int newCells[High][Width];
	int neibourNumber;
	int i,j;
	for (i=1;i<High-1;i++)
	{
		for (j=1;j<Width-1;j++)
		{
			neibourNumber =  cells[i-1][j-1] + cells[i-1][j] + cells[i-1][j+1] + cells[i][j-1] + cells[i][j+1] + cells[i+1][j-1] + cells[i+1][j] + cells[i+1][j+1];
			if(neibourNumber == 3)
				newCells[i][j] = 1;
			else if(neibourNumber == 2)
				newCells[i][j] = cells[i][j];
			else
				newCells[i][j] = 0;
		}
	}
	for (i=1;i<High-1;i++)
		for (j=1;j<Width-1;j++)
			cells[i][j] = newCells[i][j];
}

void updateWithInput()
{
	char input;
	if (kbhit())
	{
		input = getch();
		if (input == '+')
		{
			speed *= 0.8;
		}
		if (input == '-')
		{
			speed *= 1.2;
		}
	}
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