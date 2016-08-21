#ifndef STFDERIVATORFITERED_H
#define STFDERIVATORFITERED_H

#include "simulation/stransfer.h"
#include "simulation/stfdiscretefirstorder.h"
#include "simulation/discretetimetransformtype.h"

class STFDerivatorFitered : public STransfer
{
public:
    STFDerivatorFitered(double ts, double n, DiscreteTimeTransformType_t transform = BackwardEuler);

    SDataVector execute(SDataVector in);

private:
    STFDiscreteFirstOrder m_derTF;
};

#endif // STFDERIVATORFITERED_H
