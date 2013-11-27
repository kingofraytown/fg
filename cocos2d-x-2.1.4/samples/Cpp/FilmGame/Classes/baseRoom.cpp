//
//  baseRoom.cpp
//  Test1
//
//  Created by Anthony Jones on 5/17/13.
//
//
#define TAG_SPRITE 0
#define TAG_IMAGE 1
#define TAG_LABEL 2

#include "baseRoom.h"
//#include "SimpleAudioEngine.h"
#include "sstream"
#include "global.h"
#include "unistd.h"
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include "tinyxml/tinyxml.h"
#include <cmath>


using namespace cocos2d;
using namespace std;

CCScene* baseRoom::scene(baseRoom* room)
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    
if(this == room)
{
    scene->removeAllChildrenWithCleanup(true);
}
    
    room->init();
    
        scene->addChild(room);
        
    
    
    
    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool baseRoom::init()
{
    //////////////////////////////
    // 1. super init first
    if (!CCLayer::init() )
    {
        return false;
    }
    
    loading = true;
    
    lastPoint.x = 0;
    lastPoint.y = 0;
    
    
    
    // ask director the window size
    //making the scaling factors
    CCSize size = CCDirector::sharedDirector()->getWinSize();
    sfx = size.width/480;
    sfy = size.height/320;

	//initalize render counter
    render = 0;
    
    //***************************************

    
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

    //*****Adding the BG ******************
    CCSprite* BGSprite;
    cout << "type = " << type << endl;

    if(type == "shooting")
    {
        BGSprite = CCSprite::create("room_indoors1.png");
    }
    
    if(type == "unloading")
    {
        BGSprite = CCSprite::create("room_indoors2.png");
    }
    
    if (type == "crafts") {
        BGSprite = CCSprite::create("room_indoors3.png");
    }
    
    if(type == "greenroom")
    {
        BGSprite = CCSprite::create("room_indoors4.png");
    }

	 // position the background sprite on the center of the screen
    BGSprite->setScaleY(0.35 * sfy);
    BGSprite->setScaleX(0.4 * sfx);
    BGSprite->setPosition( ccp(size.width/2, size.height/2) );
    // add the sprite as a child to this layer
    this->addChild(BGSprite, 0, TAG_SPRITE);
	/***********************************************/
    
	//Setting a switching rooms flag - Used to make sure a switch room function is not called twice
	isSwitching = false;

    //adding crew stats menu labels
    char Stats[200];
    //const char* ctype = type.c_str();
    sprintf(Stats,"STAM: ");

    //******testing label******
		MoveLabel = CCLabelTTF::create(Stats, "Thonburi", 30);
		MoveLabel->setPosition(ccp(size.width/2,size.height/2 + sfy * 40 ));
		MoveLabel->setScale(sfy);
		MoveLabel->setAnchorPoint(ccp(0,0.5));

	//**************************
    
	//Stamina Label
    Lstamina = CCLabelTTF::create(Stats, "Thonburi", 18);
    Lstamina->setAnchorPoint(ccp(0,0.5));
    Lstamina->setScale(sfy);
    Lstamina->setPosition(ccp(150.0 * sfy, 170.0 * sfy));

	//Speed Label
    sprintf(Stats,"SPD: ");
    
    Lspeed = CCLabelTTF::create(Stats, "Thonburi", 18);
    Lspeed->setAnchorPoint(ccp(0,0.5));
    Lspeed->setScale(sfy);
    Lspeed->setPosition(ccp(150.0 * sfy, 156.0 * sfy));
    
	//Confindence Label
    sprintf(Stats,"CONF: ");
    
    Lconfindence = CCLabelTTF::create(Stats, "Thonburi", 18);
    Lconfindence->setAnchorPoint(ccp(0,0.5));
    Lconfindence->setScale(sfy);
    Lconfindence->setPosition(ccp(150 * sfy, 142.0 * sfy));
    
	//Focus Label
    sprintf(Stats,"FOCS: ");
    
    Lfocus = CCLabelTTF::create(Stats, "Thonburi", 18);
    Lfocus->setAnchorPoint(ccp(0,0.5));
    Lfocus->setScale(sfy);
    Lfocus->setPosition(ccp(150.0 * sfy, 128.0 * sfy));
    
	//Social Label
    sprintf(Stats,"SOCL: ");
    
    Lsocial = CCLabelTTF::create(Stats, "Thonburi", 18);
    Lsocial->setAnchorPoint(ccp(0,0.5));
    Lsocial->setScale(sfy);
    Lsocial->setPosition(ccp(150.0 * sfy, 114.0 * sfy));
    
	//Skill Label
    sprintf(Stats,"SKILL: ");
    
    Lskill = CCLabelTTF::create(Stats, "Thonburi", 18);
    Lskill->setAnchorPoint(ccp(0,0.5));
    Lskill->setScale(sfy);
    Lskill->setPosition(ccp(150.0 * sfy, 100.0 * sfy));

	this->addChild(Lskill,0, TAG_LABEL);
    this->addChild(Lstamina, 0, TAG_LABEL);
    this->addChild(Lspeed, 0, TAG_LABEL);
    this->addChild(Lfocus, 0, TAG_LABEL);
    this->addChild(Lsocial,0, TAG_LABEL);
    this->addChild(Lconfindence, 0, TAG_LABEL);
    this->addChild(MoveLabel, 20, TAG_LABEL);
    crewIndex = 0;
    
	//****Setting up the menu bar and menu buttons*******
    CCMenuItemImage* menuButton = CCMenuItemImage::create("menu_icon.png", "menu_icon.png", this, menu_selector(baseRoom::MenuButton));
    menuButton->setPosition(ccp(0,0));
    menuButton->setAnchorPoint(ccp(1,0));
    menuButton->setScale(0.1 * sfy);
    menu_button = CCMenu::create(menuButton, NULL);
   
    
    menu_button->setPosition(ccp(size.width - 10,10));
    this->addChild(menu_button, 10 , TAG_SPRITE);
    
	//Crew button
    CCMenuItemImage* crewButton = CCMenuItemImage::create("crew_button.png", "crew_button_down.png", this, menu_selector(baseRoom::crewStats));
    crewButton->setScale(sfy);
    crewButton->setPosition(ccp(0, 0));
    
	//Save button
    CCMenuItemImage* saveButton = CCMenuItemImage::create("save_button_up.png", "save_button_down.png", this, menu_selector(baseRoom::saveGame));
    saveButton->setScale(sfy);
    saveButton->setPosition(ccp(size.width/4  , 0));
    
    //Load button
    CCMenuItemImage* loadButton = CCMenuItemImage::create("load_button_up.png", "load_button_down.png", this, menu_selector(baseRoom::loadGame));
    loadButton->setScale(sfy);
    loadButton->setPosition(ccp((size.width/4) + ((sfy) * 100), 0));

    //the menu bar BG
    menuBar = new CCSprite();
    menuBar->initWithSpriteFrameName("menuBar");
    menuBar->setScale(sfy);
    menuBar->setPosition(ccp(size.width/2, 20 * sfy));
    
    buttonPress = false;
    
    //menuBar->addChild(menu_bar);
    menuWidth = menuBar->boundingBox().size.width;
    menuHeight = menuBar->boundingBox().size.height;

    
    menu_bar = CCMenu::create(crewButton,saveButton, loadButton, NULL);
    menu_bar->setPosition(ccp((size.width/4) + (15 * sfy),(10 *sfy)));
    statsBG = new CCSprite();
    statsBG->initWithSpriteFrameName("menu_bg");
    statsBG->setPosition(ccp(size.width/2, size.height/2));
    statsBG->setScaleX(sfx);
    statsBG->setScaleY(sfy);
    
    
    
    statsBG->setScale(1.5 * sfy);
    this->addChild(menuBar,-1, TAG_IMAGE);
    this->addChild(menu_bar, -1, TAG_IMAGE);
    this->addChild(statsBG,-1, TAG_IMAGE);
    
    //***************init swipe gesture*****************
    //CCArray* gestArray = cocos2d::CCArray::create();
    SwipeGesture = CCSwipeGestureRecognizer::create();
    SwipeGesture->setTarget(this, callfuncO_selector(baseRoom::handleSwipe));
    SwipeGesture->setDirection(kSwipeGestureRecognizerDirectionDown | kSwipeGestureRecognizerDirectionUp);
    SwipeGesture->setCancelsTouchesInView(true);
    this->addChild(SwipeGesture);

    
    //******Set Arrow buttons in crew stats menu**********
    
    CCMenuItemImage* leftStats = CCMenuItemImage::create("littleArrow.png", "littleArrow.png", this, menu_selector(baseRoom::switchStatsLeft));
    leftStats->setRotation(0);
    leftStats->setScale(sfy);
    ArrowStateLeft = CCMenu::create(leftStats,NULL);
    ArrowStateLeft->setPosition(ccp(20 * sfy, 100 * sfy));
    
    CCMenuItemImage* rightStats = CCMenuItemImage::create("littleArrow.png", "littleArrow.png", this, menu_selector(baseRoom::switchStatsRight));
    rightStats->setRotation(180);
    rightStats->setScale(sfy);
    ArrowStateRight = CCMenu::create(rightStats, NULL);
    ArrowStateRight->setPosition(ccp(size.width - (20 * sfy), 100 * sfy));
    ArrowStateRight->setEnabled(false);
    ArrowStateLeft->setEnabled(false);
    
    profilePic = new CCSprite();
    profilePic->initWithSpriteFrameName("blue_c_profile");
    this->addChild(profilePic,-1, TAG_IMAGE);
   
    this->addChild(ArrowStateLeft, -1, TAG_IMAGE);
    this->addChild(ArrowStateRight, -1, TAG_IMAGE);
	//**************************************************

	//********Room test info labels*******************
    char text[200];
    const char* ctype = type.c_str();
    sprintf(text,"%s", dbP.c_str());
    
    RoomName = CCLabelTTF::create(text, "Thonburi", 12);
    RoomName->setPosition(ccp(130.0 * sfy, 250.0 * sfy));
    sprintf(text,"(0,0,0,0,0,0)");
    
    TSVlabel = CCLabelTTF::create(text, "Thonburi", 25);
    TSVlabel->setPosition(ccp(200 * sfy, 100 * sfy));
    
    timer = CCLabelTTF::create(ctype, "Thonburi", 40);
    timer->setPosition(ccp(200.0 * sfy, 200.0 * sfy));
   
    this->addChild(RoomName, 3, TAG_LABEL);
    this->addChild(timer, 3, TAG_LABEL);
    this->addChild(TSVlabel, 4, TAG_LABEL);

	//***************************************************
        
	//****Room transition images******
	
	//blue fade for switching to top room
    blueFade = CCSprite::create("blue_fade.png");
    blueFade->setAnchorPoint(ccp(0.5, .5));
    blueFade->setScaleY(sfy);
    blueFade->setScaleX(sfx);
    blueFade->setAnchorPoint(ccp(0.5,0));
    blueFade->setPosition(ccp(size.width/2, size.height));
    
	//green fade for switching to bottom room
    greenFade = CCSprite::create("green_fade.png");
    greenFade->setAnchorPoint(ccp(.5, .5));
    greenFade->setRotation(180);
    greenFade->setScaleY(sfy);
    greenFade->setScaleX(sfx);
    greenFade->setAnchorPoint(ccp(0.5, 0));
    greenFade->setPosition(ccp(size.width/2, 0));
    
    this->addChild(blueFade,15, TAG_IMAGE);
    this->addChild(greenFade, 15, TAG_IMAGE);
    inTransition = false;
	//**************************************

    menuUp = false;
    tempermentShift(CrewVectors.at(roomKey));
    //*****Enable Stuff*************
    this->setTouchEnabled(true);
    //******************************
    rConfig->printConfig();
    this->schedule(schedule_selector(baseRoom::update));
   
    return true;
}

