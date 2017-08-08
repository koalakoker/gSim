#include <QTime>
#include "gsim.h"
#include "ui_gsim.h"

gSim::gSim(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::gSim)
{
    m_simModel = NULL;
    m_simView = NULL;

    ui->setupUi(this);
}

gSim::~gSim()
{
    delete ui;
}

void gSim::on_startSim_clicked()
{
    QTime t;
    t.start();

    m_simModel->setDuration(ui->duration->value());
    m_simModel->setSimTime(ui->stepTime->value());
    m_simModel->setControlTime(ui->controlTime->value());

    if (m_simView)
    {
        // Update specific params
        m_simView->updateModel(); /* Update model before to start sim */
    }

    m_simModel->startSim();

    ui->simInfo->setText(QString("Time elapsed: %1 s").arg((double)t.elapsed()/1000));
}

void gSim::updateProgress(double percentage)
{
    ui->progressBar->setValue(percentage * 100);
}

void gSim::setSimModel(baseSimModel* model)
{
    m_simModel = model;

    /* Update common settings */
    ui->duration->setValue(m_simModel->duration());
    ui->stepTime->setValue(m_simModel->simTime());
    ui->controlTime->setValue(m_simModel->controlTime());

    connect(m_simModel, SIGNAL(updateProgress(double)), this, SLOT(updateProgress(double)));
}

void gSim::setSimView(baseSimView* view)
{
    m_simView = view;
}
