#ifndef SIMVIEW9_H
#define SIMVIEW9_H

#include <QWidget>
#include <QDoubleSpinBox>
#include <QList>
#include "baseSimView.h"

class simView9 : public baseSimView
{
    Q_OBJECT

public:
    explicit simView9(QWidget *parent = 0);
    ~simView9();

    void updateView(void);
    void updateModel(void);

private:
    QList<QDoubleSpinBox*> m_values;
};

#endif // SIMVIEW9_H
