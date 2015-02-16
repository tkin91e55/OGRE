/*
-----------------------------------------------------------------------------
Filename:    BasicTutorial5.cpp
-----------------------------------------------------------------------------
*/
#include "BasicTutorial5.h"

//-------------------------------------------------------------------------------------
BasicTutorial5::BasicTutorial5(void)
{
}
//-------------------------------------------------------------------------------------
BasicTutorial5::~BasicTutorial5(void)
{
}

//-------------------------------------------------------------------------------------
void BasicTutorial5::createScene(void)
{
    // create your scene here :)
    mSceneMgr->setAmbientLight(Ogre::ColourValue(0.25, 0.25, 0.25));

            // add the ninja
        Ogre::Entity *ent = mSceneMgr->createEntity("Ninja", "ninja.mesh");
            Ogre::SceneNode *node = mSceneMgr->getRootSceneNode()->createChildSceneNode("NinjaNode");
            node->attachObject(ent);

            // create the light
            Ogre::Light *light = mSceneMgr->createLight("Light1");
            light->setType(Ogre::Light::LT_POINT);
            light->setPosition(Ogre::Vector3(250, 150, 250));
            light->setDiffuseColour(Ogre::ColourValue::White);
            light->setSpecularColour(Ogre::ColourValue::White);

           // Create the scene node
            node = mSceneMgr->getRootSceneNode()->createChildSceneNode("CamNode1", Ogre::Vector3(-400, 200, 400));

            // Make it look towards the ninja
            node->yaw(Ogre::Degree(-45));

            // Create the pitch node
            node = node->createChildSceneNode("PitchNode1");
            node->attachObject(mCamera);

            // create the second camera node/pitch node
            node = mSceneMgr->getRootSceneNode()->createChildSceneNode("CamNode2", Ogre::Vector3(0, 200, 400));
            node = node->createChildSceneNode("PitchNode2");
}

void BasicTutorial5::createFrameListener(void)
{
    BaseApplication::createFrameListener();

    // set the rotation and move speed
    mRotate = 0.13;
    mMove = 250;

    mDirection = Ogre::Vector3::ZERO;
}

bool BasicTutorial5::frameRenderingQueued(const Ogre::FrameEvent& evt)
{
    if (mWindow->isClosed()) return false;
        if (mShutDown) return false;
        mKeyboard->capture();
        mMouse->capture();
        mTrayMgr->frameRenderingQueued(evt);

        // Populate the camera container
        mCamNode = mCamera->getParentSceneNode();

        mCamNode->translate(mDirection * evt.timeSinceLastFrame, Ogre::Node::TS_LOCAL);

        return true;
}

// OIS::KeyListener
bool BasicTutorial5::keyPressed( const OIS::KeyEvent& evt ){
    switch (evt.key)
    {
    case OIS::KC_ESCAPE:
        mShutDown = true;
        break;
    case OIS::KC_1:
        mCamera->getParentSceneNode()->detachObject(mCamera);
        mCamNode = mSceneMgr->getSceneNode("CamNode1");
        mCamNode->attachObject(mCamera);
        break;

    case OIS::KC_2:
        mCamera->getParentSceneNode()->detachObject(mCamera);
        mCamNode = mSceneMgr->getSceneNode("CamNode2");
        mCamNode->attachObject(mCamera);
        break;
    case OIS::KC_UP:
    case OIS::KC_W:
        mDirection.z = -mMove;
        std::cout<<"mDirection.z : " << mDirection.z << std::endl;
        break;

    case OIS::KC_DOWN:
    case OIS::KC_S:
        mDirection.z = mMove;
        break;

    case OIS::KC_LEFT:
    case OIS::KC_A:
        mDirection.x = -mMove;
        break;

    case OIS::KC_RIGHT:
    case OIS::KC_D:
        mDirection.x = mMove;
        break;

    case OIS::KC_PGDOWN:
    case OIS::KC_E:
        mDirection.y = -mMove;
        break;

    case OIS::KC_PGUP:
    case OIS::KC_Q:
        mDirection.y = mMove;
        break;
    default:
        break;
    }
    return true;
}
bool BasicTutorial5::keyReleased( const OIS::KeyEvent& evt ){
    switch (evt.key)
    {
    case OIS::KC_UP:
    case OIS::KC_W:
        mDirection.z = 0;
        break;

    case OIS::KC_DOWN:
    case OIS::KC_S:
        mDirection.z = 0;
        break;

    case OIS::KC_LEFT:
    case OIS::KC_A:
        mDirection.x = 0;
        break;

    case OIS::KC_RIGHT:
    case OIS::KC_D:
        mDirection.x = 0;
        break;

    case OIS::KC_PGDOWN:
    case OIS::KC_E:
        mDirection.y = 0;
        break;

    case OIS::KC_PGUP:
    case OIS::KC_Q:
        mDirection.y = 0;
        break;

    default:
        break;
    }
    return true;
}
// OIS::MouseListener
bool BasicTutorial5::mouseMoved( const OIS::MouseEvent& evt ){return true;}
bool BasicTutorial5::mousePressed( const OIS::MouseEvent& evt, OIS::MouseButtonID id ){return true;}
bool BasicTutorial5::mouseReleased( const OIS::MouseEvent& evt, OIS::MouseButtonID id ){return true;}

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
        BasicTutorial5 app;

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
