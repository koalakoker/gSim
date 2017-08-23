#ifndef STFINTEGRATOR_H
#define STFINTEGRATOR_H

#include "simmodules_global.h"

#include "stransfer.h"
#include "stfdiscretefirstorder.h"
#include "discretetimetransformtype.h"

class SIMMODULESSHARED_EXPORT STFIntegrator : public STransfer
{
public:
    STFIntegrator(double ts, DiscreteTimeTransformType_t transform = BackwardEuler);

    SDataVector execute(SDataVector in);

private:
    STFDiscreteFirstOrder m_intTF;
};

#endif // STFINTEGRATOR_H