void baseRoom::tempermentShift(vector<crew*>& cArray)
{
    vector<int> TSV(6);
    
    //for loop through all of the crew’s temperaments; adding up the stat bonuses/penalties
    //foreach(crew_member in rightCrewVector){
    for(int i = 0;i < cArray.size();i++)
    {
        //cArray[i]->temperAssign();
        for(int j = 0;j < 6;j++)
        {
            TSV[j] += cArray[i]->tempBonus[j];
        }
        
    }
    char text[256];
    //stam,skill,speed,focus,morale,confidence
    for(int k = 0;k < cArray.size();k++)
    {
        cArray[k]->chStamina(TSV[0]);
        cArray[k]->chSkill(TSV[1]);
        cArray[k]->chSpeed(TSV[2]);
        cArray[k]->chFocus(TSV[3]);
        cArray[k]->chMorale(TSV[4]);
        cArray[k]->chConfidence(TSV[5]);
        
        
        /*sprintf(text,"STAM: %d",cArray[0]->stamina);
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
        */
       
        sprintf(text,"(%d,%d,%d,%d,%d,%d)", TSV[0],TSV[1],TSV[2],TSV[3],TSV[4],TSV[5]);
        
        TSVlabel->setString(text);
    }
    
}
void baseRoom::setType(string t)
{
    cout << "before = " << type << endl;
    type = t;
    cout << this << endl;
    cout << "after = " << type << endl;
    
    
}

