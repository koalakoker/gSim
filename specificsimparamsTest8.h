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

    double getMotSpeedRads();
    double getExcFreq();
    double getExcAmpl();
    double getSinAttenuation();
    double getSinDelay();
    double getSinOffset();
    double getCosAttenuation();
    double getCosDelay();
    double getCosOffset();
    void setMotSpeedRads(double rads);
    void setExcFreq(double freq);
    void setExcAmpl(double ampl);
    void setSinAttenuation(double att);
    void setSinDelay(double rad);
    void setSinOffset(double off);
    void setCosAttenuation(double att);
    void setCosDelay(double rad);
    void setCosOffset(double off);

private:
    Ui::SpecificSimParamsTest8 *ui;
};

#endif // SPECIFICSIMPARAMS_H
