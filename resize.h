#ifndef RESIZEDIALOG_H
#define RESIZEDIALOG_H

#include <QDialog>
#include <QIntValidator>

namespace Ui {
class Resize;
}

class Resize : public QDialog
{
    Q_OBJECT

public:
    explicit Resize(QWidget *parent = nullptr);
    ~Resize();

    int getWidth() const;
    int getHeight() const;

    void setWidth(int value);
    void setHeight(int value);

private slots:

private:
    Ui::Resize *ui;
    int width;
    int height;
};

#endif // RESIZEDIALOG_H