string baseRoom::getType()
{
    string t;
    t = type;
    return t;
}
void baseRoom::registerWithTouchDispatcher()
{
    CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, 0, true);
}

void baseRoom::ccTouchEnded( CCTouch *touch, CCEvent *event){
	//Get current touch position
    CCPoint location = touch->getLocation();

	//Update touch state label
    MoveLabel->setString("T_Ended");

    cout << "location x:" << location.x << " y:" << location.y << endl; 

	//Check if there is a target
    if(target != NULL){
	//Call function to determine if the target is flicked
    target->onRelease();
    
    if(target->isFlicked){
        thrownCrew.push_back(target);
    }
    }
    char text[256];
    
    cout << "menuUp = " << menuUp << endl;

    target = NULL;
    SwipeGesture->setCancelsTouchesInView(true);
}

bool baseRoom::ccTouchBegan(CCTouch *touch, CCEvent *event){
    CCPoint location = touch->getLocation();
    MoveLabel->setString("T_Began");
    
    if(menuUp == false){
    for(int i = 0; i <thisRoom.size();i++){
        if(thisRoom[i]->boundingBox().containsPoint(location))
        {
            target = thisRoom[i];
            target->onGrab(location);
            SwipeGesture->setCancelsTouchesInView(false);
        }
    
    }
    }

    
   
    
    return true;
    
}

void baseRoom::ccTouchMoved(CCTouch* touch, CCEvent* event)
{
    CCPoint location = touch->getLocation();
        MoveLabel->setString("T_Moved");
    if((target != NULL) &&(!menuUp)){
        SwipeGesture->setCancelsTouchesInView(false);
        cout << "target != NULL" << endl;
        if(target->isGrabbed)
        {
            cout << "target grab TRUUUUUE" << endl;
            //if((location.x == lastPoint.x) && (location.y == lastPoint.y))
            if(distanceBetweenPoint(location, lastPoint))
            {
                cout << "target didn't move" <<endl;
                target->onRelease();
                //target->tempLocation = location;
                if(target->isFlicked){
                    thrownCrew.push_back(target);
                }
            }
            target->setPosition(location);
            target->setg_x(location.x);
            target->setg_y(location.y);
            
            target->tempLocation = location;
        }
        
    }
  
    /*if((location.x == lastPoint.x) && (location.y == lastPoint.y)){
        cout << "stuck event" << endl;
        ccTouchEnded(touch, event);
        cout << "inner touch ended" << endl;
        
    }
     */
    lastPoint = touch->getLocation();
  }

