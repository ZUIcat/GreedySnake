#include <stdio.h>
#include <Windows.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>
#include <string.h>

#define X 29
#define Y 29 //地图大小

int block[X][Y];
int direction = 4;			 //蛇的方向 8546 wsad
int snake_long = 0;			 //蛇身长度
int game_continue = 1;		 //游戏是否继续 0否 1是
int refresh_frequency = 500; //引擎刷新频率 单位毫秒
char other_information[30] = "游戏开始,祝您开心.";

//以下函数成功返回2
//-2   -1   0    1
//食物 墙体 空白 蛇

int return_random(int x, int y) //x < y
{
	int random;
	random = rand() % (y - x + 1) + x;
	return random;
}

int random_direction(void)
{
	int random = return_random(1, 4);
	if (random == 1)
		direction = 4;
	else if (random == 2)
		direction = 5;
	else if (random == 3)
		direction = 6;
	else if (random == 4)
		direction = 8;
	return 2;
}

int create_block(int x, int y, int kind) //创建方块
{
	block[x][y] = kind;
	return 2;
}

int create_line(int x1, int y1, int x2, int y2, int kind) //创建线条
{
	int i = 0;
	if (x1 == x2)
	{
		if (y1 < y2)
		{
			for (i = 0; i <= (y2 - y1); i++)
				create_block(x1, y1 + i, kind);
		}
		else if (y1 > y2)
		{
			for (i = 0; i <= (y1 - y2); i++)
				create_block(x1, y2 + i, kind);
		}
	}
	else if (y1 == y2)
	{
		if (x1 < x2)
		{
			for (i = 0; i <= (x2 - x1); i++)
				create_block(x1 + i, y1, kind);
		}
		else if (x1 > x2)
		{
			for (i = 0; i <= (x1 - x2); i++)
				create_block(x2 + i, y1, kind);
		}
	}
	return 2;
}

int create_wall(void) //创建墙
{
	create_line(0, 0, X - 1, 0, -1);
	create_line(X - 1, 0, X - 1, Y - 1, -1);
	create_line(0, 0, 0, Y - 1, -1);
	create_line(0, Y - 1, X - 1, Y - 1, -1);
	return 2;
}

int create_snake(void)
{
	int x = return_random(0, X), y = return_random(0, Y);
	if (block[x][y] == 0)
	{
		create_block(x, y, 1);
		snake_long = snake_long + 1;
	}
	else
		create_snake();
	return 2;
}

int create_food(void)
{
	int x = return_random(0, X), y = return_random(0, Y);
	if (block[x][y] == 0)
	{
		create_block(x, y, -2);
	}
	else
		create_food();
	return 2;
}

int level_up(void)
{
	if (snake_long >= 60)
	{
		strcpy(other_information, "啊啊啊啊啊啊!!!.");
		create_food();
		refresh_frequency = 20;
	}
	else if (snake_long >= 40)
	{
		strcpy(other_information, "狂暴模式开启!!!");
		create_food();
		refresh_frequency = 50;
	}
	else if (snake_long >= 30)
	{
		strcpy(other_information, "越来越猛了啊!");
		create_food();
		refresh_frequency = 100;
	}
	else if (snake_long >= 25)
	{
		strcpy(other_information, "但是没办法.");
		create_food();
		refresh_frequency = 200;
	}
	else if (snake_long >= 20)
	{
		strcpy(other_information, "频闪是有点严重.");
		create_food();
		refresh_frequency = 300;
	}
	else if (snake_long >= 15)
	{
		strcpy(other_information, "速度也会变快!");
		create_food();
		refresh_frequency = 350;
	}
	else if (snake_long >= 10)
	{
		strcpy(other_information, "食物会变多!");
		create_food();
		refresh_frequency = 400;
	}
	else if (snake_long >= 5)
	{
		strcpy(other_information, "游戏进行中!");
		create_food();
		refresh_frequency = 450;
	}
	return 2;
}

int out_put_information(void)
{
	printf("蛇的方向:%d ", direction);
	printf("你的得分:%d ", snake_long - 1);
	printf("游戏速度:%d ", refresh_frequency);
	printf("%s", other_information);
	return 2;
}

int Z_engine_start(void) //引擎启动 填充方块
{
	int x, y;
	for (y = 0; y <= Y - 1; y++)	 //填充行
		for (x = 0; x <= X - 1; x++) //填充列
			create_block(x, y, 0);
	return 2;
}

int Z_engine_redraw(void) //重画
{
	int x, y;
	system("cls");
	for (y = 0; y <= Y - 1; y++) //绘制行
	{
		for (x = 0; x <= X - 1; x++) //绘制列
		{
			if (block[x][y] == 0) //空白
				printf("%s", "  ");
			else if (block[x][y] == -1) //墙
				printf("%s", "■");
			else if (block[x][y] == -2) //食物
				printf("%s", "◇");
			else if (block[x][y] > 0) //蛇
				printf("%s", "◆");
		}
		putchar('\n');
	}
	out_put_information();
	return 2;
}

