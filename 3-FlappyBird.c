#include "stdio.h"
#include "stdlib.h"
#include "conio.h"
#include "windows.h"

int high,width;
int bird_x,bird_y;
int bar1_y,bar1_xDown,bar1_xTop;

void gotoxy(int x,int y)
{
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD pos;
	pos.X = x;
	pos.Y = y;
	SetConsoleCursorPosition(handle,pos);
}

void startup()
{
	high = 15;
	width = 21;
	bird_x = 0;
	bird_y = width / 3;
}

void show()
{
	gotoxy(0,0);
	int i,j;

	for (i = 0; i < high; i++)
	{
		for (j = 0; j < width; j++)
		{
			if ((i == bird_x)&&(j == bird_y))
				printf("@");
			else
				printf(" ");
		}
		printf("\n");
	}
}

void updateWithoutInput()
{
	bird_x++;
	Sleep(200);
}

void updateWithInput()
{
	char input;
	if (kbhit())
	{
		input = getch();
		if (input == ' ')
		{
			bird_x -= 2;
		}
	}
}


int main ()
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
