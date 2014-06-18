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
#include "PreProductionLanding.h"
#include "chooseScript.h"


using namespace cocos2d;
using namespace cocos2d::extension;
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
    scriptCount = scriptVector.size();
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
    
    //CCScene* wmap = this->scene();
    //previousScene = wmap;
    
    cout << "unsigned count = " << uscount << "signed count" << scount << endl;
    
    uscount = (unsigned int)scount;
    
    cout << "unsigned cast on int = " << uscount << endl;
    
    this->schedule(schedule_selector(ProductionOffice::update));
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
        CCMenuItemFont* tItem = CCMenuItemFont::create(tc_label, this, menu_selector(ProductionOffice::viewCrew));
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
        
        CCMenuItemFont* tItem = CCMenuItemFont::create(tc_label, this, menu_selector(ProductionOffice::viewScripts));
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
    CCSprite* pSprite = CCSprite::create("po_room_bg.png");
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
    
    poFooter = CCSprite::create("PO_footer.png");
    poFooter->setAnchorPoint(ccp(0.5,0.5));
    poFooter->setScaleY(0.7 * sfy);
    poFooter->setScaleX(1.4 * sfx);
    poFooter->setPosition(ccp(size.width/2, (22 * sfy)));
    this->addChild(poFooter, 2);
    
    /*********BUTTONS******************/
    
    inventoryImage = CCMenuItemImage::create("Inventory_Button.png", "Inventory_Button.png", this, menu_selector(ProductionOffice::viewInventory));
    inventoryImage->setPosition(ccp(0,0));
    inventoryImage->setScaleX(0.7 * sfx);
    inventoryImage->setScaleY(0.7 * sfy);
    
    inventoryButton = CCMenu::create(inventoryImage, NULL);
    inventoryButton->setAnchorPoint(ccp(0.5,0.5));
    inventoryButton->setPosition(ccp((50 * sfx) , (size.height) - (27 * sfy)));
    this->addChild(inventoryButton, 3);
    
    continueImage = CCMenuItemImage::create("continue_button.png", "continue_button.png", this, menu_selector(ProductionOffice::continueProduction));
    continueImage->setPosition(ccp(0,0));
    continueImage->setScaleX(1 * sfx);
    continueImage->setScaleY(0.8 *sfy);
    
    continueButton = CCMenu::create(continueImage, NULL);
    continueButton->setAnchorPoint(ccp(0.5,0.5));
    continueButton->setPosition(ccp((size.width) - (50 * sfx) , (22 * sfy)));
    this->addChild(continueButton, 3);
    
    
    
    /*scriptsImage = CCMenuItemImage::create("script_button.png", "script_button.png", this, menu_selector(ProductionOffice::viewScripts));
    scriptsImage->setPosition(ccp(0,0));
    scriptsImage->setScaleX(0.8 * sfx);
    scriptsImage->setScaleY(0.8 *sfy);
    
    scriptsButton = CCMenu::create(scriptsImage, NULL);
    scriptsButton->setPosition(ccp((size.width/2) - (100 * sfx) , (size.height/2) + (120 * sfy)));
    this->addChild(scriptsButton, 1);
    
    
    crewImage = CCMenuItemImage::create("crew_button.png", "crew_button.png", this, menu_selector(ProductionOffice::viewCrew));
    crewImage->setPosition(ccp(0,0));
    crewImage->setScaleX(0.8 * sfx);
    crewImage->setScaleY(0.8 * sfy);
    
    crewButton = CCMenu::create(crewImage, NULL);
    crewButton->setPosition(ccp((size.width/2) - (200 * sfx) , (size.height/2) + (120 * sfy)));
    this->addChild(crewButton, 1);
     */

    // add the sprite as a child to this layer
    this->addChild(pSprite, 0);
    
    //Labels
    
    //******************BACK BUTTON*********************
    backImage = CCMenuItemImage::create("back_button.png", "back_button.png", this, menu_selector(ProductionOffice::goback));
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
    SwipeGesture->setTarget(this, callfuncO_selector(ProductionOffice::handleSwipe));
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

    

    
    //for creating a table view
    /*tableView = CCTableView::create(this, CCSizeMake(130 * sfx, 200 * sfy));
	tableView->setDirection(kCCScrollViewDirectionVertical);
	tableView->setPosition(ccp(size.width-(150 * sfx),(size.height/2-(120 * sfy))));
	tableView->setDelegate(this);
	tableView->setVerticalFillOrder(kCCTableViewFillTopDown);
	this->addChild(tableView);
	tableView->reloadData();*/
        
    /*********************************************/
    
    
    
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

