#ifndef SET_HPP
#define SET_HPP

#include <iostream>

#include "searchable_bag.hpp"

class set
{
private:
    searchable_bag &bag;
public:
    set(searchable_bag& bag);
    ~set();
    set(const set& copy);
    set &operator=(const set& copy);

    searchable_bag &get_bag() const;
    void insert(int item);
    void insert(int *item, int count);
    void print() const;
    bool has(int item) const;
    void claer();
};

#endif