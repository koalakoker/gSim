#ifndef SIMMODELELEMENT_H
#define SIMMODELELEMENT_H

#include <QObject>

typedef enum
{
    SE_double,
    SE_bool
} simModelElementType;

class simModelElement : public QObject
{
    Q_OBJECT
public:
    explicit simModelElement(QObject *parent = nullptr);
    simModelElement(QString label, simModelElementType type, void *pValue, QObject *parent = nullptr);

    QString m_label;
    simModelElementType m_type;
    void* m_pValue;

signals:

public slots:
};

#endif // SIMMODELELEMENT_H
