//
//  TestGame.cpp
//  FilmGame
//
//  Created by Anthony Jones on 1/28/14.
//
//

#include "HelloWorldScene.h"
//#include "SimpleAudioEngine.h"
#include "sstream"
#include "global.h"
#include "TestGame.h"
#include "ProductionOffice.h"
#include "TableViewTestScene.h"
#include "StartPage.h"
#include <math.h>


using namespace cocos2d;
//using namespace CocosDenshion;
using namespace std;
static ccColor3B s_TouchColors[CC_MAX_TOUCHES] = {
    ccYELLOW,
    ccBLUE,
    ccGREEN,
    ccRED,
    ccMAGENTA
};
static CCDictionary s_dic;

class TouchPoint : public CCNode
{
public:
    TouchPoint()
    {
        setShaderProgram(CCShaderCache::sharedShaderCache()->programForKey(kCCShader_PositionTextureColor));
    }
    
    virtual void draw()
    {
        ccDrawColor4B(m_TouchColor.r, m_TouchColor.g, m_TouchColor.b, 255);
        glLineWidth(10);
        ccDrawLine( ccp(0, m_pTouchPoint.y), ccp(getContentSize().width, m_pTouchPoint.y) );
        ccDrawLine( ccp(m_pTouchPoint.x, 0), ccp(m_pTouchPoint.x, getContentSize().height) );
        glLineWidth(1);
        ccPointSize(30);
        ccDrawPoint(m_pTouchPoint);
    }
    
    void setTouchPos(const CCPoint& pt)
    {
        m_pTouchPoint = pt;
    }
    
    void setTouchColor(ccColor3B color)
    {
        m_TouchColor = color;
    }
    
    static TouchPoint* touchPointWithParent(CCNode* pParent)
    {
        TouchPoint* pRet = new TouchPoint();
        pRet->setContentSize(pParent->getContentSize());
        pRet->setAnchorPoint(ccp(0.0f, 0.0f));
        pRet->autorelease();
        return pRet;
    }
    
private:
    CCPoint m_pTouchPoint;
    ccColor3B m_TouchColor;
};

CCScene* TestGame::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // 'layer' is an autorelease object
    TestGame *layer = TestGame::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool TestGame::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !CCLayer::init() )
    {
        return false;
    }
    //create update method
    this->schedule(schedule_selector(TestGame::update));
    countDown = 60;
    enterGameReel = false;
    LeftButtonUP = true;
    LeftDelta = 0.0;
    RightDelta = 0.0;
    LeftButtonUP = false;
    lastLeftCoord = 0.0;
    currentYCoord = 0.0;
    LastRightCoord =0.0;
    lastSpeed = 0.0;
    currentSpeed = 0.0;
    
    // ask director the window size
    CCSize size = CCDirector::sharedDirector()->getWinSize();
    rSize = size;
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
    
    vArrow = CCSprite::create("vectorArrow.png");
    vArrow->setAnchorPoint(ccp(0.5, 0.5));
    vArrow->setRotation(0.0);
    vArrow->setPosition(ccp(size.width/2, size.height/2));
    this->addChild(vArrow, 2);
    
    lastAngle = vArrow->getRotation();
    
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
    backImage = CCMenuItemImage::create("back_button.png", "back_button.png", this, menu_selector(TestGame::goback));
    backImage->setPosition(ccp(0,0));
    backImage->setScaleX(0.8 * sfx);
    backImage->setScaleY(0.8 * sfy);
    
    backButton = CCMenu::create(backImage, NULL);
    backButton->setPosition(ccp((30 * sfx) , (30 * sfy)));
    this->addChild(backButton, 2);

    
    
    //***************init swipe gesture*****************
    //CCArray* gestArray = cocos2d::CCArray::create();
    SwipeGesture = CCSwipeGestureRecognizer::create();
    SwipeGesture->setTarget(this, callfuncO_selector(TestGame::handleSwipe));
    SwipeGesture->setDirection(kSwipeGestureRecognizerDirectionDown | kSwipeGestureRecognizerDirectionUp | kSwipeGestureRecognizerDirectionLeft);
    SwipeGesture->setCancelsTouchesInView(true);
    this->addChild(SwipeGesture);
    
    this->setTouchEnabled(true);
    return true;
}

void TestGame::tempermentShift(vector<crew*>& cArray)
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

/*void TestGame::registerWithTouchDispatcher()
{
    CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, 0, true);
}*/

void TestGame::ccTouchEnded( CCTouch *touch, CCEvent *event){
    
 }

bool TestGame::ccTouchBegan(CCTouch *touch, CCEvent *event){
    return true;
}

void TestGame::ccTouchMoved(CCTouch* touch, CCEvent* event)
{
    
}

void TestGame::ccTouchesCancelled(CCSet* touches, CCEvent* event){
    
}
void TestGame::registerWithTouchDispatcher(void)
{
    CCDirector::sharedDirector()->getTouchDispatcher()->addStandardDelegate(this, 0);
}

