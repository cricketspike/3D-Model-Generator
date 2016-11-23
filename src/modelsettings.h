#ifndef MODELSETTINGS_H
#define MODELSETTINGS_H

#include <QDialog>

namespace Ui {
class ModelSettings;
}

class ModelSettings : public QDialog
{
    Q_OBJECT

public:
    explicit ModelSettings(QWidget *parent = 0);
    ~ModelSettings();

private slots:
    void on_pushButton_2_clicked();

    void on_resolution_splitting_valueChanged(int arg1);

    void on_Level_dist_valueChanged(int arg1);

    void on_pushButton_clicked();

private:
    int m_res_split;
    int m_loop_dis;
    Ui::ModelSettings *ui;
};

#endif // MODELSETTINGS_H
