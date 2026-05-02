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
    std::string a = this->_str;
    std::string b = num._str;

    while(a.length() < b.length())
        a.insert(0, 1, '0');
    while(b.length() < a.length())
        b.insert(0, 1, '0');

    int carry = 0;
    int temp;
    std::string sum;

    for(int i = a.length()-1; i>=0; i--)
    {
        temp = (a[i] - '0') + (b[i] - '0') + carry;
        sum.insert(0, 1, (temp % 10) + '0');

        carry = temp / 10;
    }
    if (carry)
        sum.insert(0, 1, carry + '0');
    
    size_t check = sum.find_first_not_of('0');
    res._str = (std::string::npos == check) ? "0" : sum.substr(check);
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