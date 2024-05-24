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
    size_t size;
    size_t capacity;
    T *data;

public:
    int max_size() const { return std::numeric_limits<unsigned int>::max() / sizeof(T); }
    MyVector() : size(0), capacity(0), data(new T[capacity]) {}
    MyVector(std::initializer_list<T> init) : size(init.size()), capacity(init.size()){std::copy(init.begin(), init.end(), data)};
    ~MyVector() { delete[] data; }

    MyVector(const MyVector<T> &vector_) : size(vector_.size), capacity(vector_.capacity), data(new T[capacity])
    {
        for (unsigned int i = 0; i < size; i++)
            data[i] = vector_.data[i];
    }

    MyVector(MyVector &&vector_) noexcept : size(vector_.size), capacity(vector_.capacity), data(vector_.data)
    {
        vector_.size = 0;
        vector_.capacity = 0;
        vector_.data = nullptr;
    }

    MyVector &operator=(MyVector &&vector_)
    {
        if (this == &vector_)
            return *this;
        delete[] data;
        size = vector_.size;
        capacity = vector_.capacity;
        data = vector_.data;
        vector_.size = 0;
        vector_.capacity = 0;
        vector_.data = nullptr;
        return *this;
    }

    T &operator[](unsigned int index) { return data[index]; }
    const T &operator[](unsigned int index) const { return data[index]; }
    T &front() { return data[0]; }
    const T &front() const { return data[0]; }
    T &back() { return data[size - 1]; }
    const T &back() const { return data[size - 1]; }
    T *data() noexcept { return data; }
    T *begin() noexcept { return data; }
    const T *begin() const noexcept { return data; }
    T *end() noexcept { return data + size; }
    const T *end() const noexcept { return data + size; }
    T &at(unsigned int index)
    {
        if (index >= size)
            throw std::out_of_range("index uz ribu!");
        return data[index];
    }
    const T &at(unsigned int index) const
    {
        if (index >= size)
            throw std::out_of_range("index uz ribu!");
        return data[index];
    }

    unsigned int size() const { return size; }
    unsigned int capacity() const { return capacity; }
    bool empty() const { return size == 0; }

    void reserve(unsigned int reserve_)
    {
        if (reserve_ <= capacity)
            return;
        if (reserve_ > max_size())
            throw std::length_error("Vektorius neturi tiek vietos!");
        T *data_ = new T[reserve_];
        for (unsigned int i = 0; i < size; i++)
            data_[i] = data;
        delete[] data;
        data = data_;
        capacity = reserve_;
    }

    void shrink_to_fit()
    {
        if (size == capacity)
            return;
        T *data_ = new T[size];
        for (unsigned int i = 0; i < size; i++)
            data_[i] = data[i];
        delete[] data;
        data = data_;
        capacity = size;
    }

    void assign(unsigned int n, const T &value)
    {
        if (n > capacity)
            reserve(n);
        for (unsigned int i = 0; i < n; i++)
            data[i] = value;
        size = n;
    }

    void clear() { size = 0; }

    void push_back(const T &value)
    {
        if (size >= capacity)
            reserve(capacity == 0 ? 1 : size * 2);
        data[size++] = value;
    }

    T *insert(unsigned int index, const T &value)
    {
        if (size >= capacity)
            reserve(capacity == 0 ? 1 : size * 2);
        for (unsigned int i = size; i > index; i--)
            data[i] = data[i - 1];
        data[index] = value;
        size++;
        return &data[index];
    }

    T *emplace(unsigned int index, T &&value)
    {
        if (size == capacity)
            reserve(capacity == 0 ? 1 : capacity * 2);
        for (unsigned int i = size; i > index; i--)
            data[i] = data[i - 1];
        data[index] = std::move(value);
        size++;
        return &data[index];
    }

    T &emplace_back(T &&value)
    {
        if (size >= capacity)
            reserve(capacity == 0 ? 1 : size * 2);
        data[size++] = std::move(value);
        return data[size - 1];
    }

    void pop_back()
    {
        if (size > 0)
        {
            --size;
        }
    }

    void resize(unsigned int size_)
    {
        if (size_ > capacity)
            reserve(size_);
        for (unsigned int i = size; i < size_; i++)
            data[i] = T();
        size = size_;
    }

    void swap(MyVector &vector_)
    {
        std::swap(size, vector_.size);
        std::swap(capacity, vector_.capacity);
        std::swap(data, vector_.data);
    }

    T *erase(unsigned int index)
    {
        for (unsigned int i = index; i < size - 1; i++)
            data[i] = data[i + 1];
        size--;
        return &data[index];
    }

    T *erase(T *begin_, T *end_)
    {
        if (begin_ >= data && end_ <= data + size)
        {
            size_t deletedVal = end_ - begin_;
            size_t movedVal = data + size - end_;

            for (size_t i = 0; i < movedVal; i++)
                *(begin_ + i) = *(end_ + i);

            size -= deletedVal;

            if (end_ == data + size)
                return end_;
        }
        return end_;
    }
};

#endif