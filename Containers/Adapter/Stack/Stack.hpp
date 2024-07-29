#ifndef __STACK__HPP__
#define __STACK__HPP__

#include <iostream>

template <typename T>
class Stack
{
private:
    struct Node
    {
        T m_data;
        Node* m_next;
        Node* m_prev;
        Node(const T& value) : m_data(value), m_next(nullptr), m_prev(nullptr) {}
    };

    Node* m_top;
    int m_size;

public:
    Stack();
    Stack(const Stack& other);
    Stack& operator=(const Stack& other);
    Stack(Stack&& other);
    Stack& operator=(Stack&& other);
    ~Stack();

    void push(const T& value);
    void pop();
    T& top() const;
    bool empty() const;
    void clear();
    int size() const;

    void print() const;
};

template <typename T>
Stack<T>::Stack() : m_top(nullptr), m_size(0) {}

template <typename T>
Stack<T>::Stack(const Stack& other) : m_top(nullptr), m_size(0) 
{
    Node* current = other.m_top;
    while (current) 
    {
        push(current->m_data);
        current = current->m_prev;
    }
}

template <typename T>
Stack<T>& Stack<T>::operator=(const Stack& other) 
{
    if (this != &other) 
    {
        clear();
        Node* current = other.m_top;
        while (current) 
        {
            push(current->m_data);
            current = current->m_prev;
        }
    }
    return *this;
}

template <typename T>
Stack<T>::Stack(Stack&& other) : m_top(other.m_top), m_size(other.m_size) 
{
    other.m_top = nullptr;
    other.m_size = 0;
}

template <typename T>
Stack<T>& Stack<T>::operator=(Stack&& other)  
{
    if (this != &other) 
    {
        clear();
        m_top = other.m_top;
        m_size = other.m_size;
        
        other.m_top = nullptr;
        other.m_size = 0;
    }
    return *this;
}

template <typename T>
Stack<T>::~Stack() 
{
    clear();
}

template <typename T>
void Stack<T>::push(const T& value) 
{
    Node* newNode = new Node(value);
    if (m_top) 
    {
        newNode->m_prev = m_top;
        m_top->m_next = newNode;
    }
    m_top = newNode;
    ++m_size;
}

template <typename T>
void Stack<T>::pop() 
{
    if (m_top) 
    {
        Node* temp = m_top;
        m_top = m_top->m_prev;
        if (m_top)
        {
            m_top->m_next = nullptr;
        }

        delete temp;
        --m_size;
    }
    else 
    {
        throw std::out_of_range("Cannot pop from an empty stack");
    }
}

template <typename T>
T& Stack<T>::top() const 
{
    if (m_top) 
    {
        return m_top->m_data;
    } 
    else 
    {
        throw std::out_of_range("Stack is empty");
    }
}

template <typename T>
bool Stack<T>::empty() const 
{
    return m_size == 0;
}

template <typename T>
void Stack<T>::clear() 
{
    while (!empty()) 
    {
        pop();
    }
}

template <typename T>
int Stack<T>::size() const 
{
    return m_size;
}

template <typename T>
void Stack<T>::print() const 
{
    Node* current = m_top;
    while (current) 
    {
        std::cout << current->m_data << " ";
        current = current->m_prev;
    }
    std::cout << std::endl;
}

#endif // __STACK__HPP__