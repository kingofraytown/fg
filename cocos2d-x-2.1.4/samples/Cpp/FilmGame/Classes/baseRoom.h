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
#include "tinyxml.h"
#include "CCGestureRecognizer/CCGestureRecognizer.h"
#include "CCGestureRecognizer/CCSwipeGestureRecognizer.h"

using namespace cocos2d;
class baseRoom: public CCLayer
{
    CCSprite* menuBar;
    //CCSprite* crewButton;
    CCSprite* dayButton;
    CCSprite* hourButton;
    CCSprite* statsBG;
    CCLabelTTF* RoomName;
    CCLabelTTF* timer;
    CCSprite* profilePic;
    CCLabelTTF* TSVlabel;
    CCSprite* blueFade;
    CCSprite* greenFade;
    
    //lables
    //CCLabelTTF* StatsTitle;
    CCLabelTTF* Lstamina;
    CCLabelTTF* Lspeed;
    CCLabelTTF* Lskill;
    CCLabelTTF* Lfocus;
    CCLabelTTF* Lsocial;
    CCLabelTTF* Lconfindence;
    CCLabelTTF* MoveLabel;
    bool inTransition;
    //menu
    
    CCMenu* menu_bar;
    CCMenuItemImage* crewButton;
    CCMenu* menu_button;
    CCMenuItemImage* menuButton;
    
    //CCMenu* ArrowRight;
    //CCMenu* ArrowLeft;
    //CCMenu* ArrowUp;
    //CCMenu* ArrowDown;
    CCMenu* ArrowStateLeft;
    CCMenu* ArrowStateRight;
    CCMenu* SaveButton;
    CCMenu* LoadButton;
    //CCMenuItemImage* upArrow1;
    //CCMenuItemImage* downArrow1;
    //CCMenuItemImage* rightArrow1;
    //CCMenuItemImage* leftArrow1;
    CCMenuItemImage* leftStats;
    CCMenuItemImage* rightStats;
    CCMenuItemImage* saveButton;
    CCMenuItemImage* loadButton;
    
    CCSwipeGestureRecognizer* SwipeGesture;
    CCNode* gestureMask;
    
    int crewIndex;
    bool menuUp;
    float menuWidth;
    float menuHeight;
    CCPoint lastPoint;
   
    //string type;
    crew* target;
    
    
    vector<crew*> leftCrewVector;
    vector<crew*> rightCrewVector;
    vector<crew*> upCrewVector;
    vector<crew*> downCrewVector;
    vector<crew*> thrownCrew;
    
    char text;
    int roomCount;
    int render;
    int uCount;
    int lastcount;

public:
    
    vector<crew*> thisRoom;
     string roomKey;
    //pointers to adjacent rooms
    baseRoom* upRoom;
    baseRoom* downRoom;
    baseRoom* rightRoom;
    baseRoom* leftRoom;
    bool isSwitching;

   
    // Method 'init' in cocos2d-x returns bool, instead of 'id' in cocos2d-iphone (an object pointer)
    virtual bool init();
    
    // there's no 'id' in cpp, so we recommend to return the class instance pointer
    cocos2d::CCScene* scene(baseRoom* room);
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
    void loadGame();
    void registerWithTouchDispatcher();
    void handleSwipe(CCObject* obj);
    void gestureBufferUp();
    void gestureBufferDown();
    void removeAlmostEverything();
    bool distanceBetweenPoint(CCPoint p1, CCPoint p2);
    void MenuButton();
    void fadeUP();
    void getAdjacentRooms();
    // preprocessor macro for "static create()" constructor ( node() deprecated )
    

    string type;
    CREATE_FUNC(baseRoom);

};

#endif /* defined(__Test1__baseRoom__) */
