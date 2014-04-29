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
#include "crewRoom.h"
#include "equipmentRoom.h"
#include <vector>

using namespace cocos2d;
using namespace cocos2d::extension;
using namespace std;


CCScene* Inventory::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // 'layer' is an autorelease object
    Inventory *layer = Inventory::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool Inventory::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !CCLayer::init() )
    {
        return false;
    }
    //create update method
    //scriptCount = scriptVector.size();
    //crewCount = crewList.size();
    
    /*for(int i = 0; i < scriptVector.size(); i++)
    {
      //  cout << "title # " << i << " = " << scriptVector[i]->title << endl;
    }
    
    int scount = 0;
    unsigned int uscount = 0;
    for( int i = 0; i < scriptVector.size();i++)
    {
        scount++;
        uscount++;
    }*/
    
    tableCount = 3;
    buttonInfo crewButtonInfo;
    crewButtonInfo.label = "Crew";
    crewButtonInfo.contentID = 1;
    buttonInfo scriptButtonInfo;
    scriptButtonInfo.label = "Script";
    scriptButtonInfo.contentID = 2;
    buttonInfo equipmentButtonInfo;
    equipmentButtonInfo.label = "Equipment";
    equipmentButtonInfo.contentID = 0;
    
    cellUpImage = "invt_blue_cell.png";
    cellDownImage = "invt_green_cell.png";
    
    //load UI variables
    currentState = 0;
    
 
    m_buttons = {equipmentButtonInfo, crewButtonInfo, scriptButtonInfo};
    
    //CCScene* wmap = this->scene();
    //previousScene = wmap;
    
   /* cout << "unsigned count = " << uscount << "signed count" << scount << endl;
    
    uscount = (unsigned int)scount;
    
    cout << "unsigned cast on int = " << uscount << endl;
    */
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
    
    /*CCArray *crewMenuItems  = new CCArray();
    for(int i = 0; i < crewList.size(); i++)
    {
        char tc_label[20];
        sprintf(tc_label, "crew_ID = %i", crewList[i]);
        CCMenuItemFont* tItem = CCMenuItemFont::create(tc_label, this, menu_selector(Inventory::viewCrew));
        tItem->setFontSize(35);
        tItem->setPosition(ccp(0,0));
        tItem->setFontName("Helvetica");
        tItem->setColor(ccc3(0,0,0));
        crewMenuItems->addObject(tItem);
    }*/
    
    /*crewListMenu = CCMenu::createWithArray(crewMenuItems);
    crewListMenu->alignItemsVertically();
    crewListMenu->setPosition(ccp((size.width/2) - (100 * sfy),(size.height/2)));
    this->addChild(crewListMenu, -1);*/
    
    
    
    /*CCArray *scriptMenuItems  = new CCArray();
    
    for(int i = 0; i < scriptVector.size(); i++)
    {
        char tc_label[60];
        sprintf(tc_label, "%s", scriptVector[i]->title.c_str());
        
        CCMenuItemFont* tItem = CCMenuItemFont::create(tc_label, this, menu_selector(Inventory::viewScripts));
        tItem->setFontSize(20);
        tItem->setPosition(ccp(0,0));
        tItem->setFontName("Helvetica");
        tItem->setColor(ccc3(0,0,0));
        scriptMenuItems->addObject(tItem);
    }*/
    
    /*script_List = CCMenu::createWithArray(scriptMenuItems);
    script_List->alignItemsVertically();
    script_List->setPosition(ccp((size.width/2) - (100 * sfy),(size.height/2)));
    this->addChild(script_List, -1);*/
    
    
    
    // position the label on the center of the screen
    //pLabel->setPosition( ccp(size.width / 2, size.height - 20) );
    
    // add the label as a child to this layer
    //this->addChild(pLabel, 1);
    
    // add "background image" splash screen"
    CCSprite* pSprite = CCSprite::create("inventory_room_bg.png");
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
   /*
    poFooter = CCSprite::create("PO_footer.png");
    poFooter->setAnchorPoint(ccp(0.5,0.5));
    poFooter->setScaleY(0.7 * sfy);
    poFooter->setScaleX(1.4 * sfx);
    poFooter->setPosition(ccp(size.width/2, (22 * sfy)));
    this->addChild(poFooter, 2);
    */
    
    /*********BUTTONS******************/


    // add the sprite as a child to this layer
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
    
    //_bgNode->setScaleX(rX);
    //_bgNode->setScaleY(rY);

    
    //create tableview
    itemTable = CCTableView::create(this, CCSizeMake(130 * sfx, 200 * sfy));
	itemTable->setDirection(kCCScrollViewDirectionVertical);
    itemTable->setAnchorPoint(ccp(0.5,0));
	itemTable->setPosition(ccp((size.width - (130 * sfx)),((-300 * sfy))));
	itemTable->setDelegate(this);
	itemTable->setVerticalFillOrder(kCCTableViewFillTopDown);
	this->addChild(itemTable);

    
    //for creating a table view
    tableView = CCTableView::create(this, CCSizeMake(190 * sfx, 300 * sfy));
	tableView->setDirection(kCCScrollViewDirectionVertical);
    tableView->setAnchorPoint(ccp(0.5,0));
	tableView->setPosition(ccp((size.width - (190 * sfx)),(size.height-(350 * sfy))));
	tableView->setDelegate(this);
	tableView->setVerticalFillOrder(kCCTableViewFillTopDown);
	this->addChild(tableView);
	tableView->reloadData();
        
    /*********************************************/
    
    
    
    this->setTouchEnabled(true);
    return true;
}

