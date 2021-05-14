#pragma once

#include <vector>

#include "Matrix.h"
#include "Vector.h"
#include "MatrixView.h"
#include "Cholesky.h"
#include "Gauss.h"

#ifdef PRINT
#include "Utils.h"
#endif

namespace LinAlg
{
    namespace detail
    {
        template<typename T, typename U>
        auto forward(const IMatrix<T>&, const Vector<U>&);

        template<typename T, typename U>
        auto backward(const IMatrix<T>&, const Vector<U>&);

        template<typename T>
        auto backward(const MatrixVectorView<T>&);

        template<typename T, typename U>
        auto computeCdq(const Matrix<T>&, const Vector<U>&);
    }

    template<typename T, typename U>
    auto choleskySolve(const Matrix<T> &A, const Vector<U> &b)
    {
        auto chol = cholesky(A);
        auto y = detail::forward(chol, b);
        auto x = detail::backward(TransposeView(chol), y);

#ifdef PRINT
        std::cout << "Cholesky solver y" << std::endl;
        print(y);
        std::cout << std::endl;
#endif

        return x;
    }

    template<typename T, typename U>
    auto ldlSolve(const Matrix<T> &A, const Vector<U> &b)
    {
        auto[l, d] = ldl(A);
        auto z = detail::forward(l, b);

#ifdef PRINT
        std::cout << "LDL solver z" << std::endl;
        print(z);
        std::cout << std::endl;
#endif

        for (size_t i = 0; i < z.nval(); i++)
        {
            z(i) = z(i) / d(i);
        }

#ifdef PRINT
        std::cout << "LDL solver y" << std::endl;
        print(z);
        std::cout << std::endl;
#endif

        auto x = detail::backward(TransposeView(l), z);
        return x;
    }

    template<typename T, typename U>
    auto gaussJordanSolve(const Matrix<T> &A, const Vector<U> &b)
    {
        using ret_type = typename std::common_type<T, U>::type;
        Matrix<ret_type> m(A);
        Vector<ret_type> v(b);
        MatrixVectorView<ret_type> aug(m, v);

        for (size_t i = 0; i < m.nrow(); i++)
        {
            LinAlg::gaussJordanEliminationStep(aug, i, i);

#ifdef PRINT
            std::cout << "Gauss Jordan solver. Step: " << i + 1 << std::endl;
            std::cout << "Matrix A: " << std::endl;
            print(m);
            std::cout << "Vector b: " << std::endl;
            print(v);
#endif
        }

        return v;
    }

    template<typename T, typename U>
    auto gaussSolve(const Matrix<T> &A, const Vector<U> &b)
    {
        using ret_type = typename std::common_type<T, U>::type;
        Matrix<ret_type> m(A);
        Vector<ret_type> v(b);
        MatrixVectorView<ret_type> aug(m, v);

        for (size_t i = 0; i < m.nrow(); i++)
        {
            LinAlg::gaussEliminationStep(aug, i, i);

#ifdef PRINT
            std::cout << "Gauss solver. Step: " << i + 1 << std::endl;
            std::cout << "Matrix A: " << std::endl;
            print(m);
            std::cout << "Vector b: " << std::endl;
            print(v);
#endif
        }

        auto x = detail::backward(m, v);

        return x;
    }

    template<typename T, typename U>
    auto gaussPivotSolve(const Matrix<T> &A, const Vector<U> &b)
    {
        using ret_type = typename std::common_type<T, U>::type;
        Matrix<ret_type> m(A);
        Vector<ret_type> v(b);
        MatrixVectorView<ret_type> aug(m, v);

        for (size_t i = 0; i < m.nrow(); i++)
        {
            size_t max = getMaxRowPivotIndex(aug, i);
            aug.swapRows(i, max);

            LinAlg::gaussEliminationStep(aug, i, i);

#ifdef PRINT
            std::cout << "Gauss with pivoting solver. Step: " << i + 1 << std::endl;
            std::cout << "Matrix A: " << std::endl;
            print(m);
            std::cout << "Vector b: " << std::endl;
            print(v);
#endif
        }

        auto x = detail::backward(aug);
        return x;
    }

