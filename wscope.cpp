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

    ui->qplot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectAxes);

    connect(ui->qplot->xAxis, SIGNAL(rangeChanged(QCPRange)), ui->axisCtrl, SLOT(setRangeX(QCPRange)));
    connect(ui->qplot->yAxis, SIGNAL(rangeChanged(QCPRange)), ui->axisCtrl, SLOT(setRangeY(QCPRange)));

    connect(ui->axisCtrl, SIGNAL(XMinChanged(double)), this, SLOT(setXMin(double)));
    connect(ui->axisCtrl, SIGNAL(XMaxChanged(double)), this, SLOT(setXMax(double)));
    connect(ui->axisCtrl, SIGNAL(YMinChanged(double)), this, SLOT(setYMin(double)));
    connect(ui->axisCtrl, SIGNAL(YMaxChanged(double)), this, SLOT(setYMax(double)));

    connect(ui->axisCtrl, SIGNAL(maximizeX()), this, SLOT(maximizeX()));
    connect(ui->axisCtrl, SIGNAL(maximizeY()), this, SLOT(maximizeY()));

    connect(ui->qplot, SIGNAL(mousePress(QMouseEvent*)), this, SLOT(mousePress(QMouseEvent*)));
    connect(ui->qplot, SIGNAL(mouseWheel(QWheelEvent*)), this, SLOT(mouseWheel()));
    connect(ui->qplot, SIGNAL(mouseMove(QMouseEvent*)), this, SLOT(mouseMove(QMouseEvent*)));
    connect(ui->qplot, SIGNAL(mouseRelease(QMouseEvent*)), this, SLOT(mouseRelease()));

    connect(ui->axisCtrl, SIGNAL(axisXSelect(bool)), this, SLOT(axisXSelect(bool)));
    connect(ui->axisCtrl, SIGNAL(axisYSelect(bool)), this, SLOT(axisYSelect(bool)));

    /* Cursor */
    int i;
    for (i = 0; i < CURSOR_NUMBER; i++)
    {
        QCPItemLine* vCur = new QCPItemLine(ui->qplot);
        vCursor[i] = vCur;
        ui->qplot->addItem(vCur);

        // Set cursor line
        QPen pen = vCur->pen();
        pen.setStyle(vCursorStyle[i]);
        pen.setColor(vCursorColor[i]);
        vCur->setPen(pen);
        pen = vCur->selectedPen();
        pen.setStyle(vCursorStyle[i]);
        pen.setColor(vCursorColor[i]);
        vCur->setSelectedPen(pen);

        // Set cursor position
        vCursor[i]->start->setTypeY(QCPItemPosition::ptAxisRectRatio);
        vCursor[i]->start->setCoords(0, 0);
        vCursor[i]->end->setTypeY(QCPItemPosition::ptAxisRectRatio);
        vCursor[i]->end->setCoords( 0, 1);
        vCursorDrag[i] = false;
    }

    connect(ui->cursorCtrl, SIGNAL(cursorUpdated(int,double)), this, SLOT(cursorUpdated(int,double)));
    connect(this, SIGNAL(cursorMoved(int,double,double)), ui->cursorCtrl, SLOT(cursorMoved(int,double,double)));

    connect(ui->qplot, SIGNAL(selectionChangedByUser()), this, SLOT(selectionChanged()));
}

