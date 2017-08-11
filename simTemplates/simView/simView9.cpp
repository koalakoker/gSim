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
    QString label[NELEM] = {
        "Inertia",
        "Fricrion",
        "Poles pairs",
        "Kp",
        "Ki"
    };

    QVBoxLayout* mainLayout = new QVBoxLayout();
    QGroupBox* mainGroup = new QGroupBox("Specific sim params");
    QVBoxLayout* mainGroupLayout = new QVBoxLayout();

    for (int i = 0; i < NELEM; i++)
    {
        QHBoxLayout* hLayout = new QHBoxLayout();

        QLabel* labelW = new QLabel(label[i]);
        hLayout->addWidget(labelW);

        QDoubleSpinBox* doubleSpinBox = new QDoubleSpinBox();
        doubleSpinBox->setDecimals(5);

        hLayout->addWidget(doubleSpinBox);
        m_values[i] = doubleSpinBox;

        mainGroupLayout->addItem(hLayout);
    }

    mainGroup->setLayout(mainGroupLayout);
    mainLayout->addWidget(mainGroup);
    setLayout(mainLayout);
}

simView9::~simView9()
{

}

void simView9::updateView(void)
{
    simModel9* sim = (simModel9*) m_sim;
    m_values[0]->setValue(sim->m_j);
    m_values[1]->setValue(sim->m_f);
    m_values[2]->setValue(sim->m_pp);
    m_values[3]->setValue(sim->m_pi_kp);
    m_values[4]->setValue(sim->m_pi_ki);
}

void simView9::updateModel(void)
{
    simModel9* sim = (simModel9*) m_sim;
    sim->m_j = m_values[0]->value();
    sim->m_f = m_values[1]->value();
    sim->m_pp = m_values[2]->value();
    sim->m_pi_kp = m_values[3]->value();
    sim->m_pi_ki = m_values[4]->value();
}
