#include "Ogre.h"
#include "ExampleApplication.h"
#include "BasicTutorial7.h"
#include <windows.h>
// First, we declare a subclass of the ExampleApplication class
class FirstApp : public ExampleApplication
{
public:
    FirstApp() { }

    /** createScene is pure virtual in ExampleApplication, so we just override it to do nothing.
    * What this means is that we'll be creating an empty scene at first.
    **/
    void createScene(void) { }
};

INT WINAPI WinMain(HINSTANCE hInst, HINSTANCE, LPSTR strCmdLine, INT){
    try { // This try-catch provides a nice way of popping up errors if they occur.
        //myApp.go(); // ExampleApplication provides a go method, which starts the rendering.
		BasicTutorial7 app;  
		app.go();
    } catch (Ogre::Exception& e) {
        MessageBox( NULL, e.getFullDescription().c_str(), "An exception has occured!",
        MB_OK | MB_ICONERROR | MB_TASKMODAL);
    }
	 return 0;
}