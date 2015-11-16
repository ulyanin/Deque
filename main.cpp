#define BOOST_TEST_MODULE dequetest test
#include "deque.h"
#include <iostream>
#include <boost/test/included/unit_test.hpp>

BOOST_AUTO_TEST_SUITE (dequetest) // name of the test suite is stringtest

BOOST_AUTO_TEST_CASE (test1)
{
    Deque <int> deque;
    int n = 5;
    for (int i = 0; i < n; ++i)
        deque.push_back(i);
    for (int i = 0; i < n; ++i)
        deque.push_front(i);
    for (Deque<int>::iterator it = deque.begin(); it != deque.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;
    for (Deque<int>::reverse_iterator it = deque.rbegin(); it != deque.rend(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;
    for (int i = 0; i < 2 * n; ++i)
        std::cout << deque[i] << " ";
    std::cout << std::endl;
    for (int i = 0; i < n - 1; ++i) {
        deque.pop_back();
        deque.pop_front();
    }
    for (int i = 0; i < (int)deque.size(); ++i)
        std::cout << deque[i] << " ";
    std::cout << std::endl;
}

BOOST_AUTO_TEST_SUITE_END( )

