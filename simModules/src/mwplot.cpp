#include "mwplot.h"
#include "ui_mwplot.h"

#include <QFileDialog>
#include <QDebug>

MWPlot::MWPlot(QWidget *parent) : QMainWindow(parent), ui(new Ui::MWPlot), wCursorInfo(NULL)
{
    ui->setupUi(this);
    connect(ui->wplot,SIGNAL(newPlotter()), this, SLOT(onNewPlotter()));
    wCursorInfo = new WCursorInfo();
    wCursorInfo->updateInfo(getCursorValueTrack());
    connect (wCursorInfo, SIGNAL(cursorPosChanged(int,qreal)), this, SLOT(on_cursorPosChanged(int,qreal)));
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
void MWPlot::on_actionInfo_data_changed()
{
    if (ui->actionInfo_data->isChecked())
    {
        wCursorInfo->show();
    }
    else
    {
        wCursorInfo->hide();
    }
}

void MWPlot::on_actionTest_triggered()
{
}


