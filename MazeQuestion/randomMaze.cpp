#include "randomMazes.h"
using std::cout;
using std::endl;
rMaze::rMaze(short(&M)[MAXWIDTH][MAXLENGTH], int w, int l)
{
	for (int i = 0; i < w; ++i)
		for (int j = 0; j < l; ++j)
			this->m_m[i][j] = M[i][j];
	this->m_w = w;
	this->m_l = l;
}

rMaze randomMaze()
{
	srand((unsigned)time(nullptr));//随机数
	int t = rand() % 10;	
	int tt = rand() % 10;
	t = (t + tt) % 10;//随机数随机一个地图
	int y = 0, x = 0;
	short new_maze[MAXWIDTH][MAXLENGTH];

	//确定随机的迷宫的真实的长度与宽度
	for (y = 0; y < MAXLENGTH; ++y)
	{
		if (mazeDatabase[t][0][y] == -1)
			break;
	}
	for (x = 0; x < MAXWIDTH; ++x)
	{
		if (mazeDatabase[t][x][0] == -1)
			break;
	}

	for (int i = 0; i < x; ++i)
	{
		for (int j = 0; j < y; ++j)
		{
			new_maze[i][j] = mazeDatabase[t][i][j];
		}
	}

	return { new_maze, x, y };//返回一个随机迷宫类(包括了长和宽)
}