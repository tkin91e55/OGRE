/*
-----------------------------------------------------------------------------
Filename:    DummyTutorial.h
-----------------------------------------------------------------------------
*/
#ifndef __DummyTutorial_h_
#define __DummyTutorial_h_

#include "BaseApplication.h"

class DummyTutorial : public BaseApplication
{
public:
    DummyTutorial(void);
    virtual ~DummyTutorial(void);

protected:
    virtual void createScene(void);
    virtual void createCamera(void);
    virtual void createViewports(void);
};

#endif // #ifndef __DummyTutorial_h_
