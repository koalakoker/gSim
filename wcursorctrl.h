#ifndef WCURSORCTRL_H
#define WCURSORCTRL_H

#include <QWidget>

namespace Ui {
class wCursorCtrl;
}

class wCursorCtrl : public QWidget
{
    Q_OBJECT

public:
    explicit wCursorCtrl(QWidget *parent = 0);
    ~wCursorCtrl();

private slots:
    void on_cur1x_valueChanged(double arg1);

    void on_cur2x_valueChanged(double arg1);

private:
    Ui::wCursorCtrl *ui;

signals:
    void cursorUpdated(int cur, double x);
};

#endif // WCURSORCTRL_H
