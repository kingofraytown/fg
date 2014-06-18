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
#include "CCTableView.h"
#include "CustomTableViewCell.h"
#include "worldmap.h"
#include "Inventory.h"
#include "crewRoom.h"
#include "Script.h"
#include <vector>


using namespace cocos2d;
using namespace cocos2d::extension;
using namespace std;


CCScene* crewRoom::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // 'layer' is an autorelease object
    crewRoom *layer = crewRoom::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool crewRoom::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !CCLayer::init() )
    {
        return false;
    }
    //create update method
    
    //scriptCount = scriptVector.size();
    crewCount = crewList.size();
    
    for(int i = 0; i < scriptVector.size(); i++)
    {
        cout << "title # " << i << " = " << scriptVector[i]->title << endl;
    }
    
    int scount = 0;
    unsigned int uscount = 0;
    for( int i = 0; i < scriptVector.size();i++)
    {
        scount++;
        uscount++;
    }
      
    cout << "unsigned count = " << uscount << "signed count" << scount << endl;
    
    uscount = (unsigned int)scount;
    
    cout << "unsigned cast on int = " << uscount << endl;
    
    this->schedule(schedule_selector(crewRoom::update));
    enterGameReel = false;
    crewPressed = false;
    //scriptsPressed = false;
    menuSwitch = 1;
    
    // ask director the window size
    CCSize size = CCDirector::sharedDirector()->getWinSize();
    sfx = size.width/480;
    sfy = size.height/320;
    
    

    // load and cache the texture and sprite frames
    //CCFileUtils::sharedFileUtils()->setResour
    vector<string> Paths;
    Paths.push_back("Resources");
    CCFileUtils::sharedFileUtils()->setSearchPaths(Paths);
    cocos2d::CCSpriteFrameCache* cacher;
    cacher = CCSpriteFrameCache::sharedSpriteFrameCache();
    cacher->addSpriteFramesWithFile("testAtlas.plist");
    //make some crew members
    
       
    // add "background image" splash screen"
    CCSprite* pSprite = CCSprite::create("script_room_bg.png");
    pSprite->setAnchorPoint(ccp(0,0 ));
    pSprite->setScaleY(0.8 * sfy);
    pSprite->setScaleX(1 * sfx);
    
   // startImage = CCMenuItemImage::create("po_button.png", "po_button.png", this, );
    
    poHeader = CCSprite::create("PO_header.png");
    poHeader->setAnchorPoint(ccp(0.5,0.5));
    poHeader->setScaleY(0.7 * sfy);
    poHeader->setScaleX(1.4 * sfx);
    poHeader->setPosition(ccp(size.width/2, size.height - (27 * sfy)));
    this->addChild(poHeader, 2);
    
    lHeader = CCLabelTTF::create("Crew List", "Helvetica", 30);
    lHeader->setPosition(ccp(size.width/2, size.height - 30));
    lHeader->setAnchorPoint(ccp(0.5,0.5));
    
    this->addChild(lHeader,3);
   /*
    poFooter = CCSprite::create("PO_footer.png");
    poFooter->setAnchorPoint(ccp(0.5,0.5));
    poFooter->setScaleY(0.7 * sfy);
    poFooter->setScaleX(1.4 * sfx);
    poFooter->setPosition(ccp(size.width/2, (22 * sfy)));
    this->addChild(poFooter, 2);
    */
    
       this->addChild(pSprite, 0);
    
    //Labels
    
    //******************BACK BUTTON*********************
    backImage = CCMenuItemImage::create("back_button.png", "back_button.png", this, menu_selector(Inventory::goback));
    backImage->setPosition(ccp(0,0));
    backImage->setScaleX(0.8 * sfx);
    backImage->setScaleY(0.8 * sfy);
    
    backButton = CCMenu::create(backImage, NULL);
    backButton->setAnchorPoint(ccp(0.5,0.5));
    backButton->setPosition(ccp((22 * sfx) , (22 * sfy)));
    this->addChild(backButton, 3);

 
    
    
    
    
    //***************init swipe gesture*****************
    //CCArray* gestArray = cocos2d::CCArray::create();
    SwipeGesture = CCSwipeGestureRecognizer::create();
    SwipeGesture->setTarget(this, callfuncO_selector(Inventory::handleSwipe));
    SwipeGesture->setDirection(kSwipeGestureRecognizerDirectionDown | kSwipeGestureRecognizerDirectionUp | kSwipeGestureRecognizerDirectionLeft);
    SwipeGesture->setCancelsTouchesInView(true);
    this->addChild(SwipeGesture);
    
    //********************************************'
    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    
    _bgNode = CCNode::create();
    _bgNode->setPosition(ccp(winSize.width/2, winSize.height/2));
    this->addChild(_bgNode, -1);
    
    _bgSprite = CCSprite::create("menu_icon.png"); //use the image name that you used in
    //your project for background
        
        _bgNode->addChild(_bgSprite);
    
    //for scaling purposes
    float rX = winSize.width/_bgSprite->getContentSize().width;
    float rY = winSize.height/_bgSprite->getContentSize().height;
    

    infoView = CCSprite::create("infoSquare.png");
    infoView->setAnchorPoint(ccp(0.5, 0.5));
    infoView->setScaleX(sfx);
    infoView->setScaleY(sfy);
    infoView->setPosition(ccp((size.width/2) - (100 * sfx), (size.height/2) - (10 * sfy)));
    CCSize infoSize = infoView->boundingBox().size;
    
    sName = CCLabelTTF::create(theCrew[0]->m_name.c_str(), "Helvetica", 16);
    sName->setAnchorPoint(ccp(0.5,0.5));
    sName->setPosition(ccp((infoSize.width/2) - (0 * sfx) ,(infoSize.height/2) + (90 * sfy)));
    sName->setColor(ccc3(0,0,0));
    
       
    sRole = CCLabelTTF::create(theCrew[0]->role.c_str(), "Helvetica", 16);
    sRole->setPosition(ccp((infoSize.width/2) - (0 * sfx) ,(infoSize.height/2) + (70* sfy)));
    sRole->setColor(ccc3(0,0,0));

    //CCLabelTTF* sGenre2 = CCLabelTTF::create("Gernre 2", "Helvetica", 16);
    char dayRate[8];
    sprintf(dayRate, "$%i.00",theCrew[0]->dayRate);
    sDayRate = CCLabelTTF::create(dayRate, "Helvetica", 16);
    sDayRate->setPosition(ccp((infoSize.width/2) - (0 * sfx) ,(infoSize.height/2) + (50* sfy)));
    sDayRate->setColor(ccc3(0,0,0));
        
    
    infoView->addChild(sName, 10);
    infoView->addChild(sRole, 10);
    infoView->addChild(sDayRate, 10);
    //infoView->addChild(sPages, 10);
    this->addChild(infoView, 100);

    
    
    //for creating a table view
    tableView = CCTableView::create(this, CCSizeMake(130 * sfx, 300 * sfy));
	tableView->setDirection(kCCScrollViewDirectionVertical);
    tableView->setAnchorPoint(ccp(1,0));
	tableView->setPosition(ccp((size.width - (131 * sfx)),(size.height-(350 * sfy))));
	tableView->setDelegate(this);
	tableView->setVerticalFillOrder(kCCTableViewFillTopDown);
	this->addChild(tableView);
	tableView->reloadData();
        
    /*********************************************/
    
    
    
    this->setTouchEnabled(true);
    return true;
}

