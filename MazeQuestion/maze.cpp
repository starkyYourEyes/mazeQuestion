#include "maze.h"
#include "stack.h"

#include <iostream>
using namespace std;

MAZE::MAZE()

{   
    this->m_maze = nullptr;
    this->_width = this->_length = 0;
}
void MAZE::setMaze()
{
    cout << "输入迷宫的规模(m * n）：" << endl;
    cin >> _width >> _length;
    this->enter = { 1, 1 };
    this->aim = { _width, _length };    //设置起始点和终点?

    this->m_maze = new short* [_width + 2];
    for (int i = 0; i < _width + 2; ++i)
        this->m_maze[i] = new short[_length + 2]; //为迷宫分配内存空间
    //这里多分配了两个内存空间  是因为要把迷宫的最外围的内存设置为  障碍

    for (int i = 0; i < _length + 2; ++i)
    {   // 定义上下边的墙值为1
        this->m_maze[0][i] = 1;
        this->m_maze[_width + 1][i] = 1;
    }
    for (int i = 1; i < _width + 1; ++i)
    {   // 定义左右边除了第一行和最后一行的墙值为0
        this->m_maze[i][0] = 1;
        this->m_maze[i][_length + 1] = 1;
    }

    cout << "输入迷宫（0表示通路，1表示障碍）:" << endl;
    cout << "如果希望终止输入，输入q。" << endl;

    for (int i = 1; i < _width + 1; ++i)
        for (int j = 1; j < _length + 1; ++j)
        {
            if (!(cin >> this->m_maze[i][j]))
            {//如果中途要终止输入。
                cin.clear();
                while (cin.get() != '\n')
                    continue;
                system("cls");
                return;
            }
        }


}
MAZE::MAZE(short(& map)[MAXWIDTH][MAXLENGTH], int width, int length)
{   //构造函数，用一个二维数组来初始化迷宫
    this->_width = width;
    this->_length = length;
    this->enter = { 1, 1 };
    this->aim = { _width, _length };    //设置起始点和终点
    //this->aim = { 1, 5 };    //设置起始点和终点

    this->m_maze = new short* [_width + 2];
    for (int i = 0; i < _width + 2; ++i)
        this->m_maze[i] = new short[_length + 2]; //为迷宫分配内存空间
    //这里多分配了两个内存空间  是因为要把迷宫的最外围的内存设置为  障碍

    for (int i = 0; i < _length + 2; ++i) // 定义上下边的墙值为1
    {
        this->m_maze[0][i] = 1;
        this->m_maze[_width + 1][i] = 1;
    }
    for (int i = 1; i < _width + 1; ++i) // 定义左右边除了第一行和最后一行的墙值为0
    {
        this->m_maze[i][0] = 1;
        this->m_maze[i][_length + 1] = 1;
    }
    for (int i = 1; i < _width + 1; ++i)
        for (int j = 1; j < _length + 1; ++j)
            this->m_maze[i][j] = map[i - 1][j - 1];
    //假设  给的迷宫（即二维数组）  是没有设置最外层的障碍的
}
MAZE::~MAZE()
{   //析构函数
    if (this->m_maze == nullptr)   //如果已为空指针，不delete
        return;
    for (int i = 0; i < _width + 2; ++i)
        delete[] this->m_maze[i];
    delete[] this->m_maze;  //释放分配的所有内存



    this->m_maze = nullptr;
    _width = _length = 0;
    //类中的栈成员有自己的析构函数（自行释放内存）
}
void MAZE::show_Maze() const
{
    //cout << "--------------------------------------" << endl << endl;
 /*   cout << "迷宫的情况如下：" << endl;*/
    for (int i = 1; i < this->_length + 1; ++i)
        cout << "---";
    cout << "--" << endl;

    //for (int i = 0; i < this->_width + 2; ++i)
    //{
    //    for (int j = 0; j < this->_length + 2; ++j)
    //        cout << setw(2) << this->m_maze[i][j] << " ";
    //    cout << endl;
    //}
    for (int i = 1; i < this->_width + 1; ++i)
    {
        cout << "|";
        for (int j = 1; j < this->_length + 1; ++j)
        {
            cout << setw(2) << this->m_maze[i][j] << " ";
        }
        cout << '|' << endl;
    }
    for (int i = 1; i < this->_length + 1; ++i)
        cout << "---";
    cout << "--" << endl;
    //cout << endl << "--------------------------------------" << endl;
}