int monitor_button(void) //检测按键
{
	char button;
	if (kbhit() == 1) //按下
	{
		button = getch();
		if (button == 'w' || button == 'W')
		{
			if (direction != 5)
				direction = 8;
		}
		else if (button == 's' || button == 'S')
		{
			if (direction != 8)
				direction = 5;
		}
		else if (button == 'a' || button == 'A')
		{
			if (direction != 6)
				direction = 4;
		}
		else if (button == 'd' || button == 'D')
		{
			if (direction != 4)
				direction = 6;
		}
	}
	return 2;
}

int snake_long_reset(void)
{
	int x, y;
	for (y = 0; y <= Y - 1; y++) //检测行
	{
		for (x = 0; x <= X - 1; x++) //检测列
		{
			if (block[x][y] > 0)			   //检测到蛇
				block[x][y] = block[x][y] + 1; //kind+1
		}
	}
	return 2;
}

int game_over(void) //游戏结束
{
	game_continue = 0;
	system("color 40");
	strcpy(other_information, "YOU LOST!");
	return 2;
}

int delete_snake_tali(void)
{
	int x, y;
	for (y = 0; y <= Y - 1; y++) //检测行
	{
		for (x = 0; x <= X - 1; x++) //检测列
		{
			if (block[x][y] == snake_long + 1)
				block[x][y] = 0;
		}
	}
	return 2;
}

int move_block(void) //移动方块
{
	int x, y;
	level_up();
	for (y = 0; y <= Y - 1 && game_continue == 1; y++) //行
	{
		for (x = 0; x <= X - 1 && game_continue == 1; x++) //列
		{
			if (block[x][y] == 1) //找到蛇头
			{
				if (direction == 8)
				{
					if (block[x][y - 1] == -1) //撞到墙
						goto miao;
					else if (block[x][y - 1] == -2) //吃到食物
					{
						snake_long_reset();
						create_block(x, y - 1, 1);
						snake_long = snake_long + 1;
						create_food();
						goto wang;
					}
					else if (block[x][y - 1] > 0) //撞到自己
						goto miao;
					else //正常行走
					{
						snake_long_reset();
						create_block(x, y - 1, 1);
						delete_snake_tali();
						goto wang;
					}
				}
				else if (direction == 5)
				{
					if (block[x][y + 1] == -1) //撞到墙
						goto miao;
					else if (block[x][y + 1] == -2) //吃到食物
					{
						snake_long_reset();
						create_block(x, y + 1, 1);
						snake_long = snake_long + 1;
						create_food();
						goto wang;
					}
					else if (block[x][y + 1] > 0) //撞到自己
						goto miao;
					else //正常行走
					{
						snake_long_reset();
						create_block(x, y + 1, 1);
						delete_snake_tali();
						goto wang;
					}
				}
				else if (direction == 4)
				{
					if (block[x - 1][y] == -1) //撞到墙
						goto miao;
					else if (block[x - 1][y] == -2) //吃到食物
					{
						snake_long_reset();
						create_block(x - 1, y, 1);
						snake_long = snake_long + 1;
						create_food();
						goto wang;
					}
					else if (block[x - 1][y] > 0) //撞到自己
						goto miao;
					else
					{
						snake_long_reset();
						create_block(x - 1, y, 1);
						delete_snake_tali();
						goto wang;
					}
				}
				else if (direction == 6)
				{
					if (block[x + 1][y] == -1) //撞到墙
						goto miao;
					else if (block[x + 1][y] == -2) //吃到食物
					{
						snake_long_reset();
						create_block(x + 1, y, 1);
						snake_long = snake_long + 1;
						create_food();
						goto wang;
					}
					else if (block[x + 1][y] > 0) //撞到自己
						goto miao;
					else
					{
						snake_long_reset();
						create_block(x + 1, y, 1);
						delete_snake_tali();
						goto wang;
					}
				}
			}
		}
	}
wang:
	return 2;
miao:
	game_continue = 0;
	return 2;
}

int main(void)
{
	srand((unsigned int)time(NULL));
	system("mode con cols=58 lines=30");
	system("color 9f");
	system("title=贪吃蛇 v7.0");
	Z_engine_start();
	create_wall();
	create_snake();
	create_food();
	create_food();
	random_direction();
	for (; game_continue == 1;)
	{
		Sleep(refresh_frequency);
		monitor_button();
		move_block();
		Z_engine_redraw();
	}
	game_over();
	Z_engine_redraw();
	system("pause >nul");
	return 0;
}