void baseRoom::ccTouchesCancelled(CCSet* touches, CCEvent* event){
    
}

void baseRoom::menuCloseCallback(CCObject* pSender)
{
    CCDirector::sharedDirector()->end();
    
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}
//********************************
//assignCrewVectors - This function copies the global vectors of crew objects from the adjacent rooms to member variable vectors
//********************************
void baseRoom::assignCrewVectors(){
    
    if(upRoom){
    string up = upRoom->roomKey;
    //cout << up << endl;
    upCrewVector = CrewVectors.at(up);
    }
    if(downRoom){
    
    string down = downRoom->roomKey;
        //cout << down << endl;
    downCrewVector = CrewVectors.at(down);
        
    }
    if(rightRoom){
    string right = rightRoom->roomKey;
    rightCrewVector = CrewVectors.at(right);
    
    }
    
    if(leftRoom){
    string left = leftRoom->roomKey;
    leftCrewVector = CrewVectors.at(left);
    }
    //cout << roomKey << endl;
    thisRoom = CrewVectors.at(roomKey);

    
}
void baseRoom::update(float dt)
{
	//Get screen size
    CCSize size = CCDirector::sharedDirector()->getWinSize();

	//push crew objects that are in motion from being thrown
    for ( int j = 0; j < thrownCrew.size();j++)
    {
        thrownCrew[j]->vectorPush();
    }
    //*****************
    //Room boundry logic - Test crew objects location to determine wether they should move to the next room or bounce off a wall
    //*****************

	//left
    if(leftRoom != NULL){
        //test for crew leaving to the left room
        for(int k = 0;k < thisRoom.size();k++)
        {
            if(thisRoom[k]->getg_x() < 10 * sfy){
                thisRoom[k]->setg_x(size.width - (40 * sfy));
                thisRoom[k]->setPositionX(thisRoom[k]->getg_x());
                CCPoint p = thisRoom[k]->getPosition();
                cout << thisRoom[k] << endl;
                if(thisRoom[k]->isFlicked){
                    thisRoom[k]->isFlicked = false;
                }
                thisRoom[k]->isSwitchingRooms = true;
                CrewVectors.at(leftRoom->roomKey).push_back(thisRoom[k]);
                removeChild(thisRoom[k]);
                CrewVectors.at(roomKey).erase(CrewVectors.at(roomKey).begin() + k);
                thisRoom.erase(thisRoom.begin()+k);
                
                tempermentShift(CrewVectors.at(roomKey));
            
            }
        }
    }
    else{
        for(int k = 0;k < thisRoom.size();k++)
        {
            if(thisRoom[k]->getg_x() < 30 * sfy){
                thisRoom[k]->setg_x(30 * sfy);
                thisRoom[k]->setPositionX(thisRoom[k]->getg_x());
                if(thisRoom[k]->isFlicked){
                    thisRoom[k]->isFlicked = false;
                }

            }
        }

    }
    //right
    if(rightRoom != NULL){
	//test for crew leaving to the right room
    for(int k = 0;k < thisRoom.size();k++)
    {
        if(thisRoom[k]->getg_x() > (size.width - (30 * sfy))){
            thisRoom[k]->setg_x(20 * sfy);
            thisRoom[k]->setPositionX(thisRoom[k]->getg_x());
            CCPoint p = thisRoom[k]->getPosition();
            cout << thisRoom[k] << endl;
            if(thisRoom[k]->isFlicked){
                thisRoom[k]->isFlicked = false;
            }
            thisRoom[k]->isSwitchingRooms = true;
            CrewVectors.at(rightRoom->roomKey).push_back(thisRoom[k]);
            removeChild(thisRoom[k]);
            CrewVectors.at(roomKey).erase(CrewVectors.at(roomKey).begin() + k);
            thisRoom.erase(thisRoom.begin()+k);
            tempermentShift(CrewVectors.at(roomKey));
            
        }
    }
    }
    else{
        for(int k = 0;k < thisRoom.size();k++)
        {
            if(thisRoom[k]->getg_x() > (size.width - (30 * sfy))){
                thisRoom[k]->setg_x(size.width - (30 * sfy));
                thisRoom[k]->setPositionX(thisRoom[k]->getg_x());
                if(thisRoom[k]->isFlicked){
                    thisRoom[k]->isFlicked = false;
                }

            }
        }
        
    }
    //up
    if(upRoom != NULL){
        //test for crew leaving to the top room
        for(int k = 0;k < thisRoom.size();k++)
        {
            if(thisRoom[k]->getg_y() > (size.height - (15 * sfy))){
                thisRoom[k]->setg_y(30 * sfy);
                thisRoom[k]->setPositionY(thisRoom[k]->getg_y());
                CCPoint p = thisRoom[k]->getPosition();
                if(thisRoom[k]->isFlicked){
                    thisRoom[k]->isFlicked = false;
                }
                thisRoom[k]->isSwitchingRooms = true;
                CrewVectors.at(upRoom->roomKey).push_back(thisRoom[k]);
                removeChild(thisRoom[k]);
                CrewVectors.at(roomKey).erase(CrewVectors.at(roomKey).begin() + k);
                thisRoom.erase(thisRoom.begin()+k);
                tempermentShift(CrewVectors.at(roomKey));
                
            }
        }
    }
    else{
        for(int k = 0;k < thisRoom.size();k++)
        {
            if(thisRoom[k]->getg_y() > (size.height - (15 * sfy))){
                thisRoom[k]->setg_y(size.height - (30 * sfy));
                thisRoom[k]->setPositionY(thisRoom[k]->getg_y());
                if(thisRoom[k]->isFlicked){
                    thisRoom[k]->isFlicked = false;
                }

            }
        }
    }
	//down
    if(downRoom != NULL){
        //test for crew leaving to the bottom room
        for(int k = 0;k < thisRoom.size();k++)
        {
            if(thisRoom[k]->getg_y() < 15 * sfy){
                thisRoom[k]->setg_y(size.height - (30 * sfy));
                thisRoom[k]->setPositionY(thisRoom[k]->getg_y());
                CCPoint p = thisRoom[k]->getPosition();
                if(thisRoom[k]->isFlicked){
                    thisRoom[k]->isFlicked = false;
                }

                thisRoom[k]->isSwitchingRooms = true;
                CrewVectors.at(downRoom->roomKey).push_back(thisRoom[k]);
                removeChild(thisRoom[k]);
                CrewVectors.at(roomKey).erase(CrewVectors.at(roomKey).begin() + k);
                thisRoom.erase(thisRoom.begin()+k);
                tempermentShift(CrewVectors.at(roomKey));
                
            }
        }
    }
    else{
        for(int k = 0;k < thisRoom.size();k++)
        {
            if(thisRoom[k]->getg_y() < 15 * sfy){
                thisRoom[k]->setg_y(30 * sfy);
                thisRoom[k]->setPositionY(thisRoom[k]->getg_y());
                if(thisRoom[k]->isFlicked){
                    thisRoom[k]->isFlicked = false;
                }

            }
        }

    }
	//*******************
	// End of Room boundry logic
	//*******************

	//clean out thrownCrew vector of non moving objects
    int throwCount = thrownCrew.size();
    if(throwCount != 0){
        for ( int i = 0; i < throwCount; i++)
        {
            if(thrownCrew.size() == 0 ){
                break;
            }
            
            if(thrownCrew[i]->isFlicked == false)
            {
                thrownCrew.erase(thrownCrew.begin()+i);
            }
        }
    }
    
	//delaying the loading of crew objects
    if(loading == true){
    render++;
    }
    
    if(render == 2){
        loadOtherStuff();
        render = 0;
        loading = false;
       
    }
     
}

