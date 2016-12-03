#ifndef GSIM_H
#define GSIM_H

#include <QMainWindow>
#include "mainsimulation.h"
#include "specificsimparamsempty.h"
#include "specificsimparamsTest8.h"

namespace Ui {
class gSim;
}

class gSim : public QMainWindow
{
    Q_OBJECT

public:
    explicit gSim(QWidget *parent = 0);
    ~gSim();

private slots:
    void on_startSimulation_clicked();
    void updateProgress(double percentage);

    void on_simulation_valueChanged(int arg1);

private:
    Ui::gSim *ui;
    mainSimulation* m_sim;

    SpecificSimParamsEmpty* sspEmpty;
    SpecificSimParamsTest8* sspT8;
    QWidget* lastSetWidget;

    void updateSpecificSimParams(QWidget* newWid);

};

#endif // GSIM_H
