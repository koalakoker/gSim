#include "wscope.h"
#include "ui_wscope.h"

WScope::WScope(QWidget *parent) : QWidget(parent), ui(new Ui::WScope)
{
    ui->setupUi(this);

    ui->qplot->addGraph();
    ui->qplot->graph(0)->setData(oscope.x, oscope.y);
    // give the axes some labels:
    ui->qplot->xAxis->setLabel("x");
    ui->qplot->yAxis->setLabel("y");
    // set axes ranges, so we see all data:
    ui->qplot->xAxis->setRange(-1, 1);
    ui->qplot->yAxis->setRange(0, 1);
    ui->qplot->replot();
}

void WScope::on_listPlot_currentRowChanged(int currentRow)
{

}
