#include "wcursorctrl.h"
#include "ui_wcursorctrl.h"

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
