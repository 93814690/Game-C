#include "stdio.h"
#include "stdlib.h"
#include "conio.h"
#include "windows.h"

int high,width;
int bird_x,bird_y;
int bar1_y,bar1_xDown,bar1_xTop;
int score;


//类似于清屏函数
void gotoxy(int x,int y)
{
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD pos;
	pos.X = x;
	pos.Y = y;
	SetConsoleCursorPosition(handle,pos);
}



//数据初始化
void startup()
{
	high = 20;
	width = 24;
	bird_x = 0;
	bird_y = width / 3;
	bar1_y = width;
	bar1_xDown = high / 3;
	bar1_xTop = high / 2;
	score = 0;
}


//显示画面
void show()//显示画面
{
	gotoxy(0,0);//清屏
	int i,j;

	for (i = 0; i < high; i++)
	{
		for (j = 0; j < width; j++)
		{
			if ((i == bird_x)&&(j == bird_y))
				printf("@");//输出小鸟
			else if ((j == bar1_y)&&((i < bar1_xDown)||(i > bar1_xTop)))
				printf("*");//输出墙壁
			else if ((i +1 == high)&&(j + 1 != width))
				printf("_");
			else if (j + 1 == width)
				printf("|");
			else
				printf(" ");//输出空格
		}
		printf("\n");
	}
	printf("Score:%d\n",score );
}


//与用户输入无关的更新
void updateWithoutInput()
{
	bird_x ++;
	bar1_y --;
	if (bird_y == bar1_y)
	{
		if ((bird_x >= bar1_xDown)&&(bird_x <= bar1_xTop))
			score ++;
		else
		{
			printf("游戏失败\n");
			system("pause");
			exit(0);
		}
	}
	if (bird_x >= high)
	{
		printf("游戏失败\n");
		system("pause");
		exit(0);
	}
	if (bar1_y <= 0)// 再新生成一个障碍物
	{
		bar1_y = width;
		int temp = rand()%(int)(high*0.8);
		bar1_xDown = temp - high/10;
		bar1_xTop = temp + high/10;
	}

	Sleep(250);
}

// 与用户输入有关的更新
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
