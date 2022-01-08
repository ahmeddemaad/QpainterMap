#ifndef DRAWPANEL_H
#define DRAWPANEL_H

#include <QWidget>
#include <QMouseEvent>
#include <QPainter>
#include <QFileDialog>
#include <QtCore/QStack>
#include <QtCore/QVariant>
#include <bits/stdc++.h>
#include <circle.h>
#include <line.h>
#include <rectangle.h>
#include <enternamedialog.h>
#include <QInputDialog>

class DrawPanel : public QWidget //inheritance.
{
    Q_OBJECT //to access Qwidget.
public:
    explicit DrawPanel(QWidget *parent = nullptr);
    ~DrawPanel() override;

    virtual void mousePressEvent(QMouseEvent *event) override;
    virtual void mouseMoveEvent(QMouseEvent *event) override;
    virtual void mouseReleaseEvent(QMouseEvent *event) override;
    virtual void paintEvent(QPaintEvent *event) override;
    virtual void resizeEvent(QResizeEvent *event) override;

    void start();

    bool openImage();

    QImage getImage();
    void setImage(QImage image);

    void resize(int w, int h);

    void clear();

    void setBrushWidth (int setBrushWidth);

    void setColor(QColor setColor);
    QColor getColor();

    QColor getPrevColor() const;
    void setPrevColor(const QColor &value);

    Qt::PenStyle getPenStyle() const;
    void setPenStyle(const Qt::PenStyle &value);

    Qt::PenCapStyle getCapStyle() const;
    void setCapStyle(const Qt::PenCapStyle &value);

    Qt::PenJoinStyle getJoinStyle() const;
    void setJoinStyle(const Qt::PenJoinStyle &value);

    bool getIsRectangle() const;
    void setIsRectangle(bool value);

    bool getIsCircle() const;
    void setIsCircle(bool value);

    bool getIsStraightLine() const;
    void setIsStraightLine(bool value);

    bool getIsFilling() const;
    void setIsFilling(bool value);

    QColor getFillColor() const;
    void setFillColor(const QColor &value);

    QImage getCopyDrawing() const;
    void setCopyDrawing(const QImage &value);

    void undo();
    void redo();
    void search();
    void deleteShape();

    QMap<QString,Shape> shapesMap;
    QMap<QString,Shape> BackShapeMap;

    static stack <QString> stackUndo;
    static stack <QString> stackRedo;

private:
    QImage drawPanel;
    QImage copyDrawing;
    QPoint lastPoint;
    int x2;
    int y2;
    QPoint firstPoint;
    int x1 ;
    int y1 ;
    float raduis ;
    QColor currentColor;
    QColor prevColor;
    QColor fillColor;
    Qt::PenStyle penStyle;
    Qt::PenCapStyle capStyle;
    Qt::PenJoinStyle joinStyle;

    int brushWidth;
    bool isDrawing;
    bool isRectangle;
    bool isCircle;
    bool isStraightLine;
    bool isFilling;
    bool mousePressed;

    QString temp ;

};

#endif // DRAWPANEL_H
