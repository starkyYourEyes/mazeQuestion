#pragma once
#include "stack.h"
#include "queue.h"
#include "pos.h"
#include "general.h"
#include <iostream>
#include <iomanip>
#include <Windows.h>

using namespace std;

class MAZE      //使用迷宫类
{
private:
    short** m_maze;//用来维护迷宫的动态数组
    short _width, _length;   //表示迷宫的实际规模
    POS enter;  //入口的坐标
    POS aim;    //出口的坐标
    Stack path1;    //用来存放走过的路径的栈
    Stack spath;    //用来保存最小的路径

public:
    friend class ALGraph;//作为ALGraph，有向图的友元类

    MAZE();
    void setMaze();//自己输入迷宫
    MAZE(short (& map)[MAXWIDTH][MAXLENGTH], int width, int lnegth);    //复制构造函数,用给定的迷宫进行迷宫的初始化
    ~MAZE();
    //short[2] mazeWandL();
    bool canPass(const POS& now, const POS& next) const;    //检查当前的格子是否可以走

    void show_Maze() const;   //显示迷宫情况

    void find_Way_DFS(const POS& p);   //递归形式的算法；

    void isTherePath_DFS(); //得出有没有通路  和如果有直接输出最短路径DFS

    void find_Way_StackNotDFS();    //	用栈编写求解迷宫问题的非递归程序；

    void find_Way_BFS();    //广度优先遍历

    void backWay(short x, short y, POS (& pre)[MAXWIDTH][MAXLENGTH]); //借助栈来输出广度优先遍历的最短路径.
    
    void isTherePath_BFS();//得出有没有通路  和如果有直接输出最短路径BFS

    void showResultWithStar() const;//最短路径用 * 表示

    void showResultWithColor() const;//最短路径带颜色输出

    void showRawMaze() const;//输出原始状态的迷宫

    void recoverMaze();//恢复迷宫的原始状态，防止连续调用寻路算法相互之前的干扰

    POS checkWidthAndLength() const;//返回迷宫的长和宽

};




