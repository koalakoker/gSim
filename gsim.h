#ifndef GSIM_H
#define GSIM_H

#include <QMainWindow>

namespace Ui {
class gSim;
}

class gSim : public QMainWindow
{
    Q_OBJECT

public:
    explicit gSim(QWidget *parent = 0);
    ~gSim();

private:
    Ui::gSim *ui;
};

#endif // GSIM_H
