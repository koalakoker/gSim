#include "simModelElement.h"

simModelElement::simModelElement(QObject *parent) : QObject(parent)
{
}

simModelElement::simModelElement(QString label, simModelElementType type, void* pValue, int digit, QObject *parent) :
    QObject(parent),
    m_label(label),
    m_type(type),
    m_pValue(pValue),
    m_digit(digit)
{
}
