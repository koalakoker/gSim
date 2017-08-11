#include "simModelElement.h"

simModelElement::simModelElement(QObject *parent) : QObject(parent)
{
}

simModelElement::simModelElement(QString label, simModelElementType type, double value, QObject *parent) :
    QObject(parent),
    m_label(label),
    m_type(type),
    m_value(value)
{
}
