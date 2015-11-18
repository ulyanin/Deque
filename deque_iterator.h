#ifndef DEQUE_ITERATOR_H
#define DEQUE_ITERATOR_H

#include <iterator>
#include <iostream>


template <class T>
class Deque;

namespace DequeIterator {

    template <class ValueType>
    class Iterator
        : public std::iterator<std::random_access_iterator_tag, ValueType>
    {
        friend class Deque<ValueType>;
    public:
        Iterator(ValueType * ptr, const Deque<ValueType> &);
        Iterator(const Iterator &);
        Iterator& operator=(const Iterator &);
        ValueType operator*() const;
        ValueType& operator*();
        bool operator<(const Iterator &);
        bool operator<=(const Iterator &);
        bool operator==(const Iterator &);
        bool operator!=(const Iterator &);
        Iterator operator++(int);
        Iterator& operator++();
        Iterator operator--(int);
        Iterator& operator--();
        Iterator operator+(int) const;
        Iterator operator-(int) const;
        int operator-(const Iterator &);
    private:
        int relativePos() const;
        Iterator& movePointer(int);
        ValueType * ptr_;
        const Deque<ValueType> * owner_;
        int pos_; // position in Array [0..capacity): [left..right] or ([left..capacity) + [0..right])
    };

    template <class ValueType>
    Iterator<ValueType>::Iterator(ValueType * ptr, const Deque<ValueType> &dequeOwner)
        : ptr_(ptr)
        , owner_(&dequeOwner)
    {
        pos_ = ptr - dequeOwner.data_;
    }

    template <class ValueType>
    Iterator<ValueType>::Iterator(const Iterator &other)
        : ptr_(other.ptr_)
        , owner_(other.owner_)
        , pos_(other.pos_)
    {}

    template <class ValueType>
    Iterator<ValueType>& Iterator<ValueType>::operator=(const Iterator<ValueType> &other)
    {
        ptr_ = other.ptr_;
        owner_ = other.owner_;
        pos_ = other.pos_;
        return *this;
    }

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
    int Iterator<ValueType>::relativePos() const
    {
        if (pos_ >= owner_->left_)
            return pos_ - owner_->left_;
        return owner_->realSize_ - pos_ + owner_->right_;
    }

    template <class ValueType>
    bool Iterator<ValueType>::operator<(const Iterator<ValueType> &other)
    {
        return relativePos() < other.relativePos();

    }
    template <class ValueType>
    bool Iterator<ValueType>::operator<=(const Iterator<ValueType> &other)
    {
        return operator<(*this, other) || operator==(*this, other);
    }

    template <class ValueType>
    bool Iterator<ValueType>::operator!=(const Iterator<ValueType> &other)
    {
        return ptr_ != other.ptr_;
    }

    template <class ValueType>
    Iterator<ValueType>& Iterator<ValueType>::movePointer(int steps)
    {
        int oldPos = pos_;
        pos_ += steps;
        int capacity = owner_->realSize_;
        if (pos_ >= capacity) {
            pos_ -= capacity;
        }
        if (pos_ < 0) {
            pos_ += capacity;
        }
#ifndef NDEBUG
        if (owner_->left_ < owner_->right_) {
            if (pos_ < owner_->left_)
                throw std::range_error("negative index of iterator");
            if (pos_ > owner_->right_)
                throw std::range_error("index of iterator is too large");
        } else {
            if (!((owner_->left_ <= pos_ && pos_ < capacity) || (0 <= pos_ && pos_ <= owner_->right_))) {
                throw std::range_error("bad iterator index");
            }
        }
#endif
        ptr_ += pos_ - oldPos;
        return *this;
    }

    template <class ValueType>
    Iterator<ValueType>& Iterator<ValueType>::operator++()
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
    Iterator<ValueType>& Iterator<ValueType>::operator--()
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
    Iterator<ValueType> Iterator<ValueType>::operator-(int steps) const
    {
        Iterator<ValueType> tmp(*this);
        return tmp.movePointer(-steps);
    }

    template <class ValueType>
    Iterator<ValueType> Iterator<ValueType>::operator+(int steps) const
    {
        Iterator<ValueType> tmp(*this);
        return tmp.movePointer(+steps);
    }

    template <class ValueType>
    int Iterator<ValueType>::operator-(const Iterator <ValueType> &other)
    {
        return this->relativePos() - other.relativePos();
    }

}
#endif
