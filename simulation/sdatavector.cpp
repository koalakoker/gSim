#include "sdatavector.h"

SDataVector::SDataVector(int slot)
{
    m_data = QVector<SData>(slot);
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
