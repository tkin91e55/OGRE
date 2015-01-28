/*
-----------------------------------------------------------------------------
Filename:    BasicTutorial3.h
-----------------------------------------------------------------------------
*/
#ifndef __BasicTutorial3_h_
#define __BasicTutorial3_h_

#include "BaseApplication.h"
using namespace Ogre;

class BasicTutorial3 : public BaseApplication
{
private:
    TerrainGlobalOptions mTerrainGlobals;
    TerrainGroup* mTerrainGroup;
    bool mTerrainsImported;

    void defineTerrain(long x,long y);
    void initBlendMaps(Ogre::Terrain* terrain);
    void configureTerrainDefaults(Light* light);

public:
    BasicTutorial3(void);
    virtual ~BasicTutorial3(void);

protected:
    virtual void createScene(void);
    //virtual void createCamera(void);
    //virtual void createViewports(void);
    virtual void createFrameListener(void);
    virtual void destroyScene(void);
    virtual bool frameRenderingQueued(const FrameEvent& evt);
};

#endif // #ifndef __BasicTutorial3_h_
