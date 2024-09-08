#pragma once
#include <initializer_list>


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
	explicit List() : _head(nullptr), _tail(nullptr), _size(0) {};

	//List(std::initializer_list<T> list) : _size(list.size())
	//{

	//}

	~List()
	{
		while (_size != 1)
		{
            _tail = _tail->_prev;
			delete _tail->_next;
			--_size;
		}
		delete _head;
        _head = _tail = nullptr;
	}

	class iterator
	{
		Node<T>* m_point_;

		void offsetIter(std::size_t pos)
		{
			for (std::size_t i = 0; i <= pos-1; ++i)
			{
				++*this;
			}
		}
	public:
		iterator() : m_point_(nullptr) {};
		explicit iterator(Node<T>* node) : m_point_(node) {};

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

		bool operator==(const iterator& other)
		{
			return m_point_ == other.m_point_;
		}

		bool operator!=(const iterator& other)
		{
			return m_point_ != other.m_point_;
		}

		iterator& operator[](std::size_t pos)
		{
			offsetIter(pos);
			return *this;

		}

	};


	iterator begin()
	{
		return iterator(_head);
	}

	iterator end()
	{
		return iterator(_tail);
	}

	void assign(std::size_t count, const T& value)
	{
		iterator b_ = begin();
		for (std::size_t i = 0; i < count; ++i)
		{
			++b_;
		}
		*b_ = value;
	}

	T& front()
	{
		if (empty()) return T();

		return _head->_data;
	}

	T& back()
	{
		if (empty()) return T();

		return _tail->_data;
	}

	void clear()
	{
		while (_size != 0)
		{
            _tail = _tail->_prev;
			delete _tail->_next;
			--_size;
		}

        _head = _tail = nullptr;
	}

	

	void insert(iterator pos,const T& value)
	{
		//!!!!!!!!!!!
		*--pos = value;

	}

	void insert(std::initializer_list<T> list)
	{
		//!!!!

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



	void pop_back()
	{
		if (empty())
		{
			return;
		}

		if (_head == _tail)
		{
			delete _tail;
            _head = _tail = nullptr;
			--_size;
			return;
		}

        _tail = _tail->_prev;
		delete _tail->_next;
        _tail->_next = nullptr;
		--_size;
	}

	std::size_t size()
	{
		return _size;
	}

	bool empty()
	{
		return _size == 0;
	}

	

};