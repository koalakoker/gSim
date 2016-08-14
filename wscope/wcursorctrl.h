#ifndef WCURSORCTRL_H
#define WCURSORCTRL_H

#include <QWidget>
#include <QPointF>

namespace Ui {
class wCursorCtrl;
}

class wCursorCtrl : public QWidget
{
    Q_OBJECT

public:
    explicit wCursorCtrl(QWidget *parent = 0);
    ~wCursorCtrl();

    void setdt(double dt);
    double dt(void) {return this->dtVal;}

    QPointF cur1(void);
    QPointF cur2(void);

public slots:
    void cursorMoved(int cur, double x, double y);

private slots:
    void on_cur1x_valueChanged(double arg1);
    void on_cur2x_valueChanged(double arg1);

private:
    Ui::wCursorCtrl *ui;
    double dtVal;
    void updateStats(void);

signals:
    void cursorUpdated(int cur, double x);
};

#endif // WCURSORCTRL_H
