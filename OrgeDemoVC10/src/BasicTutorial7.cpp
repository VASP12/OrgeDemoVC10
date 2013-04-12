#include "BasicTutorial7.h"
 
//-------------------------------------------------------------------------------------
BasicTutorial7::BasicTutorial7(void)
{
}
//-------------------------------------------------------------------------------------
BasicTutorial7::~BasicTutorial7(void)
{
}
//-------------------------------------------------------------------------------------
void BasicTutorial7::createScene(void)
{
}
//-------------------------------------------------------------------------------------
void BasicTutorial7::createFrameListener(void)
{
    BaseApplication::createFrameListener();
}
//-------------------------------------------------------------------------------------
bool BasicTutorial7::frameRenderingQueued(const Ogre::FrameEvent& evt)
{
    return BaseApplication::frameRenderingQueued(evt);
}
//-------------------------------------------------------------------------------------
bool BasicTutorial7::keyPressed( const OIS::KeyEvent &arg )
{
    return BaseApplication::keyPressed(arg);
}
//-------------------------------------------------------------------------------------
bool BasicTutorial7::keyReleased( const OIS::KeyEvent &arg )
{
    return BaseApplication::keyReleased(arg);
}
//-------------------------------------------------------------------------------------
bool BasicTutorial7::mouseMoved( const OIS::MouseEvent &arg )
{
    return BaseApplication::mouseMoved(arg);
}
//-------------------------------------------------------------------------------------
bool BasicTutorial7::mousePressed( const OIS::MouseEvent &arg, OIS::MouseButtonID id )
{
    return BaseApplication::mousePressed(arg, id);
}
//-------------------------------------------------------------------------------------
bool BasicTutorial7::mouseReleased( const OIS::MouseEvent &arg, OIS::MouseButtonID id )
{
    return BaseApplication::mouseReleased(arg, id);
}
//-------------------------------------------------------------------------------------
bool BasicTutorial7::quit(const CEGUI::EventArgs &e)
{
    return true;
}