#include "DualStack.h"

template<typename T, uint capacity>
DualStack<T, capacity>::DualStack() : _size1(0), _size2(0), state(State::First)
{
    _data = new T[capacity];
}

template<typename T, uint capacity>
DualStack<T, capacity>::DualStack(const DualStack& other) : state(State::NotSelected)
{
    _data = new T[capacity];
    std::copy(other._data, other._data + capacity, _data);

    _size1 = other._size1;
    _size2 = other._size2;
    state = State::First;
}

template<typename T, uint capacity>
DualStack<T, capacity>::~DualStack()
{
    delete[] _data;
}

template<typename T, uint capacity>
DualStack<T, capacity>& DualStack<T, capacity>::first() noexcept
{
    state = State::First;
    return *this;
}

template<typename T, uint capacity>
DualStack<T, capacity>& DualStack<T, capacity>::second() noexcept
{
    state = State::Second;
    return *this;
}

template<typename T, uint capacity>
typename DualStack<T, capacity>::State DualStack<T, capacity>::getState() const noexcept
{
    return state;
}

template<typename T, uint capacity>
bool DualStack<T, capacity>::empty() const noexcept
{
    switch (state)
    {
    case State::First:
        return _size1 == 0;
    case State::Second:
        return _size2 == 0;
    }
}

template<typename T, uint capacity>
std::size_t DualStack<T, capacity>::size() const noexcept
{
    switch (state)
    {
    case State::First:
        return _size1;
    case State::Second:
        return _size2;
    }
}

template<typename T, uint capacity>
T& DualStack<T, capacity>::top()
{
    if(state == State::First)
        return _data[_size1 - 1];
    return _data[capacity- _size2];
}

template<typename T, uint capacity>
void DualStack<T, capacity>::push(const T& value)
{
    if(_size1 + _size2 == capacity)
        throw std::length_error("DualStack is full");

    if(state == State::First)
    {
         _data[_size1] = value;
         _size1++;
        return;
    }
    else
    {
        _data[capacity - _size2 - 1] = value;
        _size2++;
        return;
    }
}

template<typename T, uint capacity>
void DualStack<T, capacity>::push(T&& value)
{
    if(_size1 + _size2 == capacity)
        throw std::length_error("DualStack is full");

    if(state == State::First)
    {
         _data[_size1] = std::move(value);
         _size1++;
        return;
    }
    else
    {
        _data[capacity - _size2 - 1] = std::move(value);
        _size2++;
        return;
    }
}

template<typename T, uint capacity>
void DualStack<T, capacity>::pop()
{
    if(state == State::First)
    {
        if(_size1 == 0)
            throw std::length_error("First stack is empty");
         _size1--;
        return;
    }
    else
    {
        if(_size2 == 0)
            throw std::length_error("Second stack is empty");
         _size2--;
        return;
    }
}
