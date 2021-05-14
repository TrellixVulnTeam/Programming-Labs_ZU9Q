#pragma once

#include <unordered_map>

#include "Vector.h"
#include "Matrix.h"

namespace LinAlg
{
    template<typename T>
    class MatrixView : public IMatrix<T>
    {
    public:
        explicit MatrixView(IMatrix<T> &matrix)
        {
            this->_matrix = &matrix;
            this->_nrow = matrix.nrow();
            this->_ncol = matrix.ncol();
        }

        const T& operator()(size_t i, size_t j) const override
        {
            return this->_matrix->operator()(this->getRow(i), j);
        }

        T& operator()(size_t i, size_t j) override
        {
            return this->_matrix->operator()(this->getRow(i), j);
        }

        void swapRows(size_t i, size_t j)
        {
            if (i == j)
                return;

            size_t iNew, jNew;

            auto it = _rowMap.find(i);
            if (it != _rowMap.end())
                jNew = it->second;
            else
                jNew = i;

            it = _rowMap.find(j);
            if (it != _rowMap.end())
                iNew = it->second;
            else
                iNew = j;

            _rowMap.insert({i, iNew});
            _rowMap.insert({j, jNew});
        }

    protected:
        size_t getRow(size_t i) const noexcept
        {
            auto it = _rowMap.find(i);
            if (it != _rowMap.end())
                i = it->second;

            return i;
        }

        std::unordered_map<size_t, size_t> _rowMap;
        IMatrix<T>* _matrix;
    };

    template <typename T>
    class TransposeView : public MatrixView<T>
    {
    public:
        explicit TransposeView(IMatrix<T> &matrix) : MatrixView<T>(matrix)
        {
            this->_ncol = matrix.nrow();
            this->_nrow = matrix.ncol();
        }

        T &operator()(size_t i, size_t j) override
        {
            if (j >= this->_nrow || i >= this->_ncol)
                throw std::invalid_argument("Position is out of range");
            return this->_matrix->operator()(this->getRow(j), i);
        }

        const T& operator()(size_t i, size_t j) const override
        {
            if (j >= this->_nrow || i >= this->_ncol)
                throw std::invalid_argument("Position is out of range");
            return this->_matrix->operator()(this->getRow(j), i);
        }
    };

    template<typename T>
    class MatrixMatrixView : public MatrixView<T>
    {
    public:
        MatrixMatrixView(IMatrix<T> &matrix1, IMatrix<T> &matrix2) : MatrixView<T>(matrix1)
        {
            if (matrix1.nrow() != matrix2.nrow())
                throw std::invalid_argument("Invalid shapes");

            this->_matrix2 = &matrix2;
            this->_ncol = matrix1.ncol() + matrix2.ncol();
        }

        const T& operator()(size_t i, size_t j) const override
        {
            if (j >= this->_ncol)
                throw std::invalid_argument("Position is out of range");

            if (j >= this->_matrix->ncol())
            {
                return this->_matrix2->operator()(this->getRow(i), j - this->_matrix->ncol());
            }

            return this->_matrix->operator()(i, j);
        }

        T& operator()(size_t i, size_t j) override
        {
            if (j >= this->_ncol)
                throw std::invalid_argument("Position is out of range");

            if (j >= this->_matrix->ncol())
            {
                return this->_matrix2->operator()(this->getRow(i), j - this->_matrix->ncol());
            }

            return this->_matrix->operator()(i, j);
        }

    private:
        IMatrix<T>* _matrix2;
    };

    template<typename T>
    class MatrixVectorView : public MatrixView<T>
    {
    public:
        MatrixVectorView(IMatrix<T> &matrix, Vector<T> &vector): MatrixView<T>(matrix)
        {
            if (matrix.nrow() != vector.nval())
                throw std::invalid_argument("Invalid shapes");

            _vector = &vector;
            this->_ncol = matrix.ncol() + 1;
        }

        const T& operator()(size_t i, size_t j) const override
        {
            if (j >= this->_ncol)
                throw std::invalid_argument("Position is out of range");

            i = this->getRow(i);
            if (j >= this->_matrix->ncol())
            {
                return _vector->operator()(i);
            }

            return this->_matrix->operator()(i, j);
        }

        T& operator()(size_t i, size_t j) override
        {
            if (j >= this->_ncol)
                throw std::invalid_argument("Position is out of range");

            i = this->getRow(i);
            if (j >= this->_matrix->ncol())
            {
                return _vector->operator()(i);
            }

            return this->_matrix->operator()(i, j);
        }

    private:
        Vector<T>* _vector;
    };

    template<typename T>
    size_t getMaxRowPivotIndex(const IMatrix<T> &mat, size_t i = 0)
    {
        auto max = i;
        for (size_t l = i + 1; l < mat.nrow(); l++)
        {
            if (std::abs(mat(l, i)) > std::abs(mat(max, i)))
                max = l;
        }
        return max;
    }
}