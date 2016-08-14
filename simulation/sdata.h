#ifndef SDATA_H
#define SDATA_H

#include <QVector>

class SData
{
public:
    SData();
    QVector<double> data() {return m_data;}
    void setData(QVector<double> data){m_data = data;}
    int length() {return m_data.length();}

private:
    QVector<double> m_data;
};

#endif // SDATA_H
