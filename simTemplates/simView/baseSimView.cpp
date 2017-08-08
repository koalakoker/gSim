#include "baseSimView.h"
#include "ui_baseSimView.h"

baseSimView::baseSimView(QWidget *parent) :
    QWidget(parent)
{
}

baseSimView::~baseSimView()
{
    delete ui;
}

void baseSimView::setSimModel(baseSimModel* sim)
{
    m_sim = sim;
}

void baseSimView::updateView(void)
{
}

void baseSimView::updateModel(void)
{
}
