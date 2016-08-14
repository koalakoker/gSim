#ifndef SDATA_H
#define SDATA_H

#include <QVector>

class SData
{
public:
    SData(int pos = 1);
    QVector<double> data() {return m_data;}
    void setData(QVector<double> data){m_data = data;}
    void append(double d){m_data.append(d);}
    int size() {return m_data.size();}

    double elementAt(int pos) {return m_data[pos];}
    void setElementAt(int pos, double y);

    double& operator[](int i){return m_data[i];}

private:
    QVector<double> m_data;
};

#endif // SDATA_H
