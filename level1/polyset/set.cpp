#include "set.hpp"

set::set(searchable_bag& bag): bag(bag)
{
}

set::~set()
{}
set& set::operator=(const set& copy)
{
    if (this != &copy)
    {
        bag = copy.bag;
    }
    return(*this);
}

set::set(const set& copy): bag(copy.bag)
{}

void set::insert(int item)
{
    if(!bag.has(item))
        bag.insert(item);
}

void set::insert(int *item, int count)
{
    for(int i = 0; i < count; i++)
    {
        insert(item[i]);
    }

}

void set::claer()
{
    bag.clear();
}

bool set::has(int item) const
{
    bag.has(item);
}

void set::print() const
{
    bag.print();
}

