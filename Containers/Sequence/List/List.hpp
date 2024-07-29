#ifndef __LIST__HPP__
#define __LIST__HPP__

#include <iostream>

template <typename T>
class List
{
private:
    struct Node
    {
        T m_data;
        Node* m_next;
        Node* m_prev;
        Node(const T& value) : m_data(value), m_next(nullptr), m_prev(nullptr) {}
    };

    Node* m_head;
    Node* m_tail;
    int m_size;

public:
    List();
    List(const List& other);
    List& operator=(const List& other);
    List(List&& other);
    List& operator=(List&& other);
    ~List();

    void push_back(const T& value);
    void push_front(const T& value);
    void pop_back();
    void pop_front();
    T& front() const;
    T& back() const;
    bool empty() const;
    void clear();
    void print() const;

    int size() const;
};

template <typename T>
List<T>::List() : m_head(nullptr), m_tail(nullptr), m_size(0) {}

template <typename T>
List<T>::List(const List& other) : m_head(nullptr), m_tail(nullptr), m_size(0) 
{
    Node* current = other.m_head;
    while (current) 
    {
        push_back(current->m_data);
        current = current->m_next;
    }
}

template <typename T>
List<T>& List<T>::operator=(const List& other) 
{
    if (this != &other) 
    {
        clear();
        Node* current = other.m_head;
        while (current) 
        {
            push_back(current->m_data);
            current = current->m_next;
        }
    }
    return *this;
}

template <typename T>
List<T>::List(List&& other) : m_head(other.m_head), m_tail(other.m_tail), m_size(other.m_size) 
{
    other.m_head = nullptr;
    other.m_tail = nullptr;
    other.m_size = 0;
}

template <typename T>
List<T>& List<T>::operator=(List&& other)  
{
    if (this != &other) 
    {
        clear();
        m_head = other.m_head;
        m_tail = other.m_tail;
        m_size = other.m_size;

        other.m_head = nullptr;
        other.m_tail = nullptr;
        other.m_size = 0;
    }
    return *this;
}

template <typename T>
List<T>::~List() 
{
    clear();
}

template <typename T>
void List<T>::push_back(const T& value) 
{
    Node* newNode = new Node(value);
    if (m_tail) 
    {
        m_tail->m_next = newNode;
        newNode->m_prev = m_tail;
        m_tail = newNode;
    } 
    else 
    {
        m_head = m_tail = newNode;
    }
    ++m_size;
}

template <typename T>
void List<T>::push_front(const T& value) 
{
    Node* newNode = new Node(value);
    if (m_head) 
    {
        m_head->m_prev = newNode;
        newNode->m_next = m_head;
        m_head = newNode;
    } 
    else 
    {
        m_head = m_tail = newNode;
    }
    ++m_size;
}

template <typename T>
void List<T>::pop_back() {
    if (m_tail) 
    {
        Node* temp = m_tail;
        m_tail = m_tail->m_prev;
        if (m_tail) 
        {
            m_tail->m_next = nullptr;
        } 
        else 
        {
            m_head = nullptr;
        }

        delete temp;
        --m_size;
    } 
    else 
    {
        throw std::out_of_range("Cannot pop_back from an empty list");
    }
}

template <typename T>
void List<T>::pop_front() 
{
    if (m_head) 
    {
        Node* temp = m_head;
        m_head = m_head->m_next;
        if (m_head) 
        {
            m_head->m_prev = nullptr;
        } 
        else 
        {
            m_tail = nullptr;
        }

        delete temp;
        --m_size;
    } 
    else 
    {
        throw std::out_of_range("Cannot pop_front from an empty list");
    }
}

template <typename T>
T& List<T>::front() const 
{
    if (m_head) 
    {
        return m_head->m_data;
    } 
    else 
    {
        throw std::out_of_range("List is empty");
    }
}

template <typename T>
T& List<T>::back() const 
{
    if (m_tail) 
    {
        return m_tail->m_data;
    } 
    else 
    {
        throw std::out_of_range("List is empty");
    }
}

template <typename T>
bool List<T>::empty() const 
{
    return m_size == 0;
}

template <typename T>
void List<T>::clear() 
{
    while (m_head) 
    {
        pop_front();
    }
}

template <typename T>
void List<T>::print() const 
{
    Node* current = m_head;
    while (current) 
    {
        std::cout << current->m_data << " ";
        current = current->m_next;
    }
    std::cout << std::endl;
}

template <typename T>
int List<T>::size() const 
{
    return m_size;
}

#endif // __LIST__HPP__