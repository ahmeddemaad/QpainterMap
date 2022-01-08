#include "drawpanel.h"
#include "enternamedialog.h"
#include <QImage>
#include <QMessageBox>
#include <QMouseEvent>
#include <QPainter>
#include <QPainterPath>
#include <QtDebug>

stack <QString> DrawPanel::stackUndo;
stack <QString> DrawPanel::stackRedo;


DrawPanel::DrawPanel(QWidget *parent) : QWidget(parent)
{
    start();
}


DrawPanel::~DrawPanel() {}


void DrawPanel::start()
{
    drawPanel = QImage(this->size(), QImage::Format_RGB32);
    drawPanel.fill(Qt::white);
    setColor(Qt::black);
    setFillColor(Qt::black);
    setBrushWidth(3);
    setPenStyle(Qt::SolidLine);
    setCapStyle(Qt::RoundCap);
    setJoinStyle(Qt::RoundJoin);
    setIsCircle(false);
    setIsRectangle(false);
    setIsStraightLine(false);
    setIsFilling(false);
    mousePressed = false;
}


bool DrawPanel::openImage()
{
    QString openImageLocation = QFileDialog::getOpenFileName(this, tr("Open image"), "", tr("PNG (*.png);;JPEG (*.jpg *.jpeg);;BMP (*.bmp)" ));
    if(!openImageLocation.isEmpty())
    {
        drawPanel.load(openImageLocation);
        return true;
    }
    else
    {
        return false;
    }
}


void DrawPanel::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        firstPoint = event->pos();
        x1=firstPoint.x();
        y1=firstPoint.y();
        lastPoint = event->pos();
        x2=lastPoint.x();
        y2=lastPoint.y();
        isDrawing = true;
        mousePressed = true;

    }
    update();
}


void DrawPanel::mouseMoveEvent(QMouseEvent *event)
{
    if ((event->buttons() & Qt::LeftButton) && isDrawing)
    {
        lastPoint = event->pos();
    }
    update();
}


void DrawPanel::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton && isDrawing)
    {
        isDrawing = false;
        mousePressed = false;

        if(getIsRectangle())
        {
            int arr[] = {firstPoint.x(),firstPoint.y(),lastPoint.x(),lastPoint.y()};

            bool ok;
            QString rectangleName = QInputDialog::getText(this,tr("String"),tr("Enter shape name:"),QLineEdit::Normal,tr("Rectangle"),&ok );
            if( ok && !rectangleName.isEmpty() )
            {
                shapesMap[rectangleName] = Rectangle(rectangleName.toStdString(),arr,QRect(firstPoint,lastPoint));
                BackShapeMap[rectangleName] = Rectangle(rectangleName.toStdString(),arr,QRect(firstPoint,lastPoint));
                stackUndo.push(rectangleName);
                temp = rectangleName ;

                qDebug() << shapesMap.keys();

            }
        }
        else if(getIsCircle())
        {
            int arr[] = {firstPoint.x(),firstPoint.y(),lastPoint.x(),lastPoint.y()};

            bool ok;
            QString circleName = QInputDialog::getText(this,tr("String"),tr("Enter shape name:"),QLineEdit::Normal,tr("Circle"),&ok );
            if( ok && !circleName.isEmpty() )
            {
                shapesMap[circleName] = Circle(circleName.toStdString(),arr);
                BackShapeMap[circleName] = Circle(circleName.toStdString(),arr);
                stackUndo.push(circleName);
                temp = circleName;

                qDebug() << shapesMap.keys();

            }
        }
        else if(getIsStraightLine())
        {
            int arr[] = {firstPoint.x(),firstPoint.y(),lastPoint.x(),lastPoint.y()};

            bool ok;
            QString lineName = QInputDialog::getText(this,tr("String"),tr("Enter shape name:"),QLineEdit::Normal,tr("Line"),&ok );
            if( ok && !lineName.isEmpty())
            {
                shapesMap[lineName] = Line(lineName.toStdString(),arr);
                BackShapeMap[lineName] = Line(lineName.toStdString(),arr);
                stackUndo.push(lineName);
                temp = lineName;

                qDebug() << shapesMap.keys();

            }
        }
    }

    update();
}


