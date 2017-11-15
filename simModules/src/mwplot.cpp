#include "mwplot.h"
#include "ui_mwplot.h"

#include <QFileDialog>
#include <QDebug>

MWPlot::MWPlot(QWidget *parent) : QMainWindow(parent), ui(new Ui::MWPlot), wCursorInfo(NULL)
{
    ui->setupUi(this);
    connect(ui->wplot,SIGNAL(cursorChanged()), this, SLOT(onCursorChange()));
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
    return ui->wplot->getCursorValueTrack();
}
QVector<double> MWPlot::getCursorValueTrack(int cur)
{
    return ui->wplot->getCursorValueTrack(cur);
}
QVector<double> MWPlot::getSelectedCursorValueTrack(void)
{
    return ui->wplot->getSelectedCursorValueTrack();
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

void MWPlot::onCursorChange()
{
    emit cursorChanged();
    if (wCursorInfo)
    {
        wCursorInfo->updateInfo(getCursorValueTrack());
    }
}
void MWPlot::on_actionTest_triggered()
{
    bool oldPos = false;
    QPoint pos;
    QVector<QVector<double>> cursorInfo = getCursorValueTrack();
    if (cursorInfo.size() > 0)
    {
        if (wCursorInfo)
        {
            pos = wCursorInfo->pos();
            delete wCursorInfo;
            oldPos = true;
        }
        wCursorInfo = new WCursorInfo();
        wCursorInfo->show();
        wCursorInfo->updateInfo(cursorInfo);
        if (oldPos)
        {
            wCursorInfo->move(pos);
        }
    }
}
