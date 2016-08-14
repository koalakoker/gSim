#ifndef SDATAVECTOR_H
#define SDATAVECTOR_H

#include <QVector>
#include "sdata.h"

class SDataVector
{
public:
    SDataVector();
    QVector<SData> data() {return m_data;}
    void setData(QVector<SData> data){m_data = data;}
    int length() {return m_data.length();}

private:
    QVector<SData> m_data;
};

#endif // SDATAVECTOR_H
