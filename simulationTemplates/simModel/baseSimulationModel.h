#ifndef BASESIMULATIONMODEL_H
#define BASESIMULATIONMODEL_H

#include <QObject>

class baseSimulationModel : public QObject
{
    Q_OBJECT

public:
    baseSimulationModel();
    virtual void startSimulation(void);
    double duration(){return m_duration;}
    void setDuration(double duration){m_duration = duration;}
    double simulationTime(){return m_ts;}
    void setSimulationTime(double ts){m_ts = ts;}
    double controlTime(){return m_tc;}
    void setControlTime(double tc){m_tc = tc;}

    int m_simulation;
    QString m_description;

protected:
    double m_t;
    double m_ts;
    double m_tc;
    double m_duration;

private:
    void testSimulation0();
    void testSimulation1();
    void testSimulation2();

signals:
    void updateProgress(double percentage);
};

#endif // BASESIMULATIONMODEL_H
