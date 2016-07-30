#include "wscope.h"
#include "ui_wscope.h"

WScope::WScope(QWidget *parent) : WOut(parent), ui(new Ui::WScope)
{
    ui->setupUi(this);
}

void WScope::refresh(void)
{
    ui->qplot->replot();
}
