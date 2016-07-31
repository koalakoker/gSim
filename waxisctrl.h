#ifndef WAXISCTRL_H
#define WAXISCTRL_H

#include <QWidget>
#include "qcustomplot.h"

namespace Ui {
class wAxisCtrl;
}

class wAxisCtrl : public QWidget
{
    Q_OBJECT

public:
    explicit wAxisCtrl(QWidget *parent = 0);
    ~wAxisCtrl();

    void setXmin(double x);
    void setXmax(double x);
    void setYmin(double y);
    void setYmax(double y);
    double Xmin();
    double Xmax();
    double Ymin();
    double Ymax();

private:
    Ui::wAxisCtrl *ui;

public slots:
    void setRangeX(QCPRange r);
    void setRangeY(QCPRange r);
private slots:
    void on_yMax_valueChanged(double arg1);
    void on_xMax_valueChanged(double arg1);

signals:
    void YMaxChanged(double);
};

#endif // WAXISCTRL_H