void baseRoom::loadOtherStuff()
{
    assignCrewVectors();
    //********Adding the crew members to the layer**************
    for(int i = 0; i < thisRoom.size();i++){
        
            this->addChild(thisRoom[i], 2, TAG_SPRITE);
        
        thisRoom[i]->isSwitchingRooms = false;
        thisRoom[i]->setAnchorPoint(ccp(0.5, 0.5));
        thisRoom[i]->setPositionX((float)thisRoom[i]->getg_x());
        thisRoom[i]->setPositionY((float)thisRoom[i]->getg_y());
        thisRoom[i]->setScale(sfy);
    }
    
    
    //***********************************************************

    
}

void baseRoom::switchUp()
{
    if((upRoom != NULL) && (isSwitching == false))
    {
        isSwitching = true;
        if(inTransition == false){
        this->removeAlmostEverything();
        CCDirector::sharedDirector()->replaceScene(upRoom->scene(upRoom));
        }
        //cout << "gesture retain count = " << SwipeGesture->retainCount() << endl;
        //this->removeChild(SwipeGesture, true);
        
    }


}

void baseRoom::switchDown()
{
    if((downRoom != NULL) && (isSwitching == false))
    {
        isSwitching = true;
        this->removeAlmostEverything();
        CCDirector::sharedDirector()->replaceScene(downRoom->scene(downRoom));
       
       
    }

}


void baseRoom::switchRight()
{
    if(rightRoom != NULL)
    {
         this->removeAlmostEverything();
        CCDirector::sharedDirector()->replaceScene(rightRoom->scene(rightRoom));
       // this->removeAllChildren();
    }
}

void baseRoom::switchLeft()
{
    if(leftRoom != NULL)
    {
        this->removeAlmostEverything();
        CCDirector::sharedDirector()->replaceScene(leftRoom->scene(leftRoom));
        //this->removeAllChildren();
    }
   
}

void baseRoom::switchStatsLeft()
{
    crewIndex--;
    if (crewIndex < 0) {
        crewIndex = thisRoom.size() -1;
    }
    
    loadStats(thisRoom[crewIndex]);   
}

