#include "sdatavector.h"

SDataVector::SDataVector()
{
    m_data = QVector<SData>(0);
}

SDataVector::SDataVector(SData d)
{
    m_data = QVector<SData>();
    m_data.append(d);
}

void SDataVector::setData(int slot, SData data)
{
    m_data[slot] = data;
}

void SDataVector::setData(int slot, int pos, double y)
{
    m_data[slot].setElementAt(pos, y);
}

void SDataVector::append(SDataVector dv)
{
    m_data.append(dv.data());
}

void SDataVector::append(SData d)
{
    m_data.append(d);
}
