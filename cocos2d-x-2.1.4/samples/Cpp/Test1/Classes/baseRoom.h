//
//  baseRoom.h
//  Test1
//
//  Created by Anthony Jones on 5/17/13.
//
//

#ifndef __Test1__baseRoom__
#define __Test1__baseRoom__

#include <iostream>
#include "cocos2d.h"
#include "crew.h"
#include "SavedUserData.h"
using namespace cocos2d;
class baseRoom: public CCLayer
{
    CCSprite* rightArrow;
    CCSprite* leftArrow;
    CCSprite* upArrow;
    CCSprite* downArrow;
    CCSprite* menuBar;
    //CCSprite* crewButton;
    CCSprite* dayButton;
    CCSprite* hourButton;
    CCSprite* statsBG;
    CCLabelTTF* RoomName;
    CCLabelTTF* timer;
    CCSprite* profilePic;
    CCLabelTTF* TSVlabel;
    
    //lables
    //CCLabelTTF* StatsTitle;
    CCLabelTTF* Lstamina;
    CCLabelTTF* Lspeed;
    CCLabelTTF* Lskill;
    CCLabelTTF* Lfocus;
    CCLabelTTF* Lsocial;
    CCLabelTTF* Lconfindence;
    
    //menu
    
    CCMenu* menu_bar;
    CCMenuItemImage* crewButton;
    CCMenu* ArrowRight;
    CCMenu* ArrowLeft;
    CCMenu* ArrowUp;
    CCMenu* ArrowDown;
    CCMenu* ArrowStateLeft;
    CCMenu* ArrowStateRight;
    CCMenuItemImage* upArrow1;
    CCMenuItemImage* downArrow1;
    CCMenuItemImage* rightArrow1;
    CCMenuItemImage* leftArrow1;
    CCMenuItemImage* leftStats;
    CCMenuItemImage* rightStats;
    CCMenuItemImage* saveButton;
    
    int crewIndex;
    bool menuUp;
    float menuWidth;
    float menuHeight;
   
    //string type;
    crew* target;
    
    
    vector<crew*> leftCrewVector;
    vector<crew*> rightCrewVector;
    vector<crew*> upCrewVector;
    vector<crew*> downCrewVector;
    
    char text;
    int roomCount;
    int render;

public:
    
    vector<crew*> thisRoom;
     string roomKey;
    //pointers to adjacent rooms
    baseRoom* upRoom;
    baseRoom* downRoom;
    baseRoom* rightRoom;
    baseRoom* leftRoom;

   
    // Method 'init' in cocos2d-x returns bool, instead of 'id' in cocos2d-iphone (an object pointer)
    virtual bool init();
    
    // there's no 'id' in cpp, so we recommend to return the class instance pointer
    static cocos2d::CCScene* scene(baseRoom* room);
    bool loading;
    bool buttonPress;
    void menuCloseCallback(CCObject* pSender);
    void setType(string t);
    string getType();
    void tempermentShift(vector<crew*>& cArray);
    
    virtual bool ccTouchBegan(CCTouch* touches, CCEvent* event);
    virtual void ccTouchMoved(CCTouch* touches, CCEvent* event);
    virtual void ccTouchEnded(CCTouch* touches, CCEvent* event);
    virtual void ccTouchesCancelled(CCSet* touches, CCEvent* event);
    void assignCrewVectors();
    void switchUp();
    void switchDown();
    void switchRight();
    void switchLeft();
    void switchStatsRight();
    void switchStatsLeft();
    void crewStats();
    void saveGame();
    void update(float dt);
    void loadOtherStuff();
    void loadStats(crew *cMember);
    void loadPlist();
    void registerWithTouchDispatcher();
    // preprocessor macro for "static create()" constructor ( node() deprecated )
    

    string type;
    CREATE_FUNC(baseRoom);

};

#endif /* defined(__Test1__baseRoom__) */