void Inventory::tempermentShift(vector<crew*>& cArray)
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

void Inventory::registerWithTouchDispatcher()
{
    CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, 0, true);
}

void Inventory::ccTouchEnded( CCTouch *touch, CCEvent *event){
    
 }

bool Inventory::ccTouchBegan(CCTouch *touch, CCEvent *event){
    return true;
}

void Inventory::ccTouchMoved(CCTouch* touch, CCEvent* event)
{
    
}

void Inventory::ccTouchesCancelled(CCSet* touches, CCEvent* event){
    
}

void Inventory::menuCloseCallback(CCObject* pSender)
{
    CCDirector::sharedDirector()->end();
    
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}

void Inventory::update(float dt)
{
    //CCSize size = CCDirector::sharedDirector()->getWinSize();
    //test for crew leaving to the left room
    //if(countDown >= 0){
       // countDown--;
    //}
    
       
}

/*void Inventory::makeScript(){
    //choose a number between 101 and 110
    srand( time(NULL));
	int roll = rand() % 9 + 101; //range 1 to 3
    cout << "roll = " << roll << endl;
    vector<int> writers = {roll};
    
    Script * newScript = new Script(getCrewFromDB(writers));
    //scriptVector.push_back(newScript);
    //Script::titleBuilder();
}*/

void Inventory::handleSwipe(CCObject* obj)
{
    /*CCSwipe * swipe = (CCSwipe*)obj;
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
        
    }*/
    
}


void Inventory::gestureBufferUp(){
    
    
    /*CCCallFunc* startNext=CCCallFunc::create( this,
     callfunc_selector(baseRoom::switchUp) );
     
     CCMoveBy *slide = CCMoveBy::create(0.2, ccp(0, -350 * sfy));
     
     CCSequence* act =CCSequence::create(slide, startNext, NULL);
     blueFade->runAction(act);
     */
    //switchUp();
}

void Inventory::gestureBufferDown(){
    
    

}

void Inventory::gestureBufferRight(){
    
    

}

void Inventory::gestureBufferLeft(){
    
    cout<< "swipe left" << endl;

   
}

void Inventory::scrollViewDidScroll (CCScrollView * view){
    
}

void Inventory::scrollViewDidZoom (CCScrollView * view){
    
}

void Inventory::tableCellTouched (CCTableView * table, CCTableViewCell * cell){
    CCLog ("cell touched at index:% i", cell-> getIdx ( ));
    //here we got id of a cell and we can make some functionality depending upon our needs like
    //if(cell->getIdx()==4)
    // {
    // change the scene or do whatever what your game demands
    // }
}

unsigned int Inventory::numberOfCellsInTableView (CCTableView * table ){
    /*unsigned int x = 7;
    if( menuSwitch == 1){
    x = scriptCount;
       //cout << "number of scripts = " << scriptCount << endl;
    }
    else if (menuSwitch == 2){
        x = crewCount;
    }
    else
    {
        x = 1;
    }
   // cout << "number of cells = " << x << endl;
     */
    return tableCount;
}

