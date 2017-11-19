#include "mwplot.h"
#include "ui_mwplot.h"

#include <QFileDialog>
#include <QDebug>

MWPlot::MWPlot(QWidget *parent) : QMainWindow(parent), ui(new Ui::MWPlot), wCursorInfo(NULL)
{
    ui->setupUi(this);
    connect(ui->wplot,SIGNAL(newPlotter()), this, SLOT(onNewPlotter()));
}
MWPlot::~MWPlot()
{
    delete ui;
    if (wCursorInfo)
        delete wCursorInfo;
}

// Public
void MWPlot::loadDataFile(QString fileName)
{
    ui->wplot->loadDataFile(fileName);
}
QVector<QVector<double>> MWPlot::getCursorValueTrack(void)
{
    if (ui->wplot->m_plotter)
        return ui->wplot->m_plotter->getCursorValueTrack();
    return QVector<QVector<double>>();
}
QVector<double> MWPlot::getCursorValueTrack(int cur)
{
    if (ui->wplot->m_plotter)
        return ui->wplot->m_plotter->getCursorValueTrack(cur);
    return QVector<double>();
}
QVector<double> MWPlot::getSelectedCursorValueTrack(void)
{
    if (ui->wplot->m_plotter)
        return ui->wplot->m_plotter->getSelectedCursorValueTrack();
    return QVector<double>();
}

// Slots
void MWPlot::onNewPlotter()
{
    connect(ui->wplot->m_plotter,SIGNAL(cursorChanged()), this, SLOT(onCursorChange()));
    setWindowTitle(ui->wplot->m_fileName);
}
void MWPlot::onCursorChange()
{
    emit cursorChanged();
    if (wCursorInfo)
    {
        wCursorInfo->updateInfo(getCursorValueTrack());
    }
}

// Private Slots
void MWPlot::on_cursorPosChanged(int cur, qreal value)
{
    ui->wplot->m_plotter->setCursorPos(cur, value);
    ui->wplot->updatePlot();
}

// Actions
void MWPlot::on_actionOpen_data_file_triggered()
{
    QString fileName = QFileDialog::getOpenFileName(this,"Open data file","","*.*");
    ui->wplot->loadDataFile(fileName);
}
void MWPlot::on_actionExport_data_file_triggered()
{
    qDebug() << "Export";
}
void MWPlot::on_actionZoom_Undo_triggered()
{
    ui->wplot->zoom_Undo();
}
void MWPlot::on_actionZoom_Redo_triggered()
{
    ui->wplot->zoom_Redo();
}
void MWPlot::on_actionInfo_data_triggered(bool checked)
{
    if (!wCursorInfo)
    {
        wCursorInfo = new WCursorInfo();
        wCursorInfo->show();
        wCursorInfo->updateInfo(getCursorValueTrack());
        connect (wCursorInfo, SIGNAL(cursorPosChanged(int,qreal)), this, SLOT(on_cursorPosChanged(int,qreal)));
    }
    wCursorInfo->setVisible(checked);
}

void MWPlot::on_actionTest_triggered()
{
}

void MWPlot::on_actionBottom_toggled(bool arg1)
{
    if (ui->wplot->m_plotter)
    {
        ui->wplot->m_plotter->m_axsisBottom = arg1;
        ui->wplot->updatePlot();
    }
    ui->actionBottom_Left->blockSignals(true);
    ui->actionBottom_Left->setChecked(ui->actionBottom->isChecked() && ui->actionLeft->isChecked());
    ui->actionBottom_Left->blockSignals(false);
}
void MWPlot::on_actionLeft_toggled(bool arg1)
{
    if (ui->wplot->m_plotter)
    {
        ui->wplot->m_plotter->m_axsisLeft = arg1;
        ui->wplot->updatePlot();
    }
    ui->actionBottom_Left->blockSignals(true);
    ui->actionBottom_Left->setChecked(ui->actionBottom->isChecked() && ui->actionLeft->isChecked());
    ui->actionBottom_Left->blockSignals(false);
}
void MWPlot::on_actionRight_toggled(bool arg1)
{
    if (ui->wplot->m_plotter)
    {
        ui->wplot->m_plotter->m_axsisRight = arg1;
        ui->wplot->updatePlot();
    }
    ui->actionTop_Right->blockSignals(true);
    ui->actionTop_Right->setChecked(ui->actionTop->isChecked() && ui->actionRight->isChecked());
    ui->actionTop_Right->blockSignals(false);
}
void MWPlot::on_actionTop_toggled(bool arg1)
{
    if (ui->wplot->m_plotter)
    {
        ui->wplot->m_plotter->m_axsisTop = arg1;
        ui->wplot->updatePlot();
    }
    ui->actionTop_Right->blockSignals(true);
    ui->actionTop_Right->setChecked(ui->actionTop->isChecked() && ui->actionRight->isChecked());
    ui->actionTop_Right->blockSignals(false);
}
void MWPlot::on_actionBottom_Left_toggled(bool arg1)
{
    ui->actionBottom->setChecked(arg1);
    ui->actionLeft->setChecked(arg1);
}
void MWPlot::on_actionTop_Right_toggled(bool arg1)
{
    ui->actionTop->setChecked(arg1);
    ui->actionRight->setChecked(arg1);
}


void MWPlot::on_actionAdd_triggered()
{
    // Add cursor
    ui->wplot->m_plotter->addCursor();
    ui->wplot->updatePlot();
}
