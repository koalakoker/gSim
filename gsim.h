#ifndef GSIM_H
#define GSIM_H

#include <QMainWindow>
#include "simTemplates/simModel/baseSimModel.h"
#include "simTemplates/simView/baseSimView.h"

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
    void setSimView(baseSimView* view);
    void setSimModel(baseSimModel* model);

private slots:
    void on_startSim_clicked();
    void updateProgress(double percentage);

private:
    Ui::gSim *ui;

    baseSimModel* m_simModel;
    baseSimView* m_simView;

    QTimer testTim;


    void closeEvent(QCloseEvent *event);
};

#endif // GSIM_H
