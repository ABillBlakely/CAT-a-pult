
#include "catapult.h"

#define FULLTURN 4096

void initCatapult(void)
{
    initStepper1();
    initStepper2();
}
void setLatch(void)
{
    step1fwd(FULLTURN);
}


void releaseLatch(void)
{
    step1rev(FULLTURN);
}


void setTension(void)
{
    step2fwd(FULLTURN);
}


void releaseTension(void)
{
    step2rev(FULLTURN);
}
