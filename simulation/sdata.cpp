#include "sdata.h"

SData::SData(int pos)
{
    m_data = QVector<double>(pos);
}


void SData::setElementAt(int pos, double y)
{
    m_data[pos] = y;
}
