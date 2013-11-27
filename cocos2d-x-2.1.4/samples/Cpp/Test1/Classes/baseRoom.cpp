//
//  baseRoom.cpp
//  Test1
//
//  Created by Anthony Jones on 5/17/13.
//
//

#include "baseRoom.h"
#include "SimpleAudioEngine.h"
#include "sstream"
#include "global.h"
#include "unistd.h"
#include <stdlib.h>
#include <iostream>
#include <fstream>


using namespace cocos2d;
using namespace CocosDenshion;
using namespace std;


CCScene* baseRoom::scene(baseRoom* room)
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // 'layer' is an autorelease object
    //baseRoom *layer = baseRoom::create();
    
    // add layer as a child to scene
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
    
    //scheduleUpdate();
    //schedule(schedule_selector(loadOtherStuff(1.0)), 1.0, 1, 2.0);
    loading = true;
    
    
    
    // ask director the window size
    //making the scaling factors
    CCSize size = CCDirector::sharedDirector()->getWinSize();
    sfx = size.width/480;
    sfy = size.height/320;
    
    
    
    roomCount = 0;
    
    
    // position the label on the center of the screen
    //pLabel->setPosition( ccp(size.width / 2, size.height - 20) );
    
    // add the label as a child to this layer
    //this->addChild(pLabel, 1);
    
    
    
    render =0;
    
    //*****Adding the BG ******************
    // add "HelloWorld" splash screen"
    CCSprite* pSprite = CCSprite::create("cocos2dmix.png");
    
    // position the sprite on the center of the screen
    pSprite->setPosition( ccp(size.width/2, size.height/2) );
    
    // add the sprite as a child to this layer
    this->addChild(pSprite, 0);
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
    cout << "type = " << this << endl;
    //type = "something";
    
    //make some crew members
    
    
    //adding menu stuff
    char Stats[200];
    //const char* ctype = type.c_str();
    sprintf(Stats,"STAM: ");
    
    Lstamina = CCLabelTTF::create(Stats, "Thonburi", 18);
    Lstamina->setAnchorPoint(ccp(0,0.5));
    Lstamina->setScale(sfy);
    Lstamina->setPosition(ccp(150.0 * sfy, 170.0 * sfy));

    sprintf(Stats,"SPD: ");
    
    Lspeed = CCLabelTTF::create(Stats, "Thonburi", 18);
    Lspeed->setAnchorPoint(ccp(0,0.5));
    Lspeed->setScale(sfy);
    Lspeed->setPosition(ccp(150.0 * sfy, 156.0 * sfy));
    
    sprintf(Stats,"CONF: ");
    
    Lconfindence = CCLabelTTF::create(Stats, "Thonburi", 18);
    Lconfindence->setAnchorPoint(ccp(0,0.5));
    Lconfindence->setScale(sfy);
    Lconfindence->setPosition(ccp(150 * sfy, 142.0 * sfy));
    
    sprintf(Stats,"FOCS: ");
    
    Lfocus = CCLabelTTF::create(Stats, "Thonburi", 18);
    Lfocus->setAnchorPoint(ccp(0,0.5));
    Lfocus->setScale(sfy);
    Lfocus->setPosition(ccp(150.0 * sfy, 128.0 * sfy));
    
    sprintf(Stats,"SOCL: ");
    
    Lsocial = CCLabelTTF::create(Stats, "Thonburi", 18);
    Lsocial->setAnchorPoint(ccp(0,0.5));
    Lsocial->setScale(sfy);
    Lsocial->setPosition(ccp(150.0 * sfy, 114.0 * sfy));
    
    sprintf(Stats,"SKILL: ");
    
    Lskill = CCLabelTTF::create(Stats, "Thonburi", 18);
    Lskill->setAnchorPoint(ccp(0,0.5));
    Lskill->setScale(sfy);
    Lskill->setPosition(ccp(150.0 * sfy, 100.0 * sfy));
    crewIndex = 0;
    CCMenuItemImage* crewButton = CCMenuItemImage::create("crew_button.png", "crew_button_down.png", this, menu_selector(baseRoom::crewStats));
    menu_bar = CCMenu::create(crewButton, NULL);
    //crewButton->setAnchorPoint(ccp(0.5,0.5));
    //crewButton->setPosition(ccp(0, -10));
    
    menu_bar->setPosition(ccp((size.width/2) , 30 * sfy));
    
    menuBar = new CCSprite();
    //menuBar->setAnchorPoint(ccp(0.,0));
    menuBar->initWithSpriteFrameName("menuBar");
    //menuBar->setPosition(ccp(size.width/2,-7));
    menuBar->setScale(sfy);
    menuBar->setPosition(ccp(size.width/2, -10 * sfy));
   
    buttonPress = false;
    menuBar->addChild(menu_bar);
    menuWidth = menuBar->boundingBox().size.width;
    menuHeight = menuBar->boundingBox().size.height;
    //crewButton->setPosition(ccp(menuWidth/2 - 100 ,menuHeight/2 -5));
    
    statsBG = new CCSprite();
    statsBG->initWithSpriteFrameName("menu_bg");
    statsBG->setPosition(ccp(size.width/2, size.height/2));
    statsBG->setScaleX(sfx);
    statsBG->setScaleY(sfy);
    
    this->addChild(Lskill,0);
    this->addChild(Lstamina, 0);
    this->addChild(Lspeed, 0);
    this->addChild(Lfocus, 0);
    this->addChild(Lsocial,0);
    this->addChild(Lconfindence, 0);
    statsBG->setScale(1.5);
    this->addChild(menuBar,4);
    this->addChild(statsBG,-1);
    //*******Scaling ccsprites and adding the children to the layer
    
    //******Set Arrow buttons**********
    
    
    CCMenuItemImage* rightArrow1 = CCMenuItemImage::create("arrow.png", "arrow_down.png", this, menu_selector(baseRoom::switchRight));
    rightArrow1->setRotation(90);
    rightArrow1->setScale(sfy);
    ArrowRight = CCMenu::create(rightArrow1, NULL);
    ArrowRight->setPosition(ccp(size.width - (10 * sfy),size.height/2));
    
    CCMenuItemImage* leftArrow1 = CCMenuItemImage::create("arrow.png", "arrow_down.png", this, menu_selector(baseRoom::switchLeft));
    leftArrow1->setRotation(-90);
    leftArrow1->setScale(sfy);
    ArrowLeft = CCMenu::create(leftArrow1, NULL);
    ArrowLeft->setPosition(ccp((10 * sfy),size.height/2));

    CCMenuItemImage* upArrow1 = CCMenuItemImage::create("arrow.png", "arrow_down.png", this, menu_selector(baseRoom::switchUp));
    upArrow1->setRotation(0);
    upArrow1->setScale(sfy);
    ArrowUp = CCMenu::create(upArrow1, NULL);
    ArrowUp->setPosition(ccp(size.width/2,size.height - (10 * sfy)));
    

    
    CCMenuItemImage* downArrow1 = CCMenuItemImage::create("arrow.png", "arrow_down.png", this, menu_selector(baseRoom::switchDown));
    downArrow1->setRotation(180);
    downArrow1->setScale(sfy);
    ArrowDown = CCMenu::create(downArrow1, NULL);
    ArrowDown->setPosition(ccp(size.width/2,(10 * sfy)));
    
    
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
    this->addChild(profilePic,-1);
    this->addChild(ArrowRight, 7);
    this->addChild(ArrowLeft, 7);
    this->addChild(ArrowDown, 7);
    this->addChild(ArrowUp, 7);
    this->addChild(ArrowStateLeft, -1);
    this->addChild(ArrowStateRight, -1);
    //********Set Arrows******************************
    /*rightArrow = new CCSprite();
    leftArrow = new CCSprite();
    downArrow = new CCSprite();
    upArrow = new CCSprite();
    
    
    rightArrow->initWithSpriteFrameName("arrow");
    //rightArrow->setScaleY(0.5);
    rightArrow->setPosition(ccp(size.width - 10,size.height/2));
    rightArrow->setRotation(90);
   
    
      
    leftArrow->initWithSpriteFrameName("arrow");
    //leftArrow->setScaleY(0.5);
    leftArrow->setPosition(ccp(10,size.height/2));
    leftArrow->setRotation(-90);
       
    upArrow->initWithSpriteFrameName("arrow");
    //upArrow->setScaleY(0.5);
    upArrow->setPosition(ccp(size.width/2,size.height - 10));
    upArrow->setRotation(0);
       
    downArrow->initWithSpriteFrameName("arrow");
    //downArrow->setScaleY(0.5);
    downArrow->setPosition(ccp(size.width/2,10));
    downArrow->setRotation(180);*/
       //*************************************************
    
    
       
    pSprite->setScaleX(sfx);
    pSprite->setScaleY(sfy);
    
   
    //Jmo->setAnchorPoint(ccp(0.5,0.0));
    //Jmo->cocos2d::CCNode::setPosition(ccp(70.0 * sfx, 50.0 * sfy));
    //Doug->setAnchorPoint(ccp(0.5, 0.0));
    //Doug->cocos2d::CCNode::setPosition(ccp(40.0 * sfx, 50.0 * sfy));
    
    
       //this->addChild(room,0);
    //this->addChild(rightArrow, 7);
    //this->addChild(leftArrow, 7);
    //this->addChild(upArrow, 7);
    //this->addChild(downArrow, 7);
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
   
    this->addChild(RoomName, 3);
    this->addChild(timer, 3);
    this->addChild(TSVlabel, 4);
        
    //RoomName->setString(type);
     
    
    //********Adding the crew members to the layer**************
    //right
    /*for(int i = 0; i < thisRoom.size();i++){
        this->addChild(thisRoom[i], 2);
        // float b = rightCrewVector[i]->g_x;
        CCPoint p = thisRoom[i]->getPosition();
        cout << thisRoom[i] << endl;
        thisRoom[i]->isSwitchingRooms = false;
        thisRoom[i]->setPositionX((float)thisRoom[i]->getg_x());
        thisRoom[i]->setPositionY((float)thisRoom[i]->getg_y());
    }
   */
    
    //***********************************************************
    
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
    CCPoint location = touch->getLocation();
    cout << "location x:" << location.x << " y:" << location.y << endl;

    char text[256];
    
    cout << "menuUp = " << menuUp << endl;
    if(!buttonPress){
    if(!menuUp){
    
    
   
        
        if (menuBar->boundingBox().containsPoint(location)) {
            if(menuUp == false){
                menuBar->setPositionY(20);
                //crewButton->setPositionY(20);
                ArrowDown->setEnabled(false);
                ArrowDown->setZOrder(-1);
                menuUp = true;
            }
            
        }
    }
    else
    {
                
        if (menuBar->boundingBox().containsPoint(location)) {
            
            
                menuBar->setPositionY(-10);
                
                //crewButton->setPositionY(-10);
                
            
                ArrowDown->setEnabled(true);
                ArrowDown->setZOrder(7);
                menuUp = false;
            
            
            
        }

    }
    }
    
    target = NULL;
}