void Inventory::tableCellHighlight (CCTableView * table,CCTableViewCell * cell){
    CCTexture2D * aTexture = CCTextureCache :: sharedTextureCache () -> addImage (cellDownImage.c_str());
    CCSprite * pSprite = (CCSprite *) cell-> getChildByTag (4);
    pSprite-> setTexture (aTexture);
    cout << "button id = " << cell->getObjectID() << endl;
    

       /* if(cell->getObjectID() == e_script)
        {
            viewScripts();
        }
    */
    
        //switchTable(table, itemTable);
    
    
    
}

void Inventory::tableCellUnhighlight (CCTableView * table, CCTableViewCell * cell){
    CCTexture2D * aTexture = CCTextureCache :: sharedTextureCache () -> addImage (cellUpImage.c_str());
     CCSprite * pSprite = (CCSprite *) cell-> getChildByTag (4);
     pSprite->setTexture(aTexture);
    cout<< "cell contentID = " << cell->getObjectID() << endl;
    if(cell->getObjectID() == e_script)
    {
        viewScripts();
    }
    
    else if(cell->getObjectID() == e_crew)
    {
        viewCrew();
    }
    
    else if(cell->getObjectID() == e_equipment)
    {
        viewEquipment();
    }

}

CCSize Inventory::cellSizeForTable (CCTableView * table){
    
    return CCSizeMake(200 * sfx, 70 * sfy);;
}

CCTableViewCell * Inventory :: tableCellAtIndex (CCTableView * table, unsigned int idx)
{
    CCString* string;
    char tc_label[20];
    int contentID = 0;
                string = CCString::create(m_buttons[idx].label);
            contentID = m_buttons[idx].contentID;

          cout << "idk = " << idx << endl;

    /*if(currentState == states::e_inventory){
        char tc_label[20];
        sprintf(tc_label,"%i  %s", idx, scriptVector[idx]->title.c_str());
        string = CCString::create(m_buttons[idx].label);
        //string = CCString::create(tc_label);
        
        //cout << idx << "script name = " << string->getCString() << endl;
       //cout << "author1 = " << scriptVector[idx]->authorNames[0] << endl;
    }
    else{
        

    }*/

    CCTableViewCell *cell = table->dequeueCell();
    if (!cell) {
        cell = new CCTableViewCell();
        cell->autorelease();
        CCSprite *sprite = CCSprite::create(cellUpImage.c_str());
        sprite->setAnchorPoint(CCPointZero);
        sprite->setPosition(ccp(0, 0));
        sprite->setScaleX(sfx);
        sprite->setScaleY(sfy);
        sprite->setTag(4);
        cell->addChild(sprite);
        cell->setObjectID(contentID);
        CCLabelTTF *label = CCLabelTTF::create(string->getCString(), "Helvetica", 16.0);
        label->setPosition(ccp(sprite->boundingBox().size.width/2, sprite->boundingBox().size.height/2));
		label->setAnchorPoint(ccp(0.5, 0.5));
        //label->setPosition(CCPointZero);
		//label->setAnchorPoint(CCPointZero);
        label->setTag(123);
        cell->addChild(label);
    }
    else
    {
        CCLabelTTF *label = (CCLabelTTF*)cell->getChildByTag(123);
        label->setString(string->getCString());
    }
    cout << "cell # " << idx << "title = " << string->getCString() << endl;
    return cell;
    
    
}

void Inventory::goback()
{
    //check if level2 is true
    
    //if ture then switch table, title, and back ground
    
    //if not then to go to P.O.
        CCScene * wm = worldmap::scene();
    CCDirector::sharedDirector()->replaceScene(previousScene);


}

void Inventory::viewCrew()
{
    CCScene * sr = crewRoom::scene();
    CCDirector::sharedDirector()->replaceScene(sr);

}
void Inventory::viewScripts()
{

    CCScene * sr = scriptRoom::scene();
    CCDirector::sharedDirector()->replaceScene(sr);

    
}


void Inventory::viewEquipment()
{
    
    CCScene * sr = equipmentRoom::scene();
    CCDirector::sharedDirector()->replaceScene(sr);
}
void Inventory::switchTable(CCTableView* currentTable,CCTableView* newTable)
{
     CCSize size = CCDirector::sharedDirector()->getWinSize();
    switchData();
    //move current table out to the right and
    CCMoveTo * moveRight = CCMoveTo::create(.5, ccp(size.width, 0));
    currentTable->runAction(moveRight);
    
    //load newTable
    newTable->reloadData();
    
    //raise the new table into view
    CCMoveBy* moveUp = CCMoveBy::create(1.5, ccp(0,330));
    newTable->runAction(moveUp);
    
    
}

void Inventory::switchData()
{
    }


