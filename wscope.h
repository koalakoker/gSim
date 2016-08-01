#ifndef WSCOPE_H
#define WSCOPE_H

#include <QWidget>
#include "QVector"
#include "qcustomplot.h"

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
    void exportData(void);
    void setAxis(double xMin,double  xMax,double  yMin,double  yMax);

private:
    Ui::WScope *ui;
    QCPItemLine* vCursor[CURSOR_NUMBER];

    QVector<double> tArray;
    QVector<double> yArray;

    double xMin;
    double xMax;
    double yMin;
    double yMax;

    double getMaxSignalY(void);
    double getMaxSignalX(void);
    double getMinSignalY(void);
    double getMinSignalX(void);

private slots:
    void mousePress();
    void mouseWheel();

    void setXMin(double val);
    void setXMax(double val);
    void setYMin(double val);
    void setYMax(double val);

    void maximizeX();
    void maximizeY();

    void axisXSelect(bool ch);
    void axisYSelect(bool ch);

    void cursorUpdated(int cur, double x);

signals:

public slots:
	void refresh(void);
};

#endif // WSCOPE_H
