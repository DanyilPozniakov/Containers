#ifndef MYUMAP_HPP
#define MYUMAP_HPP
#include <utility>
#include <cassert>
#include <optional>
#include <initializer_list>

template <typename Key, typename Value>
class UMap
{
public:
    UMap()
    {
        m_capacity = 10;
        m_data = new std::pair<Key,Value>[m_capacity]{};
        m_occupied_flags = new bool[m_capacity]{false};

        assert(m_data && m_occupied_flags && "Memory allocation failed");
    };

    explicit UMap(const UMap& other) :
        m_capacity(other.m_capacity),
        m_size(other.m_size)
    {
        for(auto item : other)
        {
            add(item.first,item.second);
        }
    }

    UMap(UMap&& other) noexcept :
        m_capacity(other.m_capacity),
        m_size(other.m_size),
        m_data(other.m_data),
        m_occupied_flags(other.m_occupied_flags)
    {
        other.m_occupied_flags  = nullptr;
        other.m_data            = nullptr;
        other.m_capacity        = 0;
        other.m_size            = 0;
    }


    virtual ~UMap()
    {
        delete[] m_data;
        delete[] m_occupied_flags;
    };



    class iterator
    {
    public:
        explicit iterator(): p_date(nullptr) {};
        explicit iterator(std::pair<Key, Value>* data) : p_date(data) {}

        std::pair<Key, Value>& operator*() const
        {
            return *p_date;
        }
        std::pair<Key,Value>* operator++()
        {
            do
            {
                ++p_date;
            } while (p_date->first == Key{} && p_date != nullptr);
            return p_date;
        }
        bool operator==(const iterator& other)
        {
            return p_date == other.p_date;
        }
        bool operator!=(const iterator& other)
        {
            return p_date != other.p_date;
        }

    private:
        std::pair<Key,Value>* p_date = nullptr;
    };

    iterator begin()
    {
        return iterator(m_data);
    }

    iterator end()
    {
        return iterator(m_data + m_capacity);
    }

    void add(const Key &key, const Value &value)
    {
        auto hash = std::hash<Key>()(key);
        auto index = hash % m_capacity;
        if(m_size >= static_cast<int>(m_capacity * 0.5))
        {
            resize();
        }
        while(m_occupied_flags[index])
        {
            if(m_data[index].first == key)
            {
                m_data[index].second = value;
                return;
            }
            index = (index + 1) % m_capacity;
        }
        m_data[index] = std::make_pair(key,value);
        m_occupied_flags[index] = true;
        ++m_size;
    }

    std::optional<Value> getValue(const Key &key) const
    {
        auto hash = std::hash<Key>()(key);
        auto index  =  hash % m_capacity;
        auto start_index = index;
        do {
            if(m_data[index].first == key)
            {
                return m_data[index].second;
            }
            index = (index + 1) % m_capacity;
        } while(index != start_index);
        return std::nullopt;
    }

    const std::optional<std::pair<Key,Value>&> getPair(const Key &key) const
    {
        auto hash = std::hash<Key>()(key);
        auto index  =  hash % m_capacity;
        auto start_index = index;
        do {
            if(m_data[index].first == key)
            {
                return m_data[index];
            }
            index = (index + 1) % m_capacity;
        } while(index != start_index);
        return std::nullopt;
    }

    bool remove(const Key& key)
    {
        auto hash = std::hash<Key>(key);
        auto index = hash % m_capacity;
        auto start_index = index;
        do
        {
            if(m_data[index].first == key)
            {
                m_data[index].first = Key{};
                m_occupied_flags[index] = false;
                return true;
            }
            index = (index + 1) % m_capacity;
        }while(index != start_index);
        return false;
    }

    bool contains(const Key &key) const
    {
        auto hash = std::hash<Key>(key);
        auto index = hash % m_capacity;
        auto start_index = index;
        do
        {
            if(m_data[index].first == key)
            {
                return true;
            }
            index = (index + 1) % m_capacity;
        } while(index != start_index);
        return false;
    }

    void clear()
    {
        delete[] m_data;
        delete[] m_occupied_flags;
        m_capacity  = 10;
        m_size      = 0;
        m_data = new std::pair<Key,Value>[m_capacity]{};
        m_occupied_flags = new bool[m_capacity]{false};
    }

    [[nodiscard]] std::size_t size() const noexcept
    {
        return m_size;
    }
    [[nodiscard]] std::size_t capacity() const noexcept
    {
        return m_capacity;
    }


    Value& operator[](const Key& key)
    {
        add(key,Value{});
        return getPair(key).value().second;
    }

    UMap& operator=(const UMap& other)
    {
        if(this == &other)
        {
            return *this;
        }
        delete[] m_data;
        delete[] m_occupied_flags;
        m_capacity = other.m_capacity;
        m_size = other.m_size;
        m_data = new std::pair<Key,Value>[m_capacity]{};
        m_occupied_flags = new bool[m_capacity]{false};
        for(auto item : other)
        {
            add(item.first,item.second);
        }
        return *this;
    }


private:
    std::size_t         m_capacity   = 0;
    std::size_t         m_size       = 0;
    std::pair<Key,Value>*   m_data  = nullptr;
    bool*               m_occupied_flags = nullptr;


    void resize()
    {
        std::size_t newSize = m_capacity * 10;
        std::pair<Key,Value>* newData   = new std::pair<Key,Value>[newSize]{};
        bool* newOccupiedFlags          = new bool[newSize]{false};

        for(std::size_t i = 0; i < m_capacity; ++i)
        {
            if(m_occupied_flags[i])
            {
                auto hash = std::hash<Key>()(m_data[i].first);
                auto index = hash % newSize;
                while(newOccupiedFlags[index])
                {
                    index = (index + 1) % newSize;
                }
                newData[index] = m_data[i];
                newOccupiedFlags[index] = true;
            }
        }
        delete[] m_data;
        delete[] m_occupied_flags;

        m_data              = newData;
        m_occupied_flags    = newOccupiedFlags;
        m_capacity          = newSize;
    }

};
#endif //MYUMAP_HPP