void baseRoom::switchStatsRight()
{
    crewIndex++;
    if (crewIndex == thisRoom.size()) {
        crewIndex = 0;
    }
    
    loadStats(thisRoom[crewIndex]);
    
}

void baseRoom::crewStats()
{
    if(menuUp){
        if(!buttonPress){
            statsBG->setZOrder(14);
            Lskill->setZOrder(15);
            Lstamina->setZOrder(15);
            Lspeed->setZOrder(15);
            Lfocus->setZOrder(15);
            Lsocial->setZOrder(15);
            Lconfindence->setZOrder(15);
            buttonPress = true;
            if (thisRoom.size() != 0){
                ArrowStateLeft->setEnabled(true);
                ArrowStateRight->setEnabled(true);
                ArrowStateRight->setZOrder(15);
                ArrowStateLeft->setZOrder(15);

            
            loadStats(thisRoom[crewIndex]);
            }
        }
        else
        {
            statsBG->setZOrder(-1);
            Lskill->setZOrder(-1);
            Lstamina->setZOrder(-1);
            Lspeed->setZOrder(-1);
            Lfocus->setZOrder(-1);
            Lsocial->setZOrder(-1);
            Lconfindence->setZOrder(-1);
            buttonPress = false;
            ArrowStateRight->setEnabled(false);
            ArrowStateLeft->setEnabled(false);
            ArrowStateRight->setZOrder(-1);
            ArrowStateLeft->setZOrder(-1);
            profilePic->setScale(sfy);
            profilePic->setZOrder(-1);
            crewIndex =0;
        
        }
    }


}

void baseRoom::loadStats(crew *cMember)
{
    
    char pic[100];
    sprintf(pic,"%s_profile",cMember->image.c_str());
    cout << pic << endl;
    CCSpriteFrameCache* cache = CCSpriteFrameCache::sharedSpriteFrameCache();
    CCSpriteFrame* frame = cache->spriteFrameByName(pic);
    profilePic->setDisplayFrame(frame);
    profilePic->setOpacity(200);
    profilePic->setPosition(ccp(300 * sfy,150 * sfy));
    profilePic->setZOrder(14);
    
   
    
    char Stats[200];
    //const char* ctype = type.c_str();
    sprintf(Stats,"STAM : %d",cMember->getActiveStamina());
    Lstamina->setString(Stats);
    
    sprintf(Stats,"SPED : %d",cMember->getActiveSpeed());
    Lspeed->setString(Stats);
    
    sprintf(Stats,"SKILL : %d",cMember->getActiveSkill());
    Lskill->setString(Stats);
    
    sprintf(Stats,"FOCS : %d",cMember->getActiveFocus());
    Lfocus->setString(Stats);
    
    sprintf(Stats,"SOCL : %d",cMember->getActiveSocial());
    Lsocial->setString(Stats);
    
    sprintf(Stats,"CONF : %d",cMember->getActiveConfidence());
    Lconfindence->setString(Stats);
    
    
    
    
}
void baseRoom::gestureBufferDown(){
    if((downRoom != NULL) && (isSwitching == false))
    {

    CCCallFunc* startNext=CCCallFunc::create( this,
                                             callfunc_selector(baseRoom::switchDown) );
    
	CCMoveBy *slide = CCMoveBy::create(0.2, ccp(0, 350 * sfy));
    
	CCSequence* act =CCSequence::create(slide, startNext, NULL);
	greenFade->runAction(act);
    }
    //switchDown();
}

void baseRoom::gestureBufferUp(){
    if((upRoom != NULL) && (isSwitching == false))
    {

    CCCallFunc* startNext=CCCallFunc::create( this,
        callfunc_selector(baseRoom::switchUp) );

	CCMoveBy *slide = CCMoveBy::create(0.2, ccp(0, -350 * sfy));

	CCSequence* act =CCSequence::create(slide, startNext, NULL);
	blueFade->runAction(act);
    }
    //switchUp();
}
void baseRoom::handleSwipe(CCObject* obj)
{
    CCSwipe * swipe = (CCSwipe*)obj;
    if((target == NULL)&& (menuUp == false)){
    if(swipe->direction == kSwipeGestureRecognizerDirectionUp){

        cout << "gesture retain count = " << SwipeGesture->retainCount() << endl;
        //this->removeChild(SwipeGesture);
        gestureBufferDown();
    }
    
    if(swipe->direction == kSwipeGestureRecognizerDirectionDown){
        //swipe->release();
       
        cout << "gesture retain count = " << SwipeGesture->retainCount() << endl;
        gestureBufferUp();
        //this->removeChild(SwipeGesture);
       // switchDown();
    }
    }
}

