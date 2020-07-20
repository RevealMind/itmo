#ifndef LIST_H
#define LIST_H

#include <list>

class List
{

public:
    List(std::list<int> &);
    int prev();
    int next();
    void clear();
    void update(std::list<int>&);
private:
    std::list<int>::iterator cur;
    std::list<int> data;
};

#endif // LIST_H
