#pragma once

#include "vector"
#include "algorithm"
#include "Polynomial.h"

namespace LinAlg
{
    namespace detail
    {
        template<typename T>
        auto sturmSequence(const Polynomial<T> &poly)
        {
            std::vector<Polynomial<T>> sequence;

            sequence.push_back(poly);
            if (poly.degree() != 0)
                sequence.push_back(poly.derivate());

            while (sequence.back().degree() > 0)
            {
                auto &p2 = sequence[sequence.size() - 2];
                auto &p1 = sequence[sequence.size() - 1];
                sequence.push_back(-(p2 % p1));
            }

            return sequence;
        }

        template<typename T, typename U>
        int calculateSignChange(const std::vector<Polynomial<T>> &sturmSequence, U x)
        {
            std::vector<T> f;
            std::transform(sturmSequence.begin(), sturmSequence.end(), std::back_inserter(f),
                          [x](const auto& poly){ return  poly(x); });

            int result = 0;
            for (auto it = f.cbegin(); it != f.cend() - 1; it++)
            {
                if(*it >= 0 && *(it+1) < 0)
                    result++;
                if(*it < 0 && *(it+1) >= 0)
                    result++;
            }

            return result;
        }

        template<typename T, typename U1, typename U2>
        int calculateRoots(const std::vector<Polynomial<T>> &sturmSequence, U1 a, U2 b)
        {
            return std::abs(calculateSignChange(sturmSequence, a) - calculateSignChange(sturmSequence, b));
        }

        template<typename T>
        auto splitRoots(const Polynomial<T> &poly)
        {
            const double INFTY = 2 << 20;
            const double scale = 0.5;
            const double step = 2;

            auto sturmSeq = sturmSequence(poly);
            int positiveRootsNumber = calculateRoots(sturmSeq, 0, INFTY);
            int negativeRootsNumber = calculateRoots(sturmSeq, -INFTY, 0);
            std::vector<std::tuple<T, T>> ranges;

            auto a = 0;
            auto b = a + step;
            while (positiveRootsNumber > 0)
            {
                int rootsCount = calculateRoots(sturmSeq, a, b);
                if (rootsCount == 0)
                {
                    a = b;
                    b = a + step;
                }
                else if (rootsCount > 1)
                {
                    b = a + step * scale;
                }
                else
                {
                    ranges.emplace_back(a, b);
                    a = b;
                    b = a + step;
                    positiveRootsNumber--;
                }
            }

            b = 0;
            a = b - step;
            while (negativeRootsNumber > 0)
            {
                int rootsCount = calculateRoots(sturmSeq, a, b);
                if (rootsCount == 0)
                {
                    b = a;
                    a = b - step;
                }
                else if (rootsCount > 1)
                {
                    a = b - step * scale;
                }
                else
                {
                    ranges.emplace_back(a, b);
                    b = a;
                    a = b - step;
                    negativeRootsNumber--;
                }
            }

            return ranges;
        }
    }

    template<typename T>
    auto newton(const Polynomial<T> &poly, double precision = 0.00001)
    {
        std::vector<T> roots;
        auto df = poly.derivate();

        for (const auto& range: detail::splitRoots(poly))
        {
            auto[a, b] = range;
            auto x = (a + b) / 2;
            auto f = poly(x);

            while (std::abs(f) >= precision )
            {
                x = x - f / df(x);
                f = poly(x);
            }

            roots.push_back(x);
        }

        return roots;
    }
}
