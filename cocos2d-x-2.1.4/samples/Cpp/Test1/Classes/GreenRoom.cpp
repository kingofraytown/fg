//
//  GreenRoom.cpp
//  Test1
//
//  Created by Anthony Jones on 4/20/13.
//
//
#include "HelloWorldScene.h"
#include "GreenRoom.h"
#include "SimpleAudioEngine.h"
#include "sstream"
#include "global.h"


using namespace cocos2d;
using namespace CocosDenshion;
using namespace std;


CCScene* GreenRoom::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // 'layer' is an autorelease object
    GreenRoom *layer = GreenRoom::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool GreenRoom::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !CCLayer::init() )
    {
        return false;
    }
    scheduleUpdate();
    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.
    
    // add a "close" icon to exit the progress. it's an autorelease object
    
    /*CCMenuItemImage *pCloseItem = CCMenuItemImage::create(
     "CloseNormal.png",
     "CloseSelected.png",
     this,
     menu_selector(GreenRoom::menuCloseCallback) );
     pCloseItem->setPosition( ccp(CCDirector::sharedDirector()->getWinSize().width - 20, 20) );
     
     // create menu, it's an autorelease object
     CCMenu* pMenu = CCMenu::create(pCloseItem, NULL);
     pMenu->setPosition( CCPointZero );
     this->addChild(pMenu, 1);
     */
    
    /////////////////////////////
    // 3. add your codes below...
    
    // add a label shows "Hello World"
    // create and initialize a label
    //CCLabelTTF* pLabel = CCLabelTTF::create("Hello World", "Thonburi", 34);
    
    
    
    
    
    // ask director the window size
    //making the scaling factors
    CCSize size = CCDirector::sharedDirector()->getWinSize();
    sfx = size.width/480;
    sfy = size.height/320;
    
    
    
    
    
    
    // position the label on the center of the screen
    //pLabel->setPosition( ccp(size.width / 2, size.height - 20) );
    
    // add the label as a child to this layer
    //this->addChild(pLabel, 1);
    
    
    
    
    
    //*****Adding the BG ******************
    // add "HelloWorld" splash screen"
    CCSprite* pSprite = CCSprite::create("cocos2dmix.png");
    
    // position the sprite on the center of the screen
    pSprite->setPosition( ccp(size.width/2, size.height/2) );
    
    // add the sprite as a child to this layer
    this->addChild(pSprite, 0);
    //***************************************
    
    
    
    
    
    
    //Labels
    
    
    //*******************************************************
    // load and cache the texture and sprite frames
    vector<string> Paths;
    Paths.push_back("Resources");
    CCFileUtils::sharedFileUtils()->setSearchPaths(Paths);
    cocos2d::CCSpriteFrameCache* cacher;
    cacher = CCSpriteFrameCache::sharedSpriteFrameCache();
    cacher->addSpriteFramesWithFile("testAtlas.plist");
    roomCount = 0;
    //*******************************************************
    
    
    //make some crew members
   // crew *Doug = new crew();
    //crew *Jmo = new crew();
    room = new CCSprite();
    button = new CCSprite();
    rightArrow = new CCSprite();
    
    
    
    //*******Scaling ccsprites and adding the children to the layer
    
    //button->initWithSpriteFrameName("button");
    //room->initWithSpriteFrameName("grey_room");
    //Jmo->initWithSpriteFrameName("red_c");
    //Doug->initWithSpriteFrameName("blue_c");
    
    rightArrow->initWithSpriteFrameName("arrow");
    rightArrow->setScaleY(0.5);
    rightArrow->setPosition(ccp(size.width - 10,size.height/2));
    rightArrow->setRotation(90);

    
    //Doug->setScaleX(sfx);
    //Doug->setScaleY(sfy);
    
    //Jmo->setScaleX(sfx);
    //Jmo->setScaleY(sfy);
    
    room->setScaleX(sfx);
    room->setScaleY(sfy);
    
    button->setScaleX(sfx);
    button->setScaleY(sfy);
    
    pSprite->setScaleX(sfx);
    pSprite->setScaleY(sfy);
    
    button->cocos2d::CCNode::setPosition(350.00 * sfx,20.0 * sfy);
    //Jmo->setAnchorPoint(ccp(0.5,0.0));
    //Jmo->cocos2d::CCNode::setPosition(ccp(70.0 * sfx, 50.0 * sfy));
    //Doug->setAnchorPoint(ccp(0.5, 0.0));
    //Doug->cocos2d::CCNode::setPosition(ccp(40.0 * sfx, 50.0 * sfy));
    
    
    
    room->setAnchorPoint(ccp(0.5,0.5));
    room->cocos2d::CCSprite::setPosition(ccp(300.0 * sfx, 180.0 * sfy));
    
    
    //room2crew.push_back(Doug);
    //room2crew.push_back(Jmo);
    
    /*
    Doug->temperament[0] = 1;
    Doug->temperament[1] = 4;
    
    
    Jmo->temperament[0] = 4;
    Jmo->temperament[1] = 10;
    
    
    
    
    Doug->social = 60;
    Doug->focus = 8;
    Doug->skill = 80;
    Doug->speed = 80;
    Doug->morale = 80;
    Doug->stamina = 80;
    Doug->baseConfidence = 80;
    
    Jmo->stamina = 70;
    Jmo->speed = 70;
    Jmo->skill = 70;
    Jmo->social = 70;
    Jmo->focus = 7;
    Jmo->morale = 65;
    Jmo->baseConfidence = 70;
    
    Doug->temperAssign();
    Jmo->temperAssign();
    
    this->addChild(Doug,2);
    this->addChild(Jmo,2);
     */
    //this->addChild(room,0);
    this->addChild(rightArrow, 4);
    
    char text[256];
    //sprintf(text,"STAM: %d",Doug->stamina);
    /*
    Lstamina = CCLabelTTF::create(text, "Thonburi", 16);
    Lstamina->setPosition(ccp(35.0 * sfx, 300.0 * sfy));
    
    sprintf(text, "SPD: %d",Doug->speed);
    Lspeed = CCLabelTTF::create(text, "Thonburi", 16);
    Lspeed->setPosition(ccp(40.0 * sfx, 285.0 * sfy));
    
    sprintf(text, "SKILL: %d",Doug->skill);
    Lskill = CCLabelTTF::create(text, "Thonburi", 16);
    Lskill->setPosition(ccp(35.0 * sfx,270.0 * sfy));
    
    sprintf(text, "FOCS: %d",Doug->focus);
    Lfocus = CCLabelTTF::create(text, "Thonburi", 16);
    Lfocus->setPosition(ccp(35.0 * sfx,255.0 * sfy));
    
    sprintf(text, "SOCL: %d",Doug->social);
    Lsocial = CCLabelTTF::create(text, "Thonburi", 16);
    Lsocial->setPosition(ccp(35.0 * sfx, 240.0 * sfy));
    
    sprintf(text,"CONF: %d", Doug->baseConfidence);
    LbaseConfidence = CCLabelTTF::create(text, "Thonburi", 16);
    LbaseConfidence->setPosition(ccp(35.0 * sfx, 225.0 * sfy));
    
    sprintf(text,"ROOM: %d", roomCount);
    Lroom = CCLabelTTF::create(text, "Thonburi", 16);
    Lroom->setPosition(ccp(35.0 * sfx, 210.0 * sfy));
    
    
    sprintf(text,"STAM: %d",Jmo->stamina);
    Lstamina2 = CCLabelTTF::create(text, "Thonburi", 16);
    Lstamina2->setPosition(ccp(105.0 * sfx, 300.0 * sfy));
    
    sprintf(text, "SPD: %d",Jmo->speed);
    Lspeed2 = CCLabelTTF::create(text, "Thonburi", 16);
    Lspeed2->setPosition(ccp(100.0 * sfx, 285.0 * sfy));
    
    sprintf(text, "SKILL: %d",Jmo->skill);
    Lskill2 = CCLabelTTF::create(text, "Thonburi", 16);
    Lskill2->setPosition(ccp(105.0 * sfx,270.0 * sfy));
    
    sprintf(text, "FOCS: %d",Jmo->focus);
    Lfocus2 = CCLabelTTF::create(text, "Thonburi", 16);
    Lfocus2->setPosition(ccp(105.0 * sfx ,255.0 * sfy));
    
    sprintf(text, "SOCL: %d",Jmo->social);
    Lsocial2 = CCLabelTTF::create(text, "Thonburi", 16);
    Lsocial2->setPosition(ccp(105.0 * sfx, 240.0 * sfy));
    
    sprintf(text,"CONF: %d", Jmo->baseConfidence);
    LbaseConfidence2 = CCLabelTTF::create(text, "Thonburi", 16);
    LbaseConfidence2->setPosition(ccp(105.0 * sfx, 225.0 * sfy));
    */
    /*CCSize screenSizePixels = CCDirector::sharedDirector()->getWinSizeInPixels();
     CCSize visableSize = CCDirector::sharedDirector()->getVisibleSize();
     */
    
    //room->boundingBox().setRect(room->getPositionX(), room->getPositionY(), room->getTexture()->getContentSizeInPixels().width, room->getTexture()->getContentSizeInPixels().height);
    
    /*
    sprintf(text,"ContentSize: %f x %f", room->getContentSize().width/2, room->getContentSize().height/2);
    Lcontent = CCLabelTTF::create(text, "Thonburi", 16);
    Lcontent->setPosition(ccp(125.0 * sfx, 140.0 * sfy));
    
    sprintf(text,"Size: %f x %f", room->boundingBox().size.width, room->boundingBox().size.height);
    Lsize = CCLabelTTF::create(text, "Thonburi", 16);
    Lsize->setPosition(ccp(135.0 * sfx, 120.0 * sfy));
    */
    /*sprintf(text,"VisableSize: %f x %f", visableSize.width, visableSize.height);
     CCLabelTTF *LscreenV = CCLabelTTF::create(text, "Thonburi", 16);
     LscreenV->setPosition(ccp(130.0, 100.0));
     */
    
    //********Adding the crew members to the layer**************
    for(int i = 0; i < room2crew.size();i++){
        this->addChild(room2crew[i], 2);
        // float b = room2crew[i]->g_x;
        CCPoint p = room2crew[i]->getPosition();
        cout << room2crew[i] << endl;
        room2crew[i]->isSwitchingRooms = false;
        room2crew[i]->setPositionX((float)room2crew[i]->getg_x());
    }
    //***********************************************************
    
    
    /*
    this->addChild(Lstamina, 4);
    this->addChild(Lspeed, 4);
    this->addChild(Lskill, 4);
    this->addChild(Lfocus, 4);
    this->addChild(Lsocial, 4);
    this->addChild(LbaseConfidence, 4);
    
    this->addChild(Lstamina2, 4);
    this->addChild(Lspeed2, 4);
    this->addChild(Lskill2, 4);
    this->addChild(Lfocus2, 4);
    this->addChild(Lsocial2, 4);
    this->addChild(LbaseConfidence2, 4);
    this->addChild(button, 1);
    this->addChild(Lroom,4);
    
    this->addChild(Lcontent,4);
    this->addChild(Lsize,4);
     */
    /*
     this->addChild(LscreenV,4);
     */
    
    //*****Enable Stuff*************
    this->setTouchEnabled(true);
    
    //******************************
    
    return true;
}

