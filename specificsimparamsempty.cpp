#include "specificsimparamsempty.h"
#include "ui_specificsimparamsempty.h"

SpecificSimParamsEmpty::SpecificSimParamsEmpty(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SpecificSimParamsEmpty)
{
    ui->setupUi(this);
}

SpecificSimParamsEmpty::~SpecificSimParamsEmpty()
{
    delete ui;
}
