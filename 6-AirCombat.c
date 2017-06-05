#include "stdio.h"
#include "stdlib.h"
#include "conio.h"
#include "windows.h"

#define HIGH 15
#define WIDTH 25
#define ENEMYNUM 5

//全局变量
int position_x,position_y;
int enemy_x[ENEMYNUM],enemy_y[ENEMYNUM];
int canvas[HIGH][WIDTH] = {0};
int score;
int BulletWidth;
int EnemyMoveSpeed;

void gotoxy(int x,int y)  //光标移动到(x,y)位置
{
    HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD pos;
    pos.X = x;
    pos.Y = y;
    SetConsoleCursorPosition(handle,pos);
}

void HideCursor()//隐藏光标
{
	CONSOLE_CURSOR_INFO cursor_info = {1, 0};
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor_info);
}


void newEnemy(int k)
{
	enemy_x[k] = rand() % 2;
	enemy_y[k] = rand() %WIDTH;
	canvas[enemy_x[k]][enemy_y[k]] = 3;
}

void startup()
{
	position_x = HIGH - 1;
	position_y = WIDTH / 2;
	canvas[position_x][position_y] = 1;
	for (int k = 0; k < ENEMYNUM; ++k)
	{
		newEnemy(k);
	}
	score = 0;
	BulletWidth = 0;
	EnemyMoveSpeed = 20;
}

void show()
{
	gotoxy(0,0);
	for (int i = 0; i < HIGH; ++i)
	{
		for (int j = 0; j < WIDTH; ++j)
		{
			if (canvas[i][j] == 0)
			{
				printf(" ");
			}
			else if (canvas[i][j] == 1)
			{
				printf("*");
			}
			else if (canvas[i][j] == 2)
			{
				printf("|");
			}
			else if (canvas[i][j] == 3)
			{
				printf("@");
			}
		}
		printf("\n");
	}
	printf("得分:%d\n",score );
	Sleep(20);
}

void updateWithoutInput()
{
	for (int i = 0; i < HIGH; ++i)
	{
		for (int j = 0; j < WIDTH; ++j)
		{
			if (canvas[i][j] == 2)
			{
				for (int k = 0; k < ENEMYNUM; ++k)
				{
					if ((i == enemy_x[k])&&(j == enemy_y[k]))
					{
						score++;
						if (score%5==0 && EnemyMoveSpeed>3)
						{
							EnemyMoveSpeed--;
						}
						if (score%5==0)
						{
							BulletWidth++;
						}
						canvas[enemy_x[k]][enemy_y[k]] = 0;
						newEnemy(k);
						canvas[i][j] = 0;
					}
				}
				//子弹向上移动
				canvas[i][j] = 0;
				if (i>0)
				{
					canvas[i-1][j] = 2;
				}
			}
		}
	}

	static int speed = 0;
	if (speed<EnemyMoveSpeed)
	{
		speed++;
	}

	for (int k = 0; k < ENEMYNUM; ++k)
	{
		if ((position_x == enemy_x[k]) && (position_y == enemy_y[k]))
		{
			printf("失败！\n");
			Sleep(3000);
			system("pause");
			exit(0);
		}
		
		//敌机跑出屏幕
		if (enemy_x[k]>HIGH)
		{
			canvas[enemy_x[k]][enemy_y[k]] == 0;
			newEnemy(k);
			score--;
		}

		if (speed == EnemyMoveSpeed)
		{
			//敌机下落
			for (int k = 0; k < ENEMYNUM; ++k)
			{
				canvas[enemy_x[k]][enemy_y[k]] = 0;
				enemy_x[k]++;
				speed = 0;
				canvas[enemy_x[k]][enemy_y[k]] = 3;
			}
		}
	}

	HideCursor();
}

void updateWithInput()
{
	char input;
	if (kbhit())
	{
		input = getch();
		if (input == 'a' && position_y>0) 
		{
			canvas[position_x][position_y] = 0;
			position_y--;  // 位置左移
			canvas[position_x][position_y] = 1;
		}
		else if (input == 'd' && position_y < WIDTH-1)
		{
			canvas[position_x][position_y] = 0;
			position_y++;  // 位置右移
			canvas[position_x][position_y] = 1;
		}
		else if (input == 'w')
		{
			canvas[position_x][position_y] = 0;
			position_x--;  // 位置上移
			canvas[position_x][position_y] = 1;
		}
		else if (input == 's' && position_x < HIGH-1)
		{
			canvas[position_x][position_y] = 0;
			position_x++;  // 位置下移
			canvas[position_x][position_y] = 1;
		}
		else if (input == ' ')
		{
			int left = position_y - BulletWidth;
			int right = position_y + BulletWidth;
			if (left<0)
			{
				left = 0;
			}
			if (right > WIDTH-1)
			{
				right = WIDTH-1;
			}
			for (int k = left; k <= right; ++k)
			{
				canvas[position_x-1][k] = 2;
			}
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