#ifndef STFINTEGRATOR_H
#define STFINTEGRATOR_H

#include "simulation/stransfer.h"
#include "simulation/stfdiscretefirstorder.h"
#include "simulation/discretetimetransformtype.h"

class STFIntegrator : public STransfer
{
public:
    STFIntegrator(double ts, DiscreteTimeTransformType_t transform = BackwardEuler);

    SDataVector execute(SDataVector in);

private:
    STFDiscreteFirstOrder m_intTF;
};

#endif // STFINTEGRATOR_H
