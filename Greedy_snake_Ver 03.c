#include<stdio.h>
#include<Windows.h>
#define X 29
#define Y 29
int block[X][Y][6];
int collision_or_not = 0;
//以下所有函数成功返回2 □■

int create_block(int pattern, int x, int y, int xm, int ym, int collision) //创建方块 [图案,x,y,x移动坐标,y移动坐标,障碍物标识]
{
	block[x][y][0] = pattern;
	block[x][y][1] = x;
	block[x][y][2] = y;
	block[x][y][3] = xm;
	block[x][y][4] = ym;
	block[x][y][5] = collision;
	return 2;
}
int create_line(int pattern, int x1, int y1, int x2, int y2, int xm, int ym, int collision) //创建线条 
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
int create_wall() //创建墙 
{
	create_line("■", 0, 0, X - 1, 0, 0, 0, 1);
	create_line("■", X - 1, 0, X - 1, Y - 1, 0, 0, 1);
	create_line("■", 0, 0, 0, Y - 1,0 , 0, 1);
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
			printf("%s", block[x][y][0]);
		putchar('\n');
	}
	return 2;
}
int move_block()
{
	int x, y,xm,ym;
	for (y = 0; y <= Y - 1&& collision_or_not == 0; y++) //行
	{
		for (x = 0; x <= X - 1&& collision_or_not == 0; x++) //列
		{
			
			xm = block[x][y][3];
			ym = block[x][y][4];
			if (xm == 0 && ym == 0)
			{
				;
			}
			else
			{
				monitor_collision(x, y, x + xm, y + ym, 1);
				block[x + xm][y + ym][0] = block[x][y][0];
				block[x + xm][y + ym][3] = block[x][y][3];
				block[x + xm][y + ym][4] = block[x][y][4];
				block[x + xm][y + ym][5] = block[x][y][5];
				//block[x][y][0] = "□";
				//block[x][y][3] = 0;
				//block[x][y][4] = 0;
				Z_engine_redraw();
				Sleep(1000);
			}
		}
		putchar('\n');
	}
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
				if (block[x1][y1 + i][5] == collision)
					collision_or_not = 1;
				else
					;
			}
		}
		else
		{
			for (i = 1; i <= y1 - y2; i++)
			{
				if (block[x1][y2 + i - 1][5] == collision)
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
				if (block[x1 + i][y1][5] == collision)
					collision_or_not = 1;
				else
					;
			}
		}
		else
		{
			for (i = 1; i <= x1 - x2; i++)
			{
				if (block[x2 + i - 1][y1][5] == collision)
					collision_or_not = 1;
				else
					;
			}
		}

	}
	return 2;
}
int monitor_button() //检测按键 
{

	return 2;
}
int main(void)
{
	Z_engine_start();
	create_wall();

	block[10][5][0] = "■";
	block[10][5][3] = 1;
	block[10][5][4] = 0;
	block[10][5][5] = 1;
	block[9][5][0] = "■";
	block[9][5][3] = 1;
	block[9][5][4] = 0;
	block[9][5][5] = 1;
	
	move_block();
	printf("%d", collision_or_not);
	system("pause");
	return 0;
}
