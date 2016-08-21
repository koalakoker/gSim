#include "sdatavector.h"

SDataVector::SDataVector(int slot)
{
    m_data = QVector<SData>(slot);
}

SDataVector::SDataVector(SData d)
{
    m_data = QVector<SData>();
    m_data.append(d);
}

SDataVector::SDataVector(double d) : m_data(QVector<SData>(1))
{
    setData(0,0,d);
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
