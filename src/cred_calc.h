#ifndef CRED_CALC_H
#define CRED_CALC_H

#include <QDialog>

extern "C" {
#include "s21_calc.h"
}

namespace Ui {
class Cred_calc;
}

class Cred_calc : public QDialog
{
    Q_OBJECT

public:
    explicit Cred_calc(QWidget *parent = nullptr);
    ~Cred_calc();

private slots:
    void on_pushButton_res_clicked();

    void on_annu_clicked();

    void on_diff_clicked();

private:
    Ui::Cred_calc *ui;
    int FlagCred;
};

#endif // CRED_CALC_H
