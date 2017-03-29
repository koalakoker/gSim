#ifndef SIMULATIONVIEW9_H
#define SIMULATIONVIEW9_H

#include <QWidget>
#include "baseSimulationView.h"

namespace Ui {
class SpecificSimParamsTest9;
}

class simulationView9 : public baseSimulationView
{
    Q_OBJECT

public:
    explicit simulationView9(QWidget *parent = 0);
    ~simulationView9();

    void updateView(void);
    void updateModel(void);

private:
    Ui::SpecificSimParamsTest9 *ui;
};

#endif // SIMULATIONVIEW9_H
