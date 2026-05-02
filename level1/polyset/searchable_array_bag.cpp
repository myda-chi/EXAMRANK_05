#include "searchable_array_bag.hpp"

searchable_array_bag::searchable_array_bag(): array_bag()
{
}
searchable_array_bag::~searchable_array_bag()
{
}
searchable_array_bag::searchable_array_bag(const searchable_array_bag& copy)
{
    *this = copy;
}
searchable_array_bag& searchable_array_bag::operator=(const searchable_array_bag& copy)
{
    if(this != &copy)
        array_bag::operator=(copy);
    return(*this);

}

bool searchable_array_bag::has(int item) const
{
    for(int i = 0; i < size; i++)
    {
        if(data[i] == item)
            return(true);
    }
    return(false);
}