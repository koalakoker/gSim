#ifndef SPECIFICSIMPARAMSEMPTY_H
#define SPECIFICSIMPARAMSEMPTY_H

#include <QWidget>
#include "mainsimulation.h"

namespace Ui {
class SpecificSimParamsEmpty;
}

class SpecificSimParamsEmpty : public QWidget
{
    Q_OBJECT

public:
    explicit SpecificSimParamsEmpty(QWidget *parent = 0);
    ~SpecificSimParamsEmpty();

    void setSimulationModel(mainSimulation* sim);
    virtual void updateView(void);
    virtual void updateModel(void);

private:
    Ui::SpecificSimParamsEmpty *ui;

protected:
    mainSimulation* m_sim;
};

#endif // SPECIFICSIMPARAMSEMPTY_H
