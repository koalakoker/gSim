#ifndef SIMVIEW8_H
#define SIMVIEW8_H

#include <QWidget>
#include "baseSimView.h"

namespace Ui {
class SpecificSimParamsTest8;
}

class simView8 : public baseSimView
{
    Q_OBJECT

public:
    explicit simView8(QWidget *parent = 0);
    ~simView8();

    void updateView(void);
    void updateModel(void);

private:
    Ui::SpecificSimParamsTest8 *ui;
};

#endif // SIMVIEW8_H
