#ifndef __QUEUE__HPP__
#define __QUEUE__HPP__

#include <iostream>

template <typename T>
class Queue
{
private:
    struct Node
    {
        T m_data;
        Node* m_next;
        Node* m_prev;
        Node(const T& value) : m_data(value), m_next(nullptr), m_prev(nullptr) {}
    };

    Node* m_front;
    Node* m_back;
    int m_size;

public:
    Queue();
    Queue(const Queue& other);
    Queue& operator=(const Queue& other);
    Queue(Queue&& other);
    Queue& operator=(Queue&& other);
    ~Queue();

    void enqueue(const T& value);
    void dequeue();
    T& front() const;
    T& back() const;
    bool empty() const;
    void clear();
    int size() const;

    void print() const;
};

template <typename T>
Queue<T>::Queue() : m_front(nullptr), m_back(nullptr), m_size(0) {}

template <typename T>
Queue<T>::Queue(const Queue& other) : m_front(nullptr), m_back(nullptr), m_size(0) 
{
    Node* current = other.m_front;
    while (current) 
    {
        enqueue(current->m_data);
        current = current->m_next;
    }
}

template <typename T>
Queue<T>& Queue<T>::operator=(const Queue& other) 
{
    if (this != &other) 
    {
        clear();
        Node* current = other.m_front;
        while (current) 
        {
            enqueue(current->m_data);
            current = current->m_next;
        }
    }
    return *this;
}

template <typename T>
Queue<T>::Queue(Queue&& other) : m_front(other.m_front), m_back(other.m_back), m_size(other.m_size) 
{
    other.m_front = nullptr;
    other.m_back = nullptr;
    other.m_size = 0;
}

template <typename T>
Queue<T>& Queue<T>::operator=(Queue&& other) 
{
    if (this != &other) 
    {
        clear();
        m_front = other.m_front;
        m_back = other.m_back;
        m_size = other.m_size;

        other.m_front = nullptr;
        other.m_back = nullptr;
        other.m_size = 0;
    }
    return *this;
}

template <typename T>
Queue<T>::~Queue() 
{
    clear();
}

template <typename T>
void Queue<T>::enqueue(const T& value) 
{
    Node* newNode = new Node(value);

    if (m_back) 
    {
        m_back->m_next = newNode;
        newNode->m_prev = m_back;
        m_back = newNode;
    } 
    else 
    {
        m_front = m_back = newNode;
    }

    ++m_size;
}

template <typename T>
void Queue<T>::dequeue() 
{
    if (m_front) 
    {
        Node* temp = m_front;
        m_front = m_front->m_next;

        if (m_front) 
        {
            m_front->m_prev = nullptr;
        } 
        else 
        {
            m_back = nullptr;
        }

        delete temp;
        --m_size;

    } 
    else 
    {
        throw std::out_of_range("Cannot dequeue from an empty queue");
    }
}

template <typename T>
T& Queue<T>::front() const 
{
    if (m_front) 
    {
        return m_front->m_data;
    } 
    else 
    {
        throw std::out_of_range("Queue is empty");
    }
}

template <typename T>
T& Queue<T>::back() const 
{
    if (m_back) 
    {
        return m_back->m_data;
    } 
    else 
    {
        throw std::out_of_range("Queue is empty");
    }
}

template <typename T>
bool Queue<T>::empty() const 
{
    return m_size == 0;
}

template <typename T>
void Queue<T>::clear() 
{
    while (!empty()) 
    {
        dequeue();
    }
}

template <typename T>
int Queue<T>::size() const 
{
    return m_size;
}

template <typename T>
void Queue<T>::print() const 
{
    Node* current = m_front;
    while (current) 
    {
        std::cout << current->m_data << " ";
        current = current->m_next;
    }
    std::cout << std::endl;
}

#endif // __QUEUE__HPP__