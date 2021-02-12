#include <gtest/gtest.h>
#include <iostream>
#include <stdexcept>
#include "../src/Array.h"

TEST(ArrayTests, push_back)
{
    Array<int> array;
    int a = 5, b = 60;

    array.push_back(a);

    ASSERT_EQ(array.size(), 1);
}

TEST(ArrayTests, remove)
{
    Array<int> array;
    int a = 48, b = 60;

    array.push_back(a);
    array.push_back(b);

    array.remove(1);

    EXPECT_EQ(array.size(), 1);
    EXPECT_EQ(array[0], a);
}

TEST(ArrayTests, update)
{
    Array<int> array;
    int a = 48, b = 60, c = 70;

    array.push_back(a);
    array.push_back(b);

    array.update(1, c);

    ASSERT_EQ(array[1], c);
}

TEST(ArrayTests, find)
{
    Array<int> array;
    int a = 48, b = 60, c = 70;

    array.push_back(a);
    array.push_back(b);
    array.push_back(c);

    auto pos = array.find(b);

    ASSERT_EQ(pos, 1);
}

TEST(ArrayTests, clear)
{
    Array<int> array;
    int a = 48, b = 60;

    array.push_back(a);
    array.push_back(b);
    array.clear();

    EXPECT_EQ(array.size(), 0);
    EXPECT_THROW(array[0], std::invalid_argument);
}

TEST(ArrayTests, output)
{
    Array<int> array;
    Array<int> array2;

    int a = 48, b = 60;

    array.push_back(a);
    array.push_back(b);
    array2.push_back(b);
    array2.push_back(a);

    std::ostringstream stream;
    stream << array << array2;
    std::string output = stream.rdbuf()->str();

    ASSERT_EQ(output, "48\n60\n60\n48\n");
}

TEST(ArrayTests, input)
{
    Array<int> array(2);
    Array<int> array2(2);

    std::stringstream stream;
    stream << 4 << std::endl;

#ifdef IGNORE_INVALID_STREAM_VALUE
    stream << "invalid value" << std::endl;
#endif

    stream << 5 << std::endl;
    stream >> array;
    stream << 6 << std::endl;
    stream << 7 << std::endl;
    stream >> array2;

    EXPECT_EQ(array[0], 4);
    EXPECT_EQ(array2[0], 6);
    EXPECT_EQ(array[1], 5);
    EXPECT_EQ(array2[1], 7);
}

TEST(ArrayTests, scale)
{
    Array<int> array(1);
    int a = 4, b = 5;

    array.push_back(a);
    array.push_back(b);

    EXPECT_EQ(array.size(), 2);
    EXPECT_EQ(array[0], 4);
    EXPECT_EQ(array[1], 5);
}

TEST(ArrayTests, indexingCorrect)
{
    Array<int> array;
    int a = 48, b = 60;

    array.push_back(a);
    array.push_back(b);

    EXPECT_EQ(a, array[0]);
    EXPECT_EQ(b, array[1]);
}

TEST(ArrayTests, indexingInCorrect)
{
    Array<int> array;
    int a = 48, b = 60;

    array.push_back(a);
    array.push_back(b);

    ASSERT_THROW(array[3], std::invalid_argument);
}

TEST(ArrayTests, plusCorrect)
{
    Array<int> array1;
    Array<int> array2;

    int a = 48, b = 60, c = 12, d = -10;

    array1.push_back(a);
    array1.push_back(b);
    array2.push_back(c);
    array2.push_back(d);

    Array<int> array3 = array1 + array2;

    EXPECT_EQ(array3.size(), 2);
    EXPECT_EQ(array3[0], a + c);
    EXPECT_EQ(array3[1], b + d);
}

TEST(ArrayTests, productCorrect)
{
    Array<int> array1;
    Array<int> array2;

    int a = 48, b = 60, c = 12, d = -10;

    array1.push_back(a);
    array1.push_back(b);
    array2.push_back(c);
    array2.push_back(d);

    Array<int> array3 = array1 * array2;

    EXPECT_EQ(array3.size(), 2);
    EXPECT_EQ(array3[0], a * c);
    EXPECT_EQ(array3[1], b * d);
}

TEST(ArrayTests, plusInCorrect)
{
    Array<int> array1;
    Array<int> array2;

    int a = 48, b = 60, c = 12;

    array1.push_back(a);
    array1.push_back(b);
    array2.push_back(c);

    ASSERT_THROW(array1 + array2, std::invalid_argument);
}

TEST(ArrayTests, productInCorrect)
{
    Array<int> array1;
    Array<int> array2;

    int a = 48, b = 60, c = 12;

    array1.push_back(a);
    array1.push_back(b);
    array2.push_back(c);

    ASSERT_THROW(array1 * array2, std::invalid_argument);
}

class Hard
{
public:
    Hard(double A, double B)
    {
        _a = A;
        _b = B;
    }

    double a() const noexcept
    {
        return _a;
    }

    double b() const noexcept
    {
        return _b;
    }

    Hard operator+(const Hard &h2) noexcept
    {
        return Hard(h2._a + _a, h2._b + _b);
    }

    Hard operator*(const Hard &h2) noexcept
    {
        return Hard(h2._a * _a, h2._b * _b);
    }

private:
    double _a;
    double _b;
};

TEST(ArrayTests, hardTemplate)
{
    Array<Hard> array;

    Hard h1 = Hard(4.0, 5.0);
    array.push_back(h1);
    Array<Hard> summ = array + array;

    EXPECT_EQ(summ.size(), 1);
    EXPECT_EQ(summ[0].a(), 8);
    EXPECT_EQ(summ[0].b(), 10);
}