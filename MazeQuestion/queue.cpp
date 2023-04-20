#include "queue.h"
#include <iostream>
using std::cout;

Queue::Queue()
{
	this->rear = this->front = new QNode;
	this->front->next = nullptr;//初始化队列
	this->size = 0;
}
Queue::~Queue()
{
	while (this->front)
	{
		auto p = this->front;
		this->front = this->front->next;
		delete p;
	}
	this->front = this->rear = nullptr;
	this->size = 0;
	//cout << "Queue的析构函数的调用" << endl;
}
void Queue::push(const QElemType& val)
{	//头插法，入队
	QNode* elem = new QNode{ val,nullptr };
	this->rear->next = elem;
	this->rear = elem;	
	this->size++;
}
void Queue::pop()
{
	if (this->size == 0 || this->front == this->rear)
	{
		cout << "队列为空，出队失败！" << endl;
		return;
	}
	auto p = this->front->next;
	this->front->next = p->next;
	if (this->rear == p)		//如果队列中只有一个元素（特殊处理下
		this->rear = this->front;
	delete p;

	this->size--;

}
bool Queue::isEmpty() const
{
	return this->size == 0;
}
void Queue::destroyQueue()
{
	this->size = 0;
	QNode* p = this->front;
	while (this->front)
	{
		this->front = this->front->next;
		delete p;
		p = this->front;
	}
	this->front = this->rear = nullptr;
}
int Queue::size_of_queue() const
{
	return this->size;
}
QElemType Queue::frontElem() const
{
	if (!this->isEmpty())
	{
		return this->front->next->data;
	}
	else
	{
		cout << "队列为空，输出无效" << endl;
		return { -1,-1 };
	}
}
QElemType Queue::rearElem() const
{
	if (!this->isEmpty())
	{
		return this->rear->data;
	}
	else
	{
		cout << "队列为空，输出无效" << endl;
		return { -1,-1 };
	}
}
void Queue::show_Queue() const
{
	int num = 0;
	if (this->isEmpty())
	{
		cout << "队列为空 " << endl;
		return;
	}
	auto p = this->front->next;
	while (p)
	{//从  队头  开始遍历整个队列
		num++;
		cout << p->data << " -> ";
		p = p->next;
		if (num % 5 == 0)
			cout << endl;
	}
	cout << "\b\b\b    " << endl;
}
Queue::Queue(const Queue& q)
{
	this->rear = this->front = new QNode;
	this->front->next = nullptr;//初始化队列

	this->size = q.size;
	QNode* p = q.front->next;
	while (p)
	{
		QNode* elem = new QNode{ p->data, nullptr };
		this->rear->next = elem;
		this->rear = elem;
		p = p->next;
	}
}
Queue& Queue::operator=(const Queue& q)
{
	this->destroyQueue();//销毁原来的队列
	this->size = q.size;

	this->rear = this->front = new QNode;
	this->front->next = nullptr;//初始化队列

	this->size = q.size;
	QNode* p = q.front->next;
	while (p)
	{
		QNode* elem = new QNode{ p->data, nullptr };
		this->rear->next = elem;
		this->rear = elem;
		p = p->next;
	}
	//cout << "重载的 = 的调用；" << endl;
	return *this;
}