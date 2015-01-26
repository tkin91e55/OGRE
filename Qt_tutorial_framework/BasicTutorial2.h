/*
-----------------------------------------------------------------------------
Filename:    BasicTutorial2.h
-----------------------------------------------------------------------------
*/
#ifndef __BasicTutorial2_h_
#define __BasicTutorial2_h_

#include "BaseApplication.h"

class BasicTutorial2 : public BaseApplication
{
public:
    BasicTutorial2(void);
    virtual ~BasicTutorial2(void);

protected:
    virtual void createScene(void);
};

#endif // #ifndef __BasicTutorial2_h_
