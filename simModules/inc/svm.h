#ifndef SVMCALC_H
#define SVMCALC_H

typedef struct abc
{
    double a;
    double b;
    double c;
    int sect;
} abc_t;

typedef struct alphabeta
{
    double alpha;
    double beta;
} alphabeta_t;


class svm
{
public:
    svm();

    static double calcModuleNorm(int modulePerc);
    static double calcRad(int angleDeg);
    static alphabeta_t calcAlphaBeta(double moduleNorm, double phaseRad);
    static alphabeta_t calcAlphaBeta(int modulePerc, int angleDeg);
    static abc_t calcSVM(alphabeta_t ab);
};

#endif // SVMCALC_H
