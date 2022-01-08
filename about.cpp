#include "about.h"
#include "ui_about.h"

About::About(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::About)
{
    ui->setupUi(this);
    ui->plainTextEdit->document()->setPlainText("Made by the SHERIF and with small help from his team :D");
}

About::~About()
{
    delete ui;
}

//#include <QDebug>

//qDebug() << "hello";
