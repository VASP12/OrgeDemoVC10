#include "ITutorial02.h"

#include "ITutorial02.h"
#include <cstdlib>

extern void getTerrainImage(bool flipX, bool flipY, Ogre::Image& img);
//-------------------------------------------------------------------------------------
ITutorial02::ITutorial02(void)
{
}
//-------------------------------------------------------------------------------------
ITutorial02::~ITutorial02(void)
{
   // We created the query, and we are also responsible for deleting it.
    OGRE_DELETE mTerrainGroup;
	OGRE_DELETE mTerrainGlobals;
}
//-------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------
void ITutorial02::defineTerrain(long x, long y)
{
   // see tutorial for descriptions
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
void ITutorial02::initBlendMaps(Ogre::Terrain* terrain)
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
void ITutorial02::configureTerrainDefaults(Ogre::Light* light)
{
   // Configure global
    mTerrainGlobals->setMaxPixelError(8); // decides how precise our terrain is going to be. A lower number will mean a more accurate terrain, at the cost of performance (because of more vertices). 
    // testing composite map
    mTerrainGlobals->setCompositeMapDistance(3000); //decides how far the Ogre terrain will render the lightmapped terrain. 

   // Important to set these so that the terrain knows what to use for derived (non-realtime) data
    mTerrainGlobals->setLightMapDirection(light->getDerivedDirection());
    mTerrainGlobals->setCompositeMapAmbient(mSceneMgr->getAmbientLight());
    mTerrainGlobals->setCompositeMapDiffuse(light->getDiffuseColour());

   // Configure default import settings for if we use imported image
    Ogre::Terrain::ImportData& defaultimp = mTerrainGroup->getDefaultImportSettings();
    defaultimp.terrainSize = 513;
    defaultimp.worldSize = 12000.0f;
    defaultimp.inputScale = 600; // due terrain.png is 8 bpp
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
void ITutorial02::createScene(void)
{
   //TERRAIN (Basic Tutorial 3)
    mCamera->setFarClipDistance(50000);
    if (mRoot->getRenderSystem()->getCapabilities()->hasCapability(Ogre::RSC_INFINITE_FAR_PLANE))
    {
        mCamera->setFarClipDistance(0);   // enable infinite far clip distance if we can
    }
   
   // light
   Ogre::Vector3 lightdir(0.55, -0.3, 0.75);
    lightdir.normalise();
 
    Ogre::Light* light = mSceneMgr->createLight("tstLight");
    light->setType(Ogre::Light::LT_DIRECTIONAL);
    light->setDirection(lightdir);
    light->setDiffuseColour(Ogre::ColourValue::White);
    light->setSpecularColour(Ogre::ColourValue(0.4, 0.4, 0.4));
   
   // configure terrain
   mTerrainGlobals = OGRE_NEW Ogre::TerrainGlobalOptions();

   mTerrainGroup = OGRE_NEW Ogre::TerrainGroup(mSceneMgr, Ogre::Terrain::ALIGN_X_Z, 513, 12000.0f);
    mTerrainGroup->setFilenameConvention(Ogre::String("ITutorial02Terrain"), Ogre::String("dat"));
    mTerrainGroup->setOrigin(Ogre::Vector3::ZERO);

   configureTerrainDefaults(light);

   // define our terrains and instruct the TerrainGroup to load them all: 
   for (long x = 0; x <= 0; ++x)
        for (long y = 0; y <= 0; ++y)
            defineTerrain(x, y);
 
    // sync load since we want everything in place when we start
    mTerrainGroup->loadAllTerrains(true);

   // if we just imported our terrains, we would like our blendmaps to be calculated: 
   if (mTerrainsImported)
    {
        Ogre::TerrainGroup::TerrainIterator ti = mTerrainGroup->getTerrainIterator();
      // loops through the available terrains and calls initBlendMaps on each. 
        while(ti.hasMoreElements())
        {
            Ogre::Terrain* t = ti.getNext()->instance;
            initBlendMaps(t);
        }
    }
   // clean up after the initial terrain creation: 
   mTerrainGroup->freeTemporaryResources();

   Ogre::Plane plane;
   plane.d = 10;
   plane.normal = Ogre::Vector3::NEGATIVE_UNIT_Y;

   //TERRAIN (Basic Tutorial 3) END

   // Set ambient light
   mSceneMgr->setAmbientLight(Ogre::ColourValue(0.5, 0.5, 0.5));
   mSceneMgr->setSkyDome(true, "Examples/CloudySky", 5, 8);
 
   // Set camera look point
   mCamera->setPosition(40, 100, 580);
   mCamera->pitch(Ogre::Degree(-90));
   mCamera->yaw(Ogre::Degree(-90));

 
   // CEGUI setup
   mGUIRenderer = &CEGUI::OgreRenderer::bootstrapSystem();
   // Mouse
   CEGUI::SchemeManager::getSingleton().create((CEGUI::utf8*)"TaharezLook.scheme");
   CEGUI::MouseCursor::getSingleton().setImage("TaharezLook", "MouseArrow");
}
void ITutorial02::createFrameListener(void)
{
   BaseApplication::createFrameListener();
   // Setup default variables
   mCount = 0;
   mCurrentObject = NULL;
   mLMouseDown = false;
   mRMouseDown = false;
   // Reduce move speed
   mRotateSpeed = .1;
   // Create RaySceneQuery
   mRaySceneQuery = mSceneMgr->createRayQuery(Ogre::Ray());

    mInfoLabel = mTrayMgr->createLabel(OgreBites::TL_TOP, "TInfo", "", 350);
}

bool ITutorial02::frameRenderingQueued(const Ogre::FrameEvent &evt)
{
   bool ret = BaseApplication::frameRenderingQueued(evt);
   // Process the base frame listener code.  Since we are going to be
    // manipulating the translate vector, we need this to happen first.
    if (!ret)
        return false;

   // Setup the scene query
   Ogre::Vector3 camPos = mCamera->getPosition();
   Ogre::Ray cameraRay(Ogre::Vector3(camPos.x, 5000.0f, camPos.z), Ogre::Vector3::NEGATIVE_UNIT_Y);
   mRaySceneQuery->setRay(cameraRay);
 
   // Perform the scene query
   Ogre::RaySceneQueryResult &result = mRaySceneQuery->execute();

   // Get the results, set the camera height
   //FROM FORUM
   camPos = mCamera->getPosition();

   if (camPos.y < mTerrainGroup->getHeightAtWorldPosition(camPos) + 10.0f)
      // we are going too low, fix camera position:
      mCamera->setPosition(camPos.x, mTerrainGroup->getHeightAtWorldPosition(camPos) + 10.0f, camPos.z);
   //FROM FORUM END

    if (mTerrainGroup->isDerivedDataUpdateInProgress())
    {
        mTrayMgr->moveWidgetToTray(mInfoLabel, OgreBites::TL_TOP, 0);
        mInfoLabel->show();
        if (mTerrainsImported)
        {
            mInfoLabel->setCaption("Building terrain, please wait...");
        }
        else
        {
            mInfoLabel->setCaption("Updating textures, patience...");
        }
    }
    else
    {
        mTrayMgr->removeWidgetFromTray(mInfoLabel);
        mInfoLabel->hide();
        if (mTerrainsImported)
        {
            mTerrainGroup->saveAllTerrains(true);
            mTerrainsImported = false;
        }
    }
 
    return true;
}
bool ITutorial02::mouseMoved(const OIS::MouseEvent &arg)
{
   // Update CEGUI with the mouse motion
   CEGUI::System::getSingleton().injectMouseMove(arg.state.X.rel, arg.state.Y.rel);
   // If we are dragging the left mouse button.
   if (mLMouseDown)
   {
      CEGUI::Point mousePos = CEGUI::MouseCursor::getSingleton().getPosition();
      Ogre::Ray mouseRay = mCamera->getCameraToViewportRay(mousePos.d_x/float(arg.state.width),mousePos.d_y/float(arg.state.height));
      mRaySceneQuery->setRay(mouseRay);
      Ogre::RaySceneQueryResult &result = mRaySceneQuery->execute();
   } // if
 
   // If we are dragging the right mouse button.
   else if (mRMouseDown)
   {
      mCamera->yaw(Ogre::Degree(-arg.state.X.rel * mRotateSpeed));
      mCamera->pitch(Ogre::Degree(-arg.state.Y.rel * mRotateSpeed));
   } // else if
   return true;
}
bool ITutorial02::mousePressed(const OIS::MouseEvent &arg, OIS::MouseButtonID id)
{
   // Left mouse button down
   if (id == OIS::MB_Left)
   {
      // Setup the ray scene query, use CEGUI's mouse position
      CEGUI::Point mousePos = CEGUI::MouseCursor::getSingleton().getPosition();
      Ogre::Ray mouseRay = mCamera->getCameraToViewportRay(mousePos.d_x/float(arg.state.width), mousePos.d_y/float(arg.state.height));
      mRaySceneQuery->setRay(mouseRay);
      // Execute query
      Ogre::RaySceneQueryResult &result = mRaySceneQuery->execute();
      
      // Get results, create a node/entity on the position
      //FROM FORUM
      //mGUI->injectMousePress(arg.state.X.abs, arg.state.Y.abs, MyGUI::MouseButton::Enum(id));
      mouseRay=mCamera->getCameraToViewportRay(Ogre::Real(arg.state.X.abs)/Ogre::Real(arg.state.width),Ogre::Real(arg.state.Y.abs)/Ogre::Real(arg.state.height));
      Ogre::Terrain* pTerrain = mTerrainGroup->getTerrain(0, 0);
      std::pair <bool, Ogre::Vector3> check_mouse_click;
      check_mouse_click = pTerrain->rayIntersects(mouseRay, true, 0);
      if (check_mouse_click.first = true) 
        {
         Ogre::Entity *ent;
         char name[16];
         sprintf_s(name, "Robot%d", mCount++);
         ent = mSceneMgr->createEntity(name, "robot.mesh");
         Ogre::SceneNode* entScnNode = mSceneMgr->getRootSceneNode()->createChildSceneNode(Ogre::String(name) + "Node", check_mouse_click.second);
         entScnNode->attachObject(ent);
         entScnNode->setScale(1.f, 1.f, 1.f);
        }
      //FROM FORUM END

      mLMouseDown = true;
   } // if
 
 
   // Right mouse button down
   else if (id == OIS::MB_Right)
   {
      CEGUI::MouseCursor::getSingleton().hide();
      mRMouseDown = true;
   } // else if
 
   return true;
}
bool ITutorial02::mouseReleased(const OIS::MouseEvent &arg, OIS::MouseButtonID id)
{
   // Left mouse button up
    if (id == OIS::MB_Left)
    {
        mLMouseDown = false;
    } // if
 
    // Right mouse button up
    else if (id == OIS::MB_Right)
    {
        CEGUI::MouseCursor::getSingleton().show();
        mRMouseDown = false;
    } // else if
   return true;
}