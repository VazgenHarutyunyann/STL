#ifndef __UNORDERED_MAP__HPP__
#define __UNORDERED_MAP__HPP__

#include <iostream>
#include <vector>
#include <list>
#include <stdexcept>
#include <functional>

template <typename K, typename V>
class UnorderedMap
{
private:
    struct Node
    {
        K m_key;
        V m_value;
        Node(const K& key, const V& value) : m_key(key), m_value(value) {}
    };

    std::vector<std::list<Node>> m_buckets;
    size_t m_size;
    size_t m_bucketCount;

    size_t hash(const K& key) const;

public:
    UnorderedMap(size_t bucketCount = 10);
    UnorderedMap(const UnorderedMap& other);
    UnorderedMap& operator=(const UnorderedMap& other);
    UnorderedMap(UnorderedMap&& other) noexcept;
    UnorderedMap& operator=(UnorderedMap&& other) noexcept;
    ~UnorderedMap();

    void insert(const K& key, const V& value);
    void erase(const K& key);
    V& at(const K& key);
    bool contains(const K& key) const;
    bool empty() const;
    void clear();
    size_t size() const;

    void print() const;
};

template <typename K, typename V>
UnorderedMap<K, V>::UnorderedMap(size_t bucketCount) : m_bucketCount(bucketCount), m_size(0)
{
    m_buckets.resize(bucketCount);
}

template <typename K, typename V>
UnorderedMap<K, V>::UnorderedMap(const UnorderedMap& other) : m_bucketCount(other.m_bucketCount), m_size(other.m_size)
{
    m_buckets.resize(m_bucketCount);
    for (size_t i = 0; i < m_bucketCount; ++i)
    {
        m_buckets[i] = other.m_buckets[i];
    }
}

template <typename K, typename V>
UnorderedMap<K, V>& UnorderedMap<K, V>::operator=(const UnorderedMap& other)
{
    if (this != &other)
    {
        m_buckets = other.m_buckets;
        m_size = other.m_size;
        m_bucketCount = other.m_bucketCount;
    }
    return *this;
}

template <typename K, typename V>
UnorderedMap<K, V>::UnorderedMap(UnorderedMap&& other) noexcept : m_buckets(std::move(other.m_buckets)),
    m_size(other.m_size), m_bucketCount(other.m_bucketCount)
{
    other.m_size = 0;
    other.m_bucketCount = 0;
}

template <typename K, typename V>
UnorderedMap<K, V>& UnorderedMap<K, V>::operator=(UnorderedMap&& other) noexcept
{
    if (this != &other)
    {
        m_buckets = std::move(other.m_buckets);
        m_size = other.m_size;
        m_bucketCount = other.m_bucketCount;
        other.m_size = 0;
        other.m_bucketCount = 0;
    }
    return *this;
}

template <typename K, typename V>
UnorderedMap<K, V>::~UnorderedMap()
{
    clear();
}

template <typename K, typename V>
size_t UnorderedMap<K, V>::hash(const K& key) const
{
    return std::hash<K>()(key) % m_bucketCount;
}

template <typename K, typename V>
void UnorderedMap<K, V>::insert(const K& key, const V& value)
{
    size_t index = hash(key);
    for (auto& node : m_buckets[index])
    {
        if (node.m_key == key)
        {
            node.m_value = value;
            return;
        }
    }
    m_buckets[index].emplace_back(key, value);
    ++m_size;
}

template <typename K, typename V>
void UnorderedMap<K, V>::erase(const K& key)
{
    size_t index = hash(key);
    auto& bucket = m_buckets[index];
    for (auto it = bucket.begin(); it != bucket.end(); ++it)
    {
        if (it->m_key == key)
        {
            bucket.erase(it);
            --m_size;
            return;
        }
    }
}

template <typename K, typename V>
V& UnorderedMap<K, V>::at(const K& key)
{
    size_t index = hash(key);
    for (auto& node : m_buckets[index])
    {
        if (node.m_key == key)
        {
            return node.m_value;
        }
    }
    throw std::out_of_range("Key not found");
}

template <typename K, typename V>
bool UnorderedMap<K, V>::contains(const K& key) const
{
    size_t index = hash(key);
    for (const auto& node : m_buckets[index])
    {
        if (node.m_key == key)
        {
            return true;
        }
    }
    return false;
}

template <typename K, typename V>
bool UnorderedMap<K, V>::empty() const
{
    return m_size == 0;
}

template <typename K, typename V>
void UnorderedMap<K, V>::clear()
{
    for (auto& bucket : m_buckets)
    {
        bucket.clear();
    }
    m_size = 0;
}

template <typename K, typename V>
size_t UnorderedMap<K, V>::size() const
{
    return m_size;
}

template <typename K, typename V>
void UnorderedMap<K, V>::print() const
{
    for (const auto& bucket : m_buckets)
    {
        for (const auto& node : bucket)
        {
            std::cout << "[" << node.m_key << ": " << node.m_value << "] ";
        }
        std::cout << std::endl;
    }
}

#endif // __UNORDERED_MAP__HPP__