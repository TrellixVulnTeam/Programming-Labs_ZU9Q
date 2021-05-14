#pragma once

#include "vector"
#include "initializer_list"

namespace LinAlg
{
    template<typename T>
    class Polynomial
    {
    private:
        std::vector<T> m_coeffs;

        void shrinkToFit()
        {
            while (m_coeffs.back() == 0 && m_coeffs.size() > 1)
                m_coeffs.pop_back();
            m_coeffs.shrink_to_fit();
        }

        template<typename U>
        U pow(U value, int n) const
        {
            if (n == 0)
                return 1;
            if (n == 1)
                return value;
            return value * pow(value, n - 1);
        }

    public:
        explicit Polynomial(std::vector<T> coeffs) : m_coeffs(coeffs)
        {
            shrinkToFit();
        }

        Polynomial(std::initializer_list<T> initializerList) : m_coeffs(initializerList)
        {
            shrinkToFit();
        }

        [[nodiscard]] inline int degree() const noexcept
        {
            return m_coeffs.size() - 1;
        }

        template<typename U>
        auto operator()(U value) const
        {
            using ret_type = std::common_type_t<U, T>;
            ret_type result{};

            for (int i = 0; i < m_coeffs.size(); i++)
            {
                result += pow(value, i) * m_coeffs[i];
            }

            return result;
        }

        Polynomial derivate() const
        {
            std::vector<T> derivCoeffs;
            derivCoeffs.reserve(m_coeffs.size() - 1);

            for (int i = 1; i < m_coeffs.size(); i++)
            {
                derivCoeffs.push_back(i * m_coeffs[i]);
            }

            return Polynomial(derivCoeffs);
        }

        auto divmod(const Polynomial &poly) const
        {
            Polynomial mod = *this;
            std::vector<T> divCoeffs;

            const auto &divider = poly.m_coeffs[poly.degree()];
            while (mod.degree() >= poly.degree())
            {
                auto coeff = mod.m_coeffs[mod.degree()] / divider;
                divCoeffs.push_back(coeff);

                for (int i = 0; i < poly.degree(); i++)
                {
                    auto &modCoeff = mod.m_coeffs[mod.degree() - 1 - i];
                    modCoeff = modCoeff - coeff * poly.m_coeffs[poly.degree() - 1 - i];
                }

                mod.m_coeffs.pop_back();
            }

            mod.shrinkToFit();
            return std::make_tuple(Polynomial(divCoeffs), mod);
        }

        Polynomial operator%(const Polynomial &poly) const
        {
            auto[div, mod] = divmod(poly);
            return mod;
        }

        Polynomial operator/(const Polynomial &poly) const
        {
            auto[div, _] = divmod(poly);
            return div;
        }

        Polynomial operator-(const Polynomial &poly) const
        {
            std::vector<T> coeffs;
            if (poly.degree() > degree())
            {
                for (int i = 0; i < m_coeffs.size(); i++)
                    coeffs.push_back(m_coeffs[i] - poly.m_coeffs[i]);
                for (int i = degree() + 1; i < poly.m_coeffs.size(); i++)
                    coeffs.push_back(-poly.m_coeffs[i]);
            } else
            {
                for (int i = 0; i < poly.m_coeffs.size(); i++)
                    coeffs.push_back(m_coeffs[i] - poly.m_coeffs[i]);
                for (int i = poly.degree() + 1; i < m_coeffs.size(); i++)
                    coeffs.push_back(m_coeffs[i]);
            }

            return Polynomial(coeffs);
        }

        template<typename U>
        friend Polynomial<U> operator-(const Polynomial<U> &);
    };

    template<typename T>
    Polynomial<T> operator-(const Polynomial<T> &poly)
    {
        auto result = poly;
        for (auto &coeff: result.m_coeffs)
        {
            coeff = -coeff;
        }
        return result;
    }
}
