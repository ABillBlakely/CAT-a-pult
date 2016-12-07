
#include "catapult.h"

void initCatapult(void)
{
    initStepper1();
    initStepper2();
}
void setLatch(void)
{
    step1rev(LATCHTURN);
}


void releaseLatch(void)
{
    step1fwd(LATCHTURN);
}


void setTension(void)
{
    step2fwd(TENSIONTURN);
}


void releaseTension(void)
{
    step2rev(TENSIONTURN);
}
