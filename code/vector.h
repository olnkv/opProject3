#ifndef VECTOR_H
#define VECTOR_H

#include <iostream>
#include <initializer_list>
#include <limits>
#include <algorithm>
#include <stdexcept>

template <typename T>
class MyVector
{
private:
    size_t size_;
    size_t capacity_;
    T *data_;

public:
    int max_size() const { return std::numeric_limits<unsigned int>::max() / sizeof(T); }
    MyVector() : size_(0), capacity_(0), data_(new T[capacity_]) {}
    MyVector(std::initializer_list<T> init) : size_(init.size_()), capacity_(init.size_()) { std::copy(init.begin(), init.end(), data_); }
    ~MyVector() { delete[] data_; }

    MyVector(const MyVector<T> &vector_) : size_(vector_.size_), capacity_(vector_.capacity_), data_(new T[capacity_])
    {
        for (unsigned int i = 0; i < size_; i++)
            data_[i] = vector_.data_[i];
    }

    MyVector(MyVector &&vector_) noexcept : size_(vector_.size_), capacity_(vector_.capacity_), data_(vector_.data_)
    {
        vector_.size_ = 0;
        vector_.capacity_ = 0;
        vector_.data_ = nullptr;
    }

    MyVector &operator=(const MyVector &&vector_)
    {
        if (this == &vector_)
            return *this;
        delete[] data_;
        size_ = vector_.size_;
        capacity_ = vector_.capacity_;
        data_ = new T[capacity_];
        for (unsigned int i = 0; i < size_; i++)
            data_[i] = vector_.data_[i];
        return *this;
    }

    MyVector &operator=(MyVector &&vector_)
    {
        if (this == &vector_)
            return *this;
        delete[] data_;
        size_ = vector_.size_;
        capacity_ = vector_.capacity_;
        data_ = vector_.data_;
        vector_.size_ = 0;
        vector_.capacity_ = 0;
        vector_.data_ = nullptr;
        return *this;
    }

    T &operator[](unsigned int index) { return data_[index]; }
    const T &operator[](unsigned int index) const { return data_[index]; }
    T &front() { return data_[0]; }
    const T &front() const { return data_[0]; }
    T &back() { return data_[size_ - 1]; }
    const T &back() const { return data_[size_ - 1]; }
    T *data() noexcept { return data_; }
    T *begin() noexcept { return data_; }
    const T *begin() const noexcept { return data_; }
    T *end() noexcept { return data_ + size_; }
    const T *end() const noexcept { return data_ + size_; }
    T &at(unsigned int index)
    {
        if (index >= size_)
            throw std::out_of_range("Indeksas uz ribu!");
        return data_[index];
    }
    const T &at(unsigned int index) const
    {
        if (index >= size_)
            throw std::out_of_range("Indeksas uz ribu!");
        return data_[index];
    }

    unsigned int size() const { return size_; }
    unsigned int capacity() const { return capacity_; }
    bool empty() const { return size_ == 0; }

    void reserve(unsigned int reserve_)
    {
        if (reserve_ <= capacity_)
            return;
        if (reserve_ > max_size())
            throw std::length_error("Vektorius neturi tiek vietos!");
        T *newdata_ = new T[reserve_];
        for (unsigned int i = 0; i < size_; i++)
            newdata_[i] = data_[i];
        delete[] data_;
        data_ = newdata_;
        capacity_ = reserve_;
    }

    void shrink_to_fit()
    {
        if (size_ == capacity_)
            return;
        T *newdata_ = new T[size_];
        for (unsigned int i = 0; i < size_; i++)
            newdata_[i] = data_[i];
        delete[] data_;
        data_ = newdata_;
        capacity_ = size_;
    }

    void assign(unsigned int n, const T &value)
    {
        if (n > capacity_)
            reserve(n);
        for (unsigned int i = 0; i < n; i++)
            data_[i] = value;
        size_ = n;
    }

    void clear() { size_ = 0; }

    void push_back(const T &value)
    {
        if (size_ >= capacity_)
            reserve(capacity_ == 0 ? 1 : size_ * 2);
        data_[size_++] = value;
    }

    T *insert(unsigned int index, const T &value)
    {
        if (size_ >= capacity_)
            reserve(capacity_ == 0 ? 1 : size_ * 2);
        for (unsigned int i = size_; i > index; i--)
            data_[i] = data_[i - 1];
        data_[index] = value;
        size_++;
        return &data_[index];
    }

    T *emplace(unsigned int index, T &&value)
    {
        if (size_ == capacity_)
            reserve(capacity_ == 0 ? 1 : capacity_ * 2);
        for (unsigned int i = size_; i > index; i--)
            data_[i] = data_[i - 1];
        data_[index] = std::move(value);
        size_++;
        return &data_[index];
    }

    T &emplace_back(T &&value)
    {
        if (size_ >= capacity_)
            reserve(capacity_ == 0 ? 1 : size_ * 2);
        data_[size_++] = std::move(value);
        return data_[size_ - 1];
    }

    void pop_back()
    {
        if (size_ > 0)
        {
            --size_;
        }
    }

    void resize(unsigned int newsize_)
    {
        if (newsize_ > capacity_)
            reserve(newsize_);
        for (unsigned int i = size_; i < newsize_; i++)
            data_[i] = T();
        size_ = newsize_;
    }

    void swap(MyVector &vector_)
    {
        std::swap(size_, vector_.size_);
        std::swap(capacity_, vector_.capacity_);
        std::swap(data_, vector_.data_);
    }

    T *erase(unsigned int index)
    {
        for (unsigned int i = index; i < size_ - 1; i++)
            data_[i] = data_[i + 1];
        size_--;
        return &data_[index];
    }

    T *erase(T *begin_, T *end_)
    {
        if (begin_ >= data_ && end_ <= data_ + size_)
        {
            size_t deletedVal = end_ - begin_;
            size_t movedVal = data_ + size_ - end_;

            for (size_t i = 0; i < movedVal; i++)
                *(begin_ + i) = *(end_ + i);

            size_ -= deletedVal;

            if (end_ == data_ + size_)
                return end_;
        }
        return end_;
    }
};

#endif