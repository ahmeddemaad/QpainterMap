#include "rectangle.h"


Rectangle::Rectangle(string name, int coordinates[],QRect physicalShape):Shape(name,coordinates,physicalShape)
{
    this->physicalShape = physicalShape;
}
QRect Rectangle::GetphysicalShape() const{
    return physicalShape ;
}

double Rectangle::getPerimeter() const
{
    return(2 * abs(coordinates[0] - coordinates[1]) + 2 * abs(coordinates[2] - coordinates[3]));
}

double Rectangle::getArea() const
{
    return(abs(coordinates[0] - coordinates[1]) * abs(coordinates[2] - coordinates[3]));
}

bool Rectangle::operator <(const Rectangle other) const
{
    return (getPerimeter() < other.getPerimeter());
}
