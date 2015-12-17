#ifndef DEQUE_H
#define DEQUE_H

#include "deque_iterator.h"
#include <iterator>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <memory>

const size_t MIN_CAPACITY = 4;

namespace DequeIterator {
    template <class IterT, class DequeT>
        class Iterator;
}

template <class T>
class Deque
{
    friend class DequeIterator::Iterator<T, T>;
    friend class DequeIterator::Iterator<const T, T>;
public:
    typedef DequeIterator::Iterator<T, T> iterator;
    typedef DequeIterator::Iterator<const T, T> const_iterator;
    typedef std::reverse_iterator<iterator> reverse_iterator;
    typedef std::reverse_iterator<const_iterator> const_reverse_iterator;
    Deque(size_t=0);
    Deque(const Deque &);
    Deque(Deque &&);
    ~Deque();
    T pop_back();
    T pop_front();
    void push_back(const T &);
    void push_front(const T &);
    const T& operator[](size_t) const;
    T& operator[](size_t);
    const T& back() const;
    T& back();
    const T& front() const;
    T& front();
    bool empty() const;
    size_t size() const;
    void shrink_to_fit();
    std::unique_ptr<T []> getData(size_t=0) const;
    iterator begin();
    const_iterator begin() const;
    const_iterator cbegin() const;
    iterator end();
    const_iterator end() const;
    const_iterator cend() const;
    reverse_iterator rbegin();
    const_reverse_iterator rbegin() const;
    const_reverse_iterator crbegin() const;
    reverse_iterator rend();
    const_reverse_iterator rend() const;
    const_reverse_iterator crend() const;
private:
    int decMod(int &) const;
    int incMod(int &) const;
    void tryExtend();
    void tryShrink();
    std::unique_ptr<T[]> data_;
    size_t realSize_;
    size_t size_;
    int left_, right_;
};

template <class T>
Deque<T>::Deque(size_t size)
    : size_(size)
    , left_(0)
    , right_(0)
{
    data_ = std::unique_ptr<T []> (new T[realSize_ = std::max(MIN_CAPACITY, size_ * 2)]);
}

template <class T>
Deque<T>::~Deque<T>()
{
    //delete [] data_;
}

template <class T>
Deque<T>::Deque(const Deque &deque)
    : size_(deque.size_)
    , realSize_(deque.size_)
    , left_(0)
{
    right_ = static_cast<int>(size_);
    data_ = std::unique_ptr<T []> (new T [realSize_ = std::max(MIN_CAPACITY, realSize_)]);
    std::copy(deque.data_.get(), deque.data_.get() + size_, data_.get());
}

template <class T>
Deque<T>::Deque(Deque &&deque)
    : size_(deque.size_)
    , realSize_(deque.realSize_)
    , left_(deque.left_)
    , right_(deque.right_)
{
    data_ = std::move(deque.data_);
    deque.data_ = nullptr;
}


template <class T>
int Deque<T>::decMod(int &index) const
{
    --index;
    if (index < 0)
        index = static_cast<int>(realSize_) - 1;
    return index;
}

template <class T>
int Deque<T>::incMod(int &index) const
{
    ++index;
    if (index >= static_cast<int>(realSize_))
        index = 0;
    return index;
}

template <class T>
std::unique_ptr<T []> Deque<T>::getData(size_t minBufferSize) const
{
    std::unique_ptr<T []> dest(new T [std::max(minBufferSize, size_)]);
    size_t piece1, piece2;
    if (left_ <= right_) {
        piece1 = size_;
        piece2 = 0;
    } else {
        piece1 = realSize_ - left_;
        piece2 = right_;
    }
    std::copy(data_.get() + left_, data_.get() + left_ + piece1, dest.get());
    std::copy(data_.get(), data_.get() + piece2, dest.get() + piece1);
    return dest;
}

template <class T>
void Deque<T>::tryExtend()
{
    if (size_ + 1 >= realSize_) {
        std::unique_ptr<T []> buffer(std::move(this->getData(realSize_ * 2)));
        realSize_ *= 2;
        data_.swap(buffer);
        left_ = 0;
        right_ = static_cast<int>(size_);
    }
}

template <class T>
void Deque<T>::shrink_to_fit()
{
    std::unique_ptr<T []> buffer(std::move(this->getData()));
    data_.swap(buffer);
    left_ = 0;
    right_ = static_cast<int>(size_);
    realSize_ = size_;
}


template <class T>
void Deque<T>::tryShrink()
{
    if (realSize_ > 4 && size_ * 4 <= realSize_) {
        std::unique_ptr<T []> buffer(std::move(this->getData(realSize_ / 2)));
        realSize_ /= 2;
        data_.swap(buffer);
        left_ = 0;
        right_ = static_cast<int>(size_);
    }
}

