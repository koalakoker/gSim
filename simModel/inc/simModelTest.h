#ifndef SIMMODELTEST_H
#define SIMMODELTEST_H

#include"baseSimModel.h"

class simModelTest : public baseSimModel
{
private:
    /********************* *********************/
    /*   Add here parameters for simulation    */
    /********************* *********************/

    /********************* *********************/

public:
    simModelTest();

    /* Specific params for sim */
    // Params

    // Input

    // State

    void startSim(void);
};

#endif // SIMMODELTEST_H
