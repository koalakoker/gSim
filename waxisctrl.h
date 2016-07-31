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
    void setRange(QCPRange r);
};

#endif // WAXISCTRL_H
