//
//  worldmap.cpp
//  FilmGame
//
//  Created by Anthony Jones on 1/28/14.
//
//

#include "HelloWorldScene.h"
//#include "SimpleAudioEngine.h"
#include "sstream"
#include "global.h"
#include "worldmap.h"
#include "ProductionOffice.h"



using namespace cocos2d;
//using namespace CocosDenshion;
using namespace std;


CCScene* worldmap::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // 'layer' is an autorelease object
    worldmap *layer = worldmap::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool worldmap::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !CCLayer::init() )
    {
        return false;
    }
    //create update method
    this->schedule(schedule_selector(worldmap::update));
    countDown = 60;
    enterGameReel = false;
    
    // ask director the window size
    CCSize size = CCDirector::sharedDirector()->getWinSize();
    sfx = size.width/480;
    sfy = size.height/320;
    
    // position the label on the center of the screen
    //pLabel->setPosition( ccp(size.width / 2, size.height - 20) );
    
    // add the label as a child to this layer
    //this->addChild(pLabel, 1);
    
    // add "background image" splash screen"
    CCSprite* pSprite = CCSprite::create("campus1.png");
    pSprite->setAnchorPoint(ccp(0,0 ));
    pSprite->setScale(0.4);
    
    startImage = CCMenuItemImage::create("po_button.png", "po_button.png", this, menu_selector(worldmap::ProductionOfficeButton));
    startImage->setPosition(ccp(0,0));
    startImage->setScaleX(sfx);
    startImage->setScaleY(sfy);
    
    poButton = CCMenu::create(startImage, NULL);
    poButton->setPosition(ccp(size.width/2,(size.height/2) + (100 * sfy)));
    this->addChild(poButton, 1);
    
    startImage2 = CCMenuItemImage::create("script_button.png", "script_button.png", this, menu_selector(worldmap::makeScript));
    startImage2->setPosition(ccp(0,0));
    startImage2->setScaleX(sfx);
    startImage2->setScaleY(sfy);
    
    scriptButton = CCMenu::create(startImage2, NULL);
    scriptButton->setPosition(ccp(size.width/2, size.height/2));
    this->addChild(scriptButton, 1);
    // add the sprite as a child to this layer
    this->addChild(pSprite, 0);
    
    //Labels
    
    
    
    // load and cache the texture and sprite frames
    //CCFileUtils::sharedFileUtils()->setResour
    vector<string> Paths;
    Paths.push_back("Resources");
    CCFileUtils::sharedFileUtils()->setSearchPaths(Paths);
    cocos2d::CCSpriteFrameCache* cacher;
    cacher = CCSpriteFrameCache::sharedSpriteFrameCache();
    cacher->addSpriteFramesWithFile("testAtlas.plist");
    roomCount = 0;
    //make some crew members
    
    
    
    
    //***************init swipe gesture*****************
    //CCArray* gestArray = cocos2d::CCArray::create();
    SwipeGesture = CCSwipeGestureRecognizer::create();
    SwipeGesture->setTarget(this, callfuncO_selector(worldmap::handleSwipe));
    SwipeGesture->setDirection(kSwipeGestureRecognizerDirectionDown | kSwipeGestureRecognizerDirectionUp | kSwipeGestureRecognizerDirectionLeft);
    SwipeGesture->setCancelsTouchesInView(true);
    this->addChild(SwipeGesture);
    
    
    
    this->setTouchEnabled(true);
    return true;
}

void worldmap::tempermentShift(vector<crew*>& cArray)
{
    vector<int> TSV(6);
    
    //for loop through all of the crew’s temperaments; adding up the stat bonuses/penalties
    //foreach(crew_member in room1crew){
    for(int i = 0;i < cArray.size();i++)
    {
        for(int j = 0;j < 6;j++)
        {
            TSV[j] += cArray[i]->tempBonus[j];
        }
        
    }
    //stam,skill,speed,focus,morale,confidence
    for(int k = 0;k < cArray.size();k++)
    {
        cArray[k]->stamina += TSV[0];
        cArray[k]->skill += TSV[1];
        cArray[k]->speed += TSV[2];
        cArray[k]->focus += TSV[3];
        cArray[k]->morale += TSV[4];
        cArray[k]->baseConfidence += TSV[5];
        
        
        
    }
    
}

void worldmap::registerWithTouchDispatcher()
{
    CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, 0, true);
}

void worldmap::ccTouchEnded( CCTouch *touch, CCEvent *event){
    
 }

bool worldmap::ccTouchBegan(CCTouch *touch, CCEvent *event){
    return true;
}

void worldmap::ccTouchMoved(CCTouch* touch, CCEvent* event)
{
    
}

void worldmap::ccTouchesCancelled(CCSet* touches, CCEvent* event){
    
}

void worldmap::menuCloseCallback(CCObject* pSender)
{
    CCDirector::sharedDirector()->end();
    
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}

void worldmap::update(float dt)
{
    //CCSize size = CCDirector::sharedDirector()->getWinSize();
    //test for crew leaving to the left room
    //if(countDown >= 0){
       // countDown--;
    //}
    
       
}

void worldmap::makeScript(){
    //choose a number between 101 and 110
    srand( time(NULL));
	int roll = rand() % 9 + 101; //range 1 to 3
    cout << "roll = " << roll << endl;
    vector<int> writers = {roll};
    
    Script * newScript = new Script(getCrewFromDB(writers));
    scriptVector.push_back(newScript);
    //Script::titleBuilder();
}
void worldmap::ProductionOfficeButton(){
    CCScene* po = ProductionOffice::scene();
    CCDirector::sharedDirector()->replaceScene(po);

}
void worldmap::handleSwipe(CCObject* obj)
{
    CCSwipe * swipe = (CCSwipe*)obj;
    if(swipe->direction == kSwipeGestureRecognizerDirectionUp){
        
        cout << "gesture retain count = " << SwipeGesture->retainCount() << endl;
        //this->removeChild(SwipeGesture);
        gestureBufferDown();
    }
    
    if(swipe->direction == kSwipeGestureRecognizerDirectionDown){
        //swipe->release();
        
        cout << "gesture retain count = " << SwipeGesture->retainCount() << endl;
        gestureBufferUp();
        
    }
    
    
    if(swipe->direction == kSwipeGestureRecognizerDirectionLeft){
        //swipe->release();
        
        cout << "gesture retain count = " << SwipeGesture->retainCount() << endl;
        gestureBufferLeft();
        
    }
    
}


void worldmap::gestureBufferUp(){
    
    
    /*CCCallFunc* startNext=CCCallFunc::create( this,
     callfunc_selector(baseRoom::switchUp) );
     
     CCMoveBy *slide = CCMoveBy::create(0.2, ccp(0, -350 * sfy));
     
     CCSequence* act =CCSequence::create(slide, startNext, NULL);
     blueFade->runAction(act);
     */
    //switchUp();
}

void worldmap::gestureBufferDown(){
    
    

}

void worldmap::gestureBufferRight(){
    
    

}

void worldmap::gestureBufferLeft(){
    
    cout<< "swipe left" << endl;

   
}
