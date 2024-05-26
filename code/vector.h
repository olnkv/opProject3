#ifndef VECTOR_H
#define VECTOR_H

#include <iostream>
#include <initializer_list>
#include <limits>
#include <algorithm>
#include <stdexcept>

template <typename T>
/// @class MyVector
/// @brief Nuosavo konteinerio klasė
class MyVector
{
private:
    size_t size_;
    size_t capacity_;
    T *data_;

public:
    /// @brief Maksimalaus galimo vektoriaus dydžio grąžinimas
    /// @return Maksimalus vektoriaus dydis
    int max_size() const { return std::numeric_limits<unsigned int>::max() / sizeof(T); }
    MyVector() : size_(0), capacity_(0), data_(new T[capacity_]) {}
    MyVector(std::initializer_list<T> init) : size_(init.size()), capacity_(init.size()), data_(new T[capacity_]) { std::copy(init.begin(), init.end(), data_); }
    ~MyVector() { delete[] data_; }

    /// @brief Kopijavimo konstruktorius
    /// @param vector_ Vektorius, iš kurio kopijuojami duomenys
    MyVector(const MyVector<T> &vector_) : size_(vector_.size_), capacity_(vector_.capacity_), data_(new T[capacity_])
    {
        for (unsigned int i = 0; i < size_; i++)
            data_[i] = vector_.data_[i];
    }

    /// @brief Move konstuktorius
    /// @param vector_ Vektorius, iš kurio kopijuojami duomenys
    MyVector(MyVector &&vector_) noexcept : size_(vector_.size_), capacity_(vector_.capacity_), data_(vector_.data_)
    {
        vector_.size_ = 0;
        vector_.capacity_ = 0;
        vector_.data_ = nullptr;
    }

    /// @brief Kopijavimo operatorius
    /// @param vector_ Vektorius, iš kurio kopijuojami duomenys
    MyVector &operator=(const MyVector &vector_)
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

    /// @brief Move operatorius
    /// @param vector_ Vektorius, iš kurio perkeliami duomenys 
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

    //Element access

    /// @brief Nurodyto elemento grąžinimas
    /// @param index Elemento indeksas
    T &operator[](unsigned int index) { return data_[index]; }
    /// @brief Nurodyto elemento grąžinimas
    /// @param index Elemento indeksas
    const T &operator[](unsigned int index) const { return data_[index]; }
    /// @brief Pirmo elemeneto grąžinimas
    /// @return Pirmas elementas
    T &front() { return data_[0]; }
    /// @brief Pirmo elemeneto grąžinimas
    /// @return Pirmas elementas
    const T &front() const { return data_[0]; }
    /// @brief Paskutinio elemeneto grąžinimas
    /// @return Paskutinis elementas
    T &back() { return data_[size_ - 1]; }
    /// @brief Paskutinio elemeneto grąžinimas
    /// @return Paskutinis elementas
    const T &back() const { return data_[size_ - 1]; }
    /// @brief Rodyklės į duomenis grąžinimas
    /// @return Rodyklė į duomenis
    T *data() noexcept { return data_; }

    //Iterators

    /// @brief Rodyklės į pirmąjį elementą grąžinimas
    /// @return Rodyklė į pirmąjį elementą
    T *begin() noexcept { return data_; }
    /// @brief Rodyklės į pirmąjį elementą grąžinimas
    /// @return Rodyklė į pirmąjį elementą
    const T *begin() const noexcept { return data_; }
    /// @brief Rodyklės į vektoriaus pabaigą grąžinimas
    /// @return Rodyklė į vektoriaus pabaigą
    T *end() noexcept { return data_ + size_; }
    /// @brief Rodyklės į vektoriaus pabaigą grąžinimas
    /// @return Rodyklė į vektoriaus pabaigą
    const T *end() const noexcept { return data_ + size_; }
    /// @brief Nurodyto elemento grąžinimas
    /// @param index Elemento indeksas
    /// @return Elementas
    /// @throw std::out_of_range Jei indeksas už ribų
    T &at(unsigned int index)
    {
        if (index >= size_)
            throw std::out_of_range("Indeksas uz ribu!");
        return data_[index];
    }
    /// @brief Nurodyto elemento grąžinimas
    /// @param index Elemento indeksas
    /// @return Elementas
    /// @throw std::out_of_range Jei indeksas už ribų
    const T &at(unsigned int index) const
    {
        if (index >= size_)
            throw std::out_of_range("Indeksas uz ribu!");
        return data_[index];
    }

