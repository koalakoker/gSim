#ifndef SIMULATIONVIEW7_H
#define SIMULATIONVIEW7_H

#include <QWidget>
#include "baseSimulationView.h"

namespace Ui {
class simulationView7;
}

class simulationView7 : public baseSimulationView
{
    Q_OBJECT

public:
    explicit simulationView7(QWidget *parent = 0);
    ~simulationView7();

    void updateView(void);
    void updateModel(void);

private:
    Ui::simulationView7 *ui;
};

#endif // SIMULATIONVIEW7_H
