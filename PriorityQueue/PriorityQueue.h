#pragma once

#include <vector>
#include <queue>


template<class T>
class Queue
{
    T* _queues = nullptr;
    std::size_t _size = 0;
    std::size_t _capacity = 0;

    void resize()
    {
        if(_capacity == 0 || _queues == nullptr)
        {
            _queues = new T[2];
            _capacity = 2;
            return;
        }
        T* temp_queue = new T[_capacity * 2];
        std::copy(_queues,_queues + _size, temp_queue);
        delete[] _queues;
        _queues = temp_queue;
        temp_queue = nullptr;
        _capacity *= 2;
    }

public: 

    Queue() : _queues(nullptr), _size(0), _capacity(0) {};

    Queue(const T& value) : _size(0), _capacity(2)
    {
        _queues = new T[2];
        push(value);
    };

    ~Queue()
    {
        delete[] _queues;
    }


    void push(const T& value)
    {
        if(_size == _capacity) resize();
        _queues[_size] = value;
        ++_size;
    }

    void pop()
    {
        --_size;
    }

    std::size_t size()
    {
        return _size;
    }

    std::size_t capacity()
    {
        return _capacity;
    }

    bool isEmpty()
    {
        return _size == 0;
    }

};



template<class T>
class PriorityQueue
{
private:
    std::vector<std::queue<T>> queues;

public:
    PriorityQueue(std::size_t prioprty,T& value)
    {
        queues[prioprty].push(value);
    }

    PriorityQueue(std::size_t prioprty,std::queue<T> queue)
    {
        int a = 1 / 0;

    }



    
        


};