#ifndef DEQUE_ITERATOR_H
#define DEQUE_ITERATOR_H

#include <iterator>
#include <iostream>


template <class T>
class Deque;

namespace DequeIterator {

    template <typename IterT, typename DequeT=IterT> //iterator pointer value type and container value type
    class Iterator
        : public std::iterator<std::random_access_iterator_tag, IterT>
    {
        friend class Deque<DequeT>;
    public:
        Iterator(IterT * ptr, const Deque<DequeT> &);
        Iterator();
        Iterator(const Iterator &);
        Iterator& operator=(const Iterator &);
        IterT operator*() const;
        IterT& operator*();
        IterT * operator->();
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
        Iterator& operator+=(int);
        Iterator& operator-=(int);
        int operator-(const Iterator &) const;
    private:
        int relativePos() const;
        Iterator& movePointer(int);
        IterT * ptr_;
        const Deque<DequeT> * owner_;
        int pos_; // position in Array [0..capacity): [left..right] or ([left..capacity) + [0..right])
    };

    template <typename IterT, typename DequeT>
    Iterator<IterT, DequeT>::Iterator()
        : ptr_(nullptr)
        , owner_(nullptr)
        , pos_(0)
    {}

    template <typename IterT, typename DequeT>
    Iterator<IterT, DequeT>::Iterator(IterT * ptr, const Deque<DequeT> &dequeOwner)
        : ptr_(ptr)
        , owner_(&dequeOwner)
    {
        pos_ = ptr - dequeOwner.data_.get();
    }

    template <typename IterT, typename DequeT>
    Iterator<IterT, DequeT>::Iterator(const Iterator<IterT, DequeT> &other)
        : ptr_(other.ptr_)
        , owner_(other.owner_)
        , pos_(other.pos_)
    {}

    template <typename IterT, typename DequeT>
    Iterator<IterT, DequeT>& Iterator<IterT, DequeT>::operator=(const Iterator<IterT, DequeT> &other)
    {
        ptr_ = other.ptr_;
        owner_ = other.owner_;
        pos_ = other.pos_;
        return *this;
    }

    template <typename IterT, typename DequeT>
    IterT Iterator<IterT, DequeT>::operator*() const
    {
        return *ptr_;
    }

    template <typename IterT, typename DequeT>
    IterT& Iterator<IterT, DequeT>::operator*()
    {
        return *ptr_;
    }

    template <typename IterT, typename DequeT>
    IterT* Iterator<IterT, DequeT>::operator->()
    {
        return ptr_;
    }

    template <typename IterT, typename DequeT>
    bool Iterator<IterT, DequeT>::operator==(const Iterator<IterT, DequeT> &other)
    {
        return ptr_ == other.ptr_;
    }


    template <typename IterT, typename DequeT>
    int Iterator<IterT, DequeT>::relativePos() const
    {
        if (pos_ >= owner_->left_)
            return pos_ - owner_->left_;
        return owner_->realSize_ - pos_ + owner_->right_;
    }

    template <typename IterT, typename DequeT>
    bool Iterator<IterT, DequeT>::operator<(const Iterator<IterT, DequeT> &other)
    {
        return relativePos() < other.relativePos();

    }
    template <typename IterT, typename DequeT>
    bool Iterator<IterT, DequeT>::operator<=(const Iterator<IterT, DequeT> &other)
    {
        return operator<(*this, other) || operator==(*this, other);
    }

    template <typename IterT, typename DequeT>
    bool Iterator<IterT, DequeT>::operator!=(const Iterator<IterT, DequeT> &other)
    {
        return ptr_ != other.ptr_;
    }

    template <typename IterT, typename DequeT>
    Iterator<IterT, DequeT>& Iterator<IterT, DequeT>::movePointer(int steps)
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

    template <typename IterT, typename DequeT>
    Iterator<IterT, DequeT>& Iterator<IterT, DequeT>::operator++()
    {
        return this->movePointer(1);
    }

    template <typename IterT, typename DequeT>
    Iterator<IterT, DequeT> Iterator<IterT, DequeT>::operator++(int)
    {
        Iterator<IterT, DequeT> tmp(*this);
        this->operator++();
        return tmp;
    }

    template <typename IterT, typename DequeT>
    Iterator<IterT, DequeT>& Iterator<IterT, DequeT>::operator--()
    {
        return this->movePointer(-1);
    }

    template <typename IterT, typename DequeT>
    Iterator<IterT, DequeT> Iterator<IterT, DequeT>::operator--(int)
    {
        Iterator<IterT, DequeT> tmp(*this);
        this->operator--();
        return tmp;
    }

    template <typename IterT, typename DequeT>
    Iterator<IterT, DequeT> Iterator<IterT, DequeT>::operator-(int steps) const
    {
        Iterator<IterT, DequeT> tmp(*this);
        return tmp.movePointer(-steps);
    }

    template <typename IterT, typename DequeT>
    Iterator<IterT, DequeT> Iterator<IterT, DequeT>::operator+(int steps) const
    {
        Iterator<IterT, DequeT> tmp(*this);
        return tmp.movePointer(+steps);
    }

    template <typename IterT, typename DequeT>
    Iterator<IterT, DequeT>& Iterator<IterT, DequeT>::operator+=(int steps)
    {
        return this->movePointer(steps);
    }

    template <typename IterT, typename DequeT>
    Iterator<IterT, DequeT>& Iterator<IterT, DequeT>::operator-=(int steps)
    {
        return this->movePointer(-steps);
    }

    template <typename IterT, typename DequeT>
    int Iterator<IterT, DequeT>::operator-(const Iterator<IterT, DequeT> &other) const
    {
        return this->relativePos() - other.relativePos();
    }

}
#endif
