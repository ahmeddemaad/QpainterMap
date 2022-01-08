#include "shape.h"


double Shape::getLengthBetweenPoints() const
{
    int x1 = coordinates[0];
    int x2 = coordinates[1];
    int y1 = coordinates[2];
    int y2 = coordinates[3];
    return (sqrt( pow((x2 - x1),2) + pow((y2 - y1),2)));
}

Shape::Shape(string name, int arr[],QRect physical)
{
    this->name = name;
    for(int i=0;i<4;i++)
        coordinates[i] = arr[i];

      physicalShape=physical ;
}

Shape::Shape(string name, int arr[])
{
    this->name = name;
    for(int i=0;i<4;i++)
        coordinates[i] = arr[i];

}

Shape::Shape()
{
    name = "";
    for(int i=0;i<4;i++)
        coordinates[i] = 0;

}

int *Shape::getCoordinates()
{
    return coordinates;
}

string Shape::getName() const
{
    return name;
}

void Shape::setName(string name)
{
    this->name = name;
}

QRect Shape::getphysicalShape() const{
    return physicalShape;
}
