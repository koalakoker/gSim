#include "simView9.h"
#include "simTemplates/simModel/simModel9.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QDoubleSpinBox>
#include <QGroupBox>

simView9::simView9(QWidget *parent) :
    baseSimView(parent)
{
}

simView9::~simView9()
{

}

void simView9::updateView(void)
{
    if (m_sim)
    {
        simModel9* sim = (simModel9*) m_sim;

        QVBoxLayout* mainLayout = new QVBoxLayout();
        QGroupBox* mainGroup = new QGroupBox("Specific sim params");
        QVBoxLayout* mainGroupLayout = new QVBoxLayout();

        for (int i = 0; i < sim->m_userParams.size(); i++)
        {
            QHBoxLayout* hLayout = new QHBoxLayout();

            QLabel* labelW = new QLabel(sim->m_userParams[i]->m_label);
            hLayout->addWidget(labelW);

            if (sim->m_userParams[i]->m_type == SE_double)
            {
                QDoubleSpinBox* doubleSpinBox = new QDoubleSpinBox();
                doubleSpinBox->setDecimals(5);
                doubleSpinBox->setValue(*(double*)(sim->m_userParams[i]->m_pValue));

                hLayout->addWidget(doubleSpinBox);
                m_values.append(doubleSpinBox);
            }

            mainGroupLayout->addItem(hLayout);
        }

        mainGroup->setLayout(mainGroupLayout);
        mainLayout->addWidget(mainGroup);
        setLayout(mainLayout);
    }
}

void simView9::updateModel(void)
{
    simModel9* sim = (simModel9*) m_sim;

    for (int i = 0; i < sim->m_userParams.size(); i++)
    {
        if (sim->m_userParams[i]->m_type == SE_double)
        {
            *(double*)(sim->m_userParams[i]->m_pValue) = m_values[i]->value();
        }
    }
}
