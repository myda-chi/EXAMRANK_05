#include "bigint.hpp"

bigint::bigint(): _str("0")
{
}
bigint::~bigint()
{
}
bigint::bigint(const bigint& copy)
{
    *this = copy;
}
bigint& bigint::operator=(const bigint& copy)
{
    if (this != &copy)
    {
        _str = copy._str;
    }
    return(*this);
}

bigint::bigint(int num)
{
    std::stringstream ss;
    ss << num;
    _str = ss.str();
}

bigint bigint::operator+(const bigint& num) const
{
    bigint res;
    int i = _str.size() - 1;
    int j = num.str.size() - 1;
    int carry = 0;
    
    while(i >= 0|| j>=0 || carry)
    { 
        int sum = carry;
        if(i >=0) sum += _str[i--] - '0';
        if(j >= 0) sum += num._str[j--] - '0';
        res._str += sum % 10 + '0';
        carry = sum / 10;
        std::reserve(res._str.begin(), res._str.end());
    }
    return(res);
}

bigint& bigint::operator +=(const bigint& num)
{
    *this = * this + num;
    return(*this);
}

bigint& bigint::operator++()
{
    *this = *this + bigint(1);
    return(*this);
}

bigint bigint::operator++(int)
{
    bigint temp(*this);
    ++(*this);
    return(temp);
}

unsigned int atoui(std::string str)
{
    unsigned int num;
    std::stringstream ss(str);
    ss >> num;
    return(num);
}

bigint bigint::operator<<(const bigint& num)
{
    bigint temp(*this);
    temp = *this << atoui(num._str);
    return(temp);
}

bigint bigint::operator>>(const bigint& num)
{
    bigint temp(*this);
    temp = *this >> atoui(num._str);
    return(temp);
}

bigint&  bigint::operator<<=(const bigint& num)
{
    *this = *this << num;
    return(*this);
}

bigint&  bigint::operator>>=(const bigint& num)
{
    *this = *this >> num;
    return(*this);
}

bigint bigint::operator<<(int num)
{
    bigint temp(*this);
    temp._str.append(num, '0');
    return(temp);
}

bigint bigint::operator>>(int num)
{
    bigint temp(*this);
    if (num >= _str.length())
        _str = "0";
    temp._str.erase(_str.length() - num);
    return(temp);
}

bigint& bigint::operator<<=(int num)
{
    *this = *this << num;
    return(*this);
}

bigint&  bigint::operator>>=(int num)
{
    *this = *this >> num;
    return(*this);
}

bool bigint::operator<(const bigint& num) const
{
    if (_str.length() != num._str.length())
        return(_str.length() < num._str.length());
    return(_str < num._str);
}

bool bigint::operator>(const bigint& num) const
{
    return(num < *this);
}

bool bigint::operator<=(const bigint& num) const
{
    return((*this < num) || (*this == num));
}

bool bigint::operator>=(const bigint& num) const
{
    return((*this > num) || (*this == num));
}

bool bigint::operator==(const bigint& num) const
{
    return(this->_str == num._str);
}

bool bigint::operator!=(const bigint& num) const
{
    return !(*this == num);
}

std::string bigint::getstr() const{
    return(_str);
}

std::ostream& operator<<(std::ostream& os, const bigint& num)
{
    os << num.getstr();
    return(os);
}