void GreenRoom::tempermentShift(vector<crew*>& cArray)
{
    vector<int> TSV(6);
    
    //for loop through all of the crew’s temperaments; adding up the stat bonuses/penalties
    //foreach(crew_member in room2crew){
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
        
        char text[256];
        sprintf(text,"STAM: %d",cArray[0]->stamina);
        //Lstamina->setString(text);
        
        sprintf(text, "SPD: %d",cArray[0]->speed);
        //Lspeed->setString(text);
        
        sprintf(text, "SKILL: %d",cArray[0]->skill);
        //Lskill->setString(text);
        
        sprintf(text, "FOCS: %d",cArray[0]->focus);
        //Lfocus->setString(text);
        
        sprintf(text, "SOCL: %d",cArray[0]->social);
        //Lsocial->setString(text);
        
        sprintf(text,"CONF: %d", cArray[0]->baseConfidence);
        //LbaseConfidence->setString(text);
        
        sprintf(text,"STAM: %d",cArray[1]->stamina);
        //Lstamina2->setString(text);
        
        sprintf(text, "SPD: %d",cArray[1]->speed);
        //Lspeed2->setString(text);
        
        sprintf(text, "SKILL: %d",cArray[1]->skill);
        //Lskill2->setString(text);
        
        sprintf(text, "FOCS: %d",cArray[1]->focus);
        //Lfocus2->setString(text);
        
        sprintf(text, "SOCL: %d",cArray[1]->social);
        //Lsocial2->setString(text);
        
        sprintf(text,"CONF: %d", cArray[1]->baseConfidence);
        //LbaseConfidence2->setString(text);
        
    }
    
}

