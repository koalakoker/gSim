#include "sdata.h"

SData::SData(int pos)
{
    m_data = QVector<double>(pos);
}

SData::SData(double d)
{
    m_data = QVector<double>(0);
    m_data.append(d);
}


void SData::setElementAt(int pos, double y)
{
    m_data[pos] = y;
}
