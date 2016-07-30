#ifndef WSCOPE_H
#define WSCOPE_H

#include "wout.h"
#include "oscope.h"

namespace Ui {
class WScope;
}

class WScope : public WOut
{
    Q_OBJECT
public:
    explicit WScope(QWidget *parent = 0);

    OScope oscope;

private:
    Ui::WScope *ui;

signals:

public slots:
};

#endif // WSCOPE_H
