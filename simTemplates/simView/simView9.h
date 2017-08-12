#ifndef SIMVIEW9_H
#define SIMVIEW9_H

#include <QWidget>
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
    QList<QWidget*> m_widget;
};

#endif // SIMVIEW9_H
