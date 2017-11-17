#include "wtable.h"

#include <QDebug>

WTable::WTable(QWidget *parent) : QTableWidget(parent)
{

}

void WTable::resizeEvent(QResizeEvent *event)
{
    emit resized();
}
