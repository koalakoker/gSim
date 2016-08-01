#include "waxisctrl.h"
#include "ui_waxisctrl.h"

wAxisCtrl::wAxisCtrl(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::wAxisCtrl)
{
    ui->setupUi(this);
}

wAxisCtrl::~wAxisCtrl()
{
    delete ui;
}

void wAxisCtrl::setXmin(double x) {ui->xMin->setValue(x);}
void wAxisCtrl::setXmax(double x) {ui->xMax->setValue(x);}
void wAxisCtrl::setYmin(double y) {ui->yMin->setValue(y);}
void wAxisCtrl::setYmax(double y) {ui->yMax->setValue(y);}
double wAxisCtrl::Xmin() {return ui->xMin->value();}
double wAxisCtrl::Xmax() {return ui->xMax->value();}
double wAxisCtrl::Ymin() {return ui->yMin->value();}
double wAxisCtrl::Ymax() {return ui->yMin->value();}

void wAxisCtrl::setRangeX(QCPRange r)
{
    blockSignals(true);
    setXmin(r.lower);
    setXmax(r.upper);
    blockSignals(false);
}

void wAxisCtrl::setRangeY(QCPRange r)
{
    blockSignals(true);
    setYmin(r.lower);
    setYmax(r.upper);
    blockSignals(false);
}

void wAxisCtrl::on_yMax_valueChanged(double arg1)
{
    emit YMaxChanged(arg1);
}

void wAxisCtrl::on_xMax_valueChanged(double arg1)
{
    emit XMaxChanged(arg1);
}

void wAxisCtrl::on_yMin_valueChanged(double arg1)
{
    emit YMinChanged(arg1);
}

void wAxisCtrl::on_xMin_valueChanged(double arg1)
{
    emit XMinChanged(arg1);
}

void wAxisCtrl::on_maximizeX_clicked()
{
    emit maximizeX();
}

void wAxisCtrl::on_maximizeY_clicked()
{
    emit maximizeY();
}

void wAxisCtrl::on_zoomX_toggled(bool checked)
{
    emit axisXSelect(checked);
    if (checked)
    {
        if (ui->zoomY->isChecked())
        {
            blockSignals(true);
            ui->zoomY->setChecked(false);
            blockSignals(false);
            emit axisYSelect(false);
        }
    }
}

void wAxisCtrl::on_zoomY_toggled(bool checked)
{
    emit axisYSelect(checked);
    if (checked)
    {
        if (ui->zoomX->isChecked())
        {
            blockSignals(true);
            ui->zoomX->setChecked(false);
            blockSignals(false);
            emit axisXSelect(false);
        }
    }
}
