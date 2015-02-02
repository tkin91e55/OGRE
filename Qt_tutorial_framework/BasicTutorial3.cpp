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
    img.load("terrain.png", Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME);
    if (flipX)
        img.flipAroundY();
    if (flipY)
        img.flipAroundX();
}
//-------------------------------------------------------------------------------------
void BasicTutorial3::defineTerrain(long x, long y)
{
    Ogre::String filename = mTerrainGroup->generateFilename(x, y);
    if (Ogre::ResourceGroupManager::getSingleton().resourceExists(mTerrainGroup->getResourceGroup(), filename))
    {
        mTerrainGroup->defineTerrain(x, y);
    }
    else
    {
        Ogre::Image img;
        getTerrainImage(x % 2 != 0, y % 2 != 0, img);
        mTerrainGroup->defineTerrain(x, y, &img);
        mTerrainsImported = true;
    }
}
//-------------------------------------------------------------------------------------
void BasicTutorial3::initBlendMaps(Ogre::Terrain* terrain)
{
    Ogre::TerrainLayerBlendMap* blendMap0 = terrain->getLayerBlendMap(1);
    Ogre::TerrainLayerBlendMap* blendMap1 = terrain->getLayerBlendMap(2);
    Ogre::Real minHeight0 = 70;
    Ogre::Real fadeDist0 = 40;
    Ogre::Real minHeight1 = 70;
    Ogre::Real fadeDist1 = 15;
    float* pBlend0 = blendMap0->getBlendPointer();
    float* pBlend1 = blendMap1->getBlendPointer();
    for (Ogre::uint16 y = 0; y < terrain->getLayerBlendMapSize(); ++y)
    {
        for (Ogre::uint16 x = 0; x < terrain->getLayerBlendMapSize(); ++x)
        {
            Ogre::Real tx, ty;

            blendMap0->convertImageToTerrainSpace(x, y, &tx, &ty);
            Ogre::Real height = terrain->getHeightAtTerrainPosition(tx, ty);
            Ogre::Real val = (height - minHeight0) / fadeDist0;
            val = Ogre::Math::Clamp(val, (Ogre::Real)0, (Ogre::Real)1);
            *pBlend0++ = val;

            val = (height - minHeight1) / fadeDist1;
            val = Ogre::Math::Clamp(val, (Ogre::Real)0, (Ogre::Real)1);
            *pBlend1++ = val;
        }
    }
    blendMap0->dirty();
    blendMap1->dirty();
    blendMap0->update();
    blendMap1->update();
}
//-------------------------------------------------------------------------------------
void BasicTutorial3::configureTerrainDefaults(Ogre::Light* light)
{
    mTerrainGlobals->setMaxPixelError(8);
    mTerrainGlobals->setCompositeMapDistance(3000);

    //Deal with lightmapping, using the direction light
    mTerrainGlobals->setLightMapDirection(light->getDerivedDirection());
    mTerrainGlobals->setCompositeMapAmbient(mSceneMgr->getAmbientLight());
    mTerrainGlobals->setCompositeMapDiffuse(light->getDiffuseColour());

    Terrain::ImportData& defaultimp = mTerrainGroup->getDefaultImportSettings();
    defaultimp.terrainSize = 513;
    defaultimp.worldSize = 12000.0f;
    defaultimp.inputScale = 600; //due terrain.png is 8bpp
    defaultimp.minBatchSize = 33;
    defaultimp.maxBatchSize = 65;

    // textures
        defaultimp.layerList.resize(3);
        defaultimp.layerList[0].worldSize = 100;
        defaultimp.layerList[0].textureNames.push_back("dirt_grayrocky_diffusespecular.dds");
        defaultimp.layerList[0].textureNames.push_back("dirt_grayrocky_normalheight.dds");
        defaultimp.layerList[1].worldSize = 30;
        defaultimp.layerList[1].textureNames.push_back("grass_green-01_diffusespecular.dds");
        defaultimp.layerList[1].textureNames.push_back("grass_green-01_normalheight.dds");
        defaultimp.layerList[2].worldSize = 200;
        defaultimp.layerList[2].textureNames.push_back("growth_weirdfungus-03_diffusespecular.dds");
        defaultimp.layerList[2].textureNames.push_back("growth_weirdfungus-03_normalheight.dds");
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

    Ogre::Vector3 lightdir(0.55, -0.3, 0.75);
    lightdir.normalise();

    Light* light = mSceneMgr->createLight("testLight");
    light->setType(Light::LT_DIRECTIONAL);
    light->setDiffuseColour((ColourValue::White));
    light->setSpecularColour(ColourValue(0.4, 0.4, 0.4));

    mSceneMgr->setAmbientLight(ColourValue(0.2,0.2,0.2));

    //Terrain part
    mTerrainGlobals = OGRE_NEW Ogre::TerrainGlobalOptions();

    mTerrainGroup= OGRE_NEW TerrainGroup(mSceneMgr, Terrain::ALIGN_X_Z, 513, 12000.0f);
    mTerrainGroup->setFilenameConvention(String("BasicTutorial3Terrain"), String("dat"));
    mTerrainGroup->setOrigin(Vector3::ZERO);

    configureTerrainDefaults(light);

    for(long x=0; x<=0; ++x)
        for(long y=0; y<=0; ++y)
            defineTerrain(x,y);

    //sync load since we want everything in place when we start
    mTerrainGroup->loadAllTerrains(true);

    if(mTerrainsImported)
    {
        TerrainGroup::TerrainIterator ti = mTerrainGroup->getTerrainIterator();
        while(ti.hasMoreElements()){
            Terrain* t = ti.getNext()->instance;
            initBlendMaps(t);
        }
    }

    mTerrainGroup->freeTemporaryResources();
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
