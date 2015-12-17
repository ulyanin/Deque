#include "deque.h"
#include <iostream>
#include <vector>
#include <deque>
#include <algorithm>
#include <utility>

int main()
{
    Deque <std::pair <int, int> > d;
    int n = 5;
    for (int i = 0; i < n; ++i)
        d.push_back(std::make_pair(i, i + 1));
    Deque<std::pair <int, int> >::reverse_iterator it = d.rbegin();
    std::cout << (*it).first << std::endl;
    it->first = 2;
    std::cout << it->first << std::endl;
}


