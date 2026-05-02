#ifndef VECT2_HPP
#define VECT2_HPP

#include <iostream>
#include <sstream>

class vect2
{
private:
    int x;
    int y;
public:
    vect2();
    ~vect2();
    vect2(int x, int y);
    vect2(const vect2& copy);
    vect2& operator=(const vect2& copy);

    int operator[](int index) const;
    int&  operator[](int index);

    vect2 operator++(int);
    vect2& operator++();
    vect2& operator--();
    vect2 operator--(int);
    vect2  operator-();

    vect2 operator+(const vect2& num) const;
    vect2 operator-(const vect2& num) const;
    vect2 operator*(int scalar) const;

    vect2&  operator-=(const vect2& num);
    vect2&  operator+=(const vect2& num);
    vect2&  operator*=(int scalar);

    bool  operator==(const vect2& num) const;
    bool  operator!=(const vect2& num) const;

};

std::ostream& operator<<(std::ostream& os, const vect2& v);
vect2 operator*(int scalar, const vect2& num);

#endif