bool MAZE::canPass(const POS& now, const POS& next) const
{   //判断下一个 位置 是否可以通过
    if (next._x <= this->_width
        && next._x >= 1
        && next._y <= this->_length
        && next._y >= 1     //四个限制，表示在边界以内
        && (this->m_maze[next._x][next._y] == 0 //下一个点是通路（没有走过
            || this->m_maze[now._x][now._y] < this->m_maze[next._x][next._y]
            )
        )
    {
        return true;
    }
    else
    {
        return false;
    } //不能通过则返回false
}
void MAZE::find_Way_DFS(const POS& p)
{
    path1.push(p);//当前节点入栈。
    if (p._x == this->aim._x && p._y == this->aim._y)   //某一条路径达到了终点
    {
        if (path1.size_of_stack() < spath.size_of_stack() || spath.isEmpty())
        {   //如果这条路径比先前找到的段的话，就把它赋值给spath
            spath = path1;
        }
    }
    POS next;  //声明下一个节点
    static POS drct[4] = { {0,1},{1,0},{0,-1},{-1,0} };//右、下、左、上四个方向
    
    for (int i = 0; i < 4; ++i)
    {// 向四个方向进行遍历（上，右，左，下四个方向）
        next = drct[i] + p;
        if (canPass(p, next))
        {
            this->m_maze[next._x][next._y] = this->m_maze[p._x][p._y] + 1;//通过每一个节点的顺序
            find_Way_DFS(next);//下一个节点继续遍历
        }
    }
    path1.pop();    //如果四个方向都走过了，或者都不能走，当前节点出栈
}
void MAZE::isTherePath_DFS()
{   //调用这个函数提示有没有通路或者有的话就显示最短路径DFS
    this->m_maze[enter._x][enter._y] = 1;
    // 入口作为第一个点，设置为1

    this->find_Way_DFS(this->enter);
    if (this->m_maze[this->aim._x][this->aim._y] <= 1)
        cout << "\033[31;1m没有通路！\033[0m" << endl;
    else
    {
        cout << endl;
        cout << "找到到达终点的路径，"
            << "且\033[35;1m最短的路径长度为" 
            << this->spath.size_of_stack() << "\033[0m" << endl;
        cout << "路线如下：" << endl;
        cout << "\033[33;1m";
        spath.displayRightOrder();//按入栈的顺序遍历栈
        cout << "\033[0m";
        cout << endl;
        cout << "遍历之后的迷宫的情况：（白色数字表示到达每一个点的最短的步数）" << endl;
        this->showResultWithColor();
        //this->show_Maze();//显示找到最小路径后的 迷宫的情况
    }

    this->path1.destoryStack();
    this->spath.destoryStack();//清空使用的栈
    this->recoverMaze();//还原迷宫初始状态
}
void MAZE::find_Way_StackNotDFS()
{
    this->m_maze[enter._x][enter._y] = 1;
    // 入口作为第一个点，设置为1

    short visited[MAXWIDTH + 3][MAXLENGTH + 3] = { 0 }; 
    //经过某一个节点的次数（只有四个方向，所以要不大于四）
    POS now = enter;
    POS next;
    POS move[4] = { {0,1},{1,0},{0,-1},{-1,0} };//右、下、左、上

    path1.push(this->enter);//先把起始点入栈；
    while (!path1.isEmpty())
    {
        now = path1.topElem();  //（取栈顶 的元素
        for (int timesOfPOS = visited[now._x][now._y]; timesOfPOS < 4; now = path1.topElem())
        { //visited[now._x][now._y] >= 4就不可以再走了（表明这个节点的四个方向都已经遍历过了）

            visited[now._x][now._y]++;  //当前这个点已经走了上下左右中的几个方向了已经》

            next = now + move[timesOfPOS];//分别向右、向下、向左、向上进行移动
            if (this->canPass(now, next))
            {
                timesOfPOS = visited[next._x][next._y];
                //timesOfPOS = visited[now._x][now._y];
                //!!!!!!!!!!!
                //不可以走回头路(canPass函数)，只能回溯，出栈然后回溯上一个节点
                //所以说每次找到一个可以通过的节点，直接timesOfPOS = visited[next._x][next._y]，然后向新的节点的四个方向遍历
                //从这个节点的visited数值开始遍历
                this->m_maze[next._x][next._y] = this->m_maze[now._x][now._y] + 1;//经过的路线的先后顺序
                path1.push(next);//路能走就入栈先

                if (this->aim._x == next._x
                    && this->aim._y == next._y
                    && (spath.size_of_stack() == 0 || path1.size_of_stack() < spath.size_of_stack())
                    )//有一条路到达终点了！！！ 
                {
                    spath = path1;
                }  //把  最短路径  保存在spath里面。
            }
            else
            {
                timesOfPOS++;//如果这个位置走不了，换下一个方向
            }
        }
        visited[path1.top->data._x][path1.top->data._y] = 0;//节点出栈了，相应的被访问的记录清空
        path1.pop();    //当前这个点的四个方向都已经遍历过了，这个节点出栈！

    }

    if (this->m_maze[this->aim._x][this->aim._y] <= 1)
        cout << "\033[31;1m没有通路！\033[0m" << endl;
    else
    {
        cout << endl;
        cout << "找到到达终点的路径，"
            << "且\033[35;1m最短的路径长度为" 
            << this->spath.size_of_stack() << "\033[0m" << endl;
        cout << "路线如下：" << endl;
        cout << "\033[33;1m";
        spath.displayRightOrder();//按入栈的顺序遍历栈
        cout << "\033[0m";
        cout << endl;
        cout << "遍历之后的迷宫的情况：（白色数字表示到达每一个点的最短的步数）" << endl;
        //this->show_Maze();//显示找到最小路径后的 迷宫的情况
        this->showResultWithColor();
    }

    this->path1.destoryStack();
    this->spath.destoryStack();//清空使用的栈
    this->recoverMaze();//还原迷宫初始状态

}
void MAZE::find_Way_BFS()
{   //按照BFS的思想，层次遍历，第一次到达了终点，就一定是最短的路径，（即遍历的层数最低
    //int n = this->_width;
    Queue qpath;    //用来广度优先遍历的队列
    POS pre[MAXWIDTH][MAXLENGTH];//存放每一个节点的前置节点，方便回来寻找路径

    qpath.push(this->enter);

    while (!qpath.isEmpty())
    {
        POS next;
        POS temp = qpath.frontElem();
        qpath.pop();

        POS drct[4] = { {0,1},{1,0},{0,-1},{-1,0} };//右、下、左、上四个方向
        for (int i = 0; i < 4; ++i)
        {//向四个方向进行广搜
            next = temp + drct[i];

            if (canPass(temp, next))//能通过的话
            {
                this->m_maze[next._x][next._y] = this->m_maze[temp._x][temp._y] + 1;
                //通过这个点的顺序，一定是最小的（canPass函数
                qpath.push(next);//入队
                
                pre[next._x][next._y] = temp;

                if (next._x == this->aim._x && next._y == this->aim._y)
                {
                    this->backWay(this->aim._x, this->aim._y, pre);
                    return;//如果发现到了终点，那么一定是最短路径了（层次遍历}
                }
            }
        }
    }
}
void MAZE::backWay(short x, short y, POS(&pre)[MAXWIDTH][MAXLENGTH])//传数组的引用
{   //传数组的引用!
    //借助栈（后进先出）实现路径的输出
    this->spath.push({ x,y });//终点入队

    while (x != this->enter._x || y != this->enter._y)
    {   //将终点的前面的路径上的节点都入队
        POS back = pre[x][y];
        this->spath.push(back);
        x = back._x;
        y = back._y;
    }
}
void MAZE::isTherePath_BFS()
{   //调用这个函数提示有没有通路或者有的话就显示最短路径BFS
    this->m_maze[enter._x][enter._y] = 1;
    // 入口作为第一个点，设置为1

    this->find_Way_BFS();
    
    if (this->m_maze[this->aim._x][this->aim._y] <= 1)
    {
        cout << "\033[31;1m没有通路！\033[0m" << endl;
    }
    else
    {
        cout << endl;
        cout << "找到到达终点的路径，"
            << "且\033[35;1m最短的路径长度为" 
            << this->spath.size_of_stack() << "\033[0m" << endl;
        cout << "路线如下：" << endl;
        cout << "\033[33;1m";
        this->spath.show_Stack();
        cout << "\033[0m";
        cout << endl;

        cout << "遍历之后的迷宫的情况：（白色数字表示到达每一个点的最短的步数）" << endl;
        cout << "如果为零，表示BFS已经找到了最短路径，不再需要继续遍历下去了，或者是因为障碍而无法到达。" << endl;
        this->showResultWithColor();
        //this->show_Maze();//显示找到最小路径后的 迷宫的情况
    }
    this->spath.destoryStack();//清空使用的栈
    this->recoverMaze();//还原迷宫初始状态
}

