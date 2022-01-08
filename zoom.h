#ifndef ZOOM_H
#define ZOOM_H

#include <QDialog>
#include <QIntValidator>

namespace Ui {
class Zoom;
}

class Zoom : public QDialog
{
    Q_OBJECT

public:
    explicit Zoom(QWidget *parent = nullptr);
    ~Zoom();

    int getZoom() const;

private:
    Ui::Zoom *ui;

    int zoom;
};

#endif // ZOOM_H
