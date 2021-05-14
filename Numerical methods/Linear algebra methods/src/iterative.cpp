#include <iostream>

#include "Matrix.h"
#include "Vector.h"
#include "Solvers.h"
#include "Utils.h"

template<typename T>
void substractRows(LinAlg::IMatrix<T> &matrix, size_t fromIdx, size_t whatIdx, T coeff = 1)
{
    for (size_t j = 0; j < matrix.ncol(); j++)
    {
        matrix(fromIdx, j) -= coeff * matrix(whatIdx, j);
    }
}

int main()
{
    LinAlg::Matrix<double> A = {{5.5, 7,    6,    5.5},
                                {7,   10.5, 8,    7},
                                {6,   8,    10.5, 9},
                                {5.5, 7,    9,    10.5}};

    std::cout << "Matrix A" << std::endl;
    print(A);
    std::cout << std::endl;

    LinAlg::Vector<double> b = {23, 32, 33, 31};

    std::cout << "Vector b" << std::endl;
    print(b);
    std::cout << std::endl;

    LinAlg::Matrix<double> mat = A;
    LinAlg::Vector<double> vec = b;
    LinAlg::MatrixVectorView<double> tmat(mat, vec);
    LinAlg::gaussJordanEliminationStep(tmat, 0, 0);

    std::cout << "Matrix A after one Gauss-Jordan elimination iteration:" << std::endl;
    print(mat);
    std::cout << std::endl;

    substractRows(tmat, 0, 1);
    substractRows(tmat, 0, 3, 1 / 5.);

    std::cout << "Our task with diagonally dominant matrix" << std::endl;
    std::cout << "Matrix A" << std::endl;
    print(mat);
    std::cout << std::endl;
    std::cout << "Vector b" << std::endl;
    print(vec);
    std::cout << std::endl;

    auto xsi = LinAlg::simpleIteration(mat, vec);
    std::cout << "Simple iteration. Solution: " << std::endl;
    print(xsi);
    std::cout << std::endl;

    auto xgs1 = LinAlg::gaussSeidel(A, b);
    auto xgs2 = LinAlg::gaussSeidel(mat, vec);
    std::cout << "Gauss-Seidel. Solutions: " << std::endl;

    std::cout << "Without diagonally dominant matrix: " << std::endl;
    print(xgs1);
    std::cout << std::endl;

    std::cout << "With diagonally dominant matrix: " << std::endl;
    print(xgs2);

    return 0;
}