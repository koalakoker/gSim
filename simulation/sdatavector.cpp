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
