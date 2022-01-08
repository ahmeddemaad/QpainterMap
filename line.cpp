#include "line.h"


Line::Line(string name, int arr[4]):Shape(name,arr)
{

}

double Line::getPerimeter() const
{
    return getLengthBetweenPoints();
}

bool Line::operator <(const Line other) const
{
    return (getPerimeter() < other.getPerimeter());
}

