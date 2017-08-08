#ifndef BASESIMULATIONVIEW_H
#define BASESIMULATIONVIEW_H

#include <QWidget>
#include "baseSimulationModel.h"

namespace Ui {
class SpecificSimParamsEmpty;
}

class baseSimulationView : public QWidget
{
    Q_OBJECT

public:
    explicit baseSimulationView(QWidget *parent = 0);
    ~baseSimulationView();

    void setSimulationModel(baseSimulationModel* sim);
    virtual void updateView(void);
    virtual void updateModel(void);

private:
    Ui::SpecificSimParamsEmpty *ui;

protected:
    baseSimulationModel* m_sim;
};

#endif // BASESIMULATIONVIEW_H
