#include "CircularQueue.h"
#include <array>


template<typename T, int capacity>
CircularQueue<T, capacity>::CircularQueue() : _size(0), _head(0), _tail(-1)
{
    _data = new T[capacity];
}

template<typename T, int capacity>
CircularQueue<T, capacity>::CircularQueue(T* data, int size)
{
    _data = new T[capacity];
    std::copy(data, data + size, _data);

    _tail = _size - 1;
    _head = 0;
    _size = size;
}

template<typename T, int capacity>
CircularQueue<T, capacity>::CircularQueue(const CircularQueue& other) : _head(0)
{
    _data = new T[capacity];
    for(int i = 0; i < other._size; i++)
    {
        _data[i] = other._data[(other._head + i) % capacity];
    }

    _tail = other._size - 1;
    _size = other._size;
}

template<typename T, int capacity>
CircularQueue<T, capacity>::CircularQueue(std::initializer_list<T> values) : _size(0), _head(0), _tail(-1)
{
    _data =  new T[capacity];
    if(values.size() > capacity)
        throw std::length_error("CircularQueue capacity less than init values");

    for (auto &&value : values)
    {
        push(value);
    }
}

template<typename T, int capacity>
CircularQueue<T, capacity>::~CircularQueue()
{
    delete[] _data;
}

template<typename T, int capacity>
size_t CircularQueue<T, capacity>::size() const noexcept
{
    return _size;
}

template<typename T, int capacity>
bool CircularQueue<T, capacity>::empty() const noexcept
{
    return _size == 0;
}

template<typename T, int capacity>
T& CircularQueue<T, capacity>::front()
{
    if(empty())
        throw std::length_error("CircularQueue is empty");
    return _data[_head];
}

template<typename T, int capacity>
const T& CircularQueue<T, capacity>::front() const
{
    if(empty())
        throw std::length_error("CircularQueue is empty");
    return _data[_head];
}

template<typename T, int capacity>
T& CircularQueue<T, capacity>::back()
{
    if(empty())
        throw std::length_error("CircularQueue is empty");
    return _data[_tail];
}

template<typename T, int capacity>
const T& CircularQueue<T, capacity>::back() const
{
    if(empty())
        throw std::length_error("CircularQueue is empty");
    return _data[_tail];
}

template<typename T, int capacity>
void CircularQueue<T, capacity>::push(T&& value)
{
    if(_size == capacity)
        throw std::length_error("CircularQueue is full");

    _tail = (_tail + 1) % capacity;
    _data[_tail] = std::move(value);
    _size++;
};

template<typename T, int capacity>
void CircularQueue<T, capacity>::push(const T& value)
{
    if(_size == capacity)
        throw std::length_error("CircularQueue is full");

    _tail = (_tail + 1) % capacity;
    _data[_tail] = value;
    _size++;
};

template<typename T, int capacity>
void CircularQueue<T, capacity>::pop()
{
    if(empty())
        throw std::length_error("CircularQueue is empty");

    _head = (_head + 1) % capacity;
    _size--;
};


