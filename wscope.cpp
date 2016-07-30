#include "wscope.h"
#include "ui_wscope.h"
#include "qstring.h"

WScope::WScope(QWidget *parent) : QWidget(parent), ui(new Ui::WScope)
{
    ui->setupUi(this);

    ui->qplot->addGraph();

    // give the axes some labels:
    ui->qplot->xAxis->setLabel("x");
    ui->qplot->yAxis->setLabel("y");
    // set axes ranges, so we see all data:
    ui->qplot->xAxis->setRange(0, 1);
    ui->qplot->yAxis->setRange(-1, 1);
    ui->qplot->replot();
}

void WScope::reset(void)
{
    ui->qplot->graph(0)->clearData();
}

void WScope::refresh(void)
{
    ui->qplot->replot();
}

void WScope::addPoint(double t, double y)
{
    tArray.append(t);
    yArray.append(y);
    ui->qplot->graph(0)->addData(t, y);
}

void WScope::debugty(void)
{
    int size = tArray.size();
    int i;
    for (i = 0; i < size; i++)
    {
        double t = tArray[i];
        double y = yArray[i];
        QString out = QString("step %1 : %2 , %3").arg(i).arg(t).arg(y);
        ui->listPlot->addItem(out);
    }
}
