#include <gtest/gtest.h>
#include <iostream>
#include "../src/FixedArray.h"

TEST(FixedArrayTests, push_back)
{
    FixedArray<int> farray(10, 20);
    int a = 15, b = 20;

    farray.push_back(a);
    farray.push_back(b);

    ASSERT_EQ(farray.size(), 2);
}

TEST(FixedArrayTests, output)
{
    FixedArray<int> farray(10, 20);
    int a = 15, b = 20;

    farray.push_back(a);
    farray.push_back(b);

    std::ostringstream stream;
    stream << farray;
    std::string output = stream.rdbuf()->str();

    ASSERT_EQ(output, "15\n20\n");
}

TEST(FixedArrayTests, copyCtor)
{
    FixedArray<int> farray(10, 20);
    int a = 15, b = 20, c = 12;

    farray.push_back(a);
    farray.push_back(b);
    farray.push_back(c);

    FixedArray<int> cfarray = farray;
    cfarray.update(1, a);

    ASSERT_NE(cfarray[1], farray[1]);
}

TEST(FixedArrayTests, plus)
{
    FixedArray<int> array1(30, 66);
    FixedArray<int> array2(-10, 15);

    int a = 48, b = 60, c = 12, d = -10;

    array1.push_back(a);
    array1.push_back(b);
    array2.push_back(c);
    array2.push_back(d);

    FixedArray<int> array3 = array1 + array2;

    EXPECT_EQ(array3.size(), 2);
    EXPECT_EQ(array3[0], a + c);
    EXPECT_EQ(array3[1], b + d);
    EXPECT_EQ(array3.min(), 30-10);
    EXPECT_EQ(array3.max(), 66+15);
}

TEST(FixedArrayTests, product)
{
    FixedArray<int> array1(30, 66);
    FixedArray<int> array2(-10, 15);

    int a = 48, b = 60, c = 12, d = -10;

    array1.push_back(a);
    array1.push_back(b);
    array2.push_back(c);
    array2.push_back(d);

    FixedArray<int> array3 = array1 * array2;

    EXPECT_EQ(array3.size(), 2);
    EXPECT_EQ(array3[0], a * c);
    EXPECT_EQ(array3[1], b * d);
    EXPECT_EQ(array3.min(), -66*10);
    EXPECT_EQ(array3.max(), 66*15);
}

TEST(FixedArrayTests, input)
{
    FixedArray<int> array(4, 7, 2);
    FixedArray<int> array2(-1, 10, 2);

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
