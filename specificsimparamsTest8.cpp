#include "specificsimparamsTest8.h"
#include "ui_specificsimparams.h"

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
