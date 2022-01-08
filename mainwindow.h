#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <drawpanel.h>
#include <QMainWindow>
#include <QFileDialog>
#include <QInputDialog>
#include <QMessageBox>
#include <resize.h>
#include <about.h>
#include <zoom.h>

#include <QDebug>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    int openDialog();

private:
    Ui::MainWindow *ui;
    DrawPanel *drawpanel;

private slots:
    void on_actionPen_color_triggered();
    void on_actionSave_triggered();
    void on_actionPen_size_triggered();
    void on_actionEraser_triggered();

    void on_actionRectangle_triggered();
    void on_actionCircle_triggered();
    void on_actionStraightLine_triggered();
    void on_actionOpen_triggered();
    void on_actionNew_triggered();
    void on_actionClose_triggered();
    void on_actionSearch_triggered();
    void on_actionDelete_triggered();

    void on_actionResize_triggered();
    void on_actionFill_with_color_triggered();
    void on_actionFill_color_triggered();
    void on_actionCut_triggered();
    void on_actionPaste_triggered();
    void on_actionZoom_triggered();
    void on_actionUndo_triggered();
    void on_actionRedo_triggered();
};
#endif // MAINWINDOW_H
