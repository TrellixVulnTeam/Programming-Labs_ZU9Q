#include "Array.h"

#pragma region Array

template<typename T>
Array<T>::Array(size_t capacity) : _size(0), _capacity(capacity)
{
    _data = new T[_capacity];
}

template<typename T>
Array<T>::Array(std::initializer_list<T> list): _size(0)
{
    _capacity = list.size();
    _data = new T[_capacity];
    for(auto& v : list)
    {
        push_back(v);
    }
}

template<typename T>
Array<T>::Array(const Array<T>& other)
{
    _size = other._size;
    _capacity = other._size;
    _data = new T[_capacity];
    std::copy(other._data, other._data + _size, _data);
}

template<typename T>
Array<T>::~Array()
{
    delete[] _data;
}

template<typename T>
inline size_t Array<T>::size() const noexcept
{
    return _size;
}

template<typename T>
inline size_t Array<T>::capacity() const noexcept
{
    return _capacity;
}

template<typename T>
inline bool Array<T>::empty() const noexcept
{
    return _size == 0;
}

template<typename T>
void Array<T>::shrinkToFit() noexcept
{
    resize(_size);
}

template<typename T>
void Array<T>::resize(size_t newSize)
{
    if(newSize < _size)
        throw std::exception();

    _capacity = newSize;

    T* newData = new T[newSize];
    std::copy(_data, _data+_size, newData);
    delete[] _data;
    _data = newData;
}

template<typename T>
inline void Array<T>::increase()
{
    resize(2 * _capacity);
}

template<typename T>
inline void Array<T>::decrease()
{
    resize(_capacity / 2);
}

template<typename T>
inline typename Array<T>::iterator Array<T>::begin() const noexcept
{
    return iterator(_data);
}

template<typename T>
inline typename Array<T>::iterator Array<T>::end() const noexcept
{
    return iterator(_data + _size);
}

template<typename T>
inline typename Array<T>::const_iterator Array<T>::cbegin() const noexcept
{
    return const_iterator(_data);
}

template<typename T>
typename Array<T>::const_iterator Array<T>::cend() const noexcept
{
    return const_iterator(_data + _size);
}

template<typename T>
const T& Array<T>::front() const
{
    if(_size == 0)
        throw std::length_error("Array is empty");
    return _data[0];
}

template<typename T>
T& Array<T>::front()
{
    if(_size == 0)
        throw std::length_error("Array is empty");
    return _data[0];
}

template<typename T>
const T& Array<T>::back() const
{
    if(_size == 0)
        throw std::length_error("Array is empty");
    return _data[_size - 1];
}

template<typename T>
T& Array<T>::back()
{
    if(_size == 0)
        throw std::length_error("Array is empty");
    return _data[_size - 1];
}

template<typename T>
void Array<T>::push_back(const T& value)
{
    if(_size >= _capacity)
        increase();

    _data[_size] = value;
    _size++;
}

template<typename T>
void Array<T>::push_back(T&& value)
{
    if(_size >= _capacity)
        increase();

    _data[_size] = std::move(value);
    _size++;
}

template<typename T>
void Array<T>::push_front(const T& value)
{
    if(_size >= _capacity)
        increase();

    for(int i = _size - 1; i >= 0; i--)
        _data[i + 1] = _data[i];
    _data[0] = value;

    _size++;
}

template<typename T>
void Array<T>::push_front(T&& value)
{
    if(_size >= _capacity)
        increase();

    for(int i = _size - 1; i >= 0; i--)
        _data[i + 1] = _data[i];
    _data[0] = std::move(value);

    _size++;
}

template<typename T>
void Array<T>::pop_back()
{
    if(empty())
        throw std::length_error("Array is empty");
    remove(cend() - 1);
}

template<typename T>
void Array<T>::pop_front()
{
    if(empty())
        throw std::length_error("Array is empty");
    remove(cbegin());
}

template<typename T>
void Array<T>::remove(const T& value)
{
    for(int i = 0; i < _size; i++)
    {
        if(_data[i] == value)
        {
            remove(const_iterator(_data + i));
            i--;
        }
    }
}

template<typename T>
void Array<T>::remove(const_iterator position)
{
    if(position >= cend() || position < cbegin())
        throw std::out_of_range("Iterators out of container");

    for(auto it = position + 1; it != cend(); it++, position++)
    {
        *(position.ptr) = *(it.ptr);
    }
    _size--;

    if(_size <= _capacity / 3)
        decrease();
}