bool baseRoom::ccTouchBegan(CCTouch *touch, CCEvent *event){
    CCPoint location = touch->getLocation();
    
    if(menuUp == false){
    for(int i = 0; i <thisRoom.size();i++){
        if(thisRoom[i]->boundingBox().containsPoint(location))
        {
            target = thisRoom[i];
        }
        /*else
         {
         target = NULL;
         }*/
    }
    }

    
   
    
    return true;
    
}

void baseRoom::ccTouchMoved(CCTouch* touch, CCEvent* event)
{
    CCPoint location = touch->getLocation();
    if((target != NULL) &&(!menuUp)){
        target->setPosition(location);
        target->setg_x(location.x);
        target->setg_y(location.y);
    }
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
    
    //*****************
    //make the boundry values dynamic DON'T LEAVE THEM HARD CODED dumbass
    //*****************
    if(leftRoom != NULL){
        //test for crew leaving to the left room
        for(int k = 0;k < thisRoom.size();k++)
        {
            if(thisRoom[k]->getg_x() < 10 * sfy){
                thisRoom[k]->setg_x(440 * sfy);
                thisRoom[k]->setPositionX(thisRoom[k]->getg_x());
                CCPoint p = thisRoom[k]->getPosition();
                cout << thisRoom[k] << endl;
                thisRoom[k]->isSwitchingRooms = true;
                //leftCrewVector.push_back(thisRoom[k]);
                 CrewVectors.at(leftRoom->roomKey).push_back(thisRoom[k]);
                //rightCrewVector[k]->setPositionX(rightCrewVector)
                removeChild(thisRoom[k]);
                CrewVectors.at(roomKey).erase(CrewVectors.at(roomKey).begin() + k);
                thisRoom.erase(thisRoom.begin()+k);
                tempermentShift(CrewVectors.at(roomKey));
            
            }
        }
    }
    //right
    if(rightRoom != NULL){
    for(int k = 0;k < thisRoom.size();k++)
    {
        if(thisRoom[k]->getg_x() > 450 * sfy){
            thisRoom[k]->setg_x(20 * sfy);
            thisRoom[k]->setPositionX(thisRoom[k]->getg_x());
            CCPoint p = thisRoom[k]->getPosition();
            //float b = thisRoom[k]->g_x;
            cout << thisRoom[k] << endl;
            thisRoom[k]->isSwitchingRooms = true;
            //rightCrewVector.push_back(thisRoom[k]);
            CrewVectors.at(rightRoom->roomKey).push_back(thisRoom[k]);
            //rightCrewVector[k]->setPositionX(rightCrewVector)
            removeChild(thisRoom[k]);
            CrewVectors.at(roomKey).erase(CrewVectors.at(roomKey).begin() + k);
            thisRoom.erase(thisRoom.begin()+k);
            tempermentShift(CrewVectors.at(roomKey));
            
        }
    }
    }
    
    if(upRoom != NULL){
        //test for crew leaving to the left room
        for(int k = 0;k < thisRoom.size();k++)
        {
            if(thisRoom[k]->getg_y() > 305 * sfy){
                thisRoom[k]->setg_y(30 * sfy);
                thisRoom[k]->setPositionY(thisRoom[k]->getg_y());
                CCPoint p = thisRoom[k]->getPosition();
                thisRoom[k]->isSwitchingRooms = true;
                //upCrewVector.push_back(thisRoom[k]);
                CrewVectors.at(upRoom->roomKey).push_back(thisRoom[k]);
                //rightCrewVector[k]->setPositionX(rightCrewVector)
                removeChild(thisRoom[k]);
                CrewVectors.at(roomKey).erase(CrewVectors.at(roomKey).begin() + k);
                thisRoom.erase(thisRoom.begin()+k);
                tempermentShift(CrewVectors.at(roomKey));
                
            }
        }
    }
    if(downRoom != NULL){
        //test for crew leaving to the left room
        for(int k = 0;k < thisRoom.size();k++)
        {
            if(thisRoom[k]->getg_y() < 15 * sfy){
                thisRoom[k]->setg_y(290 * sfy);
                thisRoom[k]->setPositionY(thisRoom[k]->getg_y());
                CCPoint p = thisRoom[k]->getPosition();
                thisRoom[k]->isSwitchingRooms = true;
                //downCrewVector.push_back(thisRoom[k]);
                CrewVectors.at(downRoom->roomKey).push_back(thisRoom[k]);
                //rightCrewVector[k]->setPositionX(rightCrewVector)
                removeChild(thisRoom[k]);
                CrewVectors.at(roomKey).erase(CrewVectors.at(roomKey).begin() + k);
                thisRoom.erase(thisRoom.begin()+k);
                tempermentShift(CrewVectors.at(roomKey));
                
            }
        }
    }
    
    if(loading == true){
    render++;
    }
    
    if(render == 2){
        loadOtherStuff();
        render = 0;
        loading = false;
       
    }
    roomCount++;
    char stext[20];
    sprintf(stext,"%d", roomCount);
     
       }

