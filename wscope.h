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

private:
    Ui::WScope *ui;

    QVector<double> tArray;
    QVector<double> yArray;

signals:

public slots:
	void refresh(void);
};

#endif // WSCOPE_H
