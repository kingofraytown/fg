//
//  loadGame.cpp
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
#include "loadGame.h"
#include "worldmap.h"


using namespace cocos2d;
//using namespace CocosDenshion;
using namespace std;


CCScene* loadGame::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // 'layer' is an autorelease object
    loadGame *layer = loadGame::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool loadGame::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !CCLayer::init() )
    {
        return false;
    }
    //create update method
    this->schedule(schedule_selector(loadGame::update));
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
    CCSprite* pSprite = CCSprite::create("load_game_bg.png");
    pSprite->setAnchorPoint(ccp(0,0 ));
    pSprite->setScaleY(0.8);
    pSprite->setScaleX(1);
    
    
    
    loadImage1 = CCMenuItemImage::create("clearButton.png", "clearButton.png", this, menu_selector(loadGame::loadGame1));
    loadImage1->setPosition(ccp(0,0));
    loadImage1->setScaleX(.2 *sfx);
    loadImage1->setScaleY(.2 *sfy);
    
    load1 = CCMenu::create(loadImage1, NULL);
    load1->setPosition(ccp((size.width/2) - (sfx * 140), size.height/2));
    this->addChild(load1, 1);
    // add the sprite as a child to this layer

    
    
    
    loadImage2 = CCMenuItemImage::create("clearButton.png", "clearButton.png", this, menu_selector(loadGame::loadGame2));
    loadImage2->setPosition(ccp(0,0));
    loadImage2->setScaleX(.2 * sfx);
    loadImage2->setScaleY(.2 * sfy);
    
    load2 = CCMenu::create(loadImage2, NULL);
    load2->setPosition(ccp((size.width/2), size.height/2));
    this->addChild(load2, 1);
    // add the sprite as a child to this layer

    
    loadImage3 = CCMenuItemImage::create("clearButton.png", "clearButton.png", this, menu_selector(loadGame::loadGame3));
    loadImage3->setPosition(ccp(0,0));
    loadImage3->setScaleX(.2 * sfx);
    loadImage3->setScaleY(.2 * sfy);
    
    load3 = CCMenu::create(loadImage3, NULL);
    load3->setPosition(ccp((size.width/2) + (sfx * 140), size.height/2));
    this->addChild(load3, 1);
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
    SwipeGesture->setTarget(this, callfuncO_selector(loadGame::handleSwipe));
    SwipeGesture->setDirection(kSwipeGestureRecognizerDirectionDown | kSwipeGestureRecognizerDirectionUp | kSwipeGestureRecognizerDirectionLeft);
    SwipeGesture->setCancelsTouchesInView(true);
    this->addChild(SwipeGesture);
    
    
    
    this->setTouchEnabled(true);
    return true;
}

void loadGame::tempermentShift(vector<crew*>& cArray)
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

void loadGame::registerWithTouchDispatcher()
{
    CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, 0, true);
}

void loadGame::ccTouchEnded( CCTouch *touch, CCEvent *event){
    
 }

bool loadGame::ccTouchBegan(CCTouch *touch, CCEvent *event){
    return true;
}

void loadGame::ccTouchMoved(CCTouch* touch, CCEvent* event)
{
    
}

void loadGame::ccTouchesCancelled(CCSet* touches, CCEvent* event){
    
}

void loadGame::menuCloseCallback(CCObject* pSender)
{
    CCDirector::sharedDirector()->end();
    
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}

void loadGame::update(float dt)
{
    //CCSize size = CCDirector::sharedDirector()->getWinSize();
    //test for crew leaving to the left room
    //if(countDown >= 0){
       // countDown--;
    //}
    
       
}

/*void loadGame::makeScript(){
    //choose a number between 101 and 110
    srand( time(NULL));
	int roll = rand() % 9 + 101; //range 1 to 3
    cout << "roll = " << roll << endl;
    vector<int> writers = {roll};
    
    Script * newScript = new Script(getCrewFromDB(writers));
    scriptVector.push_back(newScript);
    //Script::titleBuilder();
}
 */
void loadGame::NewGameButton(){
    makeNewGameFile();
    
}
void loadGame::handleSwipe(CCObject* obj)
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


void loadGame::gestureBufferUp(){
    
    
    /*CCCallFunc* startNext=CCCallFunc::create( this,
     callfunc_selector(baseRoom::switchUp) );
     
     CCMoveBy *slide = CCMoveBy::create(0.2, ccp(0, -350 * sfy));
     
     CCSequence* act =CCSequence::create(slide, startNext, NULL);
     blueFade->runAction(act);
     */
    //switchUp();
}

void loadGame::gestureBufferDown(){
    
    

}

void loadGame::gestureBufferRight(){
    
    

}

void loadGame::gestureBufferLeft(){
    
    cout<< "swipe left" << endl;

   
}

bool loadGame::checkForFile(string fileName)
{
    bool isThere = false;
    
    //get write path
    string path = CCFileUtils::sharedFileUtils()->getWritablePath();
    
    
    //append file name
    path.append(fileName);
    //cout << path << endl;
    
    TiXmlDocument doc(path.c_str());
    
    isThere = doc.LoadFile();

    
    return isThere;

    
}

void loadGame::loadGame1()
{
    string fName = "GameMaster_1.xml";
    
    bool fileExist = checkForFile(fName);
    
    if(fileExist){
        currentGameFile = fName;
        //load scripts to globle
        loadScripts(fName);
        //load crew to gloable
        loadCrew(fName);
        //load equipment
        loadEquipment(fName);
        //load current production
        
        //load progress data
        loadStores(fName);
        //switch scene
        
        CCScene* wmap = worldmap::scene();
        CCDirector::sharedDirector()->replaceScene(wmap);

        
    }
    
    
}

void loadGame::loadGame2()
{
    string fName = "GameMaster_2.xml";
    
    bool fileExist = checkForFile(fName);
    
    if(fileExist){
        currentGameFile = fName;
        //load scripts to globle
        loadScripts(fName);
        //load crew to gloable
        loadCrew(fName);
        //load equipment
        loadEquipment(fName);
        //load current production
        
        //load progress data
        
        //switch scene

        CCScene* wmap = worldmap::scene();
        CCDirector::sharedDirector()->replaceScene(wmap);
        
        
    }
    
    
}

void loadGame::loadGame3()
{
    string fName = "GameMaster_3.xml";
    
    bool fileExist = checkForFile(fName);
    
    if(fileExist){
        currentGameFile = fName;
        //load scripts to globle
        loadScripts(fName);
        //load crew to gloable
        loadCrew(fName);
        //load equipment
        loadEquipment(fName);
        //load current production
        
        //load progress data
        
        //switch scene

        CCScene* wmap = worldmap::scene();
        CCDirector::sharedDirector()->replaceScene(wmap);
        
        
    }
    
    
}


