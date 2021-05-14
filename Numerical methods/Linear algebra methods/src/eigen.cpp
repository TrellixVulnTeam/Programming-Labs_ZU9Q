#include <iostream>

#include "Matrix.h"
#include "Eigen.h"
#include "Utils.h"

template<typename T>
void print(std::vector<T> &eigenValues)
{
    for (const auto &val: eigenValues)
    {
        std::cout << val << "\t";
    }
    std::cout << std::endl;
}

int main()
{
    LinAlg::Matrix<double> A = {{7,    0.88, 0.93, 1.21},
                                {0.88, 4.16, 1.3,  0.15},
                                {0.93, 1.3,  6.44, 2},
                                {1.21, 0.15, 2,    9}};

    std::cout << "Matrix A" << std::endl;
    print(A);
    std::cout << std::endl;

    auto jacobiEigenValues = LinAlg::jacobi(A);
    std::cout << "Jacobi eigenvalues" << std::endl;
    print(jacobiEigenValues);
    std::cout << std::endl;

    auto danEigenValues = LinAlg::danilevsky(A);
    std::cout << "Danilevsky eigenvalues" << std::endl;
    print(danEigenValues);
    std::cout << std::endl;

    LinAlg::Vector<double> y0 = {0, 0, 1, 0};
    auto krylovEigenValues = LinAlg::krylov(A, y0);
    std::cout << "Krylov eigenvalues" << std::endl;
    print(krylovEigenValues);

    return 0;
}