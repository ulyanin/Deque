#define BOOST_TEST_MODULE dequetest
#include "deque.h"
#include <iostream>
#include <algorithm>
#include <boost/test/included/unit_test.hpp>
#include <deque>

const int LARGE_TEST_SIZE = (int)(1e7);


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

BOOST_AUTO_TEST_SUITE (push_pop_testing) // name of the test suite is stringtest

BOOST_AUTO_TEST_CASE(random_push_pop)
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

BOOST_AUTO_TEST_SUITE_END( )

BOOST_AUTO_TEST_SUITE (sorts)

BOOST_AUTO_TEST_CASE(sort)
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
    std::cout << "time for sorting our deque = " << t1.elapsed() << std::endl;

    boost::timer t2;
    std::sort(dequeTrue.begin(), dequeTrue.end());
    std::cout << "time for sorting stl deque = " << t2.elapsed() << std::endl;
    BOOST_CHECK_EQUAL_COLLECTIONS(deque.begin(), deque.end(), dequeTrue.begin(), dequeTrue.end());
}

BOOST_AUTO_TEST_CASE(sort_reversed)
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
    std::cout << "time for reverse sorting our deque = " << t1.elapsed() << std::endl;

    boost::timer t2;
    std::sort(dequeTrue.rbegin(), dequeTrue.rend());
    std::cout << "time for reverse sorting stl deque = " << t2.elapsed() << std::endl;
    BOOST_CHECK_EQUAL_COLLECTIONS(deque.begin(), deque.end(), dequeTrue.begin(), dequeTrue.end());
}
BOOST_AUTO_TEST_CASE(stable_sort)
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
    std::stable_sort(deque.begin(), deque.end());
    std::cout << "time for stable sorting our deque = " << t1.elapsed() << std::endl;

    boost::timer t2;
    std::stable_sort(dequeTrue.begin(), dequeTrue.end());
    std::cout << "time for stable sorting stl deque = " << t2.elapsed() << std::endl;
    BOOST_CHECK_EQUAL_COLLECTIONS(deque.begin(), deque.end(), dequeTrue.begin(), dequeTrue.end());
}

BOOST_AUTO_TEST_CASE(sort_heap)
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
    std::make_heap(deque.rbegin(), deque.rend());
    std::sort_heap(deque.begin(), deque.end());
    std::cout << "time for heap sorting our deque = " << t1.elapsed() << std::endl;

    boost::timer t2;
    std::make_heap(dequeTrue.rbegin(), dequeTrue.rend());
    std::sort_heap(dequeTrue.begin(), dequeTrue.end());
    std::cout << "time for heap sorting stl deque = " << t2.elapsed() << std::endl;
    BOOST_CHECK_EQUAL_COLLECTIONS(deque.begin(), deque.end(), dequeTrue.begin(), dequeTrue.end());
}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE (access_check) // name of the test suite is stringtest

BOOST_AUTO_TEST_CASE(terators)
{
    std::cout << "testing iterators" << std::endl;
    Deque<int> deque;
    std::deque<int> dequeTrue;
    int n = LARGE_TEST_SIZE;
    for (int i = 0; i < n; ++i) {
        int elem = rand();
        deque.push_back(elem);
        dequeTrue.push_back(elem);
    }
    BOOST_CHECK_EQUAL_COLLECTIONS(deque.begin(), deque.end(), dequeTrue.begin(), dequeTrue.end());
    BOOST_CHECK_EQUAL_COLLECTIONS(deque.rbegin(), deque.rend(), dequeTrue.rbegin(), dequeTrue.rend());
    BOOST_CHECK_EQUAL_COLLECTIONS(deque.cbegin(), deque.cend(), dequeTrue.cbegin(), dequeTrue.cend());
    BOOST_CHECK_EQUAL_COLLECTIONS(deque.crbegin(), deque.crend(), dequeTrue.crbegin(), dequeTrue.crend());
}

BOOST_AUTO_TEST_CASE(arrow_operator)
{
    Deque<std::string> deque;
    deque.push_back("11");
    deque.push_back("22");
    BOOST_CHECK_EQUAL((deque.begin() + 1)->c_str(), "22");
    BOOST_CHECK_EQUAL(deque.begin()->c_str(), "11");
    BOOST_CHECK_EQUAL(deque.rbegin()->c_str(), "22");
    BOOST_CHECK_EQUAL(deque.cbegin()->c_str(), "11");
    BOOST_CHECK_EQUAL(deque.crbegin()->c_str(), "22");
}

BOOST_AUTO_TEST_SUITE_END( )

