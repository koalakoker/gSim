#ifndef SDATAVECTOR_H
#define SDATAVECTOR_H

#include <QVector>
#include "sdata.h"

class SDataVector
{
public:
    SDataVector();

    SDataVector(SDataVector dv1, SDataVector dv2) : SDataVector(dv1.value(), dv2.value()) {}
    SDataVector(SDataVector dv1, SDataVector dv2, SDataVector dv3) : SDataVector(dv1.value(), dv2.value(), dv3.value()) {}

    SDataVector(SData d);
    SDataVector(SData d1, SData d2) : SDataVector(d1.value(), d2.value()) {}
    SDataVector(SData d1, SData d2, SData d3) : SDataVector(d1.value(), d2.value(), d3.value()) {}
    SDataVector(SData d1, SData d2, SData d3, SData d4) : SDataVector(d1.value(), d2.value(), d3.value(), d4.value()) {}
    SDataVector(SData d1, SData d2, SData d3, SData d4, SData d5) : SDataVector(d1.value(), d2.value(), d3.value(), d4.value(), d5.value()) {}
    SDataVector(SData d1, SData d2, SData d3, SData d4, SData d5, SData d6) :
        SDataVector(d1.value(), d2.value(), d3.value(), d4.value(), d5.value(), d6.value()) {}
    SDataVector(SData d1, SData d2, SData d3, SData d4, SData d5, SData d6, SData d7) :
        SDataVector(d1.value(), d2.value(), d3.value(), d4.value(), d5.value(), d6.value(), d7.value()) {}
    SDataVector(SData d1, SData d2, SData d3, SData d4, SData d5, SData d6, SData d7, SData d8) :
        SDataVector(d1.value(), d2.value(), d3.value(), d4.value(), d5.value(), d6.value(), d7.value(), d8.value()) {}
    SDataVector(SData d1, SData d2, SData d3, SData d4, SData d5, SData d6, SData d7, SData d8, SData d9) :
        SDataVector(d1.value(), d2.value(), d3.value(), d4.value(), d5.value(), d6.value(), d7.value(), d8.value(), d9.value()) {}
    SDataVector(SData d1, SData d2, SData d3, SData d4, SData d5, SData d6, SData d7, SData d8, SData d9, SData d10) :
        SDataVector(d1.value(), d2.value(), d3.value(), d4.value(), d5.value(), d6.value(), d7.value(), d8.value(), d9.value(), d10.value()) {}


    SDataVector(double d);
    SDataVector(double d1, double d2);
    SDataVector(double d1, double d2, double d3);

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
