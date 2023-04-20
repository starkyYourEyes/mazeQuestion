#pragma once
#include <iostream>
#include <string>
#include "stack.h"
#include "pos.h"
#include "maze.h"
#include "general.h"
typedef POS VertexType;
typedef std::string InfoType;
//图的邻接表存储表示

typedef struct ArcNode	//边结点的类型定义
{
	int adjvex;			// 边的另一顶点的在数组中的位置
	ArcNode* nextarc;	// 指向下一条边的指针
	InfoType direction;		// 该边相关信息(是在当前点的上下左右？哪个方向)
}ArcNode;
typedef struct VNode	//顶点结点
{
	VertexType data;	//顶点信息（上下左右）
	ArcNode* firstarc;	//指向关联该顶点的边链表
}VNode, AdjList[(MAXWIDTH + 2) * (MAXLENGTH + 2)];

class ALGraph//有向图类
{
private:
	AdjList vertices;
	int vexnum, arcnum;// 图的当前顶点数和边数
public:
	ALGraph(int vex = 0, int arc = 0) : vexnum(vex), arcnum(arc)
	{}
	int LocateVex(const VertexType& v) const;//确定另一条边在有向图中的位置
	void showGraph() const;//显示有向图的邻接表表示
	void CreateGraph(const MAZE& m);//创建迷宫类的有向图对邻接表表示
};
