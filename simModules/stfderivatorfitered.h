#ifndef STFDERIVATORFITERED_H
#define STFDERIVATORFITERED_H

#include "simModules/stransfer.h"
#include "simModules/stfdiscretefirstorder.h"
#include "simModules/discretetimetransformtype.h"

class STFDerivatorFitered : public STransfer
{
public:
    STFDerivatorFitered(double ts, double n, DiscreteTimeTransformType_t transform = BackwardEuler);

    SDataVector execute(SDataVector in);

private:
    STFDiscreteFirstOrder m_derTF;
};

#endif // STFDERIVATORFITERED_H
