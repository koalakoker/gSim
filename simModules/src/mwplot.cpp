#include "mwplot.h"
#include "ui_mwplot.h"

#include <QFileDialog>
#include <QDebug>

MWPlot::MWPlot(QWidget *parent) : QMainWindow(parent), ui(new Ui::MWPlot), wCursorInfo(NULL)
{
    ui->setupUi(this);
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

void MWPlot::on_actionTest_triggered()
{
    if (wCursorInfo)
        delete wCursorInfo;
    wCursorInfo = new WCursorInfo();
    wCursorInfo->show();
    QVector<QVector<double>> cursorInfo = getCursorValueTrack();
    wCursorInfo->updateInfo(cursorInfo);
}
