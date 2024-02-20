#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QString>
#include <QVector>
#include <QTimer>
#include "cred_calc.h"


extern "C" {
#include "s21_calc.h"
}

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    Cred_calc *uicr;
    int FlagX;

    double xBegin, xEnd, h, X, xB, xE;
    int N;

    QVector<double> x,y;
    QTimer *timer;
    int time;

private slots:
    void digits_numbers();
    void funcion();
//    void on_pushButton_dot_clicked();
    void on_pushButton_ac_clicked();
    void on_pushButton_equals_clicked();
    void on_radioButton_2_clicked();
    void on_radioButton_clicked();
    void on_pushButton_graf_clicked();
    void TimerSlot();
    void on_pushButton_cred_calc_clicked();
};
#endif // MAINWINDOW_H
