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

double SpecificSimParamsTest8::getExcFreq()
{
    return ui->excFreq->value();
}

double SpecificSimParamsTest8::getExcAmpl()
{
   return ui->excAmp->value();
}

void SpecificSimParamsTest8::setExcFreq(double freq)
{
    ui->excFreq->setValue(freq);
}

void SpecificSimParamsTest8::setExcAmpl(double ampl)
{
    ui->excAmp->setValue(ampl);
}
