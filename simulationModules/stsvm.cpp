#include "stsvm.h"
#include "svm.h"

STSVM::STSVM()
{

}

SDataVector STSVM::execute(SDataVector in)
{
    double alpha = in.data(0, 0);
    double beta = in.data(0, 1);
    alphabeta_t alphabeta = {alpha, beta};
    abc_t abc = svm::calcSVM(alphabeta);
    return (SDataVector(abc.a, abc.b, abc.c));
}
