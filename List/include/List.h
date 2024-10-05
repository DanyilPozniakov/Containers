#pragma once
#include <initializer_list>
#include <cstddef>
#include <cassert>
#include <concepts>


template<class T>
class Node
{
public:
	T        _data = {};
	Node<T>* _prev = nullptr;
	Node<T>* _next = nullptr;

	explicit Node(const T& value) : _data(value) {};
};

template<class T>
class List
{
    Node<T>*    _head = nullptr;
    Node<T>*    _tail = nullptr;
    std::size_t _size = 0;

public:
    List() : _head(nullptr), _tail(nullptr), _size(0) {}

    List(std::initializer_list<T> list)
    {
        for(auto item : list)
        {
            push_back(item);
        }
    }

    List(const List<T>& other) : _size(0), _head(nullptr), _tail(nullptr)
    {
        for(const auto& item : other)
        {
            push_back(item);
        }
    }

    List(List<T>&& other) noexcept : _size(other._size), _head(other._head), _tail(other._tail)
    {
        other._head = nullptr;
        other._tail = nullptr;
        other._size = 0;
    }

    ~List()
    {
        clear();
    }

    class iterator
    {
    public:
        using iterator_category     = std::bidirectional_iterator_tag;
        using value_type            = T;
        using difference_type       = std::ptrdiff_t;
        using pointer               = T*;
        using reference             = T&;

        Node<T>* m_point_;
        List<T>* m_list_;

        iterator() : m_point_(nullptr), m_list_(nullptr) {}
        iterator(Node<T>* node,List<T>* list) : m_point_(node), m_list_(list) {}
        iterator(const iterator& it) : m_point_(it.m_point_), m_list_(it.m_list_) {}

        T& operator*() const
        {
            return m_point_->_data;
        }

        T* operator->() const
        {
            return &(m_point_->_data);
        }

        iterator& operator++()
        {
            if(m_point_)
            {
                m_point_ = m_point_->_next;
            }
            return *this;
        }

        iterator operator++(int)
        {
            iterator temp = *this;
            ++(*this);
            return temp;
        }

        iterator& operator--()
        {
            if(m_point_)
            {
                m_point_ = m_point_->_prev;
            }
            return *this;
        }

        iterator operator--(int)
        {
            iterator temp = *this;
            --(*this);
            return temp;
        }

        bool operator==(const iterator& other) const
        {
            return m_point_ == other.m_point_;
        }

        bool operator!=(const iterator& other) const
        {
            return m_point_ != other.m_point_;
        }

        explicit operator bool() const
        {
            return m_point_ != nullptr;
        }
    };

    class const_iterator
    {
    public:
        using iterator_category     = std::bidirectional_iterator_tag;
        using value_type            = T;
        using difference_type       = std::ptrdiff_t;
        using pointer               = const T*;
        using reference             = const T&;

        const Node<T>* m_point_;
        const List<T>* m_list_;

        const_iterator() : m_point_(nullptr), m_list_(nullptr) {}
        explicit const_iterator(const Node<T>* node, const List<T>* list) : m_point_(node), m_list_(list) {}
        explicit const_iterator(const iterator& it) : m_point_(it.m_point_), m_list_(it.m_list_) {}

        reference operator*() const
        {
            return m_point_->_data;
        }

        pointer operator->() const
        {
            return &(m_point_->_data);
        }

        const_iterator& operator++()
        {
            m_point_ = m_point_->_next;
            return *this;
        }

        const_iterator operator++(int)
        {
            const_iterator temp = *this;
            m_point_ = m_point_->_next;
            return temp;
        }

        const_iterator& operator--()
        {
            if (m_point_)
            {
                m_point_ = m_point_->_prev;
            }
            else
            {
                m_point_ = m_list_->_tail;
            }

            return *this;
        }

        const_iterator operator--(int)
        {
            const_iterator temp = *this;
            --(*this);
            return temp;
        }

        bool operator==(const const_iterator& other) const
        {
            return m_point_ == other.m_point_;
        }

        bool operator!=(const const_iterator& other) const
        {
            return m_point_ != other.m_point_;
        }

        explicit operator bool() const
        {
            return m_point_ != nullptr;
        }
    };

    iterator begin()
    {
        return iterator(_head,this);
    }

    iterator end()
    {
        return iterator(nullptr,this);
    }

    const_iterator begin() const
    {
        return const_iterator(_head,this);
    }

    const_iterator end() const
    {
        return const_iterator(nullptr,this);
    }


    //operators
    List<T>& operator=(const List<T>& other)
    {
        if(this == &other) return *this;
        clear();
        for(const auto& item : other)
        {
            push_back(item);
        }
        return *this;
    }

    List<T>& operator=(const List<T>&& other) noexcept
    {
        if(this != &other)
        {
            clear();

            _head = other._head;
            _tail = other._tail;
            _size = other._size;

            other._head = nullptr;
            other._tail = nullptr;
            other._size = 0;
        }
        return *this;
    }

