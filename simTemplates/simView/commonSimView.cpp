#include "commonSimView.h"
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
        if (m_simModel->m_userParams.size() == 0)
        {
            QLabel* label = new QLabel("Parameter list empty.");
            mainLayout->addWidget(label);
        }
        else
        {
            QString firstGroupName = "Specific simulation parameters";
            int startingElement = 0;
            bool isFirstGroup = (m_simModel->m_userParams[0]->m_type == SE_group);
            if (isFirstGroup)
            {
                firstGroupName = m_simModel->m_userParams[0]->m_label;
                startingElement = 1;
            }
            QGroupBox* group = new QGroupBox(firstGroupName);
            QVBoxLayout* groupLayout = new QVBoxLayout();
            if (isFirstGroup)
            {
                m_widget.append(group);
            }

            for (int i = startingElement; i < m_simModel->m_userParams.size(); i++)
            {

                switch (m_simModel->m_userParams[i]->m_type)
                {
                    case SE_double:
                    {
                        QHBoxLayout* hLayout = new QHBoxLayout();

                        QLabel* labelW = new QLabel(m_simModel->m_userParams[i]->m_label);
                        hLayout->addWidget(labelW);

                        QDoubleSpinBox* doubleSpinBox = new QDoubleSpinBox();
                        doubleSpinBox->setDecimals(m_simModel->m_userParams[i]->m_digit);
                        doubleSpinBox->setMaximum(999999999);
                        doubleSpinBox->setMinimum(-999999999);
                        doubleSpinBox->setValue(*static_cast<double*>(m_simModel->m_userParams[i]->m_pValue));

                        hLayout->addWidget(doubleSpinBox);
                        m_widget.append(doubleSpinBox);

                        groupLayout->addItem(hLayout);
                    }
                    break;

                    case SE_bool:
                    {
                        QHBoxLayout* hLayout = new QHBoxLayout();

                        QLabel* labelW = new QLabel(m_simModel->m_userParams[i]->m_label);
                        hLayout->addWidget(labelW);

                        QCheckBox* checkBox = new QCheckBox();
                        checkBox->setChecked(*static_cast<bool*>(m_simModel->m_userParams[i]->m_pValue));

                        hLayout->addWidget(checkBox);
                        m_widget.append(checkBox);

                        groupLayout->addItem(hLayout);
                    }
                    break;

                    case SE_int:
                    {
                        QHBoxLayout* hLayout = new QHBoxLayout();

                        QLabel* labelW = new QLabel(m_simModel->m_userParams[i]->m_label);
                        hLayout->addWidget(labelW);

                        QSpinBox* spinBox = new QSpinBox();
                        spinBox->setValue(*static_cast<int*>(m_simModel->m_userParams[i]->m_pValue));

                        hLayout->addWidget(spinBox);
                        m_widget.append(spinBox);

                        groupLayout->addItem(hLayout);
                    }
                    break;

                    case SE_group:
                    {
                        group->setLayout(groupLayout);
                        mainLayout->addWidget(group);

                        group = new QGroupBox(m_simModel->m_userParams[i]->m_label);
                        groupLayout = new QVBoxLayout();

                        m_widget.append(group);
                    }
                    break;
                }
            }

            group->setLayout(groupLayout);
            mainLayout->addWidget(group);

        }
    }
    else
    {
        QLabel* label = new QLabel("Model not set into the view!");
        mainLayout->addWidget(label);
    }

    QLayout* old = layout();
    delete old;
    setLayout(mainLayout);

}

void commonSimView::updateModel(void)
{
    for (int i = 0; i < m_simModel->m_userParams.size(); i++)
    {
        if (m_simModel->m_userParams[i]->m_type == SE_double)
        {
            QDoubleSpinBox* doubleSpinBox = static_cast<QDoubleSpinBox*>(m_widget[i]);
            *static_cast<double*>(m_simModel->m_userParams[i]->m_pValue) = doubleSpinBox->value();
        }

        if (m_simModel->m_userParams[i]->m_type == SE_bool)
        {
            QCheckBox* checkBox = static_cast<QCheckBox*>(m_widget[i]);
            *static_cast<bool*>(m_simModel->m_userParams[i]->m_pValue) = checkBox->isChecked();
        }
    }
}
