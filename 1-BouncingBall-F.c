#include "stdio.h"
#include "stdlib.h"
#include "windows.h"
#include "conio.h"

int ball_x,ball_y;
int velocity_x,velocity_y;
int high,width;
int bat_y;
int score;

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
    ball_x = 5;
    ball_y = 10;
    velocity_x = 1;
    velocity_y = 1;
    width = 30;
    high = 20;
    bat_y = 12;
    score = 0;
}

// 显示画面
void show()
{
	Cls(0,0);
	HideCursor();
    int i,j;
    for (i = 0; i < high; i++)
    {
    	for(j = 0;j < width;j++)
    	{
    		if ((i == ball_x)&&(j == ball_y))
    			printf("O");
            else if((i != high - 1)||((j < bat_y)||(j > bat_y + 7)))
                printf(" ");
    		else
    			printf("*");
    	}
    	printf("\n");
    }
    printf("得分：%d\n", score);
    Sleep(150);
}

// 与用户输入无关的更新
void updateWithoutInput()
{
	if (ball_x == high - 1)
    {
        if((ball_y >= bat_y)&&(ball_y <= bat_y + 7))
        {
            velocity_x = -velocity_x;
            score++;
        }
        else
        {
            printf("游戏失败\n");
            system("pause");
            exit(0);
        }
    }
    ball_x += velocity_x;
    ball_y += velocity_y;
    if (ball_x == 0)
		velocity_x = -velocity_x;
	if ((ball_y == 0)||(ball_y == width))
		velocity_y = -velocity_y;
}   


// 与用户输入有关的更新
void updateWithInput()
{
    char input;
    if (kbhit())
    {
        input = getch();
        if ((input == 'a')&&(bat_y > 0))
            bat_y -= 2;
        if ((input == 'd')&&(bat_y < width - 1))
            bat_y += 2;
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


