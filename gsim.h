#ifndef GSIM_H
#define GSIM_H

#include <QMainWindow>
#include "simTemplates/simModel/baseSimModel.h"
#include "simTemplates/simView/baseSimView.h"

#include "simTemplates/simModel/simModel8.h"

#include <QTimer>

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
    void on_startSim_clicked();
    void updateProgress(double percentage);

private:
    Ui::gSim *ui;

    baseSimModel* m_simModel;
    baseSimView* m_simView;

    simModel8 m_sim;

    void setSim(void);

    QTimer testTim;

};

#endif // GSIM_H
