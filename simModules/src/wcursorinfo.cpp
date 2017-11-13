#include "wcursorinfo.h"
#include "ui_wcursorinfo.h"

#include <QDebug>

WCursorInfo::WCursorInfo(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::WCursorInfo)
{
    ui->setupUi(this);

}

WCursorInfo::~WCursorInfo()
{
    delete ui;
}

void WCursorInfo::updateInfo(QVector<QVector<double>> cursorInfo)
{
    int cursorNum = cursorInfo.size();
    int trackNum = cursorInfo[0].size();
    ui->tableWidget->setColumnCount(trackNum);
    ui->tableWidget->setRowCount(cursorNum);
    for (int cur = 0; cur < cursorNum; cur++)
    {
        //qDebug() << "Cursor: " << cur;
        for (int track = 0;  track < trackNum;  track++)
        {
            //qDebug() << "Track: " << track << " Value:" << cursorInfo[cur][track];
            QTableWidgetItem* cell = new QTableWidgetItem(QString::number(cursorInfo[cur][track]));
            ui->tableWidget->setItem(cur,track,cell);
        }
    }
}

void WCursorInfo::on_pushButton_clicked()
{
    QTableWidgetItem* cell = new QTableWidgetItem("0");
    ui->tableWidget->setItem(0,0,cell);
}
