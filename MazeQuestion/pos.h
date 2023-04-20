#pragma once
//坐标点位置的类
#include <iostream>
using namespace std;
#include "general.h"
class POS
{   //表示位置坐标的类
public:
    short _x;
    short _y;
    POS(short x = 0, short y = 0) :_x(x), _y(y)
    {};
    POS(const POS& p);//复制构造函数
    
    POS operator+(const POS& p);//重载POS的+
    friend istream& operator>>(istream& is, POS& p);//重载输入,输入改变了值，不能const
    friend ostream& operator<<(ostream& os, const POS& p);//可以通过cout直接输出POS类型的值
    bool operator==(const POS p) const; //重载==，不允许对类类成员更改，要加const，变量前，函数后都要加
};
