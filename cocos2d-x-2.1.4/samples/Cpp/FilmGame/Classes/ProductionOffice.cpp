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
//#include "GreenRoom.h"
#include "ProductionOffice.h"



using namespace cocos2d;
//using namespace CocosDenshion;
using namespace std;


CCScene* ProductionOffice::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // 'layer' is an autorelease object
    ProductionOffice *layer = ProductionOffice::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool ProductionOffice::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !CCLayer::init() )
    {
        return false;
    }
    //create update method
    this->schedule(schedule_selector(ProductionOffice::update));
    countDown = 60;
    enterGameReel = false;
    crewPressed = false;
    scriptsPressed = false;
    
    // ask director the window size
    CCSize size = CCDirector::sharedDirector()->getWinSize();
    sfx = size.width/480;
    sfy = size.height/320;
    
    CCArray *crewMenuItems  = new CCArray();
    for(int i = 0; i < crewList.size(); i++)
    {
        char tc_label[20];
        sprintf(tc_label, "crew_ID = %i", crewList[i]);
        CCMenuItemFont* tItem = CCMenuItemFont::create(tc_label, this, menu_selector(ProductionOffice::viewCrew));
        tItem->setFontSize(35);
        tItem->setPosition(ccp(0,0));
        tItem->setFontName("Helvetica");
        tItem->setColor(ccc3(0,0,0));
        crewMenuItems->addObject(tItem);
    }
    
    crewListMenu = CCMenu::createWithArray(crewMenuItems);
    crewListMenu->alignItemsVertically();
    crewListMenu->setPosition(ccp((size.width/2) - (100 * sfy),(size.height/2)));
    this->addChild(crewListMenu, -1);
    
    
    
    CCArray *scriptMenuItems  = new CCArray();
    
    for(int i = 0; i < scriptVector.size(); i++)
    {
        char tc_label[60];
        sprintf(tc_label, "%s", scriptVector[i]->title.c_str());
        
        CCMenuItemFont* tItem = CCMenuItemFont::create(tc_label, this, menu_selector(ProductionOffice::viewScripts));
        tItem->setFontSize(20);
        tItem->setPosition(ccp(0,0));
        tItem->setFontName("Helvetica");
        tItem->setColor(ccc3(0,0,0));
        scriptMenuItems->addObject(tItem);
    }
    
    script_List = CCMenu::createWithArray(scriptMenuItems);
    script_List->alignItemsVertically();
    script_List->setPosition(ccp((size.width/2) - (100 * sfy),(size.height/2)));
    this->addChild(script_List, -1);

    
    
    // position the label on the center of the screen
    //pLabel->setPosition( ccp(size.width / 2, size.height - 20) );
    
    // add the label as a child to this layer
    //this->addChild(pLabel, 1);
    
    // add "background image" splash screen"
    CCSprite* pSprite = CCSprite::create("po_room_bg.png");
    pSprite->setAnchorPoint(ccp(0,0 ));
    pSprite->setScaleY(0.8);
    pSprite->setScaleX(1);
    
   // startImage = CCMenuItemImage::create("po_button.png", "po_button.png", this, );
    
    scriptsImage = CCMenuItemImage::create("script_button.png", "script_button.png", this, menu_selector(ProductionOffice::viewScripts));
    scriptsImage->setPosition(ccp(0,0));
    scriptsImage->setScaleX(0.8 * sfx);
    scriptsImage->setScaleY(0.8 *sfy);
    
    scriptsButton = CCMenu::create(scriptsImage, NULL);
    scriptsButton->setPosition(ccp((size.width/2) + (100 * sfx) , (size.height/2) + (110 * sfy)));
    this->addChild(scriptsButton, 1);
    
    
    crewImage = CCMenuItemImage::create("crew_button.png", "crew_button.png", this, menu_selector(ProductionOffice::viewCrew));
    crewImage->setPosition(ccp(0,0));
    crewImage->setScaleX(0.8 * sfx);
    crewImage->setScaleY(0.8 * sfy);
    
    crewButton = CCMenu::create(crewImage, NULL);
    crewButton->setPosition(ccp((size.width/2) + (100 * sfx) , (size.height/2) - (110 * sfy)));
    this->addChild(crewButton, 1);

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
    SwipeGesture->setTarget(this, callfuncO_selector(ProductionOffice::handleSwipe));
    SwipeGesture->setDirection(kSwipeGestureRecognizerDirectionDown | kSwipeGestureRecognizerDirectionUp | kSwipeGestureRecognizerDirectionLeft);
    SwipeGesture->setCancelsTouchesInView(true);
    this->addChild(SwipeGesture);
    
    
    
    this->setTouchEnabled(true);
    return true;
}

void ProductionOffice::tempermentShift(vector<crew*>& cArray)
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

void ProductionOffice::registerWithTouchDispatcher()
{
    CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, 0, true);
}

void ProductionOffice::ccTouchEnded( CCTouch *touch, CCEvent *event){
    
 }

bool ProductionOffice::ccTouchBegan(CCTouch *touch, CCEvent *event){
    return true;
}

void ProductionOffice::ccTouchMoved(CCTouch* touch, CCEvent* event)
{
    
}

void ProductionOffice::ccTouchesCancelled(CCSet* touches, CCEvent* event){
    
}

void ProductionOffice::menuCloseCallback(CCObject* pSender)
{
    CCDirector::sharedDirector()->end();
    
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}

void ProductionOffice::update(float dt)
{
    //CCSize size = CCDirector::sharedDirector()->getWinSize();
    //test for crew leaving to the left room
    //if(countDown >= 0){
       // countDown--;
    //}
    
       
}

void ProductionOffice::makeScript(){
    //choose a number between 101 and 110
    srand( time(NULL));
	int roll = rand() % 9 + 101; //range 1 to 3
    cout << "roll = " << roll << endl;
    vector<int> writers = {roll};
    
    Script * newScript = new Script(getCrewFromDB(writers));
    scriptVector.push_back(newScript);
    //Script::titleBuilder();
}

void ProductionOffice::handleSwipe(CCObject* obj)
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


void ProductionOffice::gestureBufferUp(){
    
    
    /*CCCallFunc* startNext=CCCallFunc::create( this,
     callfunc_selector(baseRoom::switchUp) );
     
     CCMoveBy *slide = CCMoveBy::create(0.2, ccp(0, -350 * sfy));
     
     CCSequence* act =CCSequence::create(slide, startNext, NULL);
     blueFade->runAction(act);
     */
    //switchUp();
}

void ProductionOffice::gestureBufferDown(){
    
    

}

void ProductionOffice::gestureBufferRight(){
    
    

}

void ProductionOffice::gestureBufferLeft(){
    
    cout<< "swipe left" << endl;

   
}

void ProductionOffice::viewCrew()
{
    if(!crewPressed){
    crewListMenu->setZOrder(10);
        crewPressed = true;
    }
    else{
        crewListMenu->setZOrder(-1);
        crewPressed = false;
    }
}
void ProductionOffice::viewScripts()
{
    if(!scriptsPressed){
        script_List->setZOrder(10);
        scriptsPressed = true;
    }
    else{
        script_List->setZOrder(-1);
        scriptsPressed = false;
    }

}