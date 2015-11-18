#define BOOST_TEST_MODULE dequetest test
#include "deque.h"
#include <iostream>
#include <algorithm>
#include <boost/test/included/unit_test.hpp>
#include <deque>

const int LARGE_TEST_SIZE = (int)(1e7);

BOOST_AUTO_TEST_SUITE (dequetest) // name of the test suite is stringtest

BOOST_AUTO_TEST_CASE (simply_test)
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

BOOST_AUTO_TEST_CASE(random_push_pop1)
{
    Deque<int> deque;
    int n = LARGE_TEST_SIZE;
    std::deque<int> dequeTrue;
    for (int i = 0; i < n; ++i) {
        int elem = rand();
        if (rand() & 1) {
            deque.push_back(elem);
            dequeTrue.push_back(elem);
        } else {
            deque.push_front(elem);
            dequeTrue.push_back(elem);
        }
    }
    while (!deque.empty()) {
        if (rand() & 1) {
            deque.pop_front();
            dequeTrue.pop_front();
        } else {
            deque.pop_back();
            dequeTrue.pop_back();
        }
    }
}

BOOST_AUTO_TEST_CASE(random_operations)
{
    Deque<int> deque;
    std::deque<int> dequeTrue;
    int n = LARGE_TEST_SIZE;
    for (int i = 0; i < n; ++i) {
        int elem = rand();
        int chose = rand();
        if (chose == 0) {
            deque.push_back(elem);
            dequeTrue.push_back(elem);
        } else if (chose == 1) {
            deque.push_front(elem);
            dequeTrue.push_front(elem);
        }
        else if (chose == 2 && !deque.empty()) {
            deque.pop_front();
            dequeTrue.pop_front();
        } else if (!deque.empty()) {
            deque.pop_back();
            dequeTrue.pop_back();
        }
    }
    BOOST_CHECK_EQUAL(deque.size(), dequeTrue.size());
    for (size_t i = 0; i < deque.size(); ++i)
        BOOST_CHECK_EQUAL(deque[i], dequeTrue[i]);
    BOOST_CHECK_EQUAL_COLLECTIONS(deque.begin(), deque.end(), dequeTrue.begin(), dequeTrue.end());
}

BOOST_AUTO_TEST_CASE(sort_deques)
{
    Deque<int> deque;
    std::deque<int> dequeTrue;
    int n = LARGE_TEST_SIZE;
    for (int i = 0; i < n; ++i) {
        int elem = rand();
        deque.push_back(elem);
        dequeTrue.push_back(elem);
    }
    boost::timer t1;
    std::sort(deque.begin(), deque.end());
    std::cout << t1.elapsed() << std::endl;

    boost::timer t2;
    std::sort(dequeTrue.begin(), dequeTrue.end());
    std::cout << t2.elapsed() << std::endl;
    BOOST_CHECK_EQUAL_COLLECTIONS(deque.begin(), deque.end(), dequeTrue.begin(), dequeTrue.end());
}

BOOST_AUTO_TEST_CASE(sort_deques_reversed)
{
    Deque<int> deque;
    std::deque<int> dequeTrue;
    int n = LARGE_TEST_SIZE;
    for (int i = 0; i < n; ++i) {
        int elem = rand();
        deque.push_back(elem);
        dequeTrue.push_back(elem);
    }
    boost::timer t1;
    std::sort(deque.rbegin(), deque.rend());
    std::cout << t1.elapsed() << std::endl;

    boost::timer t2;
    std::sort(dequeTrue.rbegin(), dequeTrue.rend());
    std::cout << t2.elapsed() << std::endl;
    std::cout << deque.size() << std::endl;
    std::cout << dequeTrue.size() << std::endl;
    BOOST_CHECK_EQUAL_COLLECTIONS(deque.begin(), deque.end(), dequeTrue.begin(), dequeTrue.end());
}

BOOST_AUTO_TEST_SUITE_END( )

