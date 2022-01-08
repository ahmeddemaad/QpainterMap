#include "resize.h"
#include "ui_resize.h"


Resize::Resize(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Resize)
{
    ui->setupUi(this);
    ui->height->setValidator( new QIntValidator(1, 5000, this) );
    ui->width->setValidator( new QIntValidator(1, 5000, this) );
}
Resize::~Resize()
{
    delete ui;
}

void Resize::setHeight(int value)
{
    ui->height->setText(QString::number(value));
}

void Resize::setWidth(int value)
{
    ui->width->setText(QString::number(value));
}

int Resize::getHeight() const
{
    return ui->height->text().toInt();
}

int Resize::getWidth() const
{
    return ui->width->text().toInt();
}

