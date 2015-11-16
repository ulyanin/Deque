#ifndef DEQUE_ITERATOR_H
#define DEQUE_ITERATOR_H

#include <iterator>

namespace DequeIterator {

template <class ValueType> class Iterator
    : public std::iterator<std::random_access_iterator_tag, ValueType>
{
public:
    Iterator(ValueType * ptr, int left, int right, int posInArray, int capacity);
    Iterator(const Iterator &);
    ValueType operator*() const;
    ValueType& operator*();
    bool operator==(const Iterator &);
    bool operator!=(const Iterator &);
    Iterator operator++(int);
    Iterator operator++();
    Iterator operator--(int);
    Iterator operator--();
    Iterator operator+(int);
    Iterator operator-(int);
private:
    Iterator movePointer(int);
    ValueType * ptr_;
    int left_, right_;
    int capacity_; // capapacity of onwer container
    int pos_; // position in Array [0..capacity): [left..right] or ([left..capacity) + [0..right])
};

template <class ValueType>
Iterator<ValueType>::Iterator(ValueType * ptr, int left, int right, int posInArray, int containerCapacity)
    : ptr_(ptr)
    , left_(left)
    , right_(right)
    , pos_(posInArray)
    , capacity_(containerCapacity)
{}

template <class ValueType>
Iterator<ValueType>::Iterator(const Iterator &other)
    : ptr_(other.ptr_)
    , left_(other.left_)
    , right_(other.right_)
    , pos_(other.pos_)
    , capacity_(other.capacity_)
{}

template <class ValueType>
ValueType Iterator<ValueType>::operator*() const
{
    return *ptr_;
}

template <class ValueType>
ValueType& Iterator<ValueType>::operator*()
{
    return *ptr_;
}

template <class ValueType>
bool Iterator<ValueType>::operator==(const Iterator<ValueType> &other)
{
    return ptr_ == other.ptr_;
}

template <class ValueType>
bool Iterator<ValueType>::operator!=(const Iterator<ValueType> &other)
{
    return ptr_ != other.ptr_;
}

template <class ValueType>
Iterator<ValueType> Iterator<ValueType>::movePointer(int steps)
{
    int oldPos = pos_;
    pos_ += steps;
    if (pos_ >= capacity_) {
        pos_ -= capacity_;
    }
    if (pos_ < 0) {
        pos_ += capacity_;
    }
#ifndef NDEBUG
    if (left_ <= right_) {
        if (pos_ < left_)
            throw std::range_error("negative index of iterator");
        if (pos_ > right_)
            throw std::range_error("index of iterator is too large");
    } else {
        if (!((left_ <= pos_ && pos_ < capacity_) || (0 <= pos_ && pos_ <= right_)))
            throw std::range_error("bad iterator index");
    }
#endif
    ptr_ += pos_ - oldPos;
    return *this;
}

template <class ValueType>
Iterator<ValueType> Iterator<ValueType>::operator++()
{
    return this->movePointer(1);
}

template <class ValueType>
Iterator<ValueType> Iterator<ValueType>::operator++(int)
{
    Iterator<ValueType> tmp(*this);
    this->operator++();
    return tmp;
}

template <class ValueType>
Iterator<ValueType> Iterator<ValueType>::operator--()
{
    return this->movePointer(-1);
}

template <class ValueType>
Iterator<ValueType> Iterator<ValueType>::operator--(int)
{
    Iterator<ValueType> tmp(*this);
    this->operator--();
    return tmp;
}

template <class ValueType>
Iterator<ValueType> Iterator<ValueType>::operator-(int steps)
{
    return this->movePointer(-steps);
}

template <class ValueType>
Iterator<ValueType> Iterator<ValueType>::operator+(int steps)
{
    return this->movePointer(steps);
}

}
#endif
