#ifndef RECTANGLE_H
#define RECTANGLE_H

class Rectangle
{
public:
    //ctors
    Rectangle(double width, double height);

    //Fields methods
    double getHeight() const noexcept;
    double getWidth() const noexcept;
    void setHeight(double);
    void setWidth(double);

    //Additional functionality
    double areaSize() const noexcept;
    bool isSquare() const noexcept;

private:
    double height;
    double width;
};

#endif