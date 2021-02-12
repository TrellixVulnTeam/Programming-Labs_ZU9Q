#ifndef ARRAY_H
#define ARRAY_H

#include <ostream>
#include <new>
#include <stdexcept>

template <typename T>
class Array
{
public:
  //ctors
  Array();
  Array(size_t);
  Array(const Array&);
  ~Array();

  //functionality
  size_t size() const noexcept;
  size_t capacity() const noexcept;

  virtual void push_back(const T&);
  virtual void update(size_t, const T&);

  void remove(size_t);
  size_t find(const T&) const;
  void clear();

  const T& operator[](size_t) const;
  Array& operator=(const Array&);
  Array operator+(const Array&) const;
  Array operator*(const Array&) const;

  template <class U>
  friend std::ostream &operator<<(std::ostream&, const Array<U>&);
  template <class U>
  friend std::istream &operator>>(std::istream&, Array<U>&);

protected:
  T* _data;
  size_t _capacity;
  size_t _size;

  void scale(size_t);

  struct Constants
  {
    static const size_t DEFAULT_CAPACITY = 10;
    static const int GROW_FACTOR = 2;
  };
};

template <class T>
Array<T>::Array(): Array(Constants::DEFAULT_CAPACITY) { }

template <class T>
Array<T>::Array(size_t capacity)
{
  _data = reinterpret_cast<T*>(::operator new(capacity * sizeof(T)));
  _capacity = capacity;
  _size = 0;
}

template <class T>
Array<T>::Array(const Array<T> &array)
{
  auto lenght = array._size * sizeof(T);
  T *new_data = reinterpret_cast<T*>(::operator new(lenght));
  memcpy(new_data, array._data, lenght);
  _data = new_data;

  _capacity = array._capacity;
  _size = array._size;
}

template<typename T>
void free_memory(T* data, size_t size, size_t capacity)
{
  for (size_t i = 0; i < size; i++)
    data[i].~T();
  ::operator delete(data, capacity * sizeof(T));
}

template <class T>
Array<T>::~Array()
{
  free_memory(_data, _size, _capacity);
}

template <class T>
void Array<T>::scale(size_t capacity)
{
  auto lenght = _size * sizeof(T);
  T *new_data = reinterpret_cast<T*>(::operator new(lenght));

  memcpy(new_data, _data, lenght);
  free_memory(_data, _size, _capacity);
  _data = new_data;
  _capacity = capacity;
}

template <class T>
size_t Array<T>::size() const noexcept
{
  return _size;
}

template <class T>
size_t Array<T>::capacity() const noexcept
{
  return _capacity;
}

template <class T>
void Array<T>::push_back(const T &item)
{
  if (_size == _capacity)
    scale(_capacity * Constants::GROW_FACTOR);

  new (_data + _size) T(item);
  _size++;
}

template <class T>
void Array<T>::remove(size_t position)
{
  if (position < _size)
  {
    for (int i = position; i < _size - 1; i++)
    {
      _data[i] = _data[i + 1];
    }
    _data[_size - 1].~T();
    _size--;

    if (_capacity / _size < Constants::GROW_FACTOR * 1.5)
      scale((size_t)(_capacity / Constants::GROW_FACTOR));
  }
  else
  {
    throw std::invalid_argument("Position out of range");
  }
}

template <class T>
void Array<T>::update(size_t position, const T& item)
{
  if(position < _size)
  {
    _data[position].~T();
    new (_data + position) T(item);
  }
  else
  {
    throw std::invalid_argument("Invalid position");
  }
}

template <class T>
size_t Array<T>::find(const T &item) const
{
  for (int i = 0; i < _size; i++)
  {
    if (_data[i] == item)
      return i;
  }

  throw std::invalid_argument("Item does not contains");
}

template <class T>
void Array<T>::clear()
{
  free_memory(_data, _size, _capacity);
  _data = new T[Constants::DEFAULT_CAPACITY];
  _capacity = Constants::DEFAULT_CAPACITY;
  _size = 0;
}

template <class T>
const T& Array<T>::operator[](size_t position) const
{
  if (position >= _size || _size <= 0)
    throw std::invalid_argument("Position out of range");

  return _data[position];
}

template <class T>
Array<T>& Array<T>::operator=(const Array<T> &array)
{
  auto lenght = array._size * sizeof(T);
  T *new_data = reinterpret_cast<T*>(::operator new(lenght));

  memcpy(new_data, array._data, lenght);
  free_memory(_data, _size, _capacity);
  _data = new_data;

  _capacity = array._capacity;
  _size = array._size;

  return *this;
}

template <class T>
Array<T> Array<T>::operator+(const Array<T> &array) const
{
  if (_size == array._size)
  {
    Array<T> result(_size);
    for (int i = 0; i < _size; i++)
    {
      result._data[i] = _data[i] + array._data[i];
      result._size++;
    }
    return result;
  }
  else
  {
    throw std::invalid_argument("Arrays have different size");
  }
}

template <class T>
Array<T> Array<T>::operator*(const Array<T> &array) const
{
  if (_size == array._size)
  {
    Array<T> result(_size);
    for (int i = 0; i < _size; i++)
    {
      result._data[i] = _data[i] * array._data[i];
      result._size++;
    }
    return result;
  }
  else
  {
    throw std::invalid_argument("Arrays have different size");
  }
}

//requires << operator for type U
template <class U>
std::ostream& operator<<(std::ostream &stream, const Array<U> &array)
{
  for (size_t i = 0; i < array._size; i++)
  {
    stream << array._data[i] << std::endl;
  }
  return stream;
}

//requires default ctot and >> operator implementation for type U
//read n(<= capacity) element from stream to array
template <class U>
std::istream& operator>>(std::istream &stream, Array<U> &array)
{
  U item;
  while (!stream.eof() && array._size < array._capacity)
  {
    stream >> item;
    if (stream.fail())
    {
#ifndef IGNORE_INVALID_STREAM_VALUE
      throw std::invalid_argument("Invalid stream value");
#endif
#ifdef IGNORE_INVALID_STREAM_VALUE
      stream.clear();
      stream.ignore();
#endif
    }
    else
    {
      array.push_back(item);
    }
  }
  return stream;
}

#endif