template <class T>
T Deque<T>::pop_back()
{
#ifndef NDEBUG
    if (size_ == 0)
        throw "pop from empty deque";
#endif
    this->decMod(right_);
    T poped = data_[right_];
    --size_;
    this->tryShrink();
    return poped;
}

template <class T>
T Deque<T>::pop_front()
{
#ifndef NDEBUG
    if (size_ == 0)
        throw "pop from empty deque";
#endif
    T poped = data_[left_];
    this->incMod(left_);
    --size_;
    this->tryShrink();
    return poped;
}

template <class T>
void Deque<T>::push_back(const T &elem)
{
    ++size_;
    data_[right_] = elem;
    this->incMod(right_);
    this->tryExtend();
}

template<class T>
void Deque<T>::push_front(const T &elem)
{
    ++size_;
    this->decMod(left_);
    data_[left_] = elem;
    this->tryExtend();
}

template <class T>
const T& Deque<T>::operator[](size_t index) const
{
#ifndef NDEBUG
    if (index >= size_)
        throw "deque index is out of range";
#endif
    index += left_;
    if (index >= realSize_) {
        index -= realSize_;
    }
#ifndef NDEBUG
    if (index >= realSize_)
        throw "deque index is out of range";
#endif
    return data_[index];
}

template <class T>
T& Deque<T>::operator[](size_t index)
{
#ifndef NDEBUG
    if (index >= size_)
        throw "deque index is out of range";
#endif
    index += left_;
    if (index >= realSize_) {
        index -= realSize_;
    }
#ifndef NDEBUG
    if (index >= realSize_)
        throw "deque index is out of range";
#endif
   return data_[index];
}

template <class T>
const T& Deque<T>::back() const
{
#ifndef NDEBUG
    if (size_ == 0)
        throw "there is no back element in empty deque";
#endif
    int r = right_;
    return data_[this->decMod(r)];
}

template <class T>
T& Deque<T>::back()
{
#ifndef NDEBUG
    if (size_ == 0)
        throw "there is no back element in empty deque";
#endif
    int r = right_;
    return data_[this->decMod(r)];
}

template <class T>
const T& Deque<T>::front() const
{
#ifndef NDEBUG
    if (size_ == 0)
        throw "there is no front element in empty deque";
#endif
    return data_[left_];
}

template <class T>
T& Deque<T>::front()
{
#ifndef NDEBUG
    if (size_ == 0)
        throw "there is no front element in empty deque";
#endif
    return data_[left_];
}

template <class T>
size_t Deque<T>::size() const
{
    return size_;
}

template <class T>
bool Deque<T>::empty() const
{
    return size_ == 0;
}


template <class T>
typename Deque<T>::iterator Deque<T>::begin()
{
    return iterator(data_.get() + left_, *this);
}

template <class T>
typename Deque<T>::const_iterator Deque<T>::begin() const
{
    return const_iterator(data_.get() + left_, *this);
}

template <class T>
typename Deque<T>::const_iterator Deque<T>::cbegin() const
{
    return const_iterator(data_.get() + left_, *this);
}

template <class T>
typename Deque<T>::iterator Deque<T>::end()
{
    return iterator(data_.get() + right_, *this);
}

template <class T>
typename Deque<T>::const_iterator Deque<T>::end() const
{
    return const_iterator(data_.get() + right_, *this);
}

template <class T>
typename Deque<T>::const_iterator Deque<T>::cend() const
{
    return const_iterator(data_.get() + right_, *this);
}

template <class T>
typename Deque<T>::reverse_iterator Deque<T>::rbegin()
{
    return reverse_iterator(iterator(data_.get() + right_, *this));
}

template <class T>
typename Deque<T>::const_reverse_iterator Deque<T>::rbegin() const
{
    return const_reverse_iterator(const_iterator(data_.get() + right_, *this));
}

template <class T>
typename Deque<T>::const_reverse_iterator Deque<T>::crbegin() const
{
    return const_reverse_iterator(const_iterator(data_.get() + right_, *this));
}

template <class T>
typename Deque<T>::reverse_iterator Deque<T>::rend()
{
    return reverse_iterator(iterator(data_.get() + left_, *this));
}

template <class T>
typename Deque<T>::const_reverse_iterator Deque<T>::rend() const
{
    return const_reverse_iterator(const_iterator(data_.get() + left_, *this));
}

template <class T>
typename Deque<T>::const_reverse_iterator Deque<T>::crend() const
{
    return const_reverse_iterator(const_iterator(data_.get() + left_, *this));
}

#endif
