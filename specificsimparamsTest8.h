#ifndef SPECIFICSIMPARAMST8_H
#define SPECIFICSIMPARAMST8_H

#include <QWidget>
#include "specificsimparamsempty.h"

namespace Ui {
class SpecificSimParamsTest8;
}

class SpecificSimParamsTest8 : public SpecificSimParamsEmpty
{
    Q_OBJECT

public:
    explicit SpecificSimParamsTest8();
    ~SpecificSimParamsTest8();

    void updateView(void);
    void updateModel(void);

private:
    Ui::SpecificSimParamsTest8 *ui;
};

#endif // SPECIFICSIMPARAMST8_H
