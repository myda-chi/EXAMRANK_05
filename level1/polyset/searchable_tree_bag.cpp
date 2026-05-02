#include "searchable_tree_bag.hpp"

searchable_tree_bag::searchable_tree_bag(): tree_bag()
{
}

searchable_tree_bag::~searchable_tree_bag()
{

}

searchable_tree_bag::searchable_tree_bag(const searchable_tree_bag& copy)
{
    *this = copy;
}

searchable_tree_bag& searchable_tree_bag::operator=(const searchable_tree_bag& copy)
{
    if(this != &copy)
        tree_bag::operator=(copy);
    return(*this);
}

bool searchable_tree_bag::has(int item) const
{
    node *current =tree;

    while(current)
    {
        if(current->value == item)
            return(true);
        else if(current->value > item)
            current = current->l;
        else
            current = current->r;
    }
    return(false);
}