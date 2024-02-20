#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->pushButton_0, SIGNAL(clicked()), this, SLOT(digits_numbers()));
    connect(ui->pushButton_1, SIGNAL(clicked()), this, SLOT(digits_numbers()));
    connect(ui->pushButton_2, SIGNAL(clicked()), this, SLOT(digits_numbers()));
    connect(ui->pushButton_3, SIGNAL(clicked()), this, SLOT(digits_numbers()));
    connect(ui->pushButton_4, SIGNAL(clicked()), this, SLOT(digits_numbers()));
    connect(ui->pushButton_5, SIGNAL(clicked()), this, SLOT(digits_numbers()));
    connect(ui->pushButton_6, SIGNAL(clicked()), this, SLOT(digits_numbers()));
    connect(ui->pushButton_7, SIGNAL(clicked()), this, SLOT(digits_numbers()));
    connect(ui->pushButton_8, SIGNAL(clicked()), this, SLOT(digits_numbers()));
    connect(ui->pushButton_9, SIGNAL(clicked()), this, SLOT(digits_numbers()));
    connect(ui->pushButton_dot, SIGNAL(clicked()), this, SLOT(digits_numbers()));
    connect(ui->pushButton_plus, SIGNAL(clicked()), this, SLOT(digits_numbers()));
    connect(ui->pushButton_minus, SIGNAL(clicked()), this, SLOT(digits_numbers()));
    connect(ui->pushButton_mult, SIGNAL(clicked()), this, SLOT(digits_numbers()));
    connect(ui->pushButton_div, SIGNAL(clicked()), this, SLOT(digits_numbers()));
    connect(ui->pushButton_mod, SIGNAL(clicked()), this, SLOT(digits_numbers()));
    connect(ui->pushButton_deg, SIGNAL(clicked()), this, SLOT(digits_numbers()));
    connect(ui->pushButton_cos, SIGNAL(clicked()), this, SLOT(funcion()));
    connect(ui->pushButton_sin, SIGNAL(clicked()), this, SLOT(funcion()));
    connect(ui->pushButton_tan, SIGNAL(clicked()), this, SLOT(funcion()));
    connect(ui->pushButton_acos, SIGNAL(clicked()), this, SLOT(funcion()));
    connect(ui->pushButton_asin, SIGNAL(clicked()), this, SLOT(funcion()));
    connect(ui->pushButton_atan, SIGNAL(clicked()), this, SLOT(funcion()));
    connect(ui->pushButton_log, SIGNAL(clicked()), this, SLOT(funcion()));
    connect(ui->pushButton_ln, SIGNAL(clicked()), this, SLOT(funcion()));
    connect(ui->pushButton_sqrt, SIGNAL(clicked()), this, SLOT(funcion()));
    connect(ui->pushButton_iks, SIGNAL(clicked()), this, SLOT(digits_numbers()));
    connect(ui->pushButton_open, SIGNAL(clicked()), this, SLOT(digits_numbers()));
    connect(ui->pushButton_close, SIGNAL(clicked()), this, SLOT(digits_numbers()));



//    xB = ui->xBegin->toPlainText().toDouble();
//    xE = ui->xEnd->toPlainText().toDouble();

    h = 0.1;
//    xBegin = xB;
//    xEnd = xE + h;

    ui->widget->xAxis->setRange(-4, 4);
    ui->widget->yAxis->setRange(-4, 4);

//    N = (xEnd - xBegin)/h + 2;

    ui->widget->addGraph();
    ui->widget->graph(0)->addData(x,y);
    ui->widget->replot();

    ui->widget->setInteraction(QCP::iRangeZoom, true);
    ui->widget->setInteraction(QCP::iRangeDrag, true);
}

MainWindow::~MainWindow()
{
    delete ui;

}

void MainWindow::on_pushButton_graf_clicked()
{
    xBegin = ui->xBegin->toPlainText().toDouble();
    xEnd = ui->xEnd->toPlainText().toDouble();
    N = (xEnd - xBegin)/h + 2;

    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(TimerSlot()));
    ui->widget->clearGraphs();
    timer->start(20);
    X = xBegin;
    x.clear();
    y.clear();

}

void MainWindow::TimerSlot()
{
    char a[250];
    double res;

    QString str= ui->display2->toPlainText();
    const QByteArray stringData = str.toUtf8();
    a[str.size()]='\0';
    std::copy(stringData.constBegin(),stringData.constBegin()+stringData.size(),a);

    if(time <= 20*N)
    {
        if(X <= xEnd)
        {
            x.push_back(X);
            calc(a, X, &res);
            y.push_back(res);
            X += h;
        }
        time += 20;
    }
    else
    {
        time = 0;
        timer->stop();
    }

    ui->widget->addGraph();
    ui->widget->graph(0)->addData(x,y);
    ui->widget->replot();

}

void MainWindow::on_radioButton_2_clicked()
{
    FlagX = 1;
}

void MainWindow::on_radioButton_clicked()
{
    FlagX = 0;
}

void MainWindow::digits_numbers()
{
    QPushButton *button = (QPushButton *)sender();

    if (FlagX == 1) {
            ui->display_x->setText(ui->display_x->toPlainText() + button->text());
        } else {
            ui->display2->setText(ui->display2->toPlainText() + button->text());
        }
}

void MainWindow::funcion()
{
    QPushButton *button = (QPushButton *)sender();
    ui->display2->setText(ui->display2->toPlainText() + button->text() + "(");
}

void MainWindow::on_pushButton_ac_clicked()
{
    ui->display2->setText("");
    ui->display_x->setText("");
}

void MainWindow::on_pushButton_equals_clicked()
{
    char a[250];
    double x;
    double res;
    int err;

    x = ui->display_x->toPlainText().toDouble();

    QString str= ui->display2->toPlainText();
    const QByteArray stringData = str.toUtf8();
    a[str.size()]='\0';
    std::copy(stringData.constBegin(),stringData.constBegin()+stringData.size(),a);

    err = calc(a, x, &res);
    if (err == 1) {
        QString toStr = "ERROR";
        ui->display2->setText(toStr);
    } else {
        QString toStr = QString::number(res,'g',8);
        ui->display2->setText(toStr);
    }
}

void MainWindow::on_pushButton_cred_calc_clicked()
{
    uicr = new Cred_calc(this);
    uicr->show();
}

