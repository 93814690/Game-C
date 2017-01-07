#include "stdio.h"
#include "stdlib.h"
#include "conio.h"
#include "windows.h"
#include "time.h"

#define High 25
#define Width 50

int cells[High][Width];

void HideCursor()
{
	CONSOLE_CURSOR_INFO cursor_info = {1, 0};
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor_info);
}

void startup()
{
	int i,j;
	for (i = 0; i < High; i++)
		for (j = 0;j < Width;j++)
		{
			cells[i][j] = rand() % 2;
		}
}

void show()
{
	HideCursor();
	system("cls");
	int i,j;
	for (i = 0; i <= High; i++)
	{
		for (j = 0; j <= Width; j++)
		{
			if (cells[i][j] == 1)
				printf("*");
			else
				printf(" ");
		}
		printf("\n");
	}
	Sleep(50);
}

void updateWithoutInput()
{
	int newCells[High][Width];
	int neibourNumber;
	int i,j;
	for (i=1;i<=High-1;i++)
	{
		for (j=1;j<=Width-1;j++)
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
	for (i=1;i<=High-1;i++)
		for (j=1;j<=Width-1;j++)
			cells[i][j] = newCells[i][j];
}

void updateWithInput()
{

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