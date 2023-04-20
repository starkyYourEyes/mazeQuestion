#pragma once
#include <iostream>
#include "pos.h"
#include "general.h"
// 使用  链栈
using namespace std;

typedef POS ElemType;
//栈的节点的定义（结构体）
struct Node
{
    ElemType data;
    Node* next;
};
// 栈 类
class Stack
{

private:
    struct Node* top;
    int size;
public:
    friend class MAZE;//友元类

    Stack(int val = 0, struct Node* s1 = NULL); //初始化栈
    Stack(const Stack& s);  //复制构造函数
    ~Stack();   //栈类的析构函数

    void push(ElemType val);    //入栈

    void pop();    // 出栈
    void destoryStack();
    void show_Stack() const;
    void displayRightOrder() const;

    inline bool isEmpty() const  //判断栈是否为空
    {
        return size == 0;
    }

    inline ElemType topElem() const   //返回栈顶元素
    {
        if (top == NULL)
        {
            cout << "栈为空！ " << endl;
            return false;
        }
        return top->data;
    }

    inline int size_of_stack() const //返回栈的大小（元素的个数）
    {
        return this->size;
    }

    Stack& operator=(const Stack& s); //重载 栈 的 =  防止浅拷贝

};



