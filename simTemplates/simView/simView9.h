#ifndef SIMVIEW9_H
#define SIMVIEW9_H

#include <QWidget>
#include "baseSimView.h"

namespace Ui {
class SpecificSimParamsTest9;
}

class simView9 : public baseSimView
{
    Q_OBJECT

public:
    explicit simView9(QWidget *parent = 0);
    ~simView9();

    void updateView(void);
    void updateModel(void);

private:
    Ui::SpecificSimParamsTest9 *ui;
};

#endif // SIMVIEW9_H