void DrawPanel::paintEvent(QPaintEvent *event)
{
    static bool wasMousePressed = false; //selects the shape.

    QRect rectArea = event->rect();
    QPainter painter(this);
    painter.drawImage(rectArea, drawPanel, rectArea); //Drawer. Allocates a place to draw in.

    if(mousePressed)
    {
        wasMousePressed = true;

        if (getIsCircle())
        {
            raduis = abs(sqrt(pow(lastPoint.x()-firstPoint.x(),2)+pow(lastPoint.y()-firstPoint.y(),2)));
            QRect circle = QRect(firstPoint, lastPoint); //determines the circle and draws it.
            QPainter circlePainter(this);
            circlePainter.setPen(QPen(currentColor,brushWidth,penStyle,capStyle,joinStyle)); //el shadda lonha mo5talef.
            circlePainter.drawEllipse(firstPoint.x(),firstPoint.y(),raduis,raduis); //for dynamic interaction.
            if(isFilling)
            {
                QBrush fillbrush(fillColor);
                QPainterPath path;
                path.addEllipse(firstPoint.x(),firstPoint.y(),raduis,raduis);
                painter.fillPath(path, fillbrush);
            }
        }
        else if (getIsRectangle())
        {
            QRect rect = QRect(firstPoint, lastPoint);
            QPainter rectanglePainter(this);
            rectanglePainter.setPen(QPen(currentColor,brushWidth,penStyle,capStyle,joinStyle));
            rectanglePainter.drawRect(rect);
            if (isFilling)
            {
                QBrush fillbrush(fillColor);
                QPainterPath path;
                path.addRoundedRect(rect,brushWidth, brushWidth);
                painter.fillPath(path,fillbrush);
            }
        }

        else if(getIsStraightLine())

        {
            QRect StraightLine = QRect(firstPoint, lastPoint); //determines the ST and draws it.
            QPainter StraightLinePainter(this);
            StraightLinePainter.setPen(QPen(currentColor,brushWidth,penStyle,capStyle,joinStyle)); //el shadda lonha mo5talef.
            StraightLinePainter.drawLine(firstPoint, lastPoint); //for dynamic interaction.
        }


        else
        {
            QPainter pencilPainter(&drawPanel);
            pencilPainter.setPen(QPen(currentColor,brushWidth,penStyle,capStyle,joinStyle));
            pencilPainter.drawLine(lastPoint, firstPoint);
            firstPoint = lastPoint;
        }

    }
    //----------------------------------------------------------------------------------------------//
    //For saving.
    else if(wasMousePressed)
    {
        QPainter painter(&drawPanel);
        painter.setPen(QPen(currentColor,brushWidth,penStyle,capStyle,joinStyle));

        if (getIsCircle())
        {
            QRect circle = QRect(firstPoint, lastPoint);
            painter.drawEllipse(x1,y1,raduis,raduis);
            if(isFilling)
            {
                QBrush fillbrush(fillColor);
                QPainterPath path;
                path.addEllipse(firstPoint.x(),firstPoint.y(),raduis,raduis);
                painter.fillPath(path, fillbrush);
            }
            std::string name = "any name";
            int arr[] = {firstPoint.x(),firstPoint.y(),lastPoint.x(),lastPoint.y()};


        }
        else if (getIsRectangle())
        {
            QRect rect = QRect(firstPoint, lastPoint);
            painter.drawRect(rect);
            if (isFilling)
            {
                QBrush fillbrush(fillColor);
                QPainterPath path;
                path.addRoundedRect(rect,brushWidth, brushWidth);
                painter.fillPath(path,fillbrush);
            }


        }

        else if(getIsStraightLine())
        {
            painter.drawLine(firstPoint, lastPoint);
        }

        else
        {
            painter.drawImage(rectArea, drawPanel, rectArea);
        }

        wasMousePressed = false;

    }
    update();

}

void DrawPanel::resizeEvent(QResizeEvent *event)
{
    if (width() != drawPanel.width() || height() != drawPanel.height())
    {
        int nWidth, nHeight;

        if (width() > drawPanel.width())
            nWidth = width();
        if (width() <= drawPanel.width())
            nWidth = drawPanel.width();
        if (height() > drawPanel.height())
            nHeight = height();
        if (height() <= drawPanel.height())
            nHeight = drawPanel.height();

        resize(nWidth,nHeight);
    }
}


QImage DrawPanel::getImage()
{
    return drawPanel;
}

