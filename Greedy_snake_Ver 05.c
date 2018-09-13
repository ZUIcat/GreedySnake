#include<stdio.h>
#include<Windows.h>
#include<stdlib.h>
#include<conio.h>
#define X 100
#define Y 29 //这两行为地图大小
char blocks[X][Y];
int death_or_not = 0; //是否死亡 0为假 1为真
char direction='w'; //蛇的起始方向
char snake_speed = 1; //蛇的速度
int snake_x = 10; 
int snake_y = 10; //这两行为蛇的初始作标
int refresh_frequency = 200; //刷新频率 单位毫秒

void draw_blocks(int x, int y, char kind) //绘制 方块 [x,y,方块种类]
{
	blocks[x][y] = kind;
}
void draw_line(int x1, int y1, int x2, int y2, char kind)
{
	int i = 0;
	if (x1 == x2)
	{
		if (y1 < y2)
		{
			for (i = 0; i <= (y2 - y1); i++)
				draw_blocks(x1, y1 + i, kind);
		}
		else if (y1 > y2)
		{
			for (i = 0; i <= (y1 - y2); i++)
				draw_blocks(x1, y2 + i, kind);
		}
	}
	else if (y1 == y2) 
	{
		if (x1 < x2)
		{
			for (i=0; i <= (x2 - x1); i++)
				draw_blocks(x1 + i, y1, kind);
		}
		else if (x1 > x2)
		{
			for (i=0; i <= (x1 - x2); i++)
				draw_blocks(x2 + i, y1, kind);
		}
	}
}
void draw_wall() //绘制 墙
{
	draw_line(0, 0, X - 1, 0, 'W');
	draw_line(X - 1, 0, X - 1, Y - 1, 'W');
	draw_line(0, 0, 0, Y - 1, 'W');
	draw_line(0, Y - 1, X - 1, Y - 1, 'W');
}
void monitor_collision(int x1, int y1, int x2, int y2, char kind) //检测碰撞 [起始坐标,终止坐标,障碍物标识]
{
	int i = 0;
	if (x1 == x2)
	{
		if (y1 < y2)
		{
			for (i = 1; i <= y2 - y1; i++)
			{
				if (blocks[x1][y1 + i] == kind)
					death_or_not = 1;
				else
					;
			}
		}
		else 
		{
			for (i = 1; i <= y1 - y2; i++)
			{
				if (blocks[x1][y2 + i-1] == kind)
					death_or_not = 1;
				else
					;
			}
		}
	}
	else if (y1 == y2)
	{
		if (x1 < x2)
		{
			for (i = 1; i <= x2 - x1; i++)
			{
				if (blocks[x1 + i][y1] == kind)
					death_or_not = 1;
				else
					;
			}
		}
		else
		{
			for (i = 1; i <= x1 - x2; i++)
			{
				if (blocks[x2 + i-1][y1] == kind)
					death_or_not = 1;
				else
					;
			}
		}
		
	}
}
void move_blocks() //移动方块
{
	if (direction == 'w'|| direction == 'W')
	{
		monitor_collision(snake_x,snake_y,snake_x, snake_y - snake_speed,'W');
		snake_y = snake_y - snake_speed;
		draw_blocks(snake_x, snake_y + snake_speed, 32);
		draw_blocks(snake_x, snake_y, 'S');
	}
	else if (direction == 's'|| direction == 'S')
	{
		monitor_collision(snake_x, snake_y, snake_x, snake_y + snake_speed, 'W');
		snake_y = snake_y + snake_speed;
		draw_blocks(snake_x, snake_y - snake_speed, 32);
		draw_blocks(snake_x, snake_y, 'S');
	}
	else if (direction == 'a'|| direction == 'A')
	{
		monitor_collision(snake_x, snake_y,snake_x - snake_speed, snake_y, 'W');
		snake_x = snake_x - snake_speed;
		draw_blocks(snake_x + snake_speed, snake_y, 32);
		draw_blocks(snake_x, snake_y, 'S');
	}
	else if (direction == 'd'|| direction == 'D')
	{
		monitor_collision(snake_x, snake_y, snake_x + snake_speed, snake_y, 'W');
		snake_x = snake_x + snake_speed;
		draw_blocks(snake_x - snake_speed, snake_y, 32);
		draw_blocks(snake_x, snake_y, 'S');
	}
}
void monitor_button(void)  //检测按键
{
	char button;
	if (kbhit() == 1) //按下
	{
		button = getch();
		if (button == 'w' || button == 'W' || button == 's' || button == 'S' || button == 'a' || button == 'A' || button == 'd' || button == 'D')
			direction = button;
		else
			;
	}
	else //没有按下
	{

	}
}
void initialize(void) //初始化 填充空格
{
	int x, y;
	for (y = 0; y <=Y-1; y++) //填充行
		for (x = 0; x <= X-1; x++) //填充列
			draw_blocks(x, y, 32);
}
void redraw(void) //重绘所有方块  
{
	int x, y;
	system("cls");
	for (y=0; y<= Y-1; y++) //绘制行
	{
		for (x=0; x <= X-1; x++) //绘制列
			printf("%c", blocks[x][y]);
		putchar('\n');
	}

}
void clock(int time) //时钟 [周期(单位毫秒)]
{
	for (;death_or_not==0;)
	{
		monitor_button();//检测按键
		move_blocks();//移动方块
		printf("%d", death_or_not);//输出情况
		redraw(); //重绘所有方块
		Sleep(time);
	}
}
int main(void)
{
	initialize(); //初始化 填充空格
	draw_wall(); //绘制 墙 	
	redraw(); //重绘所有方块  
	clock(refresh_frequency); //时钟
	return 0;
}