void crewRoom::tempermentShift(vector<crew*>& cArray)
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

void crewRoom::registerWithTouchDispatcher()
{
    CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, 0, true);
}

void crewRoom::ccTouchEnded( CCTouch *touch, CCEvent *event){
    
 }

bool crewRoom::ccTouchBegan(CCTouch *touch, CCEvent *event){
    return true;
}

void crewRoom::ccTouchMoved(CCTouch* touch, CCEvent* event)
{
    
}

void crewRoom::ccTouchesCancelled(CCSet* touches, CCEvent* event){
    
}

void crewRoom::menuCloseCallback(CCObject* pSender)
{
    CCDirector::sharedDirector()->end();
    
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}

void crewRoom::update(float dt)
{
    //CCSize size = CCDirector::sharedDirector()->getWinSize();
    //test for crew leaving to the left room
    //if(countDown >= 0){
       // countDown--;
    //}
    
       
}


void crewRoom::handleSwipe(CCObject* obj)
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


void crewRoom::gestureBufferUp(){
    
    
    /*CCCallFunc* startNext=CCCallFunc::create( this,
     callfunc_selector(baseRoom::switchUp) );
     
     CCMoveBy *slide = CCMoveBy::create(0.2, ccp(0, -350 * sfy));
     
     CCSequence* act =CCSequence::create(slide, startNext, NULL);
     blueFade->runAction(act);
     */
    //switchUp();
}

void crewRoom::gestureBufferDown(){
    
    

}

void crewRoom::gestureBufferRight(){
    
    

}

