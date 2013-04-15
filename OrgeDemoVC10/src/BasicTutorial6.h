#include <OgreRoot.h>
#include <OISEvents.h>
#include <OISInputManager.h>
#include <OISKeyboard.h>
#include <OISMouse.h>
#include <OgreWindowEventUtilities.h>
class BasicTutorial6: public Ogre::WindowEventListener, public Ogre::FrameListener{
public:
	BasicTutorial6(void);
	virtual ~BasicTutorial6(void);
	bool go(void);
protected:
	// Ogre::WindowEventListener
	virtual void windowResized(Ogre::RenderWindow* rw);
	virtual void windowClosed(Ogre::RenderWindow* rw);
	// Ogre::FrameListener
	virtual bool frameRenderingQueued(const Ogre::FrameEvent& evt);
private:
	Ogre::Root*	mRoot;
	Ogre::String	mPluginsCfg;
	Ogre::String	mResourceCfg;

	Ogre::RenderWindow* mWindow;

	Ogre::SceneManager* mSceneMgr;
	Ogre::Camera* mCamera;

	// OIS Input devices
	OIS::InputManager* mInputManager;
	OIS::Mouse*    mMouse;
	OIS::Keyboard* mKeyboard;
};