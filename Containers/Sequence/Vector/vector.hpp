#ifndef __VECTOR__
#define __VECTOR__

#include <iostream>
#include <algorithm>
#include <stdexcept>

template <typename T>
class Vector
{
private:
    int m_size;
    int m_capacity;
    T* m_data;

public:
    Vector();
    Vector(const int& size);
    ~Vector();

    Vector(const Vector& other);
    Vector& operator=(const Vector& other);

    Vector(Vector&& other) noexcept;
    Vector& operator=(Vector&& other) noexcept;
    
    void reserve(const int& newCapacity);    
    void resize(const int& newSize, const T& value = T());
    void push_back(const T& value);

    int getSize() const;
    int getCapacity() const;
    T& operator[](const int& index) const;
    T& at(const int& index);

    void clear();
    bool empty() const;
    void pop_back();
    T& front() const;
    T& back() const;

    void print() const;
};

// Your existing functions

template <typename T>
Vector<T>::Vector() : m_size(0), m_capacity(0), m_data(nullptr) {}

template <typename T>
Vector<T>::Vector(const int& size) : m_size(size), m_capacity(2 * size)
{
    m_data = new T[m_capacity];
}

template <typename T>
Vector<T>::~Vector()
{
    delete[] m_data;
    m_data = nullptr;
}

template <typename T>
Vector<T>::Vector(const Vector& other) : m_size(other.m_size), m_capacity(other.m_capacity)
{
    m_data = new T[m_capacity];
    for (int i = 0; i < m_size; ++i)
    {
        m_data[i] = other.m_data[i];
    }
}

template <typename T>
Vector<T>& Vector<T>::operator=(const Vector& other)
{
    if (this != &other)
    {
        m_size = other.m_size;
        m_capacity = other.m_capacity;
        
        delete[] m_data;
        m_data = new T[m_capacity];

        for (int i = 0; i < m_size; ++i)
        {
            m_data[i] = other.m_data[i];
        }
    }
    
    return *this;
}

template <typename T>
Vector<T>::Vector(Vector&& other) noexcept : m_size(other.m_size), m_capacity(other.m_capacity), m_data(other.m_data)
{
    other.m_size = 0;
    other.m_capacity = 0;
    other.m_data = nullptr;
}

template <typename T>
Vector<T>& Vector<T>::operator=(Vector&& other) noexcept
{
    if (this != &other)
    {
        delete[] m_data;

        m_size = other.m_size;
        m_capacity = other.m_capacity;
        m_data = other.m_data;

        other.m_size = 0;
        other.m_capacity = 0;
        other.m_data = nullptr;
    }

    return *this;
}

template <typename T>
void Vector<T>::reserve(const int& newCapacity)
{
    if (newCapacity > m_capacity)
    {
        T* newData = new T[newCapacity];
        for (int i = 0; i < m_size; ++i) 
        {
            newData[i] = std::move(m_data[i]);
        }
        delete[] m_data;
        m_data = newData;
        m_capacity = newCapacity;
    }
}

template <typename T>
void Vector<T>::resize(const int& newSize, const T& value) 
{
    if (newSize > m_capacity) 
    {
        reserve(newSize);
    }
    if (newSize > m_size) 
    {
        std::fill(m_data + m_size, m_data + newSize, value);
    }
    m_size = newSize;
}

template <typename T>
void Vector<T>::push_back(const T& value) 
{
    if (m_size >= m_capacity) 
    {
        int newCapacity = (m_capacity == 0) ? 1 : m_capacity * 2;
        reserve(newCapacity);
    }
    m_data[m_size++] = value;
}

template <typename T>
int Vector<T>::getSize() const
{
    return m_size;
}

template <typename T>
int Vector<T>::getCapacity() const
{
    return m_capacity;
}

template <typename T>
T& Vector<T>::operator[](const int& index) const
{
    return m_data[index];
}

template <typename T>
T& Vector<T>::at(const int& index)
{
    if (index >= m_size) 
    {
        throw std::out_of_range("Index out of range");
    }
    return m_data[index];
}

template <typename T>
void Vector<T>::clear()
{
    delete[] m_data;
    m_data = nullptr;
    m_size = 0;
    m_capacity = 0;
}

template <typename T>
bool Vector<T>::empty() const
{
    return m_size == 0;
}

template <typename T>
void Vector<T>::pop_back()
{
    if (m_size > 0)
    {
        --m_size;
    }
    else
    {
        throw std::out_of_range("Cannot pop_back from an empty vector");
    }
}

template <typename T>
T& Vector<T>::front() const
{
    if (m_size == 0)
    {
        throw std::out_of_range("Vector is empty");
    }
    return m_data[0];
}

template <typename T>
T& Vector<T>::back() const
{
    if (m_size == 0)
    {
        throw std::out_of_range("Vector is empty");
    }
    return m_data[m_size - 1];
}

template <typename T>
void Vector<T>::print() const
{
    for (int i = 0; i < m_size; ++i)
    {
        std::cout << m_data[i] << " ";
    }
    std::cout << std::endl;
}

#endif // __VECTOR__