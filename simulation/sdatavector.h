#ifndef SDATAVECTOR_H
#define SDATAVECTOR_H

#include <QVector>
#include "sdata.h"

class SDataVector
{
public:
    SDataVector(int slot = 1);
    SDataVector(SData d);
    SDataVector(double d);
    QVector<SData> data() {return m_data;}
    SData data(int slot){return m_data[slot];}
    double data(int slot, int pos){return m_data[slot].elementAt(pos);}
    double value(){return data(0, 0);}
    void setValue(double y){setData(0, 0, y);}
    void setData(QVector<SData> data){m_data = data;}
    void setData(int slot, SData data);
    void setData(int slot, int pos, double y);
    int length() {return m_data.length();}
    void append(SDataVector dv);
    void append(SData d);

private:
    QVector<SData> m_data;
};

#endif // SDATAVECTOR_H