void baseRoom::loadOtherStuff()
{
    assignCrewVectors();
    //sleep(10.0);
    //********Adding the crew members to the layer**************
    //right
    for(int i = 0; i < thisRoom.size();i++){
        
            this->addChild(thisRoom[i], 2);
        
        thisRoom[i]->isSwitchingRooms = false;
        thisRoom[i]->setPositionX((float)thisRoom[i]->getg_x());
        thisRoom[i]->setPositionY((float)thisRoom[i]->getg_y());
        thisRoom[i]->setScale(sfy);
    }
    
    
    //***********************************************************

    
}

void baseRoom::switchUp()
{
    if(upRoom != NULL)
    {
        CCDirector::sharedDirector()->replaceScene(upRoom->scene(upRoom));
        this->removeAllChildren();
    }


}

void baseRoom::switchDown()
{
    if(downRoom != NULL)
    {
        CCDirector::sharedDirector()->replaceScene(downRoom->scene(downRoom));
        this->removeAllChildren();
    }

}


void baseRoom::switchRight()
{
    if(rightRoom != NULL)
    {
        CCDirector::sharedDirector()->replaceScene(rightRoom->scene(rightRoom));
        this->removeAllChildren();
    }
}

void baseRoom::switchLeft()
{
    if(leftRoom != NULL)
    {
        CCDirector::sharedDirector()->replaceScene(leftRoom->scene(leftRoom));
        this->removeAllChildren();
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

void baseRoom::saveGame()
{
    //get write path
    string path = CCFileUtils::sharedFileUtils()->getWritablePath();
    
    //append file name
    path.append("saveGame.plist");
    
    gameSave->writeToFile(
    
}

void baseRoom::loadPlist()
{
    //get write path
    string path = CCFileUtils::sharedFileUtils()->getWritablePath();
    
    //append file name
    path.append("saveGame.plist");
    
    CCDictionary *dict = NULL;
    
    //ifstream
    ifstream iFile; (path.c_str(), ios::in | ios::binary);
    
    
    //if file exist and open for input
    if(iFile.is_open())
    {
        //create a dictionary with plist
        dict = CCDictionary::createWithContentsOfFile(path.c_str());
    }
    else{
        cout << "no file " << endl;
        
        //make file
        
    }//
    
    
    
}

;


