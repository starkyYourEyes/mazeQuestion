#include "pos.h"
#include <iostream>
#include <iomanip>
using namespace std;

POS::POS(const POS& p)
{
    this->_x = p._x;
    this->_y = p._y;//拷贝构造
}

ostream& operator<<(ostream& os, const POS& p)
{
    os << "(" << setw(2) << p._x << "," << setw(2) << p._y << ")";
    return os;//如果需要继续输出。。。
}
istream& operator>>(istream& is, POS& p)
{
    cin >> p._x >> p._y;
    return is;//如果需要继续输入。。。。
}

POS POS::operator+(const POS& p)
{
    short x = this->_x + p._x;
    short y = this->_y + p._y;
    return { x, y };//返回一个对象
}

bool POS::operator==(const POS p) const//两个const！
{
    if (this->_x == p._x && this->_y == p._y)
        return true;
    return false;
}