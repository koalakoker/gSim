#ifndef OSCOPE_H
#define OSCOPE_H

#include "out.h"
#include "QVector"

#define ELEMENT 100

class OScope : Out
{
public:
    OScope();

    QVector<double> x;
    QVector<double> y;

};

#endif // OSCOPE_H
