#ifndef BASESIMVIEW_H
#define BASESIMVIEW_H

#include <QWidget>
#include "simTemplates/simModel/baseSimModel.h"

namespace Ui {
class SpecificSimParamsEmpty;
}

class baseSimView : public QWidget
{
    Q_OBJECT

public:
    explicit baseSimView(QWidget *parent = 0);
    ~baseSimView();

    void setSimModel(baseSimModel* sim);
    virtual void updateView(void);
    virtual void updateModel(void);

private:
    Ui::SpecificSimParamsEmpty *ui;

protected:
    baseSimModel* m_sim;
};

#endif // BASESIMVIEW_H
