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

static QSize myGetQTableWidgetSize(QTableWidget *t) {
   int w = t->verticalHeader()->width() + 4; // +4 seems to be needed
   for (int i = 0; i < t->columnCount(); i++)
      w += t->columnWidth(i); // seems to include gridline (on my machine)
   int h = t->horizontalHeader()->height() + 4;
   for (int i = 0; i < t->rowCount(); i++)
      h += t->rowHeight(i);
   return QSize(w, h);
}

void WCursorInfo::updateInfo(QVector<QVector<double>> cursorInfo)
{
    int cursorNum = cursorInfo.size();
    if (cursorNum > 0)
    {
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
        ui->tableWidget->setMaximumSize(myGetQTableWidgetSize(ui->tableWidget));
        ui->tableWidget->setMinimumSize(ui->tableWidget->maximumSize()); // optional
        resize(ui->tableWidget->size());
    }
}

void WCursorInfo::on_pushButton_clicked()
{
    //QTableWidgetItem* cell = new QTableWidgetItem("0");
    //ui->tableWidget->setItem(0,0,cell);
}
