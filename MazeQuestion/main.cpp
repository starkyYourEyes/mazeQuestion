//迷宫的最大规模为（30 * 30）.可以更改，只要修改general.h中的#define MAXWIDTH 和 MAXLENGTH即可
#include "stack.h"
#include "maze.h"
#include "randomMazes.h"
#include "queue.h"
#include "graph.h"
#include "pos.h"
#include "general.h"
#include <iostream>
#include <cstdlib>
using namespace std;

int main()
{ 
    int choice;
    MAZE* m = new MAZE();
    system("cls");

    while (1)
    {
        menu();

        //使用ANSI控制码，来改变输出的颜色。,WIN - 支持的ANSI码
        //"\033[字背景颜色;字体颜色m字符串\033[0m"
        //"\n\033[1;32;40m在交互输入模式下可见为绿色加粗字体\033[0m\n";

        cout << "\033[34;1m请输入：\033[0m";
        //WHITE
        cout << "\033[33;1m";//输入的字改成黄色
        while (!(cin >> choice))//错误地输入非数字的处理
        {
            cout << "\033[0m";
            cout << "\033[31;1m输入有误，请重新输入\033[0m" << endl;
            //BLUE
            cout << "\033[34;1m请输入：\033[0m";
            //WHITE
            cin.clear();//恢复输入
            while (cin.get() != '\n')//清空缓冲区
                continue;
            /*system("pause");
            system("cls");*/
        }
        cout << "\033[0m";
        switch (choice)
        {
        case 1:
        {
            //MAZE m;
            //如果是使用普通类，只能在while(1)循环外定义[[[若在循环内，每次循环重新定义，没意义]]]
            //(case中不用语句块报错【初始化操作由“case”标签跳过】)
            //把类放在case中的语句块中定义的话，输入1，MAZE自动析构,再输入4 无法正常显示结果的情况
            //并且如果是普通类，每次重复输入1，2要重新赋值，需要重载 ’=‘，
            //在这里使用MAZE类型的指针省去了很多不必要的操作
            //并且防止每次重新赋值相互之间的影响，且可以清空之前对于迷宫地图的修改，还原类中的栈类成员，
            if (m != NULL)
            {
                delete m;//清空之前的操作
            }
            m = new MAZE();
            m->setMaze();
        }
        break;

        case 2:
        {
            if (m != NULL)
            {
                delete m;
            }
            rMaze rm = randomMaze();//获得一个随机的迷宫地图
            m = new MAZE(rm.m_m, rm.m_w, rm.m_l);
            cout << "随机的迷宫为如下：" << endl;
            m->show_Maze();
        }
        break;

        case 3:
        {
            if (m->checkWidthAndLength() == POS{ 0, 0 })
            {//如果没有在输入3  之前输入 1 或者 2,即没有创建地图
                cout << endl << "请先输入或随机一个迷宫地图。" << endl;
                system("pause");
                system("cls");
                break;
            }
            bool flag = true;
            menu2();
            while (flag)
            {
                int selection;
                cout << "\033[34;1m请选择一种算法：\033[0m";
                while (!(cin >> selection))//错误地输入非数字的处理
                {
                    cout << "\033[0m";
                    cout << "\033[31;1m输入有误，请重新输入\033[0m" << endl;
                    //BLUE
                    cout << "\033[34;1m请输入：\033[0m";
                    //WHITE
                    cin.clear();//恢复输入
                    while (cin.get() != '\n')//清空缓冲区
                        continue;
                }

                switch (selection)
                {
                case 1:
                    flag = false;
                    cout << endl << "栈的非递归：" << endl;
                    m->find_Way_StackNotDFS();
                    break;

                case 2:
                    flag = false;
                    cout << endl << "DFS的结果：" << endl;
                    m->isTherePath_DFS();
                    break;

                case 3:
                    flag = false;
                    cout << endl << "BFS的结果：" << endl;
                    m->isTherePath_BFS();
                    break;

                default://输入如果有错的话，返回继续输入。
                    cout << "输入有误，请重新输入" << endl;
                    break;
                }
            }
            system("pause");
            system("cls");
        }
        break;

        case 4:
        {
            if (m->checkWidthAndLength() == POS{ 0, 0 })
            {//如果没有在输入4  之前输入 1 或者 2,即没有创建地图
                cout << endl << "请先输入或随机一个迷宫地图。" << endl;
                system("pause");
                system("cls");
            }
            else
            {
                ALGraph G;
                G.CreateGraph(*m);
                cout << endl << "迷宫的邻接表表示如下：" << endl << endl;;
                G.showGraph();
                system("pause");
                system("cls");
            }
        }
        break;

        case 5:
        {
            //RED
            cout << "\033[33;4m确定要退出吗？(输入 'Y'确定 / 'N'取消)\033[0m" << endl;
            //WHITE
            string sure;
            cin >> sure;
            if (sure == "y" || sure == "Y")
            {
                cout << "\033[32;5m欢迎下次使用\033[0m" << endl;
                exit(EXIT_SUCCESS);
            }
            system("pause");
            system("cls");
        }
        break;

        }
    }
    return 0;
}