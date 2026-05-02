#include "vect2.hpp"

vect2::vect2(): x(0), y(0)
{
}

vect2::~vect2()
{
}

vect2::vect2(int x, int y): x(x), y(y)
{
}

vect2::vect2(const vect2& copy): x(copy.x), y(copy.y)
{
}

vect2& vect2::operator=(const vect2& copy)
{
    if (this != &copy)
    {
        x = copy.x;
        y = copy.y;
    }
    return(*this);
}

int  vect2::operator[](int index) const
{
    if (index == 0)
        return(x);
    return(y);
}

int& vect2::operator[](int index)
{
    if (index == 0)
        return(x);
    return(y);
}

vect2 vect2::operator++(int)
{
    vect2 temp(*this);
    ++x;
    ++y;
    return(temp);
}

vect2& vect2::operator++()
{
    *this = *this + vect2(1, 1);
   return(*this); 
}

vect2& vect2::operator--()
{
   *this = *this - vect2(1, 1);
   return(*this); 
}

vect2 vect2::operator--(int)
{
    vect2 temp(*this);
    --x;
    --y;
    return(temp);
}

vect2 vect2::operator-()
{
    vect2 temp(-x, -y);
    return(temp);
}

vect2 vect2::operator+(const vect2& num) const
{
    vect2 temp(*this);
    temp.x = this->x + num.x;
    temp.y = this->y + num.y;
    return(temp);
}

vect2 vect2::operator-(const vect2& num) const
{
    vect2 temp(*this);
    temp.x = this->x - num.x;
    temp.y = this->y - num.y;
    return(temp);
}

vect2 vect2::operator*(int scalar) const
{
    vect2 temp(*this);
    temp.x = this->x * scalar;
    temp.y = this->y * scalar;
    return(temp);
}

vect2&  vect2::operator-=(const vect2& num)
{
    x -= num.x;
    y -= num.y;
    return(*this);
}

vect2&  vect2::operator+=(const vect2& num)
{
    x += num.x;
    y += num.y;
    return(*this);
}

vect2&  vect2::operator*=(int scalar)
{
    this->x *= scalar;
    this->y *= scalar;
    return(*this);
}

bool  vect2::operator==(const vect2& num) const
{
    return((this->x == num.x) && (this->y == num.y));
}

bool  vect2::operator!=(const vect2& num) const
{
    return !(*this == num);
}

std::ostream& operator<<(std::ostream& os, const vect2& v)
{
    os << "{" << v[0] << ", " << v[1] << "}";
    return(os);
}

vect2 operator*(int scalar, const vect2& num)
{
    return (num * scalar);
}
