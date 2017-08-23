#ifndef BASESIMVIEW_H
#define BASESIMVIEW_H

#include <QWidget>
#include "simModel/inc/baseSimModel.h"

class baseSimView : public QWidget
{
    Q_OBJECT

public:
    explicit baseSimView(QWidget *parent = 0);
    ~baseSimView();

    void setSimModel(baseSimModel* sim);
    void setMainWidget(QWidget* mainW);
    void resetMainWidget(void);
    virtual void updateView(void);
    virtual void updateModel(void);

private:

protected:
    baseSimModel* m_simModel;
};

#endif // BASESIMVIEW_H
