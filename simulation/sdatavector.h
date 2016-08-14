#ifndef SDATAVECTOR_H
#define SDATAVECTOR_H

#include <QVector>
#include "sdata.h"

class SDataVector
{
public:
    SDataVector(int slot = 1);
    QVector<SData> data() {return m_data;}
    SData data(int slot){return m_data[slot];}
    double data(int slot, int pos){return m_data[slot].elementAt(pos);}
    void setData(QVector<SData> data){m_data = data;}
    void setData(int slot, SData data);
    void setData(int slot, int pos, double y);
    int length() {return m_data.length();}

private:
    QVector<SData> m_data;
};

#endif // SDATAVECTOR_H
