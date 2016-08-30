#include "svm.h"
#include "math.h"

#define PI 3.14159265359

svm::svm()
{

}

double svm::calcModuleNorm(int modulePerc)
{
    return ((double)modulePerc / 100.0);
}

double svm::calcRad(int angleDeg)
{
    return (2*PI*(double)angleDeg) / 360.0;
}

alphabeta_t svm::calcAlphaBeta(double moduleNorm, double phaseRad)
{
    alphabeta_t ab = { 0.0, 0.0};
    if ((moduleNorm < 0.0) || (moduleNorm > 1.0))
        return ab;

    ab.alpha = moduleNorm * cos(phaseRad);
    ab.beta = moduleNorm * sin(phaseRad);
    return ab;
}

alphabeta_t svm::calcAlphaBeta(int modulePerc, int angleDeg)
{
    return svm::calcAlphaBeta(svm::calcModuleNorm(modulePerc),svm::calcRad(angleDeg));
}

abc_t svm::calcSVM(alphabeta_t ab)
{
    abc_t out = {0.0, 0.0, 0.0, 0};

    double Ua = sqrt(3) * ab.alpha;
    double Ub = ab.beta;

    double X = Ub;
    double Y = (Ua + Ub) / 2;
    double Z = (Ub - Ua) / 2;

    if (Y < 0)
    {
        if (Z < 0)
        {
            out.sect = 5;
        }
        else
        {
            if (X > 0)
            {
                out.sect = 3;
            }
            else
            {
                out.sect = 4;
            }
        }
    }
    else
    {
        if (Z < 0)
        {
            if (X > 0)
            {
                out.sect = 1;
            }
            else
            {
                out.sect = 6;
            }
        }
        else
        {
            out.sect = 2;
        }
    }

    if ((out.sect == 1) | (out.sect == 4))
    {
        out.a = (1 + X - Z) / 2;
        out.b = out.a + Z;
        out.c = out.b - X;
    }
    else
    {
        if ((out.sect == 2) | (out.sect == 5))
        {
            out.a = (1 + Y - Z) / 2;
            out.b = out.a + Z;
            out.c = out.a - Y;
        }
        else
        {
            out.a = (1 - X + Y) / 2;
            out.c = out.a - Y;
            out.b = out.c + X;
        }
    }

//    //FLAT BOTTOM
//    T = [Ta Tb Tc];
//    D = min(T);
//    Ta = Ta - D;
//    Tb = Tb - D;
//    Tc = Tc - D;

    return out;
}
