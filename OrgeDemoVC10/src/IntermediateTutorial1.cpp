#include "IntermediateTutorial1.h"

//-------------------------------------------------------------------------------------
IntermediateTutorial1::IntermediateTutorial1(void)
{
}
//-------------------------------------------------------------------------------------
IntermediateTutorial1::~IntermediateTutorial1(void)
{
}

//-------------------------------------------------------------------------------------
void IntermediateTutorial1::createScene(void)
{
	mSceneMgr->setAmbientLight(Ogre::ColourValue(1.0f, 1.0f, 1.0f));
	mEntity = mSceneMgr->createEntity("Robot", "robot.mesh");
	mNode = mSceneMgr->getRootSceneNode()->
		createChildSceneNode("RobotNode", Ogre::Vector3(0.0f, 0.0f, 25.0f));
	mNode->attachObject(mEntity);
	mWalkList.push_back(Ogre::Vector3(550.0f,  0.0f,  50.0f ));
	mWalkList.push_back(Ogre::Vector3(-100.0f,  0.0f, -200.0f));
	mWalkList.push_back(Ogre::Vector3(350.0f,  0.0f, -50.0f));
	Ogre::Entity *ent;
	Ogre::SceneNode *node;

	ent = mSceneMgr->createEntity("Knot1", "knot.mesh");
	node = mSceneMgr->getRootSceneNode()->createChildSceneNode("Knot1Node",
		Ogre::Vector3(0.0f, -10.0f,  25.0f));
	node->attachObject(ent);
	node->setScale(0.1f, 0.1f, 0.1f);

	ent = mSceneMgr->createEntity("Knot2", "knot.mesh");
	node = mSceneMgr->getRootSceneNode()->createChildSceneNode("Knot2Node",
		Ogre::Vector3(550.0f, -10.0f,  50.0f));
	node->attachObject(ent);
	node->setScale(0.1f, 0.1f, 0.1f);

	ent = mSceneMgr->createEntity("Knot3", "knot.mesh");
	node = mSceneMgr->getRootSceneNode()->createChildSceneNode("Knot3Node",
		Ogre::Vector3(-100.0f, -10.0f,-200.0f));
	node->attachObject(ent);
	node->setScale(0.1f, 0.1f, 0.1f);

	ent = mSceneMgr->createEntity("Knot4", "knot.mesh");
	node = mSceneMgr->getRootSceneNode()->createChildSceneNode("Knot4Node",
		Ogre::Vector3(350.0f, -10.0f,-50.0f));
	node->attachObject(ent);
	node->setScale(0.1f, 0.1f, 0.1f);

	mCamera->setPosition(90.0f, 280.0f, 535.0f);
	mCamera->pitch(Ogre::Degree(-30.0f));
	mCamera->yaw(Ogre::Degree(-15.0f));
}
void IntermediateTutorial1::createFrameListener(void){
	BaseApplication::createFrameListener();
	// Set idle animation
    mAnimationState = mEntity->getAnimationState("Idle");
    mAnimationState->setLoop(true);
    mAnimationState->setEnabled(true);
    // Set default values for variables
    mWalkSpeed = 35.0f;
    mDirection = Ogre::Vector3::ZERO;
}
bool IntermediateTutorial1::nextLocation(void){
	if (mWalkList.empty()) return false;
    mDestination = mWalkList.front();  // this gets the front of the deque
    mWalkList.pop_front();             // this removes the front of the deque
    mDirection = mDestination - mNode->getPosition();
    mDistance = mDirection.normalise();
    return true;
}
//this to the application itself
void IntermediateTutorial1::rotateRobotToDirection(void) {
  Ogre::Vector3 src = mNode->getOrientation() * Ogre::Vector3::UNIT_X;      // Orientation from initial direction
  src.y = 0;                                                    // Ignore pitch difference angle
  mDirection.y = 0;
  src.normalise();
  Ogre::Real mDistance = mDirection.normalise( );                     // Both vectors modified so renormalize them
  Ogre::Quaternion quat = src.getRotationTo(mDirection);
 
  mNode->rotate(quat);
}
bool IntermediateTutorial1::frameRenderingQueued(const Ogre::FrameEvent &evt){
	if (mDirection == Ogre::Vector3::ZERO) {
		if (nextLocation()) {
			// Set walking animation
			mAnimationState = mEntity->getAnimationState("Walk");
			mAnimationState->setLoop(true);
			mAnimationState->setEnabled(true);				
			rotateRobotToDirection();
		}//if
	}else{
		Ogre::Real move = mWalkSpeed * evt.timeSinceLastFrame;
		mDistance -= move;
		if (mDistance <= 0.0f){                 
			mNode->setPosition(mDestination);
			mDirection = Ogre::Vector3::ZERO;				
			// Set animation based on if the robot has another point to walk to. 
			if (!nextLocation()){
				// Set Idle animation                     
				mAnimationState = mEntity->getAnimationState("Die");
				mAnimationState->setLoop(false);
				mAnimationState->setEnabled(true);
			}else{
				// Rotation Code will go here later
				Ogre::Vector3 src = mNode->getOrientation() * Ogre::Vector3::UNIT_X;
				if ((1.0f + src.dotProduct(mDirection)) < 0.0001f) {
					mNode->yaw(Ogre::Degree(180));						
				}else{
					Ogre::Quaternion quat = src.getRotationTo(mDirection);
					mNode->rotate(quat);
				} // else
			}//else
		}else{
			mNode->translate(mDirection * move);
		} // else
	} // if
	mAnimationState->addTime(evt.timeSinceLastFrame);
	return BaseApplication::frameRenderingQueued(evt);
}