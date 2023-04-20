#include "graph.h"
#include "maze.h"
using namespace std;

int ALGraph::LocateVex(const VertexType& v) const
{
	for (int i = 0; i < this->vexnum; ++i)
	{
		if (this->vertices[i].data == v)
			return i;
	}
	return 0;
}

void ALGraph::showGraph() const
{
	for (int i = 0; i < this->vexnum; ++i)
	{	//输出头结点信息
		cout << "\033[36;1m[" << setw(2) << this->vertices[i].data._x << "," << setw(2) << this->vertices[i].data._y << "]" << ": \033[0m";
		ArcNode* p = this->vertices[i].firstarc;

		while (p)//输出每一条边的信息以及对应的节点坐标
		{
			cout << p->direction << ":" << this->vertices[p->adjvex].data << ", ";
			p = p->nextarc;
		}
		if (this->vertices[i].firstarc)
			cout << "\b\b  ";//清除最后输出的", "
		cout << endl;
	}
}

void ALGraph::CreateGraph(const MAZE& m)
{
	VertexType v1, v2;
	//因为之前对于迷宫的更改，需要对起始点（1，1）进行特殊处理
	this->vexnum = 0;//顶点的个数
	for (short i = 1; i < m._width + 1; ++i)
	{//头结点数组
		for (short j = 1; j < m._length + 1; ++j)
		{
			this->vertices[this->vexnum++] = { { i, j }, nullptr };
		}
	}
	this->arcnum = 0;
	POS move[4] = { {0,1},{1,0},{0,-1},{-1,0} };//右、下、左、上四个方向
	//对（1，1）单独处理
	for (int j = 0; j < 4; ++j)//向四个方向遍历，建立每一个头结点对应的单链表
	{
		POS next = this->vertices[0].data + move[j];//下一个坐标点
		string dir[4] = { "右","下","左","上" };//边的信息
		if (m.m_maze[next._x][next._y] != 1)//如果是可以通过的
		{
			int m = LocateVex(next);//确定  另一个节点  在图中 的位置。

			ArcNode* p = new ArcNode{ m, this->vertices[0].firstarc, dir[j] };//生成一个新的边结点
			this->vertices[0].firstarc = p;//将新结点插入到顶点vi的边链表头部 （头插法
			this->arcnum++;
		}
	}

	for (int i = 1; i < this->vexnum; ++i)	//构造邻接表
	{
		if (m.m_maze[this->vertices[i].data._x][this->vertices[i].data._y] == 1)
		{//如果是墙体，直接跳过
			continue;
		}
		for (int j = 0; j < 4; ++j)//向四个方向遍历，建立每一个头结点对应的单链表
		{
			POS next = this->vertices[i].data + move[j];//下一个坐标点
			string dir[4] = { "右","下","左","上" };//边的信息
			if (m.m_maze[next._x][next._y] != 1 || POS{ next._x, next._y } == m.enter)//如果是可以通过的
			{
				int m = LocateVex(next);//确定  另一个节点  在G中 的位置。
				
				ArcNode* p = new ArcNode{ m, this->vertices[i].firstarc, dir[j]};//生成一个新的边结点
				this->vertices[i].firstarc = p;//将新结点插入到顶点Vi的边链表头部
				this->arcnum++;
			}
		}
	}
}



