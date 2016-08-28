#ifndef GSIM_H
#define GSIM_H

#include <QMainWindow>
#include "mainsimulator.h"

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

private:
    Ui::gSim *ui;
    mainSimulator m_sim;
};

#endif // GSIM_H
