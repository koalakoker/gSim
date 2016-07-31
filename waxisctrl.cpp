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
    setXmin(r.lower);
    setXmax(r.upper);
}

void wAxisCtrl::setRangeY(QCPRange r)
{
    setYmin(r.lower);
    setYmax(r.upper);
}
