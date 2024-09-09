#pragma once
#include <initializer_list>
#include <cstddef>

template<class T>
class Node
{
public:
	T _data;
	Node<T>* _prev = nullptr;
	Node<T>* _next = nullptr;
	explicit Node(const T& value) : _data(value) {};

};





template<class T>
class List
{
    Node<T>* _head = nullptr;
    Node<T>* _tail = nullptr;
    std::size_t _size = 0;

public:
    explicit List() : _head(nullptr), _tail(nullptr), _size(0) {}

    ~List()
    {
        clear();
    }

    class iterator
    {
        Node<T>* m_point_;
    public:
        using iterator_category = std::bidirectional_iterator_tag;
        using value_type = T;
        using difference_type = std::ptrdiff_t;
        using pointer = T*;
        using reference = T&;


        iterator() : m_point_(nullptr) {}
        explicit iterator(Node<T>* node) : m_point_(node) {}

        T& operator*()
        {
            return m_point_->_data;
        }

        iterator& operator++()
        {
            m_point_ = m_point_->_next;
            return *this;
        }

        iterator& operator--()
        {
            m_point_ = m_point_->_prev;
            return *this;
        }

        bool operator==(const iterator& other) const
        {
            return m_point_ == other.m_point_;
        }

        bool operator!=(const iterator& other) const
        {
            return m_point_ != other.m_point_;
        }
    };

    iterator begin()
    {
        return iterator(_head);
    }

    iterator end()
    {
        return iterator(_tail->_next);
    }

    const T& front()
    {
        return _head->_data;
    }

    const T& back()
    {
        return _tail->_data;
    }

    void push_back(const T& value)
    {
        Node<T>* node = new Node<T>(value);
        if (_size == 0)
        {
            _head = _tail = node;
        }
        else
        {
            node->_prev = _tail;
            _tail->_next = node;
            _tail = node;
        }
        ++_size;
    }

    void clear()
    {
        while (_tail != nullptr)
        {
            auto* temp = _tail;
            _tail = _tail->_prev;
            delete temp;
        }
        _head = _tail = nullptr;
        _size = 0;
    }

    std::size_t size()
    {
        return _size;
    }
};



