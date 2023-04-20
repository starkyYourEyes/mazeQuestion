#pragma once
#include "pos.h"
#include "general.h"
// 链 队
typedef POS QElemType;

struct QNode
{
	QElemType data;
	struct QNode* next;
};

class Queue
{
private:
	QNode* front;//队头
	QNode* rear;//队尾
	int size;//队列的元素的个数
public:
	friend class MAZE;//友元类
	Queue();//默认构造函数，初始化队列
	Queue(const Queue& q);//复制构造函数
	~Queue();//析构
	void push(const QElemType& val);//入队
	void pop();//出队
	void destroyQueue();//销毁队列
	bool isEmpty() const;//队列是否为空
	int size_of_queue() const;//返回队列的size
	QElemType frontElem() const;//获得队尾元素
	QElemType rearElem() const;//获得队头元素
	void show_Queue() const;//显示队列中的元素
	Queue& operator=(const Queue& s); //重载 队列类 的 = 
};