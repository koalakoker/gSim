#include "wcursorctrl.h"
#include "ui_wcursorctrl.h"

#define DTFACTOR 10

wCursorCtrl::wCursorCtrl(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::wCursorCtrl)
{
    ui->setupUi(this);
}

wCursorCtrl::~wCursorCtrl()
{
    delete ui;
}

void wCursorCtrl::on_cur1x_valueChanged(double arg1)
{
    emit cursorUpdated(0, arg1);
}

void wCursorCtrl::on_cur2x_valueChanged(double arg1)
{
    emit cursorUpdated(1, arg1);
}

void wCursorCtrl::cursorMoved(int cur, double x, double y)
{
    blockSignals(true);
    if (cur == 0)
    {
        ui->cur1x->setValue(x);
        ui->cur1y->setValue(y);
    }
    else
    {
        ui->cur2x->setValue(x);
        ui->cur2y->setValue(y);
    }
    blockSignals(false);
}

void wCursorCtrl::setdt(double dt)
{
    dtVal = dt;
    ui->cur1x->setSingleStep(dt * DTFACTOR);
    ui->cur2x->setSingleStep(dt * DTFACTOR);

    int i = 0;
    while ((dt * (double)pow(10,i)) < 1.0)
    {
        i++;
    }
    ui->cur1x->setDecimals(i);
    ui->cur2x->setDecimals(i);
}
