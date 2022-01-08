#include "enternamedialog.h"
#include "ui_enternamedialog.h"

enterNameDialog::enterNameDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::enterNameDialog)
{
    ui->setupUi(this);
}

enterNameDialog::~enterNameDialog()
{
    delete ui;
}

void enterNameDialog::on_buttonBox_accepted()
{
    std::string name = ui->nameTextEdit->toPlainText().toStdString();

//    enterNameDialog::close();
}


void enterNameDialog::on_buttonBox_rejected()
{
    enterNameDialog::close();
}

