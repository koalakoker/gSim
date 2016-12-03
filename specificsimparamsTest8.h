#ifndef SPECIFICSIMPARAMS_H
#define SPECIFICSIMPARAMS_H

#include <QWidget>

namespace Ui {
class SpecificSimParamsTest8;
}

class SpecificSimParamsTest8 : public QWidget
{
    Q_OBJECT

public:
    explicit SpecificSimParamsTest8(QWidget *parent = 0);
    ~SpecificSimParamsTest8();

    double getExcFreq();
    double getExcAmpl();
    void setExcFreq(double freq);
    void setExcAmpl(double ampl);

private:
    Ui::SpecificSimParamsTest8 *ui;
};

#endif // SPECIFICSIMPARAMS_H
