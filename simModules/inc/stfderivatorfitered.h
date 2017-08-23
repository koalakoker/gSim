#ifndef STFDERIVATORFITERED_H
#define STFDERIVATORFITERED_H

#include "simmodules_global.h"

#include "stransfer.h"
#include "stfdiscretefirstorder.h"
#include "discretetimetransformtype.h"

class SIMMODULESSHARED_EXPORT STFDerivatorFitered : public STransfer
{
public:
    STFDerivatorFitered(double ts, double n, DiscreteTimeTransformType_t transform = BackwardEuler);

    SDataVector execute(SDataVector in);

private:
    STFDiscreteFirstOrder m_derTF;
};

#endif // STFDERIVATORFITERED_H
