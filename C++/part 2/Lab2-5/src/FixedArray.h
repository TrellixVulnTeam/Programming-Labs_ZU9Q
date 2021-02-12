#ifndef FIXED_ARRAY_H
#define FIXED_ARRAY_H

#include "Array.h"

template <class T>
class FixedArray : public Array<T>
{
public:
  FixedArray(T, T);
  FixedArray(T, T, size_t);
  FixedArray(const FixedArray&);

  void push_back(const T&) override;
  void update(size_t, const T&) override;
  T min() const noexcept;
  T max() const noexcept;

  FixedArray& operator=(const FixedArray&);
  FixedArray operator+(const FixedArray&) const;
  FixedArray operator*(const FixedArray&) const;

private:
  T _min;
  T _max;
};

template<class T>
FixedArray<T>::FixedArray(T min, T max)
{
  _min = min;
  _max = max;
}

template<class T>
FixedArray<T>::FixedArray(const FixedArray& array) : Array<T>(array)
{
  _min = array._min;
  _max = array._max;
}

template<class T>
FixedArray<T>::FixedArray(T min, T max, size_t capacity): Array<T>(capacity)
{
  _min = min;
  _max = max;
}

template<class T>
FixedArray<T>& FixedArray<T>::operator=(const FixedArray<T>& array)
{
  if(array._min < _min || array._max > _max)
    throw std::invalid_argument("Invalid min-max range");

  auto lenght = array._size * sizeof(T);
  T *new_data = reinterpret_cast<T*>(::operator new(lenght));

  memcpy(new_data, array._data, lenght);
  free_memory(this->_data, this->_size, this->_capacity);
  this->_data = new_data;

  this->_capacity = array._capacity;
  this->_size = array._size;
  _min = array._min;
  _max = array._max;

  return *this;
}

template<class T>
T FixedArray<T>::min() const noexcept
{
  return _min;
}

template<class T>
T FixedArray<T>::max() const noexcept
{
  return _max;
}

template<class T>
void FixedArray<T>::push_back(const T& item)
{
    if(item >= _min && item <= _max)
    {
    	Array<T>::push_back(item);
    }
    else
    {
      throw std::invalid_argument("Item is out of range");
    }
}

template<class T>
void FixedArray<T>::update(size_t position, const T& item)
{
	if(item >= _min && item <= _max)
	{
		Array<T>::update(position, item);
	}
  else
  {
    throw std::invalid_argument("Item is out of range");
  }
}

template <class T>
FixedArray<T> FixedArray<T>::operator+(const FixedArray<T> &arr) const
{
  if (this->_size == arr._size)
  {
    FixedArray<T> result(arr._min + _min, arr._max + _max, this->_size);
    for (int i = 0; i < this->_size; i++)
    {
      result._data[i] = this->_data[i] + arr._data[i];
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
FixedArray<T> FixedArray<T>::operator*(const FixedArray<T> &arr) const
{
  if (this->_size == arr._size)
  {
    T temp[] = {arr._min * _min, arr._min * _max,
                arr._max * _min,arr._max * _max };
    T min = *std::min_element(temp, temp+4);
    T max = *std::max_element(temp, temp+4);

    FixedArray<T> result(min, max, this->_size);
    for (int i = 0; i < this->_size; i++)
    {
      result._data[i] = this->_data[i] * arr._data[i];
      result._size++;
    }
    return result;
  }
  else
  {
    throw std::invalid_argument("Arrays have different size");
  }
}

#endif