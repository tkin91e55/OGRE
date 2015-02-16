/*
-----------------------------------------------------------------------------
Filename:    BasicTutorial5.h
-----------------------------------------------------------------------------
*/
#ifndef __BasicTutorial5_h_
#define __BasicTutorial5_h_

#include "BaseApplication.h"

class BasicTutorial5 : public BaseApplication
{
public:
    BasicTutorial5(void);
    virtual ~BasicTutorial5(void);

protected:
    virtual void createScene(void);
    virtual void createCamera(void);
    virtual void createViewports(void);
};

#endif // #ifndef __BasicTutorial5_h_