    template<typename T, typename U>
    auto simpleIteration(const Matrix<T> &A, const Vector<U> &b, double precision = 0.0001, int maxIteration = 100)
    {
        if (A.ncol() != A.nrow() || A.nrow() != b.nval())
            throw std::invalid_argument("Invalid sizes");

        using ret_type = typename std::common_type<T, U>::type;
        auto[C, d, q] = detail::computeCdq(A, b);

#ifdef PRINT
        std::cout << "Matrix C: " << std::endl;
        print(C);
        std::cout << "Vector d: " << std::endl;
        print(d);
#endif

        Vector<ret_type> x = d;
        Vector<ret_type> xprev(b.nval());

        int iteration = 0;
        double criterion;
        precision = precision * (1 - q) / q;

        do
        {
            xprev = x;
            x = C * xprev + d;
            criterion = getMaxAbsValue(xprev - x);

#ifdef PRINT
            std::cout << "Iteration: " << iteration + 1 << std::endl;
            std::cout << "x: " << std::endl;
            print(x);
            std::cout << "Residue: "<< std::endl;
            printAbs(A*x - b);
            std::cout << "Criteria: " << criterion / (1-q) * q << std::endl;
#endif

            iteration++;
        } while (criterion > precision && iteration < maxIteration);

        return x;
    }

    template<typename T, typename U>
    auto gaussSeidel(const Matrix<T> &A, const Vector<U> &b, double precision = 0.0001, int maxIteration = 100)
    {
        if (A.ncol() != A.nrow() || A.nrow() != b.nval())
            throw std::invalid_argument("Invalid sizes");

        using ret_type = typename std::common_type<T, U>::type;
        auto[C, d, q] = detail::computeCdq(A, b);

#ifdef PRINT
        std::cout << "Matrix C: " << std::endl;
        print(C);
        std::cout << "Vector d: " << std::endl;
        print(d);
#endif

        Vector<ret_type> x = d;
        Vector<ret_type> xprev(b.nval());

        int iteration = 0;
        double criterion;

        do
        {
            xprev = x;

            for (size_t i = 0; i < C.nrow(); i++)
            {
                x(i) = d(i);
                for (size_t j = 0; j < C.ncol(); j++)
                {
                    if (i > j)
                    {
                        x(i) += C(i, j) * x(j);
                    } else
                    {
                        x(i) += C(i, j) * xprev(j);
                    }
                }
            }

            criterion = getMaxAbsValue(xprev - x);

#ifdef PRINT
            std::cout << "Iteration: " << iteration + 1 << std::endl;
            std::cout << "x: " << std::endl;
            print(x);
            std::cout << "Residue: "<< std::endl;
            printAbs(A*x - b);
            std::cout << "Criteria: " << criterion << std::endl;
#endif

            iteration++;
        } while (criterion > precision && iteration < maxIteration);

        return x;
    }

    namespace detail
    {
        template<typename T, typename U>
        auto forward(const IMatrix<T> &A, const Vector<U> &b)
        {
            if (A.nrow() != b.nval() || A.ncol() != b.nval())
                throw std::invalid_argument("Invalid sizes");

            Vector<typename std::common_type<T, U>::type> x(b.nval());

            for (size_t i = 0; i < A.nrow(); i++)
            {
                T sum = 0;
                for (size_t j = 0; j < i; j++)
                {
                    sum += A(i, j) * x(j);
                }
                x(i) = (b(i) - sum) / A(i, i);
            }

            return x;
        }

        template<typename T, typename U>
        auto backward(const IMatrix<T> &A, const Vector<U> &b)
        {
            if (A.nrow() != b.nval() || A.ncol() != b.nval())
                throw std::invalid_argument("Invalid sizes");

            Vector<typename std::common_type<T, U>::type> x(b.nval());

            size_t i = A.nrow();
            do
            {
                i--;
                T sum = 0;
                for (size_t j = i + 1; j < A.nrow(); j++)
                {
                    sum += A(i, j) * x(j);
                }
                x(i) = (b(i) - sum) / A(i, i);
            } while (i != 0);

            return x;
        }

        template<typename T>
        auto backward(const MatrixVectorView<T> &aug)
        {
            size_t i = aug.nrow();
            Vector<T> res(aug.nrow());
            do
            {
                i--;
                T sum = 0;
                for (size_t j = i + 1; j < aug.nrow(); j++)
                {
                    sum += aug(i, j) * res(j);
                }
                res(i) = (aug(i, aug.ncol() - 1) - sum) / aug(i, i);
            } while (i != 0);

            return res;
        }

        template<typename T, typename U>
        auto computeCdq(const Matrix<T> &A, const Vector<U> &b)
        {
            using ret_type = typename std::common_type<T, U>::type;
            Matrix<ret_type> C(A.nrow(), A.ncol());
            Vector<ret_type> d(b.nval());
            double q;

            for (size_t i = 0; i < C.nrow(); i++)
            {
                const auto &a = A(i, i);
                double qTemp = 0;

                for (size_t j = 0; j < C.ncol(); j++)
                {
                    if (i != j)
                    {
                        auto value = -A(i, j) / a;
                        C(i, j) = value;
                        qTemp += std::abs(value);
                    }
                }

                d(i) = b(i) / a;

                if (q < qTemp)
                    q = qTemp;
            }

            return std::make_tuple(C, d, q);
        }
    }
}
