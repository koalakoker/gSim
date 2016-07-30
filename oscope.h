#ifndef OSCOPE_H
#define OSCOPE_H

#include "QVector"

#define ELEMENT 100

class OScope
{
public:
    OScope();

    QVector<double> x;
    QVector<double> y;

};

#endif // OSCOPE_H
