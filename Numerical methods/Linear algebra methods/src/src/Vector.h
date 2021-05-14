#pragma once

#include <cmath>
#include <initializer_list>
#include "Buffer.h"

namespace LinAlg
{
    template<typename T>
    class Vector
    {
    public:
        explicit Vector(size_t nval) : _buff(nval) {}

        Vector(std::initializer_list<T> values): _buff(values.size())
        {
            size_t i = 0;
            for (const auto& value: values)
            {
                _buff[i] = value;
                i++;
            }
        }

        template<typename U>
        Vector(const Vector<U> &vector) : _buff(vector.nval())
        {
            for (size_t i = 0; i < vector.nval(); i++)
            {
                _buff[i] = vector(i);
            }
        };

        inline size_t nval() const noexcept
        {
            return _buff.size();
        }

        T& operator()(size_t i);

        const T &operator()(size_t i) const;

        auto norm() const noexcept;

        template<typename U>
        friend Vector<U> operator-(const Vector<U> &vector);

    private:
        Buffer <T> _buff;
    };

    template<typename T>
    T &Vector<T>::operator()(size_t i)
    {
        if (i >= _buff.size())
            throw std::invalid_argument("Position is out of range");
        return _buff[i];
    }

    template<typename T>
    const T& Vector<T>::operator()(size_t i) const
    {
        if (i >= _buff.size())
            throw std::invalid_argument("Position is out of range");
        return _buff[i];
    }

    template<typename T>
    auto Vector<T>::norm() const noexcept
    {
        T sum = 0;
        for (size_t i = 0; i < _buff.size(); i++)
        {
            sum += _buff[i] * _buff[i];
        }
        return std::sqrt(sum);
    }

    template<typename T>
    Vector<T> operator-(const Vector<T> &vector)
    {
        Vector<T> result(vector.nval());
        for (size_t i = 0; i < vector.nval(); i++)
        {
            result(i) = -vector(i);
        }
        return result;
    }

    template<typename T, typename U>
    auto operator+(const Vector<T> &rhs, const Vector<U> &lhs)
    {
        if (rhs.nval() != lhs.nval())
            throw std::invalid_argument("Different size");

        Vector<typename std::common_type<T, U>::type> result(rhs.nval());
        for (size_t i = 0; i < rhs.nval(); i++)
        {
            result(i) = rhs(i) + lhs(i);
        }
        return result;
    }

    template<typename T, typename U>
    auto operator-(const Vector<T> &rhs, const Vector<U> &lhs)
    {
        if (rhs.nval() != lhs.nval())
            throw std::invalid_argument("Different size");

        Vector<typename std::common_type<T, U>::type> result(rhs.nval());
        for (size_t i = 0; i < rhs.nval(); i++)
        {
            result(i) = rhs(i) - lhs(i);
        }
        return result;
    }

    template<typename T>
    T getMaxAbsValue(const Vector<T> &vector)
    {
        T max = std::abs(vector(0));

        for (size_t i = 1; i < vector.nval(); i++)
        {
            if (max < std::abs(vector(i)))
                max = std::abs(vector(i));
        }

        return max;
    }
}
