#include "wscope.h"
#include "ui_wscope.h"
#include "qstring.h"

WScope::WScope(QWidget *parent) : QWidget(parent), ui(new Ui::WScope)
{
    ui->setupUi(this);

    ui->qplot->addGraph();

    ui->qplot->xAxis->setLabel("x");
    ui->qplot->yAxis->setLabel("y");
    setAxis(0,1,-2,2);

    ui->qplot->setInteractions(QCP::iRangeDrag);

    connect(ui->qplot->xAxis, SIGNAL(rangeChanged(QCPRange)), ui->axisCtrl, SLOT(setRangeX(QCPRange)));
    connect(ui->qplot->yAxis, SIGNAL(rangeChanged(QCPRange)), ui->axisCtrl, SLOT(setRangeY(QCPRange)));
}

void WScope::setAxis(double xMin,double  xMax,double  yMin,double  yMax)
{
    this->xMin = xMin;
    this->xMax = xMax;
    ui->qplot->xAxis->setRange(xMin, xMax);
    ui->axisCtrl->setXmin(xMin);
    ui->axisCtrl->setXmax(xMax);
    this->yMin = yMin;
    this->yMax = yMax;
    ui->qplot->yAxis->setRange(yMin, yMax);
    ui->axisCtrl->setYmin(yMin);
    ui->axisCtrl->setYmax(yMax);
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