void TestGame::ccTouchesBegan(CCSet *pTouches, CCEvent *pEvent)
{
    CCSetIterator iter = pTouches->begin();
    for (; iter != pTouches->end(); iter++)
    {
        CCTouch* pTouch = (CCTouch*)(*iter);
        TouchPoint* pTouchPoint = TouchPoint::touchPointWithParent(this);
        CCPoint location = pTouch->getLocation();
        
        pTouchPoint->setTouchPos(location);
        pTouchPoint->setTouchColor(s_TouchColors[pTouch->getID()]);
        
        if(location.x > (rSize.width/2))
           {
             //RIGHT TOUCH
               LastRightCoord = location.y;
               //LastRightPoint = &location;
           }
        if(location.x <= (rSize.width/2))
           {
               //LEFT TOUCH
               
               lastLeftCoord = location.y;
           }
        
        addChild(pTouchPoint);
        s_dic.setObject(pTouchPoint, pTouch->getID());
    }
    
    
}

void TestGame::ccTouchesMoved(CCSet *pTouches, CCEvent *pEvent)
{

    bool updatelocationLeft = true;
    CCSetIterator iter = pTouches->begin();
    for (; iter != pTouches->end(); iter++)
    {

        CCTouch* pTouch = (CCTouch*)(*iter);
        TouchPoint* pTP = (TouchPoint*)s_dic.objectForKey(pTouch->getID());
        CCPoint location = pTouch->getLocation();
        if(location.x > (rSize.width/2))
           {
               //RIGHT TOUCH
               RightDelta = location.y - LastRightCoord;
               
               
               LastRightCoord = location.y;
           }
        if(pTouch->getLocation().x <= (rSize.width/2))
        {
            //LEFT TOUCH
              
            LeftDelta = location.y - lastLeftCoord;
            lastLeftCoord = location.y;
        }
        
        
        pTP->setTouchPos(location);
    }
    
}

void TestGame::ccTouchesEnded(CCSet *pTouches, CCEvent *pEvent)
{
    int p = 0;
    CCSetIterator iter = pTouches->begin();
    CCTouch* pTouch = (CCTouch*)(*iter);
    CCPoint location = pTouch->getLocation();
    for (; iter != pTouches->end(); iter++)
    {
        p++;
        if(pTouch->getLocation().x > (rSize.width/2))
        {
            //RIGHT TOUCH
            //RightDelta = 0.0;
            
            
            //LastRightPoint = &location;
        }
        if(pTouch->getLocation().x <= (rSize.width/2))
        {
            
        }
        
        CCTouch* pTouch = (CCTouch*)(*iter);
        TouchPoint* pTP = (TouchPoint*)s_dic.objectForKey(pTouch->getID());
        removeChild(pTP, true);
        s_dic.removeObjectForKey(pTouch->getID());
    }
}


void TestGame::menuCloseCallback(CCObject* pSender)
{
    CCDirector::sharedDirector()->end();
    
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}

void TestGame::update(float dt)
{
    
    if(lastLeftCoord != currentYCoord )
    {
       
        lastAngle = vArrow->getRotation();
        float dt = LeftDelta * 0.8;
    
        if(dt > 90)
        {
            dt = 90;
        }
        if(dt < -90)
        {
            dt = -90;
        }
        CCPoint p = vArrow->getPosition();
        //vArrow->setRotation(lastAngle + dt);
        vArrow->setPositionX(p.x + LeftDelta);
        currentYCoord = lastLeftCoord;
    }
    
    if(LastRightCoord != currentSpeed)
    {
        lastAngle = vArrow->getRotation();
        
        //delta x = speed cos( lastAngle)
        float dx = RightDelta * cosf(lastAngle);
        float dy = RightDelta * sinf(lastAngle);
        //delta y = speed sin(lastAngle)
        CCPoint p = vArrow->getPosition();
        //vArrow->setPosition(ccp(p.x + (dx * sfx),p.y + (dy * sfy)));
        vArrow->setPositionY(p.y + RightDelta);
        
        currentSpeed = LastRightCoord;
    }
    else{
        
    }
        
    
    
    
}

void TestGame::handleSwipe(CCObject* obj)
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


void TestGame::gestureBufferUp(){
    
    
    /*CCCallFunc* startNext=CCCallFunc::create( this,
     callfunc_selector(baseRoom::switchUp) );
     
     CCMoveBy *slide = CCMoveBy::create(0.2, ccp(0, -350 * sfy));
     
     CCSequence* act =CCSequence::create(slide, startNext, NULL);
     blueFade->runAction(act);
     */
    //switchUp();
}

void TestGame::gestureBufferDown(){
    
    

}

void TestGame::gestureBufferRight(){
    
    

}

void TestGame::gestureBufferLeft(){
    
    cout<< "swipe left" << endl;

   
}

void TestGame::goback()
{
    scriptVector.clear();
    crewList.clear();
    CCScene * sp = StartPage::scene();
    sp->retain();
    CCDirector::sharedDirector()->replaceScene(sp);
    
}

