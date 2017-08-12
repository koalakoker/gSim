#ifndef COMMONSIMVIEW_H
#define COMMONSIMVIEW_H

#include <QWidget>
#include <QList>
#include "baseSimView.h"

class commonSimView : public baseSimView
{
    Q_OBJECT

public:
    explicit commonSimView(QWidget *parent = 0);
    ~commonSimView();

    void updateView(void);
    void updateModel(void);

private:
    QList<QWidget*> m_widget;
};

#endif // COMMONSIMVIEW_H
