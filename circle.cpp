#include "circle.h"
#include <QtMath>


Circle::Circle(string name, int coordinates[]):Shape(name,coordinates)
{

}

double Circle::getArea() const
{
    return(M_PI * pow(getLengthBetweenPoints(),2));
}

double Circle::getPerimeter() const
{
    return(2 * M_PI * getLengthBetweenPoints());
}

bool Circle::operator <(const Circle other) const
{
    return (getPerimeter() < other.getPerimeter());
}
