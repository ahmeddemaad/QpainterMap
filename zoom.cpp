#include "zoom.h"
#include "ui_zoom.h"

Zoom::Zoom(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Zoom)
{
    ui->setupUi(this);
    ui->lineEdit->setText(QString::number(100));
    ui->lineEdit->setValidator( new QIntValidator(10, 200, this) );
}

Zoom::~Zoom()
{
    delete ui;
}

int Zoom::getZoom() const
{
    return ui->lineEdit->text().toInt();
}
