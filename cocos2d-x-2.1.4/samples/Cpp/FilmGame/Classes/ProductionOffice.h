//
//  worldmap.h
//  FilmGame
//
//  Created by Anthony Jones on 1/28/14.
//
//

#ifndef __FilmGame__ProductionOffice__
#define __FilmGame__ProductionOffice__

#include "cocos2d.h"
#include "crew.h"
#include "CCGestureRecognizer/CCGestureRecognizer.h"
#include "CCGestureRecognizer/CCSwipeGestureRecognizer.h"
#include "Script.h"


using namespace cocos2d;
class ProductionOffice : public CCLayer
{
public:
    // Method 'init' in cocos2d-x returns bool, instead of 'id' in cocos2d-iphone (an object pointer)
    virtual bool init();
    
    // there's no 'id' in cpp, so we recommend to return the class instance pointer
    static cocos2d::CCScene* scene();
    
    vector<crew*> crewArray;
    vector<CCNode*> nodeArray;
    crew* target;
    
    CCSprite* topBorder;
    CCSprite* bottomBorder;
    CCSprite* rightBorder;
    CCSprite* leftBorder;

    
    CCSprite* rightArrow;
    bool startAnimation;
    bool nextReel;
    bool enterGameReel;
    bool crewPressed;
    bool scriptsPressed;
    CCMenu* newGame;
    CCMenu* scriptsButton;
    CCMenu* crewButton;
    CCMenu* crewListMenu;
    CCMenu* script_List;

    CCMenuItemImage* scriptsImage;
    CCMenuItemImage* crewImage;
    CCSwipeGestureRecognizer* SwipeGesture;
    int roomCount;
    int countDown;
    
    // a selector callback
    void menuCloseCallback(CCObject* pSender);
    
    void tempermentShift(vector<crew*>& cArray);
    void makeScript();
    virtual bool ccTouchBegan(CCTouch* touches, CCEvent* event);
    virtual void ccTouchMoved(CCTouch* touches, CCEvent* event);
    virtual void ccTouchEnded(CCTouch* touches, CCEvent* event);
    virtual void ccTouchesCancelled(CCSet* touches, CCEvent* event);
    virtual void update(float dt);
    void handleSwipe(CCObject* obj);
    void gestureBufferRight();
    void gestureBufferLeft();
    void gestureBufferDown();
    void gestureBufferUp();
    void registerWithTouchDispatcher();
    void viewCrew();
    void viewScripts();
    // preprocessor macro for "static create()" constructor ( node() deprecated )
    CREATE_FUNC(ProductionOffice);
    };


#endif /* defined(__FilmGame__ProductionOffice__) */
