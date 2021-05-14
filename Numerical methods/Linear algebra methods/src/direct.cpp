#include <iostream>
#include <iomanip>

#include "Matrix.h"
#include "Vector.h"
#include "Solvers.h"
#include "Utils.h"

int main()
{
    LinAlg::Matrix<double> mat = {{5.5, 7,    6,    5.5},
                                  {7,   10.5, 8,    7},
                                  {6,   8,    10.5, 9},
                                  {5.5, 7,    9,    10.5}};

    std::cout << "Matrix A" << std::endl;
    print(mat);
    std::cout << std::endl;

    LinAlg::Vector<int> vec = {23, 32, 33, 31};

    std::cout << "Vector b" << std::endl;
    print(vec);
    std::cout << std::endl;

    std::cout << std::setprecision(16); //specify precision

    auto xch = LinAlg::choleskySolve(mat, vec);
    std::cout << "Roots cholesky" << std::endl;
    print(xch);

    auto res = mat * xch - vec;
    std::cout << "cholesky res" << std::endl;
    printAbs(res);
    std::cout << std::endl;

    auto xld = LinAlg::ldlSolve(mat, vec);
    std::cout << "Roots LDL" << std::endl;
    print(xld);

    res = mat * xld - vec;
    std::cout << "LDL res" << std::endl;
    printAbs(res);
    std::cout << std::endl;

    auto xgj = LinAlg::gaussJordanSolve(mat, vec);
    std::cout << "Gauss-Jordan" << std::endl;
    print(xgj);

    res = mat * xgj - vec;
    std::cout << "Gauss Jordan res" << std::endl;
    printAbs(res);
    std::cout << std::endl;

    auto xg = LinAlg::gaussSolve(mat, vec);
    std::cout << "Gauss" << std::endl;
    print(xg);

    res = mat * xg - vec;
    std::cout << "Gauss res" << std::endl;
    printAbs(res);
    std::cout << std::endl;

    auto xgp = LinAlg::gaussPivotSolve(mat, vec);
    std::cout << "Gauss with pivot" << std::endl;
    print(xgp);

    res = mat * xgp - vec;
    std::cout << "Gauss with pivot res" << std::endl;
    printAbs(res);

    return 0;
}