void WScope::setdt(double dt)
{
    dtVal = dt;
    ui->cursorCtrl->setdt(dt);
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

void WScope::setData(QVector<double> tArray,QVector<double> yArray)
{
    this->tArray = tArray;
    this->yArray = yArray;
    ui->qplot->graph(0)->setData(this->tArray, this->yArray);
    ui->qplot->replot();
}

void WScope::exportData(void)
{
    int size = tArray.size();
    int i;
    for (i = 0; i < size; i++)
    {
        double t = tArray[i];
        double y = yArray[i];
        QString out = QString("step %1 : %2 , %3").arg(i).arg(t).arg(y);
    }
}

void WScope::setXMin(double val)
{
    ui->qplot->xAxis->setRangeLower(val);
    ui->qplot->replot();
}

void WScope::setXMax(double val)
{
    ui->qplot->xAxis->setRangeUpper(val);
    ui->qplot->replot();
}

void WScope::setYMin(double val)
{
    ui->qplot->yAxis->setRangeLower(val);
    ui->qplot->replot();
}

void WScope::setYMax(double val)
{
    ui->qplot->yAxis->setRangeUpper(val);
    ui->qplot->replot();
}

double WScope::getMaxSignalY(void)
{
    double max = 0.0;
    int nPoint = yArray.length();
    if (nPoint > 0)
    {
        max = yArray[0];
        int i;
        for (i = 1; i < nPoint; i++)
        {
            if (yArray[i] > max)
            {
                max = yArray[i];
            }
        }
    }
    return max;
}

double WScope::getMaxSignalX(void)
{
    double max = 0.0;
    int nPoint = tArray.length();
    if (nPoint > 0)
    {
        max = tArray[0];
        int i;
        for (i = 1; i < nPoint; i++)
        {
            if (tArray[i] > max)
            {
                max = tArray[i];
            }
        }
    }
    return max;
}

double WScope::getMinSignalY(void)
{
    double min = 0.0;
    int nPoint = yArray.length();
    if (nPoint > 0)
    {
        min = yArray[0];
        int i;
        for (i = 1; i < nPoint; i++)
        {
            if (yArray[i] < min)
            {
                min = yArray[i];
            }
        }
    }
    return min;
}

double WScope::getMinSignalX(void)
{
    double min = 0.0;
    int nPoint = tArray.length();
    if (nPoint > 0)
    {
        min = tArray[0];
        int i;
        for (i = 1; i < nPoint; i++)
        {
            if (tArray[i] < min)
            {
                min = tArray[i];
            }
        }
    }
    return min;
}

void WScope::maximizeX()
{
    setXMax(getMaxSignalX());
    setXMin(getMinSignalX());
}

void WScope::maximizeY()
{
    setYMax(getMaxSignalY());
    setYMin(getMinSignalY());
}

void WScope::mousePress(QMouseEvent* event)
{
    // Check if cursor is clicked
    QCPAbstractItem* item = ui->qplot->itemAt(event->pos());

    // if cursor is selected then mouse will move it
    int i;
    bool cursorHit = false;
    for (i = 0; i < CURSOR_NUMBER; i++)
    {
        if ((QCPAbstractItem*)vCursor[i] == item)
        {
            vCursor[i]->setSelected(true);
            ui->qplot->replot();
            ui->qplot->axisRect()->setRangeDrag(0);
            vCursorDrag[i] = true;
            cursorHit = true;
            break;
        }
    }

    if (!cursorHit)
    {
        // if an axis is selected, only allow the direction of that axis to be dragged
        // if no axis is selected, both directions may be dragged
        if (ui->qplot->xAxis->selectedParts().testFlag(QCPAxis::spAxis))
            ui->qplot->axisRect()->setRangeDrag(ui->qplot->xAxis->orientation());
        else if (ui->qplot->yAxis->selectedParts().testFlag(QCPAxis::spAxis))
            ui->qplot->axisRect()->setRangeDrag(ui->qplot->yAxis->orientation());
        else
            ui->qplot->axisRect()->setRangeDrag(Qt::Horizontal|Qt::Vertical);
    }
}

void WScope::mouseWheel()
{
    // if an axis is selected, only allow the direction of that axis to be zoomed
    // if no axis is selected, both directions may be zoomed

    if (ui->qplot->xAxis->selectedParts().testFlag(QCPAxis::spAxis))
        ui->qplot->axisRect()->setRangeZoom(ui->qplot->xAxis->orientation());
    else if (ui->qplot->yAxis->selectedParts().testFlag(QCPAxis::spAxis))
        ui->qplot->axisRect()->setRangeZoom(ui->qplot->yAxis->orientation());
    else
        ui->qplot->axisRect()->setRangeZoom(Qt::Horizontal|Qt::Vertical);
}

void WScope::mouseMove(QMouseEvent* event)
{
    int i;
    for (i = 0; i < CURSOR_NUMBER; i++)
    {
        if (vCursorDrag[i])
        {
            double x = ui->qplot->xAxis->pixelToCoord(event->pos().x());
            vCursor[i]->start->setCoords(x, 0);
            vCursor[i]->end->setCoords(x, 1);
            ui->qplot->replot();
            int index = (int)(round(x / dtVal));
            x = (double)index * dtVal;
            double y = yArray[index];
            emit cursorMoved(i, x, y);
        }
    }
}

void WScope::mouseRelease()
{
    int i;
    for (i = 0; i < CURSOR_NUMBER; i++)
    {
        if (vCursorDrag[i])
        {
            vCursorDrag[i] = false;
            vCursor[i]->setSelected(false);
            ui->qplot->replot();
        }
    }
}

void WScope::axisXSelect(bool ch)
{
    if (ch)
    {
        ui->qplot->xAxis->setSelectedParts(QCPAxis::spAxis);
    }
    else
    {
        ui->qplot->xAxis->setSelectedParts(QCPAxis::spNone);
    }
    ui->qplot->replot();
}

void WScope::axisYSelect(bool ch)
{
    if (ch)
    {
        ui->qplot->yAxis->setSelectedParts(QCPAxis::spAxis);
    }
    else
    {
        ui->qplot->yAxis->setSelectedParts(QCPAxis::spNone);
    }
    ui->qplot->replot();
}

void WScope::cursorUpdated(int cur, double x)
{
    vCursor[cur]->start->setCoords( x, 0);
    vCursor[cur]->end->setCoords( x, 1);
    ui->qplot->replot();
}

void WScope::selectionChanged()
{
    if (ui->qplot->xAxis->selectedParts().testFlag(QCPAxis::spAxis) || ui->qplot->xAxis->selectedParts().testFlag(QCPAxis::spTickLabels))
    {
        ui->qplot->xAxis->setSelectedParts(QCPAxis::spAxis|QCPAxis::spTickLabels);
    }

    if (ui->qplot->yAxis->selectedParts().testFlag(QCPAxis::spAxis) || ui->qplot->yAxis->selectedParts().testFlag(QCPAxis::spTickLabels))
    {
        ui->qplot->yAxis->setSelectedParts(QCPAxis::spAxis|QCPAxis::spTickLabels);
    }

    for (int i=0; i<ui->qplot->graphCount(); ++i)
    {
        QCPGraph *graph = ui->qplot->graph(i);
        QCPPlottableLegendItem *item = ui->qplot->legend->itemWithPlottable(graph);
        if (item->selected() || graph->selected())
        {
            item->setSelected(true);
            graph->setSelected(true);
        }
    }
}
