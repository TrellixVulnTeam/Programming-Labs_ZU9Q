#pragma once

#include <cstddef>
#include <algorithm>

using std::size_t;


namespace LinAlg
{
    template <typename T>
    class Buffer
    {
    public:
        explicit Buffer(size_t size)
        {
            _size = size;
            _data = new T[size]();
        }

        Buffer(const Buffer &buff)
        {
            _data = new T[buff._size];
            _size = buff._size;
            std::copy(buff._data, buff._data + buff._size, _data);
        }

        Buffer(Buffer &&lhs) noexcept
        {
            _data = std::exchange(lhs._data, nullptr);
            _size = std::exchange(lhs._size, 0);
        }

        ~Buffer()
        {
            delete[] _data;
        }

        Buffer& operator=(const Buffer &buff)
        {
            if (&buff == this)
                return *this;

            T *_newData = new T[buff._size];
            std::copy(buff._data, buff._data + buff._size, _newData);

            _size = buff._size;
            delete[] _data;
            _data = _newData;

            return *this;
        }

        Buffer& operator=(Buffer &&buff) noexcept
        {
            std::swap(_data, buff._data);
            std::swap(_size, buff._size);
            return *this;
        }

        T& operator[](std::size_t pos)
        {
            return _data[pos];
        }

        const T& operator[](std::size_t pos) const
        {
            return _data[pos];
        }

        [[nodiscard]] inline size_t size() const noexcept { return _size; }

    private:
        T *_data;
        size_t _size;
    };
}
