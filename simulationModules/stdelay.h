#ifndef STDELAY_H
#define STDELAY_H

#include <QQueue>
#include "simulationModules/stransfer.h"

class STDelay : public STransfer
{
public:
    STDelay(double ts, double delay);

    SDataVector execute(SDataVector in);

private:
    double m_ts;
    double m_delay;

    QQueue<SDataVector> m_queue;
};

#endif // STDELAY_H