void DrawPanel::setImage(QImage image)
{
    drawPanel = image;
}

void DrawPanel::resize(int w, int h)
{
    QPixmap newImage(QSize(w, h));
    newImage.fill(Qt::white);
    QPainter painter(&newImage);
    painter.drawImage(QPoint(0, 0), drawPanel);
    setImage(newImage.toImage());
    update();
}

void DrawPanel::clear()
{
    drawPanel.fill(Qt::white);
    update();
}

QColor DrawPanel::getPrevColor() const
{
    return prevColor;
}

void DrawPanel::setPrevColor(const QColor &value)
{
    prevColor = value;
}

Qt::PenStyle DrawPanel::getPenStyle() const
{
    return penStyle;
}

void DrawPanel::setPenStyle(const Qt::PenStyle &value)
{
    penStyle = value;
}

Qt::PenCapStyle DrawPanel::getCapStyle() const
{
    return capStyle;
}

void DrawPanel::setCapStyle(const Qt::PenCapStyle &value)
{
    capStyle = value;
}

Qt::PenJoinStyle DrawPanel::getJoinStyle() const
{
    return joinStyle;
}

void DrawPanel::setJoinStyle(const Qt::PenJoinStyle &value)
{
    joinStyle = value;
}

bool DrawPanel::getIsRectangle() const
{
    return isRectangle;
}

void DrawPanel::setIsRectangle(bool value)
{
    isRectangle = value;
}

bool DrawPanel::getIsCircle() const
{
    return isCircle;
}

void DrawPanel::setIsCircle(bool value)
{
    isCircle = value;
}

bool DrawPanel::getIsStraightLine() const
{
    return isStraightLine;
}

void DrawPanel::setIsStraightLine(bool value)
{
    isStraightLine = value;
}

bool DrawPanel::getIsFilling() const
{
    return isFilling;
}

void DrawPanel::setIsFilling(bool value)
{
    isFilling = value;
}

QColor DrawPanel::getFillColor() const
{
    return fillColor;
}

void DrawPanel::setFillColor(const QColor &value)
{
    fillColor = value;
}

QImage DrawPanel::getCopyDrawing() const
{
    return copyDrawing;
}

void DrawPanel::setCopyDrawing(const QImage &value)
{
    copyDrawing = value;
}

void DrawPanel::setColor(QColor setColor)
{
    currentColor = setColor;
}

void DrawPanel::setBrushWidth(int setBrushWidth)
{
    brushWidth = setBrushWidth;
}

QColor DrawPanel::getColor()
{
    return currentColor;
}

void DrawPanel::undo()
{
    QPainter painter(this);
    if (!shapesMap.empty()){

        shapesMap.remove(stackUndo.top());
        stackRedo.push(stackUndo.top());
        stackUndo.pop();
        DrawPanel::clear();

        QMap<QString, Shape>::iterator i;
        for (i = shapesMap.begin(); i != shapesMap.end(); ++i){
        painter.drawRect(i->getphysicalShape());

        qDebug() << shapesMap.keys();
        update();
        }
        update();
    }
    else{
        DrawPanel::clear();
    }
}

void DrawPanel::redo()
{
    if (!stackRedo.empty()){



        shapesMap[stackRedo.top()] = BackShapeMap[stackRedo.top()];
        stackUndo.push(stackRedo.top());
        stackRedo.pop();
        qDebug() << shapesMap.keys();
        update();
    }
}


void DrawPanel:: search(){
    bool ok;
    QString shapeName = QInputDialog::getText(this,tr("Search"),tr("Enter shape name:"),QLineEdit::Normal,tr(""),&ok );
    if( ok && !shapeName.isEmpty())
    {
        if(shapesMap.contains(shapeName)){
            QMessageBox::information(this,tr("Search"),tr("Found!!"));
        }
        else{
            QMessageBox::information(this,tr("Search"),tr("Not Found!!"));
        }
    }
}

void DrawPanel:: deleteShape(){
    bool ok;
    QString ShapesToDelete = QInputDialog::getItem(this,tr("Delete"),tr("Shapes: "),shapesMap.keys(),0,true,&ok);
    if( ok )
    {
        shapesMap.remove(ShapesToDelete);
        qDebug() << shapesMap.keys();
        QMessageBox::information(this,tr("Delete"),tr("Shape is Deleted!!"));
    }
}
