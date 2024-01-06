#pragma once
#include <initializer_list>


template<class T>
class Node
{
public:
	T data;
	Node<T>* prev_ = nullptr;
	Node<T>* next_ = nullptr;

	Node(const T& value) : data(value) {};


};



template<class T>
class List
{
	Node<T>* head_;
	Node<T>* tail_;
	std::size_t size_;




public:
	List() : head_(nullptr), tail_(nullptr), size_(0) {};

	//List(std::initializer_list<T> list) : size_(list.size())
	//{

	//}

	~List()
	{
		while (size_ != 1)
		{
			tail_ = tail_->prev_;
			delete tail_->next_;
			--size_;
		}
		delete head_;
		head_ = tail_ = nullptr;
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
		iterator(Node<T>* node) : m_point_(node) {};
		iterator(Node<T>& node) : m_point_(node) {};

		T& operator*() 
		{
			return m_point_->data;
		}

		iterator& operator++()
		{
			m_point_ = m_point_->next_;
			return *this;
		}

		iterator& operator--()
		{
			m_point_ = m_point_->prev_;
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

	class const_iterator
	{

	};

	iterator begin()
	{
		return iterator(head_);
	}

	iterator end()
	{
		return iterator(tail_);
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

		return head_->data;
	}

	T& back()
	{
		if (empty()) return T();

		return tail_->data;
	}

	void clear()
	{
		while (size_ != 0)
		{
			tail_ = tail_->prev_;
			delete tail_->next_;
			--size_;
		}

		head_ = tail_ = nullptr;
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

		if (size_ == 0)
		{
			head_ = tail_ = node;
			head_->prev_ = nullptr;
		}
		else
		{
			node->prev_ = tail_;
			tail_->next_ = node;
			tail_ = node;
			tail_->next_ = nullptr;
		}
		++size_;
	}



	void pop_back()
	{
		if (empty())
		{
			return;
		}

		if (head_ == tail_)
		{
			delete tail_;
			head_ = tail_ = nullptr;
			--size_;
			return;
		}

		tail_ = tail_->prev_;
		delete tail_->next_;
		tail_->next_ = nullptr;
		--size_;
	}

	std::size_t size()
	{
		return size_;
	}

	bool empty()
	{
		return size_ == 0;
	}

	

};