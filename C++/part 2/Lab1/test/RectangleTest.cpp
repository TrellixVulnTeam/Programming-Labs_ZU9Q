#include <gtest/gtest.h>
#include <stdexcept>
#include "../src/Rectangle.h"

//lab requires explicit example of use object and pointer to object -> 2 kind of tests

TEST(RectangleTest, createRectAsObjectWithArgs)
{
    Rectangle rect = Rectangle(15, 15);
    EXPECT_DOUBLE_EQ(rect.getWidth(), 15);
    EXPECT_DOUBLE_EQ(rect.getHeight(), 15);
}

TEST(RectangleTest, createRectAsPointerWithArgs)
{
    Rectangle *rect = new Rectangle(15, 15);

    EXPECT_TRUE(rect);
    EXPECT_DOUBLE_EQ(rect->getWidth(), 15);
    EXPECT_DOUBLE_EQ(rect->getHeight(), 15);

    delete rect;
}

TEST(RectangleTest, getWidhtAsObject)
{
    Rectangle rect = Rectangle(18, 20);
    ASSERT_DOUBLE_EQ(rect.getWidth(), 18);
}

TEST(RectangleTest, getWidhtAsPointer)
{
    Rectangle *rect = new Rectangle(18, 20);
    ASSERT_DOUBLE_EQ(rect->getWidth(), 18);
    delete rect;
}

TEST(RectangleTest, getHeightAsObject)
{
    Rectangle rect = Rectangle(18, 20);
    ASSERT_DOUBLE_EQ(rect.getHeight(), 20);
}

TEST(RectangleTest, getHeightAsPointer)
{
    Rectangle *rect = new Rectangle(18, 20);
    ASSERT_DOUBLE_EQ(rect->getHeight(), 20);
    delete rect;
}

TEST(RectangleTest, setCorrectWidthAsObject)
{
    Rectangle rect = Rectangle(18, 20);
    rect.setWidth(30);
    ASSERT_DOUBLE_EQ(rect.getWidth(), 30);
}

TEST(RectangleTest, setCorrectWidthAsPointer)
{
    Rectangle *rect = new Rectangle(18, 20);

    rect->setWidth(30);

    ASSERT_DOUBLE_EQ(rect->getWidth(), 30);
    delete rect;
}

TEST(RectangleTest, setInCorrectWidthAsObject)
{
    Rectangle rect = Rectangle(18, 20);
    ASSERT_THROW(rect.setWidth(-4);, std::invalid_argument);
}

TEST(RectangleTest, setInCorrectWidthAsPointer)
{
    Rectangle *rect = new Rectangle(18, 20);
    ASSERT_THROW(rect->setWidth(-4);, std::invalid_argument);
    delete rect;
}

TEST(RectangleTest, setCorrectHeightAsObject)
{
    Rectangle rect = Rectangle(18, 20);
    rect.setHeight(30);
    ASSERT_DOUBLE_EQ(rect.getHeight(), 30);
}

TEST(RectangleTest, setCorrectHeightAsPointer)
{
    Rectangle *rect = new Rectangle(18, 20);
    rect->setHeight(30);
    ASSERT_DOUBLE_EQ(rect->getHeight(), 30);
    delete rect;
}

TEST(RectangleTest, setInCorrectHeightAsObject)
{
    Rectangle rect = Rectangle(18, 20);
    ASSERT_THROW(rect.setHeight(-4), std::invalid_argument);
}

TEST(RectangleTest, setInCorrectHeightAsPointer)
{
    Rectangle *rect = new Rectangle(18, 20);
    ASSERT_THROW(rect->setHeight(-4), std::invalid_argument);
    delete rect;
}

TEST(RectangleTest, areaSizeAsObject)
{
    Rectangle rect = Rectangle(18, 20);
    ASSERT_DOUBLE_EQ(rect.areaSize(), 18 * 20);
}

TEST(RectangleTest, areaSizeAsPointer)
{
    Rectangle *rect = new Rectangle(18, 20);
    ASSERT_DOUBLE_EQ(rect->areaSize(), 18 * 20);
    delete rect;
}

TEST(RectangleTest, isSquareAsObject)
{
    Rectangle rect = Rectangle(20, 20);
    EXPECT_TRUE(rect.isSquare());

    rect.setHeight(4);
    rect.setWidth(4);

    EXPECT_TRUE(rect.isSquare());
}

TEST(RectangleTest, isSquareAsPointer)
{
    Rectangle *rect = new Rectangle(20, 20);
    EXPECT_TRUE(rect->isSquare());

    rect->setHeight(4);
    rect->setWidth(4);

    EXPECT_TRUE(rect->isSquare());
    delete rect;
}

TEST(RectangleTest, isNotSquareAsObjectIncorrectWidth)
{
    Rectangle rect = Rectangle(20, 20);
    rect.setWidth(4);
    ASSERT_FALSE(rect.isSquare());
}

TEST(RectangleTest, isNotSquareAsPointerIncorrectWidth)
{
    Rectangle *rect = new Rectangle(20, 20);

    rect->setWidth(4);

    ASSERT_FALSE(rect->isSquare());
    delete rect;
}

TEST(RectangleTest, isNotSquareAsObjectIncorrectHeight)
{
    Rectangle rect = Rectangle(20, 20);
    rect.setHeight(4);
    ASSERT_FALSE(rect.isSquare());
}

TEST(RectangleTest, isNotSquareAsPointerIncorrectHeight)
{
    Rectangle *rect = new Rectangle(20, 20);

    rect->setHeight(4);

    ASSERT_FALSE(rect->isSquare());
    delete rect;
}