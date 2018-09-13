#include<stdio.h>
#include<Windows.h>
#include<stdlib.h>
#include<conio.h>
#define X 29
#define Y 29
struct blo
{
	char pattern[3];
	int x;
	int y;
	int xm;
	int ym;
	int collision;
}block[X][Y];
int collision_or_not = 0; //是否碰撞 0为假 1为真
int eat_food_or_not = 0; //是否吃到食物 0为没有 1为有
int direction = 6; //方向 8546 上下左右
int engine_status = -1; //引擎状态 -1或1
int snake_long=0; //蛇的长度
int xxx, yyy; //蛇头坐标
int sss; //蛇头属性
char background[3] = "□";
char snake_pattern[3] = "■";
//以下所有函数成功返回2 □■

int create_block(char pattern[3], int x, int y, int xm, int ym, int collision) //创建方块 [图案,x,y,x移动坐标,y移动坐标,障碍物标识]
{
	block[x][y].pattern[0] = pattern[0];
	block[x][y].pattern[1] = pattern[1];
	block[x][y].pattern[2] = pattern[2];
	block[x][y].x = x;
	block[x][y].y = y;
	block[x][y].xm = xm;
	block[x][y].ym = ym;
	block[x][y].collision = collision;
	return 2;
}
int create_line(char pattern[3], int x1, int y1, int x2, int y2, int xm, int ym, int collision) //创建线条 
{
	int i = 0;
	if (x1 == x2)
	{
		if (y1 < y2)
		{
			for (i = 0; i <= (y2 - y1); i++)
				create_block(pattern, x1, y1 + i, xm, ym, collision);
		}
		else if (y1 > y2)
		{
			for (i = 0; i <= (y1 - y2); i++)
				create_block(pattern, x1, y2 + i, xm, ym, collision);
		}
	}
	else if (y1 == y2)
	{
		if (x1 < x2)
		{
			for (i = 0; i <= (x2 - x1); i++)
				create_block(pattern, x1 + i, y1, xm, ym, collision);
		}
		else if (x1 > x2)
		{
			for (i = 0; i <= (x1 - x2); i++)
				create_block(pattern, x2 + i, y1, xm, ym, collision);
		}
	}
	return 2;
}
int creat_snake_head(void)
{
	create_block("■", 9, 9, (snake_long = snake_long + 1), 0, 1);
	return 2;
}
int creat_snake_tail(void)
{
	create_block("■", 8, 9, (snake_long = snake_long + 1), 0, 1);
	return 2;
}
int create_wall(void) //创建墙 
{
	create_line("■", 0, 0, X - 1, 0, 0, 0, 1);
	create_line("■", X - 1, 0, X - 1, Y - 1, 0, 0, 1);
	create_line("■", 0, 0, 0, Y - 1, 0, 0, 1);
	create_line("■", 0, Y - 1, X - 1, Y - 1, 0, 0, 1);
	return 2;
}
int Z_engine_start(void) //引擎启动 填充方块 
{
	int x, y;
	for (y = 0; y <= Y - 1; y++) //填充行
		for (x = 0; x <= X - 1; x++) //填充列
			create_block("□", x, y, 0, 0, 0);
	return 2;
}
int Z_engine_redraw(void) //重画 
{
	int x, y;
	system("cls");
	for (y = 0; y <= Y - 1; y++) //绘制行
	{
		for (x = 0; x <= X - 1; x++) //绘制列
			printf("%s", block[x][y].pattern);
		putchar('\n');
	}
	printf("direction:%d  ", direction);
	printf("collision_or_not:%d  ", collision_or_not);
	printf("engine_status:%d  ", engine_status);
	printf("蛇头坐标:%d  %d  ", xxx,yyy);
	printf("蛇头属性: %d", sss);
	return 2;
}
int monitor_collision(int x1, int y1, int x2, int y2, int collision) //检测碰撞 [起始坐标,终止坐标,障碍物标识]
{
	int i = 0;
	if (x1 == x2)
	{
		if (y1 < y2)
		{
			for (i = 1; i <= y2 - y1; i++)
			{
				if (block[x1][y1 + i].collision == collision)
					collision_or_not = 1;
				else
					;
			}
		}
		else
		{
			for (i = 1; i <= y1 - y2; i++)
			{
				if (block[x1][y2 + i - 1].collision == collision)
					collision_or_not = 1;
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
				if (block[x1 + i][y1].collision == collision)
					collision_or_not = 1;
				else
					;
			}
		}
		else
		{
			for (i = 1; i <= x1 - x2; i++)
			{
				if (block[x2 + i - 1][y1].collision== collision)
					collision_or_not = 1;
				else
					;
			}
		}

	}
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
			if (direction == 5);
			else direction = 8;
		}
		else if (button == 's' || button == 'S')
		{
			if (direction == 8);
			else direction = 5;
		}
		else if (button == 'a' || button == 'A')
		{
			if (direction == 6);
			else direction = 4;
		}
		else if (button == 'd' || button == 'D')
		{
			if (direction == 4);
			else direction = 6;
		}
		else;
	}
	else;
	return 2;
}
int move_block(void)
{
	engine_status = engine_status*(-1);
	int x, y;
	for (y = 0; y <= Y - 1 && collision_or_not == 0; y++) //行
	{
		for (x = 0; x <= X - 1 && collision_or_not == 0; x++) //列
		{
			if (block[x][y].xm == engine_status) //蛇头
			{
				if (direction == 8)
				{
					//monitor_collision(x, y, x,y - 1,1);
					block[x][y - 1].collision = block[x][y].collision;
					block[x][y - 1].xm = -1 * block[x][y].xm;
					block[x][y].xm = 0;
					block[x][y - 1].pattern[0] = block[x][y].pattern[0];
					block[x][y - 1].pattern[1] = block[x][y].pattern[1];
					block[x][y - 1].pattern[2] = block[x][y].pattern[2];
				}
				else if (direction == 5)
				{
					//monitor_collision(x, y, x,y + 1,1);
					block[x][y + 1].collision = block[x][y].collision;
					block[x][y + 1].xm = -1 * block[x][y].xm;
					block[x][y].xm = 0;
					block[x][y + 1].pattern[0] = block[x][y].pattern[0];
					block[x][y + 1].pattern[1] = block[x][y].pattern[1];
					block[x][y + 1].pattern[2] = block[x][y].pattern[2];
				}
				else if (direction == 4)
				{
					//monitor_collision(x, y, x-1, y, 1);
					block[x - 1][y].collision = block[x][y].collision;
					block[x - 1][y].xm = -1 * block[x][y].xm;
					block[x][y].xm = 0;
					block[x - 1][y].pattern[0] = block[x][y].pattern[0];
					block[x - 1][y].pattern[1] = block[x][y].pattern[1];
					block[x - 1][y].pattern[2] = block[x][y].pattern[2];
				}
				else if (direction == 6)
				{
					//monitor_collision(x, y, x + 1, y, 1);
					//block[x + 1][y].collision = block[x][y].collision; //移交碰撞属性
					block[x + 1][y].xm = (-1) * engine_status; //移交蛇头属性
					//block[x][y].xm = 0; //删除蛇头属性
					sss = block[x + 1][y].xm;
					xxx = x + 1, yyy = y;
					block[x + 1][y].pattern[0] = snake_pattern[0]; //移交蛇头外形
					block[x + 1][y].pattern[1] = snake_pattern[1];
					block[x + 1][y].pattern[2] = snake_pattern[2];
					printf("\a");
				}
				else;
			}
			else if (block[x][y].xm !=0 && block[x][y].xm != 1&& block[x][y].xm != -1) //蛇尾
			{
				if (eat_food_or_not == 0) //没吃到食物删除蛇尾
				{
					/*block[x + 1][y].collision = 0;
					block[x + 1][y].xm = 0;
					block[x][y].pattern[0] = background[0];
					block[x][y].pattern[1] = background[1];
					block[x][y].pattern[2] = background[2];*/
				}
				else //吃到食物不删除蛇尾
				{
					/*block[x + 1][y].collision = 0;
					block[x + 1][y].xm = 0;
					block[x][y].pattern[0] = background[0];
					block[x][y].pattern[1] = background[1];
					block[x][y].pattern[2] = background[2];*/
				}
			}
			else;
		}
	}
	return 2;
}
int main(void)
{
	for (; collision_or_not == 0;)
	{
		Sleep(1000);
		Z_engine_start();
		create_wall();
		creat_snake_head();
		//creat_snake_tail();
		monitor_button();
		
		move_block();

		Z_engine_redraw();
	}
	return 0;
}