#include "wcursorctrl.h"
#include "ui_wcursorctrl.h"
#include <math.h>

#define DTFACTOR 10

wCursorCtrl::wCursorCtrl(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::wCursorCtrl)
{
    ui->setupUi(this);
    updateStats();
}

wCursorCtrl::~wCursorCtrl()
{
    delete ui;
}

QPointF wCursorCtrl::cur1(void)
{
    return QPointF(ui->cur1x->value(),ui->cur1y->value());
}

QPointF wCursorCtrl::cur2(void)
{
    return QPointF(ui->cur2x->value(),ui->cur2y->value());
}

void wCursorCtrl::on_cur1x_valueChanged(double arg1)
{
    updateStats();
    emit cursorUpdated(0, arg1);
}

void wCursorCtrl::on_cur2x_valueChanged(double arg1)
{
    updateStats();
    emit cursorUpdated(1, arg1);
}

void wCursorCtrl::updateStats(void)
{
    double x1 = ui->cur1x->value();
    double x2 = ui->cur2x->value();
    double d = x2-x1;
    ui->delta->setValue(d);
    if (d != 0)
    {
        if (d < 0.0)
        {
            d = -d;
        }
        ui->freqLabel->setVisible(true);
        ui->freq->setVisible(true);
        ui->freq->setValue(1/d);
    }
    else
    {
        ui->freqLabel->setVisible(false);
        ui->freq->setVisible(false);
    }
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
    updateStats();
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
