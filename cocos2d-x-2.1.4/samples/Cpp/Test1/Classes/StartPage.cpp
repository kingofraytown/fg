#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"
#include "sstream"
#include "global.h"
#include "GreenRoom.h"
#include "StartPage.h"



using namespace cocos2d;
using namespace CocosDenshion;
using namespace std;


CCScene* StartPage::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // 'layer' is an autorelease object
    StartPage *layer = StartPage::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool StartPage::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !CCLayer::init() )
    {
        return false;
    }
    scheduleUpdate();
    
    //  if(crewMembers.size() == 0)
    //{
    //  initCrewMembers();
    //}
    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.
    
    // add a "close" icon to exit the progress. it's an autorelease object
    
    /*CCMenuItemImage *pCloseItem = CCMenuItemImage::create(
     "CloseNormal.png",
     "CloseSelected.png",
     this,
     menu_selector(StartPage::menuCloseCallback) );
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
    CCSize size = CCDirector::sharedDirector()->getWinSize();
    sfx = size.width/480;
    sfy = size.height/320;
    
    // position the label on the center of the screen
    //pLabel->setPosition( ccp(size.width / 2, size.height - 20) );
    
    // add the label as a child to this layer
    //this->addChild(pLabel, 1);
    
    // add "HelloWorld" splash screen"
    CCSprite* pSprite = CCSprite::create("startPage.fw.png");
    
    // position the sprite on the center of the screen
    pSprite->setPosition( ccp(size.width/2, size.height/2) );
    
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
    
    
    
    room = new CCSprite();
    button = new CCSprite();
       
    
    
    
    
    button->initWithFile("startButton.fw.png");
    room->initWithSpriteFrameName("grey_room");
    //Jmo->initWithSpriteFrameName("red_c");
    //Doug->initWithSpriteFrameName("blue_c");
    
    
       
    
    room->setScaleX(sfx);
    room->setScaleY(sfy);
    
    button->setScaleX(sfx);
    button->setScaleY(sfy);
    
    pSprite->setScaleX(sfx);
    pSprite->setScaleY(sfy);
    
  
    button->cocos2d::CCNode::setPosition(350.00 * sfx,20.0 * sfy);
    //Jmo->setAnchorPoint(ccp(0.5,0.0));
    
    
    
    
    
    room->setAnchorPoint(ccp(0.5,0.5));
    room->cocos2d::CCSprite::setPosition(ccp(300.0 * sfx, 180.0 * sfy));
    
    
    //room1crew.push_back(Doug);
    //room1crew.push_back(Jmo);
    
    
    
    for(int i = 0; i < room1crew.size();i++){
        this->addChild(room1crew[i], 2);
        float b = room1crew[i]->getg_x();
        cout << "crew g_x " << b << endl;
        room1crew[i]->isSwitchingRooms = false;
        room1crew[i]->setPositionX(room1crew[i]->getg_x());
    }
    
    //this->addChild(Doug,2);
    this->addChild(button,1);
    //this->addChild(room,0);
   
       
    room->boundingBox().setRect(room->getPositionX(), room->getPositionY(), room->getTexture()->getContentSizeInPixels().width, room->getTexture()->getContentSizeInPixels().height);
    
    /*
     sprintf(text,"ContentSize: %f x %f", room->getContentSize().width/2, room->getContentSize().height/2);
     Lcontent = CCLabelTTF::create(text, "Thonburi", 16);
     Lcontent->setPosition(ccp(125.0 * sfx, 140.0 * sfy));
     
     sprintf(text,"Size: %f x %f", room->boundingBox().size.width, room->boundingBox().size.height);
     Lsize = CCLabelTTF::create(text, "Thonburi", 16);
     Lsize->setPosition(ccp(135.0 * sfx, 120.0 * sfy));*/
    
    /*sprintf(text,"VisableSize: %f x %f", visableSize.width, visableSize.height);
     CCLabelTTF *LscreenV = CCLabelTTF::create(text, "Thonburi", 16);
     LscreenV->setPosition(ccp(130.0, 100.0));
     */
    
        
    
    this->setTouchEnabled(true);
    return true;
}

void StartPage::tempermentShift(vector<crew*>& cArray)
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

void StartPage::registerWithTouchDispatcher()
{
    CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, 0, true);
}

void StartPage::ccTouchEnded( CCTouch *touch, CCEvent *event){
    CCPoint location = touch->getLocation();
    char text[256];
    
    // cocos2d::CCRect rect1 = cocos2d::CCRect(room->getPositionX(), room->getPositionY(), room->getTexture()->getContentSizeInPixels().width/2, room->getTexture()->getContentSizeInPixels().height/2);
    CCRect rect3 = CCRect(room->getPositionX(), room->getPositionY(),room->boundingBox().size.width/2,room->boundingBox().size.height/2);
    char text1[256];
    sprintf(text1,"ContentSize: %f x %f", room->boundingBox().size.width/2, room->boundingBox().size.height/2);
    //Lcontent->setString(text1);
    
    
    if(button->boundingBox().containsPoint(location))
    {
        initCrewMembers();
        rConfig->printConfig();
        baseRoom* firstRoom;
        cout << "firstroom = " << firstRoom << endl;
        
        for(int i = 0; i < rConfig->rooms.size();i++)
        {
            cout << "**** startroom types******" << endl;
            cout << "[" << i  << "] = "<< rConfig->rooms[i]->getType() << endl;
            if (rConfig->rooms[i]->getType() == "unloading")
            {
                firstRoom = rConfig->rooms[i];
            }
        }
        cout << "firstroom = " << firstRoom << endl;
        CCDirector::sharedDirector()->replaceScene(firstRoom->scene(firstRoom));
        
    }
       
       target = NULL;
}

bool StartPage::ccTouchBegan(CCTouch *touch, CCEvent *event){
    CCPoint location = touch->getLocation();
    
    for(int i = 0; i <room1crew.size();i++){
        if(room1crew[i]->boundingBox().containsPoint(location))
        {
            target = room1crew[i];
        }
        /*else
         {
         target = NULL;
         }*/
    }
    
    return true;
    
}

void StartPage::ccTouchMoved(CCTouch* touch, CCEvent* event)
{
    CCPoint location = touch->getLocation();
    if(target != NULL){
        target->setPosition(location);
        target->setg_x(location.x);
        target->g_y =location.y;
    }
}

void StartPage::ccTouchesCancelled(CCSet* touches, CCEvent* event){
    
}

void StartPage::menuCloseCallback(CCObject* pSender)
{
    CCDirector::sharedDirector()->end();
    
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}

void StartPage::update(float dt)
{
    //test for crew leaving to the left room
    for(int k = 0;k < room1crew.size();k++)
    {
        if(room1crew[k]->getg_x() < 10){
            room1crew[k]->setg_x(440);
            room1crew[k]->setPositionX(room1crew[k]->getg_x());
            CCPoint p = room1crew[k]->getPosition();
            //float b = room1crew[k]->g_x;
            cout << room1crew[k] << endl;
            room1crew[k]->isSwitchingRooms = true;
            room2crew.push_back(room1crew[k]);
            //room2crew[k]->setPositionX(room2crew)
            removeChild(room1crew[k]);
            room1crew.erase(room1crew.begin()+k);
            
        }
    }
    
}
