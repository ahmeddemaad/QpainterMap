#ifndef CIRCLE_H
#define CIRCLE_H

#include <shape.h>

class Circle:public Shape
{
public:
    Circle(string name,int coordinates[4]);
    double getArea()const;
    double getPerimeter()const;
    bool operator <(const Circle other) const;


};

#endif // CIRCLE_H
