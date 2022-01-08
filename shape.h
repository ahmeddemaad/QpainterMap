#ifndef SHAPE_H
#define SHAPE_H

#include <bits/stdc++.h>
#include <QRect>
using namespace std;

class Shape
{
protected:
    int coordinates[4];
    string name;
    QRect physicalShape;
    double getLengthBetweenPoints()const;

public:
    virtual double getArea() const{}
    virtual double getPerimeter() const{}
    virtual bool operator < (const Shape other) const{}
    Shape(string name,int arr[4],QRect physical);
    Shape(string name,int arr[4]);
    Shape();
    int *getCoordinates();
    string getName() const;
    void setName(string name);
    QRect getphysicalShape() const ;

};

#endif // SHAPE_H
