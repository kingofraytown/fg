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
#include "scriptRoom.h"
#include "Script.h"
#include <vector>


using namespace cocos2d;
using namespace cocos2d::extension;
using namespace std;


CCScene* scriptRoom::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // 'layer' is an autorelease object
    scriptRoom *layer = scriptRoom::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool scriptRoom::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !CCLayer::init() )
    {
        return false;
    }
    //create update method
    
    scriptCount = scriptVector.size();
    //crewCount = crewList.size();
    
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
    
    this->schedule(schedule_selector(Inventory::update));
    enterGameReel = false;
    crewPressed = false;
    scriptsPressed = false;
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
    
    lHeader = CCLabelTTF::create("Script Vault", "Helvetica", 30);
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
    
    sTitle = CCLabelTTF::create(scriptVector[0]->title.c_str(), "Helvetica", 16);
    sTitle->setAnchorPoint(ccp(0.5,0.5));
    sTitle->setPosition(ccp((infoSize.width/2) - (0 * sfx) ,(infoSize.height/2) + (90 * sfy)));
    sTitle->setColor(ccc3(0,0,0));
    switch(scriptVector[0]->scriptType)
    {
        case 1:
            sType  = CCLabelTTF::create("Shortfilm", "Helvetica", 16);
            break;
            
        case 2:
            sType  = CCLabelTTF::create("Commercial", "Helvetica", 16);

            break;
            
        case 3:
            sType  = CCLabelTTF::create("Feature", "Helvetica", 16);

            break;
    }
    sType->setPosition(ccp((infoSize.width/2) - (0 * sfx) ,(infoSize.height/2) + (70 * sfy)));
    sType->setColor(ccc3(0,0,0));
    
    sGenre1 = CCLabelTTF::create(scriptVector[0]->title.c_str(), "Helvetica", 16);
    sGenre1->setPosition(ccp((infoSize.width/2) - (0 * sfx) ,(infoSize.height/2) + (50* sfy)));
    sGenre1->setColor(ccc3(0,0,0));

    //CCLabelTTF* sGenre2 = CCLabelTTF::create("Gernre 2", "Helvetica", 16);
    char pageCount[8];
    sprintf(pageCount, "%i",scriptVector[0]->pages);
    sPages = CCLabelTTF::create(pageCount, "Helvetica", 16);
    sPages->setPosition(ccp((infoSize.width/2) - (0 * sfx) ,(infoSize.height/2) + (30* sfy)));
    sPages->setColor(ccc3(0,0,0));
        
    
    infoView->addChild(sTitle, 10);
    infoView->addChild(sType, 10);
    infoView->addChild(sGenre1, 10);
    infoView->addChild(sPages, 10);
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

void scriptRoom::tempermentShift(vector<crew*>& cArray)
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

void scriptRoom::registerWithTouchDispatcher()
{
    CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, 0, true);
}

void scriptRoom::ccTouchEnded( CCTouch *touch, CCEvent *event){
    
 }

bool scriptRoom::ccTouchBegan(CCTouch *touch, CCEvent *event){
    return true;
}

void scriptRoom::ccTouchMoved(CCTouch* touch, CCEvent* event)
{
    
}

void scriptRoom::ccTouchesCancelled(CCSet* touches, CCEvent* event){
    
}

void scriptRoom::menuCloseCallback(CCObject* pSender)
{
    CCDirector::sharedDirector()->end();
    
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}

void scriptRoom::update(float dt)
{
    //CCSize size = CCDirector::sharedDirector()->getWinSize();
    //test for crew leaving to the left room
    //if(countDown >= 0){
       // countDown--;
    //}
    
       
}


void scriptRoom::handleSwipe(CCObject* obj)
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


void scriptRoom::gestureBufferUp(){
    
    
    /*CCCallFunc* startNext=CCCallFunc::create( this,
     callfunc_selector(baseRoom::switchUp) );
     
     CCMoveBy *slide = CCMoveBy::create(0.2, ccp(0, -350 * sfy));
     
     CCSequence* act =CCSequence::create(slide, startNext, NULL);
     blueFade->runAction(act);
     */
    //switchUp();
}

void scriptRoom::gestureBufferDown(){
    
    

}

void scriptRoom::gestureBufferRight(){
    
    

}

void scriptRoom::gestureBufferLeft(){
    
    cout<< "swipe left" << endl;

   
}

void scriptRoom::viewCrew()
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
void scriptRoom::viewScripts()
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

void scriptRoom::scrollViewDidScroll (CCScrollView * view){
    
}

void scriptRoom::scrollViewDidZoom (CCScrollView * view){
    
}

void scriptRoom::tableCellTouched (CCTableView * table, CCTableViewCell * cell){
    CCLog ("cell touched at index:% i", cell-> getIdx ( ));
    //here we got id of a cell and we can make some functionality depending upon our needs like
    //if(cell->getIdx()==4)
    // {
    // change the scene or do whatever what your game demands
    // }
}

unsigned int scriptRoom::numberOfCellsInTableView (CCTableView * table ){
    unsigned int x = 7;
   
    x = scriptCount;
    return scriptCount;
}

void scriptRoom::tableCellHighlight (CCTableView * table,CCTableViewCell * cell){
    CCTexture2D * aTexture = CCTextureCache :: sharedTextureCache () -> addImage ("pink_cell.png");
    CCSprite * pSprite = (CCSprite *) cell-> getChildByTag (4);
    pSprite-> setTexture (aTexture);
    char titleChar[30];
    int cellID = cell->getObjectID();
    sprintf(titleChar, "%s", scriptVector[cellID]->title.c_str());
    //title
    sTitle->setString(titleChar);
    
    //type
    switch(scriptVector[0]->scriptType)
    {
        case 1:
            sType->setString("Shortfilm");
            break;
            
        case 2:
            sType->setString("Commercial");
            
            break;
            
        case 3:
            sType->setString("Feature");
            
            break;
    }

    //genre1
    cout << "scriptgenre size = " << scriptVector[cellID]->scriptGenres.size() << endl;
    genre* g = scriptVector[cellID]->scriptGenres[0];
    
    int tg = static_cast<genre::GenresEnum>(g->m_genre);
    sGenre1->setString(genreArray[tg].c_str());
    
    //page
    char tPage[5];
    sprintf(tPage, "%i", scriptVector[cellID]->pages);
    sPages->setString(tPage);
    
    
}

void scriptRoom::tableCellUnhighlight (CCTableView * table, CCTableViewCell * cell){
    CCTexture2D * aTexture = CCTextureCache :: sharedTextureCache () -> addImage ("grey_cell.png");
     CCSprite * pSprite = (CCSprite *) cell-> getChildByTag (4);
     pSprite->setTexture(aTexture);
}

CCSize scriptRoom::cellSizeForTable (CCTableView * table){
    
    return CCSizeMake(120 * sfx, 40 * sfy);;
}

CCTableViewCell * scriptRoom:: tableCellAtIndex (CCTableView * table, unsigned int idx)
{
    CCString* string;
    char tc_label[30];
    int contentID = 0;
        sprintf(tc_label,"%s", scriptVector[idx]->title.c_str());
        //string = CCString::create(m_buttons[idx].label);
        string = CCString::create(tc_label);
        
        //cout << idx << "script name = " << string->getCString() << endl;
       //cout << "author1 = " << scriptVector[idx]->authorNames[0] << endl;
    
   
    CCTableViewCell *cell;// = table->dequeueCell();
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

void scriptRoom::goback()
{
    
    CCScene * wm = worldmap::scene();
    CCDirector::sharedDirector()->replaceScene(previousScene);

}