void GreenRoom::registerWithTouchDispatcher()
{
    CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, 0, true);
}

void GreenRoom::ccTouchEnded( CCTouch *touch, CCEvent *event){
    CCPoint location = touch->getLocation();
    char text[256];
    
    // cocos2d::CCRect rect1 = cocos2d::CCRect(room->getPositionX(), room->getPositionY(), room->getTexture()->getContentSizeInPixels().width/2, room->getTexture()->getContentSizeInPixels().height/2);
    CCRect rect3 = CCRect(room->getPositionX(), room->getPositionY(),room->boundingBox().size.width/2,room->boundingBox().size.height/2);
    char text1[256];
    sprintf(text1,"ContentSize: %f x %f", room->boundingBox().size.width/2, room->boundingBox().size.height/2);
    //Lcontent->setString(text1);
    
    for(int k = 0;k < room2crew.size();k++)
    {
        cocos2d::CCRect rect2 = CCRect(room2crew[k]->getPositionX(), room2crew[k]->getPositionY(),room2crew[k]->boundingBox().size.width * 0.5, room2crew[k]->boundingBox().size.height * 0.5);
        
        
        if (rect3.intersectsRect(rect2))
        {
            if(room2crew[k]->onSet == false){
                roomCount++;
                room2crew[k]->onSet = true;
            }
            sprintf(text, "ROOM: %d", roomCount);
            //Lroom->setString(text);
        }
        
        if((rect3.intersectsRect(rect2)==false))
        {
            if(room2crew[k]->onSet == true)
            {
                roomCount--;
                room2crew[k]->onSet = false;
            }
            
            sprintf(text, "ROOM: %d", roomCount);
            //Lroom->setString(text);
        }
    }
    
    if((rightArrow->boundingBox().containsPoint(location)) && (target==NULL))
    {
        
        CCDirector::sharedDirector()->replaceScene(HelloWorld::scene());
    }

    
    if(roomCount > 1)
    {
        tempermentShift(room2crew);
    }
    
    target = NULL;
}

