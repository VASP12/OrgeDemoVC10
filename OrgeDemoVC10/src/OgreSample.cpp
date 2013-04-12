#include "stdafx.h" 
#ifdef _DEBUG 
#pragma comment(lib,"ogremain_d.lib") 
#else 
#pragma comment(lib,"ogremain.lib") 
#endif 
//INT WINAPI WinMain( HINSTANCE hInst, HINSTANCE, LPSTR strCmdLine, INT ) 
//{ 
//        using namespace Ogre; 
//        try 
//        { 
//                /// Root的构造函数里会创建所有Factory以及Manager 
//                /// 这里的3个参数，都是可以为空的（不是省略）. 
//                /// 第1个参数指明了插件配置的文件名. 这个文件里指明了我们将要使用的图形驱动（DX or GL)等DLL. 
//                /// 既然是图形程序，所以肯定要有图形驱动了，如果这个参数为空，那么我们必须手动去加载图形驱动. 
//                /// 第2个参数指明了OGRE的图形驱动配置文件。 
//                /// 这个参数实际上是在调试的时候使用的，发布版本的时候肯定是不要它的. 
//                /// 它在Root里的ShowDialg里使用，用来动态的配置当前要使用的图形驱动. 
//                /// 如果我们可以确定我们要使用的图形驱动，完全可以配置我们自己的图形驱动. 具体代码可以参考下面. 
//                /// 第3个参数指定了我们要使用的LOG文件名 
//                Root * root = new Root("", 
//                                       "", 
//                                       ""); 
//                /// 我们手动加载图形驱动 
//#ifdef _DEBUG 
//                root->loadPlugin("../OgreSDK/dll/release/RenderSystem_Direct3D9_d"); 
//#else 
//                root->loadPlugin("../OgreSDK/dll/release/RenderSystem_Direct3D9"); 
//#endif 
//                /// 由于OGRE的资源加载都由ResourceGroupManager来管理,不通过WINDOWS直接管理. 
//                /// 所以，要正常使用OGRE的资源加载，我们还得把我们的资源目录给加到这个Manager里去. 
//                /// 说白了，就是资源的环境路径. 
//                /// 最起码，当前目录是要加的吧 ^_^ 
//                /// 这里也有3个参数。 
//                /// 第1个参数指明了我们要加入的资源的相对目录名 
//                /// 第2个参数指明了我们要加入的资源属于什么资源包。 
//                /// 这个参数比较诡异，到底这个参数要依据什么原则来填写呢。 
//                /// 其实这个参数的名字OGRE的代码里已经定义好了. 
//                /// 如果是文件系统包呢，就查看FileSystemArchiveFactory这个类的定义里的createInstance，名字为FileSystem 
//                /// 如果是ZIP压缩包呢，就查看ZipArchiveFactory这个类的定义里的createInstance，名字为Zip 
//                /// 也就是说，这个名字必须以ArchiveFactory的派生类里定义的为准，否则肯定会出错地. 
//                /// 第3个参数就比较简单了，可以随便填写，它只是对资源做一个逻辑上的分类. 
//                ResourceGroupManager::getSingleton().addResourceLocation( 
//                    ".", "FileSystem", "General"); 
//                ResourceGroupManager::getSingleton().addResourceLocation( 
//                    "media1", "FileSystem", "General"); 
//                /// 做完以上这步，我们需要把这些资源路径里的文件信息都提取出来，以便加速查找. 
//                /// 下面这个函数就是干这个苦差事的. 
//                ResourceGroupManager::getSingleton().initialiseAllResourceGroups(); 
//                /// 刚刚不是说了吗，我们把Root里的第二个参数给留空了，也就是说我们得自己指定一个RenderSystem， 
//                /// 以及给它配置属性 
//                /// 这里我们就用在Plugins里加载进OGRE里的第一个RenderSystem,我这里是DX 
//               //RenderSystem *render_system = *root->getAvailableRenderers().begin(); 
//			   RenderSystem * render_system = root->getRenderSystemByName("Direct3D9 Rendering Subsystem");
//				/// 设置为窗口模式 
//                render_system->setConfigOption("Full Screen","Yes"); 
//                /// 把这个RenderSystem给设为系统默认的 
//                root->setRenderSystem(render_system); 
//                /// 好了， 有了RenderSystem，我们就可以初始化我们的Root了.(其实就是创建窗口的过程) 
//                /// 这里我们把RenderSystem的名字也显示在窗口的标题栏中. 
//                RenderWindow *render_win = root->initialise(true,String("my simple orge window,rendersystem : ") + render_system->getName()); 
//                /// 场景的渲染,SceneManager必须创建一个，这个就是我们的游戏舞台了 
//                SceneManager * scene_mgr = root->createSceneManager(ST_GENERIC, "my scene"); 
//                /// 设置灯光的亮度 
//                scene_mgr->setAmbientLight(ColourValue(1,1,1)); 
//                /// 场景设置好了，但必须还得有个观察者，这个观察者在这里就是Camera 
//                Camera * camera = scene_mgr->createCamera("my camera"); 
//                camera->setPosition(Vector3(0,0,500)); 
//                camera->lookAt(Vector3(0,0,-300)); 
//                camera->setNearClipDistance(5); 
//                /// 有了观察者，但我们怎么看到场景的内容呢？ 
//                /// 我们还得需要一个眼睛，在这里叫做Viewport 
//                Viewport* vp = render_win->addViewport(camera); 
//                vp->setBackgroundColour(ColourValue(0,0,0)); 
//                /// 这里设置camera的图形比例,必须设置，否则图象会变形 
//                camera->setAspectRatio(Real(vp->getActualWidth()) / Real(vp->getActualHeight())); 
//                /// 我们通过例子里的资源模型ogrehead来做个演示 
//                Entity *ent = scene_mgr->createEntity("Robot","ogrehead.mesh"); 
//                SceneNode *node = scene_mgr->getRootSceneNode()->createChildSceneNode("RobotNode"); 
//                node->setPosition(50,30,0); 
//                node->attachObject(ent); 
//                root->startRendering(); 
//                delete root; 
//        } 
//        catch (Ogre::Exception & e) 
//        { 
//                ::MessageBox( NULL, 
//                                e.getFullDescription().c_str(), 
//                                "An exception has occured!", 
//                                MB_OK | MB_ICONERROR | MB_TASKMODAL); 
//        } 
//} 