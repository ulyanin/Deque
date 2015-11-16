#ifndef IDEQUE_H
#define IDEQUE_H

#include <cstdio>

template <class T>
class IDeque {
public:
    virtual T pop_back() = 0;
    virtual T pop_front() = 0;
    virtual void push_back(const T &) = 0;
    virtual void push_front(const T &) = 0;
    virtual ~IDeque() {}
    virtual T operator[](size_t) const = 0;
    virtual T& operator[](size_t) = 0;
    virtual T back() const = 0;
    virtual T& back() = 0;
    virtual T front() const = 0;
    virtual T& front() = 0;
    virtual bool empty() const = 0;
    virtual size_t size() const = 0;
};

#endif
