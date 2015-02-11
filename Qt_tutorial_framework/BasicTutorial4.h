/*
-----------------------------------------------------------------------------
Filename:    BasicTutorial4.h
-----------------------------------------------------------------------------
*/
#ifndef __BasicTutorial4_h_
#define __BasicTutorial4_h_

#include "BaseApplication.h"

class BasicTutorial4 : public BaseApplication
{
public:
    BasicTutorial4(void);
    virtual ~BasicTutorial4(void);

protected:
    virtual void createScene(void);
    // Ogre::FrameListener
    virtual bool frameRenderingQueued(const Ogre::FrameEvent& evt);
private:
    bool processUnbufferedInput(const Ogre::FrameEvent& evt);
};

#endif // #ifndef __BasicTutorial4_h_