void MAZE::showResultWithStar() const
{
    bool isShort[MAXWIDTH][MAXLENGTH] = { false };//空间换时间,记录某一个节点是不是在最短路径中。
    auto p = this->spath.top;
    while (p)
    {
        isShort[p->data._x][p->data._y] = true;
        p = p->next;
    }
    for (int i = 1; i < this->_length + 1; ++i)
        cout << "---";
    cout << "--" << endl;
    for (int i = 1; i <= this->_width; ++i)
    {
        cout << "|";
        for (int j = 1; j <= this->_length; ++j)
        {
            if (isShort[i][j])
                cout << " * ";
            else
                cout << setw(2) << this->m_maze[i][j] << " ";
        }
        cout << '|' << endl;
    }
    for (int i = 1; i < this->_length + 1; ++i)
        cout << "---";
    cout << "--" << endl;
}
void MAZE::showResultWithColor() const
{
    cout << "紫色数字1为障碍，最短路径由红色标出：" << endl;
    bool isShort[MAXWIDTH][MAXLENGTH] = { false };//空间换时间,记录某一个节点是不是在最短路径中。
    auto p = this->spath.top;
    while (p)
    {
        isShort[p->data._x][p->data._y] = true;
        p = p->next;//遍历栈中元素，寻找最短路径经过的点
    }
    for (int i = 1; i < this->_length + 1; ++i)
        cout << "----";
    cout << "--" << endl;//输出最顶端的墙
    for (int i = 1; i <= this->_width; ++i)
    {
        cout << "|";
        for (int j = 1; j <= this->_length; ++j)
        {
            if (isShort[i][j])//带颜色输出最短的路径
            {
                //RED
                cout << "\033[31;1m" << setw(3) << this->m_maze[i][j] << "\033[0m ";
                //WHITE
            }
            else
            {
                if (this->m_maze[i][j] == 1)
                    cout << "\033[95;1m" << setw(3) << this->m_maze[i][j] << "\033[0m ";
                else
                    cout << setw(3) << this->m_maze[i][j] << " ";

            }
        }
        cout << '|' << endl;
    }
    for (int i = 1; i < this->_length + 1; ++i)
        cout << "----";//最下方的墙
    cout << "--" << endl;
}
void MAZE::showRawMaze() const
{//原始状态的迷宫，如果需要查看原始状态（即调用寻找路径的函数之前迷宫的样子）可以调用此函数
    cout << "初始的迷宫状态如下：" << endl;
    for (int i = 1; i < this->_length + 1; ++i)
        cout << "---";
    cout << "--" << endl;
    for (int i = 1; i < this->_width + 1; ++i)
    {
        cout << "|";
        for (int j = 1; j < this->_length + 1; ++j)
        {
            if (this->m_maze[i][j] > 1 || (i == j && j == 1))
                cout << setw(2) << 0 << " ";
            else
                cout << setw(2) << this->m_maze[i][j] << " ";
        }
        cout << '|' << endl;
    }
    for (int i = 1; i < this->_length + 1; ++i)
        cout << "---";
    cout << "--" << endl;

}
void MAZE::recoverMaze()
{
    this->m_maze[this->enter._x][this->enter._y] = 0;
    for (int i = 1; i < this->_width + 1; ++i)
        for (int j = 1; j < this->_length + 1; ++j)
            if (this->m_maze[i][j] > 1)
                this->m_maze[i][j] = 0;//把之前的走过的都还原为0
}
POS MAZE::checkWidthAndLength() const//返回当前迷宫的长和宽
{
    return POS{ this->_width, this->_length };
}

void menu()
{
    cout << "\033[32;1m";
    cout << "****************************************************" << endl;
    cout << "*                请输入您的选择：                  *" << endl;
    cout << "*                                                  *" << endl;
    cout << "*                1.自行输入迷宫                    *" << endl;
    cout << "*                2.随机一个迷宫                    *" << endl;
    cout << "*               3.查看是否有通路                   *" << endl;
    cout << "*            4.输出迷宫的邻接表表示                *" << endl;
    cout << "*                  5.退出系统                      *" << endl;
    cout << "*                                                  *" << endl;
    cout << "****************************************************" << endl;
    cout << "\033[0m";
}

void menu2()
{
    cout << "\n\033[32;1m";
    cout << "    ###########################################" << endl;
    cout << "    #            请选择一种算法：             #" << endl;
    cout << "    #                                         #" << endl;
    cout << "    #            1.栈的非递归                 #" << endl;
    cout << "    #         2.递归形式的算法（DFS）         #" << endl;
    cout << "    #          3.广度优先遍历（BFS）          #" << endl;
    cout << "    #                                         #" << endl;
    cout << "    ###########################################" << endl;
    cout << "\033[0m";
}
