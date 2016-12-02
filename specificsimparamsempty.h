#ifndef SPECIFICSIMPARAMSEMPTY_H
#define SPECIFICSIMPARAMSEMPTY_H

#include <QWidget>

namespace Ui {
class SpecificSimParamsEmpty;
}

class SpecificSimParamsEmpty : public QWidget
{
    Q_OBJECT

public:
    explicit SpecificSimParamsEmpty(QWidget *parent = 0);
    ~SpecificSimParamsEmpty();

private:
    Ui::SpecificSimParamsEmpty *ui;
};

#endif // SPECIFICSIMPARAMSEMPTY_H