void baseRoom::saveGame()
{
    //get write path
    string path = CCFileUtils::sharedFileUtils()->getWritablePath();
    
    //append file name
    path.append("saveGame.xml");
    cout << path << endl;
   
    //*********************************
    TiXmlDocument *doc = new TiXmlDocument();
    
    //declearation
    TiXmlDeclaration* decl = new TiXmlDeclaration("1.0", "", "");
    doc->LinkEndChild( decl );
    
    //root
    TiXmlElement* root = new TiXmlElement("crewmembers");
    root->SetAttribute("name", "crewmembers");
    doc->LinkEndChild( root);
    
    //loop through crew
    for(int i = 0; i < CrewVectors.at("room1crew").size();i++)
    {
        cout << i << endl;
        crew* tempCrew = CrewVectors.at("room1crew")[i];
        char intBuf[50];
        //make stats element
        TiXmlElement* crew = new TiXmlElement("crew");
        crew->SetAttribute("name", "crew");
        root->LinkEndChild(crew);
        
        //make stats element
        TiXmlElement* stats = new TiXmlElement("stats");
        stats->SetAttribute("name", "stats");
        crew->LinkEndChild(stats);
    
            //make stat nodes
        TiXmlElement* skill = new TiXmlElement("skill");
        stats->LinkEndChild(skill);
        //convert int to CString
        sprintf(intBuf, "%d", tempCrew->skill);
        skill->LinkEndChild(new TiXmlText(intBuf));
       
        TiXmlElement* speed = new TiXmlElement("speed");
        stats->LinkEndChild(speed);
        sprintf(intBuf, "%d", tempCrew->speed);
        speed->LinkEndChild(new TiXmlText(intBuf));
        
        TiXmlElement* morale = new TiXmlElement("morale");
        stats->LinkEndChild(morale);
        sprintf(intBuf, "%d", tempCrew->morale);
        morale->LinkEndChild(new TiXmlText(intBuf));
        
        TiXmlElement* focus = new TiXmlElement("focus");
        stats->LinkEndChild(focus);
        sprintf(intBuf, "%d", tempCrew->focus);
        focus->LinkEndChild(new TiXmlText(intBuf));
        
        TiXmlElement* baseConfidence = new TiXmlElement("baseConfidence");
        stats->LinkEndChild(baseConfidence);
        sprintf(intBuf, "%d", tempCrew->baseConfidence);
        baseConfidence->LinkEndChild(new TiXmlText(intBuf));
        
        TiXmlElement* social = new TiXmlElement("social");
        stats->LinkEndChild(social);
        sprintf(intBuf, "%d", tempCrew->social);
        social->LinkEndChild(new TiXmlText(intBuf));
        
        TiXmlElement* stamina = new TiXmlElement("stamina");
        stats->LinkEndChild(stamina);
        sprintf(intBuf, "%d", tempCrew->stamina);
        stamina->LinkEndChild(new TiXmlText(intBuf));

        TiXmlElement* prodSkill = new TiXmlElement("prodSkill");
        stats->LinkEndChild(prodSkill);
        //convert int to CString
        sprintf(intBuf, "%d", tempCrew->prodSkill);
        prodSkill->LinkEndChild(new TiXmlText(intBuf));
        
        TiXmlElement* prodSpeed = new TiXmlElement("prodSpeed");
        stats->LinkEndChild(prodSpeed);
        sprintf(intBuf, "%d", tempCrew->prodSpeed);
        prodSpeed->LinkEndChild(new TiXmlText(intBuf));
        
        TiXmlElement* prodMorale = new TiXmlElement("prodMorale");
        stats->LinkEndChild(prodMorale);
        sprintf(intBuf, "%d", tempCrew->prodMorale);
        prodMorale->LinkEndChild(new TiXmlText(intBuf));
        
        TiXmlElement* prodFocus = new TiXmlElement("prodFocus");
        stats->LinkEndChild(prodFocus);
        sprintf(intBuf, "%d", tempCrew->prodFocus);
        prodFocus->LinkEndChild(new TiXmlText(intBuf));
        
        TiXmlElement* prodConfidence = new TiXmlElement("prodConfidence");
        stats->LinkEndChild(prodConfidence);
        sprintf(intBuf, "%d", tempCrew->prodConfidence);
        prodConfidence->LinkEndChild(new TiXmlText(intBuf));
        
        TiXmlElement* prodSocial = new TiXmlElement("prodSocial");
        stats->LinkEndChild(prodSocial);
        sprintf(intBuf, "%d", tempCrew->prodSocial);
        prodSocial->LinkEndChild(new TiXmlText(intBuf));
        
        TiXmlElement* prodStamina = new TiXmlElement("prodStamina");
        stats->LinkEndChild(prodStamina);
        sprintf(intBuf, "%d", tempCrew->prodStamina);
        prodStamina->LinkEndChild(new TiXmlText(intBuf));
        //end of stats

        //crew id
        TiXmlElement* crewID = new TiXmlElement("crewID");
        crewID->SetAttribute("name", "crewID");
        crew->LinkEndChild(crewID);
        sprintf(intBuf, "%d", tempCrew->crewID);
        crewID->LinkEndChild( new TiXmlText(intBuf));
        
        //hours on set
        
        //days on set
        
        //image name
        
        //bool yesterday
        
        //bool onSet
        
        char floatBuf[16];
        //g_x
        TiXmlElement* gcoordX = new TiXmlElement("gcoordX");
        gcoordX->SetAttribute("name","gcoordX");
        crew->LinkEndChild(gcoordX);
        sprintf(floatBuf, "%f", tempCrew->getg_x());
        gcoordX->LinkEndChild( new TiXmlText(floatBuf));
        
        //g_y
        TiXmlElement* gcoordY = new TiXmlElement("gcoordY");
        gcoordY->SetAttribute("name","gcoordY");
        crew->LinkEndChild(gcoordY);
        sprintf(floatBuf, "%f", tempCrew->getg_y());
        gcoordY->LinkEndChild( new TiXmlText(floatBuf));
        
        //temperaments
        
            //make element
        TiXmlElement* temperaments = new TiXmlElement("temperaments");
        crew->LinkEndChild(temperaments);

        
            //loop through temperaments
            for(int k = 0; k < tempCrew->temperament.size(); k++){
                
                //make node for each
                TiXmlElement* temperament = new TiXmlElement("temperament");
                crew->LinkEndChild(temperament);
                sprintf(intBuf, "%d", tempCrew->temperament[k]);
                temperament->LinkEndChild( new TiXmlText(intBuf));
                
            }

            
    }
    doc->SaveFile(path.c_str());
    
    
    
}

