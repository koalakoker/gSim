#ifndef SIMULATIONVIEW8_H
#define SIMULATIONVIEW8_H

#include <QWidget>
#include "baseSimulationView.h"

namespace Ui {
class SpecificSimParamsTest8;
}

class simulationView8 : public baseSimulationView
{
    Q_OBJECT

public:
    explicit simulationView8(QWidget *parent = 0);
    ~simulationView8();

    void updateView(void);
    void updateModel(void);

private:
    Ui::SpecificSimParamsTest8 *ui;
};

#endif // SIMULATIONVIEW8_H