template<typename T>
void Array<T>::remove(const_iterator first, const_iterator last)
{
    if(first >= cend() || first < cbegin() || last >= cend() || first < cbegin())
        throw std::out_of_range("Iterators out of container");
    if(first > last)
        throw std::invalid_argument("First > last");

    auto current = first;
    for(auto it = last + 1; it != cend(); it++, current++)
    {
        *(current.ptr) = *(it.ptr);
    }
    _size -= (last - first + 1);  //for last - first > newSize

    if(_size <= _capacity / 3)
        decrease();
}

template<typename T>
typename Array<T>::iterator Array<T>::insert(const_iterator position, const T& value)
{
    if(position >= cend() || position < cbegin())
        throw std::out_of_range("Iterators out of container");

    if(_size >= _capacity)
        increase();
    _size++;

    for(auto it = cend() - 2; it != position ; it--) //cend() - 2 is last item
    {
        *(it + 1).ptr = *it;
    }

    auto dest = (position + 1).ptr;
    *dest = value;

    return iterator(dest);
}

template<typename T>
typename Array<T>::iterator Array<T>::insert(const_iterator position, T&& value)
{
    if(position >= cend() || position < cbegin())
        throw std::out_of_range("Iterators out of container");

    if(_size >= _capacity)
        increase();
    _size++;

    for(auto it = cend() - 2; it != position ; it--) //cend() - 2 is last item
    {
        *(it + 1).ptr = *it;
    }

    auto dest = (position + 1).ptr;
    *dest = std::move(value);

    return iterator(dest);
}

template<typename T>
inline void Array<T>::clear() noexcept
{
    _size = 0;
}

template<typename T>
T& Array<T>::operator[](int index)
{
    if(index >= _size || index < 0)
        throw std::out_of_range("Iterators out of container");

    return _data[index];
}

template<typename T>
const T& Array<T>::operator[](int index) const
{
    if(index >= _size || index < 0)
        throw std::out_of_range("Iterators out of container");

    return _data[index];
}

#pragma endregion

#pragma region Iterator

template<typename T>
array_iterator<T>::array_iterator(array_iterator<T>::real_type* pointer)
{
    if(pointer != nullptr)
        ptr = pointer;
    else
        throw std::exception();
}

template<typename T>
array_iterator<T>::array_iterator(const array_iterator& other)
{
    ptr = other.ptr;
}

template<typename T>
inline typename array_iterator<T>::reference array_iterator<T>::operator*()
{
    return *ptr;
}

template<typename T>
inline typename array_iterator<T>::pointer array_iterator<T>::operator->()
{
    return ptr;
}

template<typename T>
array_iterator<T>& array_iterator<T>::operator++()
{
    ptr++;
    return *this;
}

template<typename T>
array_iterator<T> array_iterator<T>::operator++(int)
{
    array_iterator res = *this;
    ptr++;
    return res;
}

template<typename T>
array_iterator<T>& array_iterator<T>::operator--()
{
    ptr--;
    return *this;
}

template<typename T>
array_iterator<T> array_iterator<T>::operator--(int)
{
    array_iterator res = *this;
    ptr--;
    return res;
}

template<typename T>
array_iterator<T> array_iterator<T>::operator+(array_iterator<T>::difference_type n)
{
    return array_iterator(ptr + n);
}

template<typename T>
array_iterator<T> array_iterator<T>::operator-(array_iterator<T>::difference_type n)
{
    return array_iterator(ptr - n);
}

template<typename T>
array_iterator<T>& array_iterator<T>::operator+=(array_iterator<T>::difference_type n)
{
    ptr+=n;
    return *this;
}

template<typename T>
array_iterator<T>& array_iterator<T>::operator-=(array_iterator<T>::difference_type n)
{
    ptr-=n;
    return *this;
}

template<typename T>
array_iterator<T> array_iterator<T>::operator[](array_iterator<T>::difference_type n)
{
    return array_iterator(ptr + n);
}

template<typename T>
inline typename array_iterator<T>::difference_type array_iterator<T>::operator-(const array_iterator<T>& other)
{
    return ptr - other.ptr;
}

template<typename T>
inline bool array_iterator<T>::operator==(const array_iterator& other)
{
    return ptr == other.ptr;
}

template<typename T>
inline bool array_iterator<T>::operator!=(const array_iterator& other)
{
    return !operator==(other);
}

template<typename T>
inline bool array_iterator<T>::operator<(const array_iterator& other)
{
    return ptr < other.ptr; //how if custom allocator is used?
}

template<typename T>
inline bool array_iterator<T>::operator<=(const array_iterator& other)
{
    return operator<(other) || operator==(other);
}

template<typename T>
inline bool array_iterator<T>::operator>(const array_iterator& other)
{
    return !operator<=(other);
}

template<typename T>
inline bool array_iterator<T>::operator>=(const array_iterator& other)
{
    return !operator<(other);
}

#pragma endregion