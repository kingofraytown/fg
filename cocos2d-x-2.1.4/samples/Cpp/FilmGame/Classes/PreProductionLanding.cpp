//
//  PreProductionLanding.cpp
//  FilmGame
//
//  Created by Anthony Jones on 1/28/14.
//
//

#include "HelloWorldScene.h"
//#include "SimpleAudioEngine.h"
#include "sstream"
#include "global.h"
#include "PreUtility.h"
#include "PreProductionLanding.h"
#include "ProductionOffice.h"
#include "TableViewTestScene.h"
#include "StartPage.h"


using namespace cocos2d;
//using namespace PreUtility;
using namespace std;


CCScene* PreProductionLanding::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // 'layer' is an autorelease object
    PreProductionLanding *layer = PreProductionLanding::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool PreProductionLanding::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !CCLayer::init() )
    {
        return false;
    }
    //create update method
    this->schedule(schedule_selector(PreProductionLanding::update));
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
    CCSprite* pSprite = CCSprite::create("Pre_bg.png");
    pSprite->setAnchorPoint(ccp(0,0 ));
    pSprite->setScale(1* sfy);
    
    manualImage = CCMenuItemImage::create("Manual_button.png", "po_button_down.png", this, menu_selector(PreProductionLanding::ManualSelection));
    manualImage->setPosition(ccp(0,0));
    manualImage->setScaleX(sfx);
    manualImage->setScaleY(sfy);
    
    manualButton = CCMenu::create(manualImage, NULL);
    manualButton->setPosition(ccp(size.width/2,(size.height/2) + (100 * sfy)));
    this->addChild(manualButton, 1);
    
    cheapImage = CCMenuItemImage::create("Cheap_button.png", "script_button_down.png", this, menu_selector(PreProductionLanding::DoItCheap));
    cheapImage->setPosition(ccp(0,0));
    cheapImage->setScaleX(sfx);
    cheapImage->setScaleY(sfy);
    
    cheapButton = CCMenu::create(cheapImage, NULL);
    cheapButton->setPosition(ccp(size.width/2, size.height/2));
    this->addChild(cheapButton, 1);
    
    wellDoneImage = CCMenuItemImage::create("WellDone_button.png", "script_button_down.png", this, menu_selector(PreProductionLanding::DoItWell));
    wellDoneImage->setPosition(ccp(0,0));
    wellDoneImage->setScaleX(sfx);
    wellDoneImage->setScaleY(sfy);
    
    wellDoneButton = CCMenu::create(wellDoneImage, NULL);
    wellDoneButton->setPosition(ccp(size.width/2, (size.height/2)- (100 * sfy)));
    this->addChild(wellDoneButton, 1);

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
    
    //******************BACK BUTTON*********************
    backImage = CCMenuItemImage::create("back_button.png", "back_button.png", this, menu_selector(PreProductionLanding::goback));
    backImage->setPosition(ccp(0,0));
    backImage->setScaleX(0.8 * sfx);
    backImage->setScaleY(0.8 * sfy);
    
    backButton = CCMenu::create(backImage, NULL);
    backButton->setPosition(ccp((30 * sfx) , (30 * sfy)));
    this->addChild(backButton, 2);

    
    
    //***************init swipe gesture*****************
    //CCArray* gestArray = cocos2d::CCArray::create();
    SwipeGesture = CCSwipeGestureRecognizer::create();
    SwipeGesture->setTarget(this, callfuncO_selector(PreProductionLanding::handleSwipe));
    SwipeGesture->setDirection(kSwipeGestureRecognizerDirectionDown | kSwipeGestureRecognizerDirectionUp | kSwipeGestureRecognizerDirectionLeft);
    SwipeGesture->setCancelsTouchesInView(true);
    this->addChild(SwipeGesture);
    
    
    
    this->setTouchEnabled(true);
    return true;
}


