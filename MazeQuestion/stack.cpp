#include "stack.h"
#include "maze.h"
#include <iostream>
using namespace std;

Stack::Stack(int val, Node* s1)
{
    size = val;
    top = s1;
}
Stack::Stack(const Stack& s)  //复制构造函数（深拷贝
{
    this->size = s.size;
    Node* n = s.top;
    int s_size = 0;
    POS* items = new POS[s.size];
    while (n)   //这里的原理和displayRightOrder()函数差不多
    {
        items[s.size - s_size - 1] = n->data;
        s_size++;
        n = n->next;
    }
    this->destoryStack();
    for (; s_size > 0; s_size--)
    {   //依次把每个元素加入到新的栈里面
        auto p = new Node{ items[s.size - s_size],this->top };
        this->top = p;
        this->size++;
    }
}
Stack::~Stack()
{
    for (auto p = top; p != nullptr; p = top)
    {
        top = top->next;
        delete p;
    }
    size = 0;
    /*cout << "栈已销毁" << endl;*/
};
void Stack::destoryStack()
{   //销毁栈(和析构函数差不多)
    if (this->top == nullptr)
        return;
    for (auto p = top; p != nullptr; p = top)
    {
        top = top->next;
        delete p;
    }
    this->size = 0;
}
void Stack::show_Stack() const
{
    auto p = this->top;
    for (int i = 1; p; p = p->next, ++i)
    {
        cout << "(" << p->data._x << "," << p->data._y << ") -> ";
        if (i == this->size)
            cout << "\b\b\b    " << endl; //最后一次输出的时候，消除掉最后出现的 " -> "
        if (i % 5 == 0) //每输出5个就换行
            cout << endl;
    }
}
void Stack::displayRightOrder()  const
{   //按照入栈的顺序进行输出栈中的元素
    auto p = this->top;
    ElemType* items = new ElemType[this->size]; //辅助数组
    auto x = this->size;
    while (p)
    {   //遍历栈 并把元素存入到辅助数组中
        /*cout << p->data._x << " " << p->data._y << endl;*/
        items[x - 1] = { p->data._x, p->data._y };
        x--;
        p = p->next;
    }
    for (int i = 1; i <= this->size; ++i)
    {
        cout << "(" << items[i - 1]._x << "," << items[i - 1]._y << ") -> ";
        if (i == this->size)
            cout << "\b\b\b    " << endl; //最后一次输出的时候，消除掉最后出现的 " -> "
        if (i % 5 == 0) //每输出5个就换行
            cout << endl;

    }

    delete[] items;//销毁辅助数组
}
void Stack::push(ElemType val)
{   //简单的入栈操作
    auto p = new Node{ val, top };
    top = p;
    size++;
}
void Stack::pop()
{   //简单的出栈操作
    if (top == nullptr)
    {
        cout << "栈为空！操作失败" << endl;
        return;
    }
    auto p = top;
    top = top->next;
    delete p;
    size--;
}

Stack& Stack::operator=(const Stack& s) //重载栈的 = 防止浅拷贝同时也把栈中的元素顺序反过来，便于输出
{
    Node* n = s.top;
    int s_size = 0;
    POS* items = new POS[s.size];
    while (n)
    {
        items[s.size - s_size - 1] = n->data;
        s_size++;
        n = n->next;
    }
    this->destoryStack();
    //for (int i = 0; i < s_size; ++i)
    //{
    //    cout << items[i]._x << items[i]._y << endl;
    //}
    for (; s_size > 0; s_size--)
    {
        auto p = new Node{ items[s.size - s_size],this->top };
        this->top = p;
        this->size++;
    }
    delete[] items;
    return *this;

}

