#ifndef SIMVIEW9_H
#define SIMVIEW9_H

#include <QWidget>
#include <QDoubleSpinBox>
#include "baseSimView.h"

#define NELEM 5

class simView9 : public baseSimView
{
    Q_OBJECT

public:
    explicit simView9(QWidget *parent = 0);
    ~simView9();

    void updateView(void);
    void updateModel(void);

private:
    QDoubleSpinBox* m_values[NELEM];
};

#endif // SIMVIEW9_H