void PreProductionLanding::ManualSelection(){
    
}
void PreProductionLanding::DoItCheap(){
    
    //get crew
    preCrewMembers = PreUtility::GetCheapCrew();
    
    //print crew skill and hire cost and crewID
    /*for(int i = 0; i < preCrewMembers.size();i++)
    {
        cout << "crewID= " <<preCrewMembers[i]->crewID << " hire cost= " << preCrewMembers[i]->hireCost << " skill= " << preCrewMembers[i]->skill <<endl;
    }*/
    //get needed equipment
    
    cout << "equipment.size = " << preEquipment.size() << endl;
    PreUtility::GetNeededEquipment();
    
    /*for (int k = 0; k < preEquipment.size(); k++) {
        cout << "equipmentID= " << preEquipment[k]->equipmentID << " type= " << preEquipment[k]->m_type << " cost= " << preEquipment[k]->cost << endl;;
    }
    */
    //get cheap equipment
    cout << "equipment.size = " << preEquipment.size() << endl;
    vector<equipment*> tempVector =  PreUtility::GetCheapEquipment();
    preEquipment.insert( preEquipment.end(), tempVector.begin(), tempVector.end() ) ;
    /*
    for (int k = 0; k < preEquipment.size(); k++) {
        cout << "equipmentID= " << preEquipment[k]->equipmentID << " type= " << preEquipment[k]->m_type << " cost= " << preEquipment[k]->cost << " rental cost= " << preEquipment[k]->rentalCost << " rentalBool = " << preEquipment[k]->rental << endl;
    }*/
    //print out equipmentID anme and rental status and 
       //generate production schedule
    PreUtility::FillProductionSchedule();
    cout << currentProduction->productionScenes[0] << endl;
    
    
    
    
                
    
}

void PreProductionLanding::DoItWell()
{
    
}


void PreProductionLanding::registerWithTouchDispatcher()
{
    CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, 0, true);
}

void PreProductionLanding::ccTouchEnded( CCTouch *touch, CCEvent *event){
    
 }

bool PreProductionLanding::ccTouchBegan(CCTouch *touch, CCEvent *event){
    return true;
}

void PreProductionLanding::ccTouchMoved(CCTouch* touch, CCEvent* event)
{
    
}

void PreProductionLanding::ccTouchesCancelled(CCSet* touches, CCEvent* event){
    
}

void PreProductionLanding::menuCloseCallback(CCObject* pSender)
{
    CCDirector::sharedDirector()->end();
    
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}

void PreProductionLanding::update(float dt)
{
    //CCSize size = CCDirector::sharedDirector()->getWinSize();
    //test for crew leaving to the left room
    //if(countDown >= 0){
       // countDown--;
    //}
    
       
}


void PreProductionLanding::handleSwipe(CCObject* obj)
{
    CCSwipe * swipe = (CCSwipe*)obj;
    if(swipe->direction == kSwipeGestureRecognizerDirectionUp){
        
        //cout << "gesture retain count = " << SwipeGesture->retainCount() << endl;
        //this->removeChild(SwipeGesture);
        gestureBufferDown();
    }
    
    if(swipe->direction == kSwipeGestureRecognizerDirectionDown){
        //swipe->release();
        
       // cout << "gesture retain count = " << SwipeGesture->retainCount() << endl;
        gestureBufferUp();
        
    }
    
    
    if(swipe->direction == kSwipeGestureRecognizerDirectionLeft){
        //swipe->release();
        
        //cout << "gesture retain count = " << SwipeGesture->retainCount() << endl;
        gestureBufferLeft();
        
    }
    
}


void PreProductionLanding::gestureBufferUp(){
    
    
    /*CCCallFunc* startNext=CCCallFunc::create( this,
     callfunc_selector(baseRoom::switchUp) );
     
     CCMoveBy *slide = CCMoveBy::create(0.2, ccp(0, -350 * sfy));
     
     CCSequence* act =CCSequence::create(slide, startNext, NULL);
     blueFade->runAction(act);
     */
    //switchUp();
}

void PreProductionLanding::gestureBufferDown(){
    
    

}

void PreProductionLanding::gestureBufferRight(){
    
    

}

void PreProductionLanding::gestureBufferLeft(){
    
    cout<< "swipe left" << endl;

   
}

void PreProductionLanding::goback()
{
    scriptVector.clear();
    crewList.clear();
    CCScene * sp = StartPage::scene();
    sp->retain();
    CCDirector::sharedDirector()->replaceScene(sp);
    
}