    bool operator==(const List& other)
    {
        if(_size != other._size)
        {
            return false;
        }

        auto iter = begin();
        auto iterOther = other.begin();
        for(;iter != end() && iterOther != other.end(); ++iter, ++iterOther)
        {
            if(*iter != *iterOther)
            {
                return false;
            }
        }
        return true;
    }

    bool operator!=(const List& other)
    {
        if(_size != other._size)
        {
            return true;
        }
        auto iter = begin();
        auto iterOther = other.begin();
        for(;iter != end() && iterOther != other.end(); ++iter, ++iterOther)
        {
            if(*iter != *iterOther)
            {
                return true;
            }
        }
        return false;
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
        auto pNode = new Node<T>(value);
        if (_size == 0)
        {
            _head = _tail = pNode;
        }
        else
        {
            pNode->_prev = _tail;
            _tail->_next = pNode;
            _tail = pNode;
        }
        ++_size;
    }


    void push_front(const T& value)
    {
        auto pNode = new Node<T>(value);
        if(_head == nullptr)
        {
            _head = _tail = pNode;
        }
        else
        {
            pNode->_next = _head;
            _head->_prev = pNode;
            _head = pNode;
        }
        ++_size;
    }

    void pop_back()
    {
        if(_tail != nullptr)
        {
            auto pNode = _tail;
            if(_tail->_prev != nullptr)
            {
                _tail = _tail->_prev;
                _tail->_next = nullptr;
            }
            else
            {
                _head = _tail = nullptr;
            }
            delete pNode;
            --_size;
        }
    }

    void pop_front()
    {
        if (_head != nullptr)
        {
            auto pNode = _head;
            if (_head->_next != nullptr)
            {
                _head = _head->_next;
                _head->_prev = nullptr;
            } else
            {
                _head = _tail = nullptr;
            }
            delete pNode;
            --_size;
        }
    }

    void insert(iterator& pos, const T& value)
    {
        assert(pos.m_list_ == this && "Iterator does not belong to this list!");

        auto pNode = new Node<T>(value);
        if(pos.m_point_ == nullptr)
        {
            if(_head == nullptr)
            {
                _head = _tail = pNode;
            }
            else
            {
                _tail->_next = pNode;
                pNode->_prev = _tail;
                _tail = pNode;
            }
        }
        else if(pos.m_point_ == _head)
        {
            pNode->_next = _head;
            _head->_prev = pNode;
            _head = pNode;
        }
        else
        {
            pNode->_prev = pos.m_point_->_prev;
            pos.m_point_->_prev->_next = pNode;
            pNode->_next = pos.m_point_;
            pos.m_point_->_prev = pNode;
        }
        ++_size;
    }

    void erase(iterator& pos)
    {
        assert(pos.m_list_ == this && "erase method, error: Iterator does not belong to this list!");

        if(pos)
        {
            if(_size == 1)
            {
                delete _head;
                _head = _tail = nullptr;
                pos.m_point_  = nullptr;
                --_size;
                return;
            }
            if(pos.m_point_ == _head)
            {
                _head = _head->_next;
                delete _head->_prev;
                _head->_prev = nullptr;
            }
            else if(pos.m_point_ == _tail)
            {
                _tail = _tail->_prev;
                delete _tail->_next;
                _tail->_next = nullptr;
            }
            else
            {
                auto pNode = pos.m_point_;
                pNode->_next->_prev = pNode->_prev;
                pNode->_prev->_next = pNode->_next;
                delete pNode;
            }
            pos.m_point_ = nullptr;
            --_size;
        }
        else
        {
            throw std::invalid_argument("Invalid iterator in erase method! -> nullptr");
        }
    }

    template<class T>
    void remove(const T& value)
    {
        static_assert(std::equality_comparable<T>,"Type T must support the == operator!");

        if(_size == 0) return;

        for(auto i = begin(); i != end(); ++i)
        {
            if(*i == value)
            {
                erase(i);
            }
        }
    }

    template<class Predicate>
    void remove_if(Predicate pred)
    {
        for(auto iter = begin(); iter != end(); ++iter)
        {
            if(pred(*iter))
            {
                auto to_ears = iter++;
                erase(to_ears);
            }
            else ++iter;
        }
    }

    void reverse()
    {
        if(_head == nullptr) return;

        Node<T>* current = _head;
        Node<T>* temp    = nullptr;

        while(current != nullptr)
        {
            temp = current->_next;
            current->_next = current->_prev;
            current->_prev = temp;

            current = temp;
        }

        auto tempHead = _head;
        _head = _tail;
        _tail = tempHead;
    }

    void splice(iterator pos, List& other)
    {
        assert(pos.m_list_ == this && "Iterator does not belong to this list!");

        for(auto item : other)
        {
            insert(pos,item);
        }
        other.clear();
    }


    //.....

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

    std::size_t size() const noexcept
    {
        return _size;
    }

    bool isEmpty() const noexcept
    {
        if(_size == 0) return true;
        return false;
    }

};



