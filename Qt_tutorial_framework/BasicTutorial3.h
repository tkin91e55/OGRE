/*
-----------------------------------------------------------------------------
Filename:    BasicTutorial3.h
-----------------------------------------------------------------------------
*/
#ifndef __BasicTutorial3_h_
#define __BasicTutorial3_h_

#include "BaseApplication.h"

class BasicTutorial3 : public BaseApplication
{
public:
    BasicTutorial3(void);
    virtual ~BasicTutorial3(void);

protected:
    virtual void createScene(void);
    virtual void createCamera(void);
    virtual void createViewports(void);
};

#endif // #ifndef __BasicTutorial3_h_
