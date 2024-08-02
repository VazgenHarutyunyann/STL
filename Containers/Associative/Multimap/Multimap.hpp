#ifndef __MULTIMAP__HPP__
#define __MULTIMAP__HPP__

#include <iostream>
#include <vector>
#include <stdexcept>

template <typename K, typename V>
class Multimap
{
private:
    struct Node
    {
        K m_key;
        std::vector<V> m_values;
        Node* m_next;
        Node* m_prev;
        Node(const K& key) : m_key(key), m_next(nullptr), m_prev(nullptr) {}
    };

    Node* m_head;
    Node* m_tail;
    int m_size;

public:
    Multimap();
    Multimap(const Multimap& other);
    Multimap& operator=(const Multimap& other);
    Multimap(Multimap&& other);
    Multimap& operator=(Multimap&& other);
    ~Multimap();

    void insert(const K& key, const V& value);
    void erase(const K& key);
    std::vector<V> at(const K& key) const;
    bool contains(const K& key) const;
    bool empty() const;
    void clear();
    int size() const;

    void print() const;

private:
    Node* findNode(const K& key) const;
};

template <typename K, typename V>
Multimap<K, V>::Multimap() : m_head(nullptr), m_tail(nullptr), m_size(0) {}

template <typename K, typename V>
Multimap<K, V>::Multimap(const Multimap& other) : m_head(nullptr), m_tail(nullptr), m_size(0) 
{
    Node* current = other.m_head;
    while (current) 
    {
        Node* newNode = new Node(current->m_key);
        newNode->m_values = current->m_values;
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
        current = current->m_next;
    }
}

template <typename K, typename V>
Multimap<K, V>& Multimap<K, V>::operator=(const Multimap& other) 
{
    if (this != &other) 
    {
        clear();
        Node* current = other.m_head;
        while (current) 
        {
            Node* newNode = new Node(current->m_key);
            newNode->m_values = current->m_values;
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
            current = current->m_next;
        }
    }
    return *this;
}

template <typename K, typename V>
Multimap<K, V>::Multimap(Multimap&& other) : m_head(other.m_head), m_tail(other.m_tail), m_size(other.m_size) 
{
    other.m_head = nullptr;
    other.m_tail = nullptr;
    other.m_size = 0;
}

template <typename K, typename V>
Multimap<K, V>& Multimap<K, V>::operator=(Multimap&& other)  
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
Multimap<K, V>::~Multimap() 
{
    clear();
}

template <typename K, typename V>
void Multimap<K, V>::insert(const K& key, const V& value) 
{
    Node* node = findNode(key);
    if (node) 
    {
        node->m_values.push_back(value);
    }
    else 
    {
        Node* newNode = new Node(key);
        newNode->m_values.push_back(value);
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
}

template <typename K, typename V>
void Multimap<K, V>::erase(const K& key) 
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
}

template <typename K, typename V>
std::vector<V> Multimap<K, V>::at(const K& key) const 
{
    Node* node = findNode(key);
    if (node) 
    {
        return node->m_values;
    }
    else 
    {
        throw std::out_of_range("Key not found");
    }
}

template <typename K, typename V>
bool Multimap<K, V>::contains(const K& key) const 
{
    return findNode(key) != nullptr;
}

template <typename K, typename V>
bool Multimap<K, V>::empty() const 
{
    return m_size == 0;
}

template <typename K, typename V>
void Multimap<K, V>::clear() 
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
int Multimap<K, V>::size() const 
{
    return m_size;
}

template <typename K, typename V>
void Multimap<K, V>::print() const 
{
    Node* current = m_head;
    while (current) 
    {
        std::cout << "[" << current->m_key << ": ";
        for (const auto& value : current->m_values) 
        {
            std::cout << value << " ";
        }
        std::cout << "] ";
        current = current->m_next;
    }
    std::cout << std::endl;
}

template <typename K, typename V>
typename Multimap<K, V>::Node* Multimap<K, V>::findNode(const K& key) const 
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

#endif // __MULTIMAP__HPP__