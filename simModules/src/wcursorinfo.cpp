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

/* Copy pasted from the WEB */
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
    const Qt::GlobalColor plotColor[] = {Qt::black,Qt::black, Qt::blue, Qt::green, Qt::red};
    int cursorNum = cursorInfo.size();
    if (cursorNum > 0)
    {
        int trackNum = cursorInfo[0].size();
        ui->tableWidget->setColumnCount(trackNum);

        QStringList horizontalLabels;
        horizontalLabels << "x";
        for (int i = 0; i < trackNum; i++)
        {
            horizontalLabels << QString("y%1").arg(i+1);
        }
        ui->tableWidget->setHorizontalHeaderLabels(horizontalLabels);

        ui->tableWidget->setRowCount(cursorNum);
        for (int cur = 0; cur < cursorNum; cur++)
        {
            for (int track = 0;  track < trackNum;  track++)
            {
                QTableWidgetItem* cell = new QTableWidgetItem(QString::number(cursorInfo[cur][track]));
                cell->setTextColor(plotColor[track]);
                ui->tableWidget->setItem(cur,track,cell);
            }
        }
    }
    else
    {
        ui->tableWidget->setColumnCount(2);
        ui->tableWidget->setRowCount(0);
        QStringList horizontalLabels;
        horizontalLabels << "x" << "y";
        ui->tableWidget->setHorizontalHeaderLabels(horizontalLabels);
    }
    ui->tableWidget->setMaximumSize(myGetQTableWidgetSize(ui->tableWidget));
    ui->tableWidget->setMinimumSize(ui->tableWidget->maximumSize()); // optional
    resize(ui->tableWidget->maximumSize());
}
