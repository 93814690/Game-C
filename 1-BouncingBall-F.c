#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

int x,y;
int velocity_x,velocity_y;
int high,width;

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
    x = 5;
    y = 10;
    velocity_x = 1;
    velocity_y = 1;
    width = 30;
    high = 20;
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
    		if ((i == x)&&(j == y))
    			printf("o");
    		else
    			printf(" ");
    	}
    	printf("\n");
    }
    Sleep(50);
}

// 与用户输入无关的更新
void updateWithoutInput()
{
	x += velocity_x;
	y += velocity_y;
	if ((x == 0)||(x == high))
		velocity_x = -velocity_x;
	if ((y == 0)||(y == width))
		velocity_y = -velocity_y;
}

// 与用户输入有关的更新
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
