#include "commonSimView.h"
#include "simTemplates/simModel/simModel9.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QDoubleSpinBox>
#include <QCheckBox>
#include <QSpinBox>
#include <QGroupBox>

commonSimView::commonSimView(QWidget *parent) :
baseSimView(parent)
{
}

commonSimView::~commonSimView()
{
}

void commonSimView::updateView(void)
{
    QVBoxLayout* mainLayout = new QVBoxLayout();

    if (m_simModel)
    {
        QGroupBox* mainGroup = new QGroupBox("Specific simulation params");
        QVBoxLayout* mainGroupLayout = new QVBoxLayout();

        for (int i = 0; i < m_simModel->m_userParams.size(); i++)
        {
            QHBoxLayout* hLayout = new QHBoxLayout();

            QLabel* labelW = new QLabel(m_simModel->m_userParams[i]->m_label);
            hLayout->addWidget(labelW);

            switch (m_simModel->m_userParams[i]->m_type)
            {
                case SE_double:
                {
                    QDoubleSpinBox* doubleSpinBox = new QDoubleSpinBox();
                    doubleSpinBox->setDecimals(5);
                    doubleSpinBox->setValue(*(double*)(m_simModel->m_userParams[i]->m_pValue));

                    hLayout->addWidget(doubleSpinBox);
                    m_widget.append(doubleSpinBox);
                }
                break;

                case SE_bool:
                {
                    QCheckBox* checkBox = new QCheckBox();
                    checkBox->setChecked(*(bool*)(m_simModel->m_userParams[i]->m_pValue));

                    hLayout->addWidget(checkBox);
                    m_widget.append(checkBox);
                }
                break;

                case SE_int:
                {
                    QSpinBox* spinBox = new QSpinBox();
                    spinBox->setValue(*(int*)(m_simModel->m_userParams[i]->m_pValue));

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
    else
    {
        QLabel* label = new QLabel("Model not set into the view!");
        mainLayout->addWidget(label);
        setLayout(mainLayout);
    }
}

void commonSimView::updateModel(void)
{
    for (int i = 0; i < m_simModel->m_userParams.size(); i++)
    {
        if (m_simModel->m_userParams[i]->m_type == SE_double)
        {
            QDoubleSpinBox* doubleSpinBox = (QDoubleSpinBox*)m_widget[i];
            *(double*)(m_simModel->m_userParams[i]->m_pValue) = doubleSpinBox->value();
        }

        if (m_simModel->m_userParams[i]->m_type == SE_bool)
        {
            QCheckBox* checkBox = (QCheckBox*)m_widget[i];
            *(bool*)(m_simModel->m_userParams[i]->m_pValue) = checkBox->isChecked();
        }
    }
}
