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
    mSceneMgr->setAmbientLight(Ogre::ColourValue(0.25, 0.25, 0.25));

    Ogre::Entity* ninjaEntity = mSceneMgr->createEntity("Ninja", "ninja.mesh");
    Ogre::SceneNode *node = mSceneMgr->getRootSceneNode()->createChildSceneNode("NinjaNode");
    node->attachObject(ninjaEntity);

    Ogre::Light* pointLight = mSceneMgr->createLight("pointLight");
    pointLight->setType(Ogre::Light::LT_POINT);
    pointLight->setPosition(Ogre::Vector3(250, 150, 250));
    pointLight->setDiffuseColour(Ogre::ColourValue::White);
    pointLight->setSpecularColour(Ogre::ColourValue::White);
}

bool BasicTutorial4::processUnbufferedInput(const Ogre::FrameEvent &evt)
{
    static bool mMouseDown = false;     // If a mouse button is depressed
    static Ogre::Real mToggle = 0.0;    // The time left until next toggle
    static Ogre::Real mRotate = 0.13;   // The rotate constant
    static Ogre::Real mMove = 250;      // The movement constant

    bool currMouse = mMouse->getMouseState().buttonDown(OIS::MB_Left);

    if (currMouse && ! mMouseDown)
    {
        Ogre::Light* light = mSceneMgr->getLight("pointLight");
        light->setVisible(! light->isVisible());
    }

    mMouseDown = currMouse;

    return true;
}

bool BasicTutorial4::frameRenderingQueued(const Ogre::FrameEvent &evt)
{
    bool ret = BaseApplication::frameRenderingQueued(evt);

    if(!processUnbufferedInput(evt)) return false;

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