bool GreenRoom::ccTouchBegan(CCTouch *touch, CCEvent *event){
    CCPoint location = touch->getLocation();
    
    for(int i = 0; i <room2crew.size();i++){
        if(room2crew[i]->boundingBox().containsPoint(location))
        {
            target = room2crew[i];
        }
        /*else
         {
         target = NULL;
         }*/
    }
    
    return true;
    
}

void GreenRoom::ccTouchMoved(CCTouch* touch, CCEvent* event)
{
    CCPoint location = touch->getLocation();
    if(target != NULL){
        target->setPosition(location);
        target->setg_x(location.x);
        target->g_y = location.y;
    }
}

void GreenRoom::ccTouchesCancelled(CCSet* touches, CCEvent* event){
    
}

void GreenRoom::menuCloseCallback(CCObject* pSender)
{
    CCDirector::sharedDirector()->end();
    
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}

void GreenRoom::update(float dt)
{
    //test for crew leaving to the left room
    for(int k = 0;k < room2crew.size();k++)
    {
        if(room2crew[k]->getg_x() > 450){
            room2crew[k]->setg_x(20);
            room2crew[k]->setPositionX(room2crew[k]->getg_x());
            // float b = room2crew[k]->g_x;
            CCPoint p = room2crew[k]->getPosition();
            cout << "crew x " << p.x << endl;
            room2crew[k]->isSwitchingRooms = true;
            room1crew.push_back(room2crew[k]);
            removeChild(room2crew[k]);
            room2crew.erase(room2crew.begin()+k);
            
        }
    }
    
}