/*void ProductionOffice::makeScript(){
    //choose a number between 101 and 110
    srand( time(NULL));
	int roll = rand() % 9 + 101; //range 1 to 3
    cout << "roll = " << roll << endl;
    vector<int> writers = {roll};
    
    Script * newScript = new Script(getCrewFromDB(writers));
    //scriptVector.push_back(newScript);
    //Script::titleBuilder();
}*/

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
    if(menuSwitch == 1){
    //crewListMenu->setZOrder(10);
        menuSwitch = 2;
        //tableView->reloadData();
    }
    else{
        //crewListMenu->setZOrder(-1);
        //crewPressed = false;
    }
}
void ProductionOffice::viewScripts()
{
    if(menuSwitch == 2){
        //script_List->setZOrder(10);
        menuSwitch = 1;
        //tableView->reloadData();
    }
    else{
        //script_List->setZOrder(-1);
        //scriptsPressed = false;
    }

}

void ProductionOffice::scrollViewDidScroll (CCScrollView * view){
    
}

void ProductionOffice::scrollViewDidZoom (CCScrollView * view){
    
}

void ProductionOffice::tableCellTouched (CCTableView * table, CCTableViewCell * cell){
    CCLog ("cell touched at index:% i", cell-> getIdx ( ));
    //here we got id of a cell and we can make some functionality depending upon our needs like
    //if(cell->getIdx()==4)
    // {
    // change the scene or do whatever what your game demands
    // }
}

unsigned int ProductionOffice::numberOfCellsInTableView (CCTableView * table ){
    unsigned int x = 7;
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
    return x;
}

void ProductionOffice::tableCellHighlight (CCTableView * table,CCTableViewCell * cell){
    CCTexture2D * aTexture = CCTextureCache :: sharedTextureCache () -> addImage ("pink_cell.png");
    CCSprite * pSprite = (CCSprite *) cell-> getChildByTag (4);
    pSprite-> setTexture (aTexture);
}

void ProductionOffice::tableCellUnhighlight (CCTableView * table, CCTableViewCell * cell){
    CCTexture2D * aTexture = CCTextureCache :: sharedTextureCache () -> addImage ("grey_cell.png");
     CCSprite * pSprite = (CCSprite *) cell-> getChildByTag (4);
     pSprite->setTexture(aTexture);
}

CCSize ProductionOffice::cellSizeForTable (CCTableView * table){
    
    return CCSizeMake(125 * sfx, 40 * sfy);;
}

CCTableViewCell * ProductionOffice :: tableCellAtIndex (CCTableView * table, unsigned int idx)
{
    CCString* string;
    cout << "idk = " << idx << endl;
    //try {
    //    string = new CCString::C;
   // }
    //catch (exception *  e)
    //{
      //  cout << e << endl;
    //}
    if(menuSwitch == 1){
        char tc_label[20];
        sprintf(tc_label,"%i  %s", idx, scriptVector[idx]->title.c_str());
    string = CCString::create(tc_label);
        
        //cout << idx << "script name = " << string->getCString() << endl;
       //cout << "author1 = " << scriptVector[idx]->authorNames[0] << endl;
    }
    else{
        char tc_label[20];
        sprintf(tc_label, "crew_ID = %i", crewList[idx]);
        std::string t = tc_label;
        string = string->create( t);

    }
    
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
        cout << "cell insides " << cell->
        CCLabelTTF *label = (CCLabelTTF*)cell->getChildByTag(123);
        label->setString(string->getCString());
    }*/
    cout << "cell # " << idx << "title = " << string->getCString() << endl;
    return cell;
    
    
}

void ProductionOffice::goback()
{
    
    CCScene * wm = worldmap::scene();
    CCDirector::sharedDirector()->replaceScene(previousScene);

}

void ProductionOffice::viewInventory()
{
    CCScene * wm = Inventory::scene();
    CCDirector::sharedDirector()->replaceScene(wm);
}
void ProductionOffice::startPreProduction()
{
    
}
void ProductionOffice::continueProduction()
{
    CCScene * wm = chooseScript::scene();
    CCDirector::sharedDirector()->replaceScene(wm);
}

