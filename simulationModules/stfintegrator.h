#ifndef STFINTEGRATOR_H
#define STFINTEGRATOR_H

#include "simulationModules/stransfer.h"
#include "simulationModules/stfdiscretefirstorder.h"
#include "simulationModules/discretetimetransformtype.h"

class STFIntegrator : public STransfer
{
public:
    STFIntegrator(double ts, DiscreteTimeTransformType_t transform = BackwardEuler);

    SDataVector execute(SDataVector in);

private:
    STFDiscreteFirstOrder m_intTF;
};

#endif // STFINTEGRATOR_H
