#include "oscope.h"

OScope::OScope()
{
    x = QVector<double>(ELEMENT);
    y = QVector<double>(ELEMENT);

    int i;
    for (i = 0; i < ELEMENT; i++)
    {
        x[i] = (double)i / ELEMENT;
        y[i] = x[i];
    }
}
