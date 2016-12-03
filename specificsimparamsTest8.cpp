#include "specificsimparamsTest8.h"
#include "ui_specificsimparamsTest8.h"

SpecificSimParamsTest8::SpecificSimParamsTest8(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SpecificSimParamsTest8)
{
    ui->setupUi(this);
}

SpecificSimParamsTest8::~SpecificSimParamsTest8()
{
    delete ui;
}

double SpecificSimParamsTest8::getMotSpeedRads()
{
    return ui->motSpeedRads->value();
}

double SpecificSimParamsTest8::getExcFreq()
{
    return ui->excFreq->value();
}

double SpecificSimParamsTest8::getExcAmpl()
{
   return ui->excAmp->value();
}

double SpecificSimParamsTest8::getSinAttenuation()
{
    return ui->sinAttenuation->value();
}

double SpecificSimParamsTest8::getSinDelay()
{
    return ui->sinDelay->value();
}

double SpecificSimParamsTest8::getSinOffset()
{
    return ui->sinOffset->value();
}

double SpecificSimParamsTest8::getCosAttenuation()
{
    return ui->cosAttenuation->value();
}

double SpecificSimParamsTest8::getCosDelay()
{
    return ui->cosDelay->value();
}

double SpecificSimParamsTest8::getCosOffset()
{
    return ui->cosOffset->value();
}

void SpecificSimParamsTest8::setMotSpeedRads(double rads)
{
    ui->motSpeedRads->setValue(rads);
}

void SpecificSimParamsTest8::setExcFreq(double freq)
{
    ui->excFreq->setValue(freq);
}

void SpecificSimParamsTest8::setExcAmpl(double ampl)
{
    ui->excAmp->setValue(ampl);
}

void SpecificSimParamsTest8::setSinAttenuation(double att)
{
    ui->sinAttenuation->setValue(att);
}

void SpecificSimParamsTest8::setSinDelay(double rad)
{
    ui->sinDelay->setValue(rad);
}

void SpecificSimParamsTest8::setSinOffset(double off)
{
    ui->sinOffset->setValue(off);
}

void SpecificSimParamsTest8::setCosAttenuation(double att)
{
    ui->cosAttenuation->setValue(att);
}

void SpecificSimParamsTest8::setCosDelay(double rad)
{
    ui->sinDelay->setValue(rad);
}

void SpecificSimParamsTest8::setCosOffset(double off)
{
    ui->sinOffset->setValue(off);
}
