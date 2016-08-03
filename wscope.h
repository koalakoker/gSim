#ifndef WSCOPE_H
#define WSCOPE_H

#include <QWidget>
#include "QVector"
#include "qcustomplot.h"
#include <QMouseEvent>

#define ELEMENT 100
#define CURSOR_NUMBER 2

namespace Ui {
class WScope;
}

class WScope : public QWidget
{
    Q_OBJECT
public:
    explicit WScope(QWidget *parent = 0);

    void reset(void);
    void addPoint(double t, double y);
    void setData(QVector<double> tArray,QVector<double> yArray);
    void exportData(void);
    void setAxis(double xMin,double  xMax,double  yMin,double  yMax);

    void setdt(double dt);
    double dt(void) {return this->dtVal;}

private:
    Ui::WScope *ui;
    QCPItemLine* vCursor[CURSOR_NUMBER];
    bool vCursorDrag[CURSOR_NUMBER];
    const QColor vCursorColor[CURSOR_NUMBER] = {Qt::black, Qt::black};
    const Qt::PenStyle vCursorStyle[CURSOR_NUMBER] = {Qt::DashLine, Qt::DashDotLine};

    QVector<double> tArray;
    QVector<double> yArray;

    double dtVal;

    double xMin;
    double xMax;
    double yMin;
    double yMax;

    double getMaxSignalY(void);
    double getMaxSignalX(void);
    double getMinSignalY(void);
    double getMinSignalX(void);

private slots:
    void mousePress(QMouseEvent* event);
    void mouseWheel();
    void mouseMove(QMouseEvent* event);
    void mouseRelease();

    void setXMin(double val);
    void setXMax(double val);
    void setYMin(double val);
    void setYMax(double val);

    void maximizeX();
    void maximizeY();

    void axisXSelect(bool ch);
    void axisYSelect(bool ch);

    void cursorUpdated(int cur, double x);

    void selectionChanged();

signals:
    void cursorMoved(int cur, double x, double y);

public slots:
	void refresh(void);
};

#endif // WSCOPE_H
