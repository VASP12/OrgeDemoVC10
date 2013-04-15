#ifndef __ITutorial02_h_
#define __ITutorial02_h_

#include "BaseApplication.h"
#include <Terrain/OgreTerrain.h>
#include <Terrain/OgreTerrainGroup.h>
#include <CEGUISystem.h>
#include <CEGUISchemeManager.h>
#include <RendererModules/Ogre/CEGUIOgreRenderer.h>
class ITutorial02 : public BaseApplication
{
public:
	ITutorial02(void);
	virtual ~ITutorial02(void);
	/*void Configure_Terrain (void);
	void defineTerrain(long x, long y);
	void getTerrainImage(bool flipX, bool flipY, Ogre::Image& img);
	void configureTerrainDefaults(Ogre::Light* light);
	Ogre::Light* CreateDirectionalLight();*/
	void defineTerrain(long x, long y);
    void initBlendMaps(Ogre::Terrain* terrain);
    void configureTerrainDefaults(Ogre::Light* light);
	
protected:
	virtual void createScene(void);
	virtual void createFrameListener(void);
	//frame listener    
	virtual bool frameRenderingQueued(const Ogre::FrameEvent &evt);
	//mouse listener
	virtual bool mouseMoved(const OIS::MouseEvent &arg);
	virtual bool mousePressed(const OIS::MouseEvent &arg,OIS::MouseButtonID id);
	virtual bool mouseReleased(const OIS::MouseEvent &arg,OIS::MouseButtonID id);
	Ogre::TerrainGlobalOptions   *mTerrainGlobals;
	Ogre::TerrainGroup         *mTerrainGroup;
	bool mTerrainsImported;
	OgreBites::Label* mInfoLabel;
protected:
	Ogre::RaySceneQuery *mRaySceneQuery;// The ray scene query pointer
	bool mLMouseDown, mRMouseDown;		// True if the mouse buttons are down
	int mCount;							// The number of robots on the screen
	Ogre::SceneNode *mCurrentObject;	// The newly created object
	CEGUI::Renderer *mGUIRenderer;		// CEGUI renderer
	float mRotateSpeed;		


};

#endif // #ifndef __ITutorial02_h_