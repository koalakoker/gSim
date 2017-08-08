#ifndef SIMVIEW7_H
#define SIMVIEW7_H

#include <QWidget>
#include "baseSimView.h"

namespace Ui {
class simView7;
}

class simView7 : public baseSimView
{
    Q_OBJECT

public:
    explicit simView7(QWidget *parent = 0);
    ~simView7();

    void updateView(void);
    void updateModel(void);

private:
    Ui::simView7 *ui;
};

#endif // SIMVIEW7_H
