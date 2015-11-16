#ifndef DEQUE_H
#define DEQUE_H

#include "deque_iterator.h"
#include <iterator>
#include <cstring>
#include <algorithm>

const size_t MIN_CAPACITY = 4;

template <class T>
class Deque
{
public:
    typedef DequeIterator::Iterator<T> iterator;
    typedef DequeIterator::Iterator<const T> const_iterator;
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
    T operator[](size_t) const;
    T& operator[](size_t);
    T back() const;
    T& back();
    T front() const;
    T& front();
    bool empty() const;
    size_t size() const;
    void shrink_to_fit();
    T * getData(size_t=0) const;
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
protected:
    int decMod(int &) const;
    int incMod(int &) const;
    void tryExtend();
    void tryShrink();
    T * data_;
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
    data_ = new T[realSize_ = std::max(MIN_CAPACITY, size_ * 2)];
}

template <class T>
Deque<T>::~Deque<T>()
{
    delete [] data_;
}

template <class T>
Deque<T>::Deque(const Deque &deque)
    : size_(deque.size_)
    , realSize_(deque.size_)
    , left_(0)
{
    right_ = static_cast<int>(size_);
    data_ = new T [realSize_ = std::max(MIN_CAPACITY, realSize_)];
    memcpy(data_, deque.data_, sizeof(T) * size_);
}

template <class T>
Deque<T>::Deque(Deque &&deque)
    : size_(deque.size_)
    , realSize_(deque.realSize_)
    , left_(deque.left_)
    , right_(deque.right_)
{
    data_ = deque.data_;
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
T * Deque<T>::getData(size_t minBufferSize) const
{
    T * dest = new T [std::max(minBufferSize, size_)];
    size_t piece1, piece2;
    if (left_ <= right_) {
        piece1 = size_;
        piece2 = 0;
    } else {
        piece1 = realSize_ - left_;
        piece2 = right_;
    }
    memcpy(dest, data_ + left_, sizeof(T) * piece1);
    memcpy(dest + piece1, data_, sizeof(T) * piece2);
    return dest;
}

template <class T>
void Deque<T>::tryExtend()
{
    if (size_ + 1 >= realSize_) {
        T * buffer = this->getData(realSize_ * 2);
        realSize_ *= 2;
        delete [] data_;
        data_ = buffer;
        left_ = 0;
        right_ = static_cast<int>(size_);
    }
}

template <class T>
void Deque<T>::shrink_to_fit()
{
    T * buffer = this->getData();
    delete [] data_;
    data_ = buffer;
    left_ = 0;
    right_ = static_cast<int>(size_);
    realSize_ = size_;
}


template <class T>
void Deque<T>::tryShrink()
{
    if (realSize_ > 4 && size_ * 4 <= realSize_) {
        T * buffer = this->getData(realSize_ / 2);
        realSize_ /= 2;
        delete [] data_;
        data_ = buffer;
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
    this->tryExtend();
    ++size_;
    data_[right_] = elem;
    this->incMod(right_);
}

template<class T>
void Deque<T>::push_front(const T &elem)
{
    this->tryExtend();
    ++size_;
    this->decMod(left_);
    data_[left_] = elem;
}

template <class T>
T Deque<T>::operator[](size_t index) const
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
T Deque<T>::back() const
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
T Deque<T>::front() const
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
    return iterator(data_ + left_, left_, right_, left_, realSize_);
}

template <class T>
typename Deque<T>::const_iterator Deque<T>::begin() const
{
    return const_iterator(data_ + left_, left_, right_, left_, realSize_);
}

template <class T>
typename Deque<T>::const_iterator Deque<T>::cbegin() const
{
    return const_iterator(data_ + left_, left_, right_, left_, realSize_);
}

template <class T>
typename Deque<T>::iterator Deque<T>::end()
{
    return iterator(data_ + right_, left_, right_, right_, realSize_);
}

template <class T>
typename Deque<T>::const_iterator Deque<T>::end() const
{
    return const_iterator(data_ + right_, left_, right_, right_, realSize_);
}

template <class T>
typename Deque<T>::const_iterator Deque<T>::cend() const
{
    return const_iterator(data_ + right_, left_, right_, right_, realSize_);
}

template <class T>
typename Deque<T>::reverse_iterator Deque<T>::rbegin()
{
    return reverse_iterator(iterator(data_ + right_, left_, right_, right_, realSize_));
}

template <class T>
typename Deque<T>::const_reverse_iterator Deque<T>::rbegin() const
{
    return const_reverse_iterator(const_iterator(data_ + right_, left_, right_, right_, realSize_));
}

template <class T>
typename Deque<T>::const_reverse_iterator Deque<T>::crbegin() const
{
    return const_reverse_iterator(const_iterator(data_ + right_, left_, right_, right_, realSize_));
}

template <class T>
typename Deque<T>::reverse_iterator Deque<T>::rend()
{
    return reverse_iterator(iterator(data_ + left_, left_, right_, left_, realSize_));
}

template <class T>
typename Deque<T>::const_reverse_iterator Deque<T>::rend() const
{
    return const_revese_iterator(const_iterator(data_ + left_, left_, right_, left_, realSize_));
}

template <class T>
typename Deque<T>::const_reverse_iterator Deque<T>::crend() const
{
    return const_reverse_iterator(const_iterator(data_ + left_, left_, right_, left_, realSize_));
}

#endif