    //Capacity

    /// @brief Vektoriaus dydžio grąžinimas
    /// @return Vektoriaus dydis
    unsigned int size() const { return size_; }
    /// @brief Vektoriaus talpos grąžinimas
    /// @return Vektoriaus talpa 
    unsigned int capacity() const { return capacity_; }
    /// @brief Patikrinimas, ar vektorius tuščias
    /// @retval TRUE vektorius tuščias
    /// @retval FALSE vektorius netuščias
    bool empty() const { return size_ == 0; }

    /// @brief Vektoriuje vietos rezervavimas
    /// @param reserve_ Nauja vektoriaus talpa
    /// @throw std::length_error Jei vektorius neturi tiek vietos
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

    /// @brief Vektoriaus talpos sumažinimas iki jo dydžio
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

    /// @brief Elemento priskyrimas nurodytam kiekiui
    /// @param n Kiekis
    /// @param value Elementas
    void assign(unsigned int n, const T &value)
    {
        if (n > capacity_)
            reserve(n);
        for (unsigned int i = 0; i < n; i++)
            data_[i] = value;
        size_ = n;
    }

    //Modifiers

    /// @brief Vektoriaus valymas
    void clear() { size_ = 0; }

    /// @brief Elemento pridėjimas į vektoriaus pabaigą
    /// @param value Pridėdamas elementas
    void push_back(const T &value)
    {
        if (size_ >= capacity_)
            reserve(capacity_ == 0 ? 1 : size_ * 2);
        data_[size_++] = value;
    }

    /// @brief Elemento pridėjimas į nurodytą poziciją
    /// @param index Indeksas
    /// @param value Elementas
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

    /// @brief Elemento pridėjimas į nurodytą poziciją
    /// @param index Indeksas
    /// @param value Elementas
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

    /// @brief Elemento pridėjimas į vektoriaus pabaigą
    /// @param value Elementas
    T &emplace_back(T &&value)
    {
        if (size_ >= capacity_)
            reserve(capacity_ == 0 ? 1 : size_ * 2);
        data_[size_++] = std::move(value);
        return data_[size_ - 1];
    }

    /// @brief Elemento šalinimas iš vektoriaus pabaigos
    void pop_back()
    {
        if (size_ > 0)
        {
            --size_;
        }
    }

    /// @brief Vektoriaus dydžio nurodymas
    /// @param newsize_ Dydis
    void resize(unsigned int newsize_)
    {
        if (newsize_ > capacity_)
            reserve(newsize_);
        for (unsigned int i = size_; i < newsize_; i++)
            data_[i] = T();
        size_ = newsize_;
    }

    /// @brief Vektorių sukeitimas vietomis
    /// @param vector_ Kitas vektorius
    void swap(MyVector &vector_)
    {
        std::swap(size_, vector_.size_);
        std::swap(capacity_, vector_.capacity_);
        std::swap(data_, vector_.data_);
    }

    /// @brief Nurodyto elemento išmetimas
    /// @param index Elementas
    T *erase(unsigned int index)
    {
        for (unsigned int i = index; i < size_ - 1; i++)
            data_[i] = data_[i + 1];
        size_--;
        return &data_[index];
    }

    /// @brief Elementų išmetimas tarp nurodytų elementų
    /// @param begin_ Pirmas elementas
    /// @param end_ Paskutinis elementas
    /// @return Rodyklė į paskutinį elementą
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