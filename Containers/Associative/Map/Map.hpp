#ifndef __MAP__HPP__
#define __MAP__HPP__

#include <iostream>
#include <stdexcept>

template <typename K, typename V>
class Map
{
private:
    struct Node
    {
        K m_key;
        V m_value;
        Node* m_next;
        Node* m_prev;
        Node(const K& key, const V& value) : m_key(key), m_value(value), m_next(nullptr), m_prev(nullptr) {}
    };

    Node* m_head;
    Node* m_tail;
    int m_size;

public:
    Map();
    Map(const Map& other);
    Map& operator=(const Map& other);
    Map(Map&& other);
    Map& operator=(Map&& other);
    ~Map();

    void insert(const K& key, const V& value);
    void erase(const K& key);
    V& at(const K& key);
    bool contains(const K& key) const;
    bool empty() const;
    void clear();
    int size() const;

    void print() const;

private:
    Node* findNode(const K& key) const;
};

template <typename K, typename V>
Map<K, V>::Map() : m_head(nullptr), m_tail(nullptr), m_size(0) {}

template <typename K, typename V>
Map<K, V>::Map(const Map& other) : m_head(nullptr), m_tail(nullptr), m_size(0) 
{
    Node* current = other.m_head;
    while (current) 
    {
        insert(current->m_key, current->m_value);
        current = current->m_next;
    }
}

template <typename K, typename V>
Map<K, V>& Map<K, V>::operator=(const Map& other) 
{
    if (this != &other) 
    {
        clear();
        Node* current = other.m_head;
        while (current) 
        {
            insert(current->m_key, current->m_value);
            current = current->m_next;
        }
    }
    return *this;
}

template <typename K, typename V>
Map<K, V>::Map(Map&& other) : m_head(other.m_head), m_tail(other.m_tail), m_size(other.m_size) 
{
    other.m_head = nullptr;
    other.m_tail = nullptr;
    other.m_size = 0;
}

template <typename K, typename V>
Map<K, V>& Map<K, V>::operator=(Map&& other)  
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

template <typename K, typename V>
Map<K, V>::~Map() 
{
    clear();
}

template <typename K, typename V>
void Map<K, V>::insert(const K& key, const V& value) 
{
    if (findNode(key)) 
    {
        throw std::invalid_argument("Key already exists");
    }

    Node* newNode = new Node(key, value);
    if (m_tail) 
    {
        m_tail->m_next = newNode;
        newNode->m_prev = m_tail;
    }
    m_tail = newNode;
    if (!m_head) 
    {
        m_head = newNode;
    }
    ++m_size;
}

template <typename K, typename V>
void Map<K, V>::erase(const K& key) 
{
    Node* node = findNode(key);
    if (node) 
    {
        if (node->m_prev) 
        {
            node->m_prev->m_next = node->m_next;
        }
        if (node->m_next) 
        {
            node->m_next->m_prev = node->m_prev;
        }
        if (node == m_head) 
        {
            m_head = node->m_next;
        }
        if (node == m_tail) 
        {
            m_tail = node->m_prev;
        }
        delete node;
        --m_size;
    }
    else 
    {
        throw std::out_of_range("Key not found");
    }
}

template <typename K, typename V>
V& Map<K, V>::at(const K& key) 
{
    Node* node = findNode(key);
    if (node) 
    {
        return node->m_value;
    }
    else 
    {
        throw std::out_of_range("Key not found");
    }
}

template <typename K, typename V>
bool Map<K, V>::contains(const K& key) const 
{
    return findNode(key) != nullptr;
}

template <typename K, typename V>
bool Map<K, V>::empty() const 
{
    return m_size == 0;
}

template <typename K, typename V>
void Map<K, V>::clear() 
{
    while (m_head) 
    {
        Node* temp = m_head;
        m_head = m_head->m_next;
        delete temp;
    }
    m_tail = nullptr;
    m_size = 0;
}

template <typename K, typename V>
int Map<K, V>::size() const 
{
    return m_size;
}

template <typename K, typename V>
void Map<K, V>::print() const 
{
    Node* current = m_head;
    while (current) 
    {
        std::cout << "[" << current->m_key << ": " << current->m_value << "] ";
        current = current->m_next;
    }
    std::cout << std::endl;
}

template <typename K, typename V>
typename Map<K, V>::Node* Map<K, V>::findNode(const K& key) const 
{
    Node* current = m_head;
    while (current) 
    {
        if (current->m_key == key) 
        {
            return current;
        }
        current = current->m_next;
    }
    return nullptr;
}

#endif // __MAP__HPP__