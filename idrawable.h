/*
 * Interface provides method draw() for futher reimplementing in derived classes.
 *
 */

#pragma once

#include <QRect>
#include <QPainter>
#include <QDebug>
#include <iostream>
#include <memory>

enum class ShapesId;

class IDrawable
{
public:

    IDrawable();
    virtual ~IDrawable() = default;

    virtual void draw(QPainter *painter) = 0;

    void setFrameColor(const QColor &val);
    QColor getFrameColor() const;

    void setFrameWidth(const int &val);
    int getFrameWidth() const;

    virtual void startDerivation(const QPoint &start) = 0;
    virtual void endDerivation(const QPoint &start) = 0;

protected:

    QColor _frameColor;
    int _frameWidth;
};
