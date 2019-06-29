#ifndef BASESIMMODEL_H
#define BASESIMMODEL_H

#include "gsimmodel_global.h"

#include <QObject>
#include <QList>
#include <QWidget>
#include "simModelElement.h"
#include "plot/ssscope.h"

class GSIMMODELSHARED_EXPORT baseSimModel : public QObject
{
    Q_OBJECT

public:
    baseSimModel();
    virtual void startSim(void);
    double duration(){return m_duration;}
    void setDuration(double duration){m_duration = duration;}
    double simTime(){return m_ts;}
    void setSimTime(double ts){m_ts = ts;}
    double controlTime(){return m_tc;}
    void setControlTime(double tc){m_tc = tc;}
    SSScope *createScope(QString name);
    void closeScopes(void);

    int m_sim;
    QString m_description;
    QList<simModelElement*> m_userParams;

protected:
    double m_t;
    double m_ts;
    double m_tc;
    double m_duration;

    QVector<QWidget*> m_scopes;

private:


signals:
    void updateProgress(double percentage);
};

#endif // BASESIMMODEL_H
