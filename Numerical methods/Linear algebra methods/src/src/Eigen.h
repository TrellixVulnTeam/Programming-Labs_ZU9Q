#pragma once

#include <vector>
#include <cmath>

#include "Vector.h"
#include "Matrix.h"
#include "MatrixUtils.h"
#include "Polynomial.h"
#include "PolynomialSolvers.h"
#include "Solvers.h"

#ifdef PRINT
#include "Utils.h"
#endif

namespace LinAlg
{
    namespace detail
    {
        template<typename T>
        auto maxNonDiagonal(const Matrix<T> &matrix)
        {
            T max = 0;
            size_t maxI;
            size_t maxJ;

            for (size_t i = 0; i < matrix.nrow(); i++)
            {
                for (size_t j = 0; j < matrix.ncol(); j++)
                {
                    auto absValue = std::abs(matrix(i, j));
                    if (i != j && absValue > max)
                    {
                        max = absValue;
                        maxI = i;
                        maxJ = j;
                    }
                }
            }

            return std::make_tuple(max, maxI, maxJ);
        }
    }

    template<typename T>
    auto jacobi(const Matrix<T> &matrix, double precision = 0.00001, int maxIteration = 1000)
    {
        if (matrix.ncol() != matrix.nrow())
            throw std::invalid_argument("Invalid sizes");

        auto A = matrix;
        auto[maxNd, i, j] = detail::maxNonDiagonal(A);

        int iteration = 0;
        do
        {
            auto tau = (A(j, j) - A(i, i)) / (2 * maxNd);
            auto tan = -tau + std::sqrt(1 + tau * tau);
            auto c = 1 / std::sqrt(1 + tan * tan);
            auto s = tan * c;

            for (size_t k = 0; k < A.nrow(); k++)
            {
                if (k != i && k != j)
                {
                    auto aki = A(k, i);
                    A(i, k) = A(k, i) = c * aki - s * A(k, j);
                    A(j, k) = A(k, j) = s * aki + c * A(k, j);
                }
            }
            auto aii = A(i, i);
            A(i, i) = c * c * aii - 2 * c * s * A(i, j) + s * s * A(j, j);
            A(j, j) = c * c * A(j, j) + 2 * c * s * A(i, j) + s * s * aii;
            A(i, j) = A(j, i) = 0;

#ifdef PRINT
            std::cout << "Iteration: " << iteration + 1 << std::endl;

            std::cout << "Matrix T" << std::endl;
            auto F = eye<T>(A.nrow());
            F(i, i) = F(j, j) = c;
            F(j, i) = -s;
            F(i, j) = s;
            print(F);

            T Sd = 0;
            T Snd = 0;
            for (size_t i = 0; i < A.nrow(); i++)
            {
                for (size_t j = 0; j < A.ncol(); j++)
                {
                    if (i == j)
                        Sd += A(i, i) * A(i, i);
                    else
                        Snd += A(i, j) * A(i, j);
                }
            }
            std::cout << "Spherical norm diag: " << Sd << std::endl;
            std::cout << "Spherical norm non diag: " << Snd << std::endl;
            std::cout << "Spherical norm: " << Sd + Snd << std::endl;
#endif

            std::tie(maxNd, i, j) = detail::maxNonDiagonal(A);
            iteration++;
        } while (maxNd > precision && iteration < maxIteration);

        std::vector<T> eigenValues;
        for (size_t i = 0; i < A.nrow(); i++)
        {
            eigenValues.push_back(A(i, i));
        }

        return eigenValues;
    }

    template<typename T>
    auto danilevsky(const Matrix<T> &matrix, double precision = 0.00001)
    {
        if (matrix.ncol() != matrix.nrow())
            throw std::invalid_argument("Invalid sizes");

        auto P = matrix;
        for (int i = P.nrow() - 2; i >= 0; i--)
        {
            auto M = eye<T>(P.nrow());
            auto MInv = eye<T>(P.nrow());

            for (int j = 0; j < P.ncol(); j++)
            {
                MInv(i, j) = P(i + 1, j);
                if (i != j)
                {
                    M(i, j) = -P(i + 1, j) / P(i + 1, i);
                } else
                {
                    M(i, i) = 1 / P(i + 1, i);
                }
            }

#ifdef PRINT
            std::cout << "Danilevsky method. Step: " << P.nrow() - 1 - i << std::endl;
            std::cout << "Matrix M" << std::endl;
            print(M);
            std::cout << "Matrix M inverse" << std::endl;
            print(MInv);
#endif

            P = MInv * P * M;
        }

#ifdef PRINT
        std::cout << "Frobenius form" << std::endl;
        print(P);
#endif

        std::vector<T> characteristicCoeffs;
        for (size_t i = P.ncol(); i > 0; i--)
            characteristicCoeffs.push_back(-P(0, i-1));
        characteristicCoeffs.push_back(1);

        Polynomial characteristic(characteristicCoeffs);
        return newton(characteristic, precision);
    }

    template<typename T>
    auto krylov(const Matrix<T> &matrix, const Vector<T> &initialY, double precision = 0.00001)
    {
        if (matrix.ncol() != matrix.nrow() || matrix.nrow() != initialY.nval())
            throw std::invalid_argument("Invalid sizes");

        Matrix<T> A(matrix.nrow(), matrix.ncol());
        Vector<T> b = initialY;

        for (size_t i = 0; i < A.nrow(); i++)
        {
            for (size_t j = 0; j < b.nval(); j++)
                A(j, A.nrow() - (i + 1)) = b(j);
            b = matrix * b;
        }

        std::vector<T> characteristicCoeffs;
        if (A.nrow() % 2 == 0)
        {
            b = -b;
            characteristicCoeffs.push_back(1);
        }
        else
        {
            characteristicCoeffs.push_back(-1);
        }

#ifdef PRINT
        std::cout << "Krylov" << std::endl;
        std::cout << "Matrix A" << std::endl;
        print(A);
        std::cout << "Vector b" << std::endl;
        print(b);
#endif

        auto p = gaussPivotSolve(A, b);

        for (size_t i = 0; i < p.nval(); i++)
        {
            characteristicCoeffs.push_back(p(i));
        }
        std::reverse(characteristicCoeffs.begin(), characteristicCoeffs.end());

        Polynomial characteristic(characteristicCoeffs);
        return newton(characteristic, precision);
    }
}