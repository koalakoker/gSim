#include "sdatavector.h"

SDataVector::SDataVector()
{
    m_data = QVector<SData>(1);
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

SDataVector::SDataVector(double d1, double d2)
{
    SData data = SData(0);
    data.append(d1);
    data.append(d2);
    m_data = QVector<SData>();
    m_data.append(data);
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
