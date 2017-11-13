#include "mwplot.h"
#include "ui_mwplot.h"

#include <QFileDialog>
#include <QDebug>

MWPlot::MWPlot(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MWPlot)
{
    ui->setupUi(this);
}

MWPlot::~MWPlot()
{
    delete ui;
}

void MWPlot::on_actionOpen_data_file_triggered()
{
    QString fileName = QFileDialog::getOpenFileName(this,"Open data file","","*.*");
    ui->centralwidget->loadDataFile(fileName);
}
void MWPlot::on_actionExport_data_file_triggered()
{
    qDebug() << "Export";
}
void MWPlot::on_actionZoom_Undo_triggered()
{
    ui->centralwidget->zoom_Undo();
}
void MWPlot::on_actionZoom_Redo_triggered()
{
    ui->centralwidget->zoom_Redo();
}
