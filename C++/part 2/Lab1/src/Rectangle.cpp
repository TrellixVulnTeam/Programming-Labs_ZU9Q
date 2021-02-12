#include <stdexcept>
#include "Rectangle.h"

Rectangle::Rectangle(double width, double height)
{
    if (width > 0 && height > 0)
    {
        this->width = width;
        this->height = height;
    }
    else
    {
        throw std::invalid_argument("Width and height must be greater than 0");
    }
}

double Rectangle::getHeight() const noexcept
{
    return height;
}

double Rectangle::getWidth() const noexcept
{
    return width;
}

void Rectangle::setHeight(double height)
{
    if (height > 0)
        this->height = height;
    else
        throw std::invalid_argument("Height must be greater than 0");
}

void Rectangle::setWidth(double width)
{
    if (width > 0)
        this->width = width;
    else
        throw std::invalid_argument("Width must be greater than 0");
}

double Rectangle::areaSize() const noexcept
{
    return height * width;
}

bool Rectangle::isSquare() const noexcept
{
    return height == width;
}