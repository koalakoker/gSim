#ifndef WSCOPE_H
#define WSCOPE_H

#include <QWidget>
#include "QVector"

#define ELEMENT 100

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
    void debugty(void);
    void setAxis(double xMin,double  xMax,double  yMin,double  yMax);

private:
    Ui::WScope *ui;

    QVector<double> tArray;
    QVector<double> yArray;

    double xMin;
    double xMax;
    double yMin;
    double yMax;

signals:

public slots:
	void refresh(void);
    void setXMin(double val);
    void setXMax(double val);
    void setYMin(double val);
    void setYMax(double val);
};

#endif // WSCOPE_H
