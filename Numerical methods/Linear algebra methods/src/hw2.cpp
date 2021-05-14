#include <iostream>
#include <iomanip>

#include "Utils.h"
#include "Matrix.h"
#include "MatrixUtils.h"

int main()
{
    LinAlg::Matrix<double> mat = {{3, 7, 1},
                                  {2, 0, 1},
                                  {1, 2, 6}};

    print(mat);
    std::cout << std::endl;

    std::cout << std::setprecision(6); //specify precision

    auto inv = LinAlg::inverse(mat);
    std::cout << "Inverse" << std::endl;
    print(inv);
    std::cout << std::endl;

    std::cout << "Check" << std::endl;
    print(inv * mat);
    std::cout << std::endl;

    auto det = LinAlg::det(mat);
    std::cout << "Det: " << det << std::endl;

    return 0;
}
