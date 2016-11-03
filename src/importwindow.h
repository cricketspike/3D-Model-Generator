#ifndef IMPORTWINDOW_H
#define IMPORTWINDOW_H

#include <QDialog>

namespace Ui {
class importwindow;
}

class importwindow : public QDialog
{
    Q_OBJECT

public:
    explicit importwindow(QWidget *parent = 0);
    ~importwindow();

private:
    Ui::importwindow *ui;
};

#endif // IMPORTWINDOW_H