void crewRoom::gestureBufferLeft(){
    
    cout<< "swipe left" << endl;

   
}

void crewRoom::viewCrew()
{
    if(menuSwitch == 1){
    //crewListMenu->setZOrder(10);
        menuSwitch = 2;
        tableView->reloadData();
    }
    else{
        //crewListMenu->setZOrder(-1);
        //crewPressed = false;
    }
}
void crewRoom::viewScripts()
{
    if(menuSwitch == 2){
        //script_List->setZOrder(10);
        menuSwitch = 1;
        tableView->reloadData();
    }
    else{
        //script_List->setZOrder(-1);
        //scriptsPressed = false;
    }

}

void crewRoom::scrollViewDidScroll (CCScrollView * view){
    
}

void crewRoom::scrollViewDidZoom (CCScrollView * view){
    
}

void crewRoom::tableCellTouched (CCTableView * table, CCTableViewCell * cell){
    CCLog ("cell touched at index:% i", cell-> getIdx ( ));
    //here we got id of a cell and we can make some functionality depending upon our needs like
    //if(cell->getIdx()==4)
    // {
    // change the scene or do whatever what your game demands
    // }
}

unsigned int crewRoom::numberOfCellsInTableView (CCTableView * table ){
    unsigned int x = 7;
   
    x = crewCount;
    return crewCount;
}

void crewRoom::tableCellHighlight (CCTableView * table,CCTableViewCell * cell){
    CCTexture2D * aTexture = CCTextureCache :: sharedTextureCache () -> addImage ("pink_cell.png");
    CCSprite * pSprite = (CCSprite *) cell-> getChildByTag (4);
    pSprite-> setTexture (aTexture);
    char nameChar[30];
    int cellID = cell->getObjectID();
    sprintf(nameChar, "%s", theCrew[cellID]->m_name.c_str());
    //title
    sName->setString(nameChar);
    
    sRole->setString(theCrew[cellID]->role.c_str());
    
    //page
    char tDayRate[10];
    sprintf(tDayRate, "$%i.00", theCrew[cellID]->dayRate);
    sDayRate->setString(tDayRate);
    
    
}

void crewRoom::tableCellUnhighlight (CCTableView * table, CCTableViewCell * cell){
    CCTexture2D * aTexture = CCTextureCache :: sharedTextureCache () -> addImage ("grey_cell.png");
     CCSprite * pSprite = (CCSprite *) cell-> getChildByTag (4);
     pSprite->setTexture(aTexture);
}

CCSize crewRoom::cellSizeForTable (CCTableView * table){
    
    return CCSizeMake(120 * sfx, 40 * sfy);;
}

CCTableViewCell * crewRoom:: tableCellAtIndex (CCTableView * table, unsigned int idx)
{
    CCString* string;
    char tc_label[30];
    int contentID = 0;
        sprintf(tc_label,"%s", theCrew[idx]->m_name.c_str());
        //string = CCString::create(m_buttons[idx].label);
        string = CCString::create(tc_label);
        
        //cout << idx << "script name = " << string->getCString() << endl;
       //cout << "author1 = " << scriptVector[idx]->authorNames[0] << endl;
    
   
    CCTableViewCell *cell; //= table->dequeueCell();
    //if (!cell) {
        cell = new CustomTableViewCell();
        cell->autorelease();
        CCSprite *sprite = CCSprite::create("grey_cell.png");
        sprite->setAnchorPoint(CCPointZero);
        sprite->setPosition(ccp(0, 0));
        sprite->setScaleX(sfx);
        sprite->setScaleY(sfy);
        sprite->setTag(4);
        cell->addChild(sprite);
        cell->setObjectID(idx);
        CCLabelTTF *label = CCLabelTTF::create(string->getCString(), "Helvetica", 12.0);
        label->setPosition(ccp(sprite->boundingBox().size.width/2, sprite->boundingBox().size.height/2));
		label->setAnchorPoint(ccp(0.5, 0.5));
        //label->setPosition(CCPointZero);
		//label->setAnchorPoint(CCPointZero);
        label->setTag(123);
        cell->addChild(label);
    //}
    /*else
    {
        CCLabelTTF *label = (CCLabelTTF*)cell->getChildByTag(123);
        label->setString(string->getCString());
    }*/
    cout << "cell # " << idx << "title = " << string->getCString() << endl;
    return cell;
    
    
}

void crewRoom::goback()
{
    
    CCScene * wm = worldmap::scene();
    CCDirector::sharedDirector()->replaceScene(previousScene);

}


