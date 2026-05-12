#ifndef BIGINT_HPP
#define BIGINT_HPP

#include <iostream>
#include <sstream>
#include <algorithm>
class bigint
{
private:
    std::string _str;
public:
    bigint();
    ~bigint();
    bigint(const bigint& copy);
    bigint& operator=(const bigint& copy);

    bigint(int num);

    std::string getstr() const;

    bigint operator+(const bigint& num) const;
    bigint& operator +=(const bigint& num);

    bigint& operator++();
    bigint operator++(int);

    bigint operator<<(const bigint& num);
    bigint operator>>(const bigint& num);
    bigint&  operator<<=(const bigint& num);
    bigint&  operator>>=(const bigint& num);

    bigint operator<<(int num);
    bigint operator>>(int num);
    bigint& operator<<=(int num);
    bigint&  operator>>=(int num);

    bool operator<(const bigint& num) const;
    bool operator>(const bigint& num) const;
    bool operator<=(const bigint& num) const;
    bool operator>=(const bigint& num) const;
    bool operator==(const bigint& num) const;
    bool operator!=(const bigint& num) const;
};

std::ostream& operator<<(std::ostream& os, const bigint& num);

#endif