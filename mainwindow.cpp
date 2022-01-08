#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QColorDialog>
#include <QScrollArea>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
      ui(new Ui::MainWindow),
      drawpanel(new DrawPanel(this))
{
    ui->setupUi(this);
    //QMainWindow::showFullScreen();
    setCentralWidget(drawpanel);
}

MainWindow::~MainWindow()
{
    delete ui;
    delete drawpanel;
}

int MainWindow::openDialog()
{
    QMessageBox dialog(QMessageBox::Question, tr("PaintQT"), tr("Do you want to save changes?"), QMessageBox::Yes | QMessageBox::No | QMessageBox::Cancel, this);
    dialog.setButtonText(QMessageBox::Yes, tr("Yes"));
    dialog.setButtonText(QMessageBox::No, tr("No"));
    dialog.setButtonText(QMessageBox::Cancel, tr("Cancel"));
    dialog.setDefaultButton(QMessageBox::Yes);

    return dialog.exec();
}

void MainWindow::on_actionPen_color_triggered()
{
    QColor customColor = QColorDialog::getColor(Qt::white, this, QString("Pick a color"), QColorDialog::ShowAlphaChannel);
    drawpanel->setColor(customColor);
}

void MainWindow::on_actionSave_triggered()
{
    QImage saveDrawing = drawpanel->getImage();
    QString filePath = QFileDialog::getSaveFileName(this, "Save Image", "", "PNG (*.png);;JPEG (*.jpg *.jpeg);;BMP (*.bmp)");
    saveDrawing.save(filePath);
}

void MainWindow::on_actionPen_size_triggered()
{
    bool correct = false;

    int size = QInputDialog::getInt(this, "Set pen size", "Pen size", 1, 1, 50, 1, &correct);

    if (correct)
    {
        drawpanel->setBrushWidth(size);
    }
}

void MainWindow::on_actionEraser_triggered()
{
    if(ui->actionEraser->isChecked() == true)
    {
       drawpanel->setPrevColor(drawpanel->getColor());
       drawpanel->setColor(Qt::white);
       drawpanel->setBrushWidth(50);
       drawpanel->setIsCircle(false);
       drawpanel->setIsRectangle(false);
       drawpanel->setIsStraightLine(false);
       ui->actionRectangle->setChecked(false);
       ui->actionCircle->setChecked(false);
       ui->actionStraightLine->setChecked(false);
       ui->actionFill_with_color->setChecked(false);

    }
    if(ui->actionEraser->isChecked() == false)
    {
        drawpanel->setColor(drawpanel->getPrevColor());
        drawpanel->setBrushWidth(10);
    }
}

void MainWindow::on_actionRectangle_triggered()
{
    if(ui->actionRectangle->isChecked() == true)
    {
        ui->actionCircle->setChecked(false);
        ui->actionStraightLine->setChecked(false);

        drawpanel->setIsRectangle(true);
        drawpanel->setIsCircle(false);
        drawpanel->setIsStraightLine(false);
    }
    if(ui->actionRectangle->isChecked() == false)
    {
        drawpanel->setIsRectangle(false);
    }
}

void MainWindow::on_actionCircle_triggered()
{
    if(ui->actionCircle->isChecked() == true)
    {
        ui->actionRectangle->setChecked(false);
        ui->actionStraightLine->setChecked(false);

        drawpanel->setIsCircle(true);
        drawpanel->setIsRectangle(false);
        drawpanel->setIsStraightLine(false);
    }
    if(ui->actionCircle->isChecked() == false)
    {
        drawpanel->setIsCircle(false);
    }
}

void MainWindow::on_actionStraightLine_triggered()
{
    if(ui->actionStraightLine->isChecked() == true)
    {
        ui->actionRectangle->setChecked(false);
        ui->actionCircle->setChecked(false);

        drawpanel->setIsCircle(false);
        drawpanel->setIsRectangle(false);
        drawpanel->setIsStraightLine(true);
    }
    if(ui->actionStraightLine->isChecked() == false)
    {
        drawpanel->setIsStraightLine(false);
    }
}

void MainWindow::on_actionOpen_triggered()
{
    int dialog = openDialog();
    if(dialog == QMessageBox::Yes)
    {
       on_actionSave_triggered();
       drawpanel->openImage();
    }
    else if(dialog == QMessageBox::No)
    {
        drawpanel->openImage();
    }
    else if(dialog == QMessageBox::Cancel)
    {
        return;
    }
}

void MainWindow::on_actionNew_triggered()
{
    int dialog = openDialog();
    if(dialog == QMessageBox::Yes)
    {
       on_actionSave_triggered();
       drawpanel->start();
       update();
    }
    else if(dialog == QMessageBox::No)
    {
        drawpanel->start();
        update();
    }
    else if(dialog == QMessageBox::Cancel)
    {
        return;
    }
}

void MainWindow::on_actionClose_triggered()
{
    int dialog = openDialog();
    if(dialog == QMessageBox::Yes)
    {
       on_actionSave_triggered();
       QApplication::quit();
    }
    else if(dialog == QMessageBox::No)
    {
        QApplication::quit();
    }
    else if(dialog == QMessageBox::Cancel)
    {
        return;
    }
}

void MainWindow::on_actionResize_triggered()
{
    Resize resize;
    resize.setWidth(drawpanel->getImage().width());
    resize.setHeight(drawpanel->getImage().height());
    if(resize.exec() == QDialog::Accepted)
    {
        int nWidth = resize.getWidth();
        int nHeight = resize.getHeight();

        drawpanel->resize(nWidth, nHeight);
    }

}

void MainWindow::on_actionSearch_triggered(){

    drawpanel->search();
}

void MainWindow::on_actionDelete_triggered(){

    drawpanel->deleteShape();
}

void MainWindow::on_actionFill_with_color_triggered()
{
    if(ui->actionFill_with_color->isChecked() == true)
    {
        drawpanel->setIsFilling(true);
    }
    else if(ui->actionFill_with_color->isChecked() == false)
    {
        drawpanel->setIsFilling(false);
    }
}

void MainWindow::on_actionFill_color_triggered()
{
    QColor customColor = QColorDialog::getColor(Qt::white, this, QString("Pick a fill color"), QColorDialog::ShowAlphaChannel);
    drawpanel->setFillColor(customColor);
}

void MainWindow::on_actionCut_triggered()
{
    drawpanel->setCopyDrawing(drawpanel->getImage());
    drawpanel->clear();
    ui->actionPaste->setEnabled(true);
}

void MainWindow::on_actionPaste_triggered()
{
    drawpanel->setImage(drawpanel->getCopyDrawing());
    QPainter painter;
    painter.drawImage(0,0, drawpanel->getImage());
}

void MainWindow::on_actionZoom_triggered()
{
    Zoom zoomDialog;
    if(zoomDialog.exec() == QDialog::Accepted)
    {
        int zoom = zoomDialog.getZoom();

        int newW = drawpanel->getImage().width() * zoom / 100;
        int newH = drawpanel->getImage().height() * zoom / 100;

        QImage zoomedImage = drawpanel->getImage();

        drawpanel->clear();
        drawpanel->resize(newW, newH);

        drawpanel->setImage(zoomedImage.scaled(newW, newH, Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
    }
}

void MainWindow::on_actionUndo_triggered()
{
    this->drawpanel->undo();
}

void MainWindow::on_actionRedo_triggered()
{
    this->drawpanel->redo();
}