void baseRoom::loadGame()
{
    //get write path
    string path = CCFileUtils::sharedFileUtils()->getWritablePath();
    
    //append file name
    path.append("saveGame.xml");
    cout << path << endl;
    
    TiXmlDocument doc(path.c_str());
    
    bool loadOkay = doc.LoadFile();
    
    if(loadOkay){
        
    /*this will just reposition the crew for right now*/

        TiXmlElement* pElem;
        TiXmlHandle hroot(0);
        TiXmlHandle hdoc(&doc);
        
        //hroot=TiXmlHandle(pElem);
        
        //get the number of active crew members
        
        //for loop by number of crew
        TiXmlElement* xCoord;
        TiXmlElement* yCoord;
        TiXmlElement* cID;
        TiXmlElement* tempElem;
        
        int cid;
        float gy, gx;
        pElem=hdoc.FirstChildElement().Element();
        hroot=TiXmlHandle(pElem);
        //int i = 0;
        pElem=hroot.FirstChild( "crew" ).FirstChild().Element();
        for( pElem=hroot.FirstChild( "crew" ).Element(); pElem; pElem=pElem->NextSiblingElement()){
            //tempElement
            tempElem = pElem;
            cout << pElem->Attribute("name") << endl;
            
            //pElem = pElem->FirstChildElement();
            //pElem = pElem->NextSiblingElement();
            //crew ID
        cID = pElem->FirstChild()->NextSiblingElement();
            //x and y coordinates
            //pElem = pElem->NextSiblingElement();
        xCoord = pElem->FirstChild()->NextSiblingElement()->NextSiblingElement();
            
            //pElem = pElem->NextSiblingElement();
        yCoord = pElem->FirstChild()->NextSiblingElement()->NextSiblingElement()->NextSiblingElement();
            // get the crew ID for matching
            //cID = pElem->NextSiblingElement();
            //const char* xv = xCoord->Value();
        gx = atof(xCoord->GetText());
        gy = atof(yCoord->GetText());
        cid = atoi(cID->GetText());
            
        cout << "gx:" << gx << " gy:" << gy<< " id:" << cid<< endl;
            
        vector<crew*> roomcrew = CrewVectors.at("room1crew");
            //loop throught room1crew vector to find matching crew object by crewId
            for(int i = 0; i < CrewVectors.at("room1crew").size();i++)
            {
                if(cid == roomcrew[i]->crewID){
                    roomcrew[i]->setPosition(ccp(gx,gy));
                }
            }
        //pElem = tempElem->NextSiblingElement();
            
                      
        }
        
        
    }
    else{
        cout << "load failed" << endl;
    }
    
    
}
void baseRoom::removeAlmostEverything()
{
    CCNode * aChild;
    while ((aChild = this->getChildByTag(TAG_LABEL)) != NULL)
    {
        removeChild(aChild, true);
    }
    
    while ((aChild = this->getChildByTag(TAG_IMAGE)) != NULL)
    {
        removeChild(aChild, true);
    }
    
    while ((aChild = this->getChildByTag(TAG_SPRITE)) != NULL)
    {
        removeChild(aChild, true);
    }


}

bool baseRoom::distanceBetweenPoint(CCPoint p1, CCPoint p2){
    float deltaX, deltaY;
    deltaX = p2.x - p1.x;
    deltaY = p2.y - p1.y;
    
    if((abs(deltaX) <= .80) && (abs(deltaY) <= .80))
    {
        return true;
    }
    else{
        return false;
    }
    

}

void baseRoom::MenuButton()
{
    if((menuUp == false) && (target== NULL)){
        menuBar->setZOrder(4);
        menu_bar->setZOrder(5);
        menuUp = true;
    }
    else{
        menuBar->setZOrder(-1);
        menu_bar->setZOrder(-1);

        if(buttonPress)
        {
            crewStats();
        }
    menuUp = false;
    }

    

}
void baseRoom::fadeUP()
{
    inTransition = true;
    CCMoveBy *slide = CCMoveBy::create(5, ccp(0, -400));
    slide->initWithDuration(5, ccp(0,-400));
    blueFade->runAction(slide);
    inTransition = false;
}
;


