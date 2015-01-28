/*
-----------------------------------------------------------------------------
Filename:    BasicTutorial3.cpp
-----------------------------------------------------------------------------
*/
#include "BasicTutorial3.h"

//-------------------------------------------------------------------------------------
BasicTutorial3::BasicTutorial3(void)
{
    std::cout << "BasicTutorial3::BasicTutorial3() called" << std::endl;
}
//-------------------------------------------------------------------------------------
BasicTutorial3::~BasicTutorial3(void)
{
}

//-------------------------------------------------------------------------------------
void BasicTutorial3::destroyScene(void)
{

}
//-------------------------------------------------------------------------------------
void getTerrainImage(bool flipX, bool flipY, Ogre::Image& img)
{

}
//-------------------------------------------------------------------------------------
void BasicTutorial3::defineTerrain(long x, long y)
{

}
//-------------------------------------------------------------------------------------
void BasicTutorial3::initBlendMaps(Ogre::Terrain* terrain)
{

}
//-------------------------------------------------------------------------------------
void BasicTutorial3::configureTerrainDefaults(Ogre::Light* light)
{

}
//-------------------------------------------------------------------------------------
void BasicTutorial3::createScene(void)
{
    //create scene here:
    mCamera->setPosition(Vector3(1683, 50, 2116));
    mCamera->lookAt(Vector3(1963, 50, 1660));
    mCamera->setNearClipDistance(0.1);
    mCamera->setFarClipDistance(50000);

    if(mRoot->getRenderSystem()->getCapabilities()->hasCapability(RSC_INFINITE_FAR_PLANE)){
        mCamera->setFarClipDistance(0); //try to enable infinite far clip distance
    }
}
//-------------------------------------------------------------------------------------
void BasicTutorial3::createFrameListener(void)
{

}
//-------------------------------------------------------------------------------------
bool BasicTutorial3::frameRenderingQueued(const Ogre::FrameEvent& evt)
{
    bool ret = BaseApplication::frameRenderingQueued(evt);
    return ret;
}



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
        BasicTutorial3 app;

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
