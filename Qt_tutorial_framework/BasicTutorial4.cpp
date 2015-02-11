/*
-----------------------------------------------------------------------------
Filename:    BasicTutorial4.cpp
-----------------------------------------------------------------------------
*/
#include "BasicTutorial4.h"

//-------------------------------------------------------------------------------------
BasicTutorial4::BasicTutorial4(void)
{
}
//-------------------------------------------------------------------------------------
BasicTutorial4::~BasicTutorial4(void)
{
}

//-------------------------------------------------------------------------------------
void BasicTutorial4::createScene(void)
{
    // create your scene here :)

}

bool BasicTutorial4::processUnbufferedInput(const Ogre::FrameEvent &evt)
{
    return true;
}

bool BasicTutorial4::frameRenderingQueued(const Ogre::FrameEvent &evt)
{
    bool ret = BaseApplication::frameRenderingQueued(evt);
    return ret;
}

virtual bool frameStarted(const FrameEvent& evt);
virtual bool frameRenderingQueued(const FrameEvent& evt);
virtual bool frameEnded(const FrameEvent& evt);

#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
#define WIN32_LEAN_AND_MEAN
#include "windows.h"
#endif

#ifdef __cplusplus
extern "C" {
#endif

#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
    INT WINAPI WinMain( HINSTANCE hInst, HINSTANCE, LPSTR strCmdLine, INT )
#else
    int main(int argc, char *argv[])
#endif
    {
        // Create application object
        BasicTutorial4 app;

        try {
            app.go();
        } catch( Ogre::Exception& e ) {
#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
            MessageBox( NULL, e.getFullDescription().c_str(), "An exception has occured!", MB_OK | MB_ICONERROR | MB_TASKMODAL);
#else
            std::cerr << "An exception has occured: " <<
                e.getFullDescription().c_str() << std::endl;
#endif
        }

        return 0;
    }

#ifdef __cplusplus
}
#endif
