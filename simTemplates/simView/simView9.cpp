#include "simView9.h"
#include "simTemplates/simModel/simModel9.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QDoubleSpinBox>
#include <QCheckBox>
#include <QSpinBox>
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
    if (m_simModel)
    {
        simModel9* sim = (simModel9*) m_simModel;

        QVBoxLayout* mainLayout = new QVBoxLayout();
        QGroupBox* mainGroup = new QGroupBox("Specific sim params");
        QVBoxLayout* mainGroupLayout = new QVBoxLayout();

        for (int i = 0; i < sim->m_userParams.size(); i++)
        {
            QHBoxLayout* hLayout = new QHBoxLayout();

            QLabel* labelW = new QLabel(sim->m_userParams[i]->m_label);
            hLayout->addWidget(labelW);

            switch (sim->m_userParams[i]->m_type)
            {
                case SE_double:
                {
                    QDoubleSpinBox* doubleSpinBox = new QDoubleSpinBox();
                    doubleSpinBox->setDecimals(5);
                    doubleSpinBox->setValue(*(double*)(sim->m_userParams[i]->m_pValue));

                    hLayout->addWidget(doubleSpinBox);
                    m_widget.append(doubleSpinBox);
                }
                break;

                case SE_bool:
                {
                    QCheckBox* checkBox = new QCheckBox();
                    checkBox->setChecked(*(bool*)(sim->m_userParams[i]->m_pValue));

                    hLayout->addWidget(checkBox);
                    m_widget.append(checkBox);
                }
                break;

                case SE_int:
                {
                    QSpinBox* spinBox = new QSpinBox();
                    spinBox->setValue(*(int*)(sim->m_userParams[i]->m_pValue));

                    hLayout->addWidget(spinBox);
                    m_widget.append(spinBox);
                }
                break;
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
    simModel9* sim = (simModel9*) m_simModel;

    for (int i = 0; i < sim->m_userParams.size(); i++)
    {
        if (sim->m_userParams[i]->m_type == SE_double)
        {
            QDoubleSpinBox* doubleSpinBox = (QDoubleSpinBox*)m_widget[i];
            *(double*)(sim->m_userParams[i]->m_pValue) = doubleSpinBox->value();
        }

        if (sim->m_userParams[i]->m_type == SE_bool)
        {
            QCheckBox* checkBox = (QCheckBox*)m_widget[i];
            *(bool*)(sim->m_userParams[i]->m_pValue) = checkBox->isChecked();
        }
    }
}
