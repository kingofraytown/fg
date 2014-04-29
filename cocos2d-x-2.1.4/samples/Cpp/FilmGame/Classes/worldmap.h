//
//  worldmap.h
//  FilmGame
//
//  Created by Anthony Jones on 1/28/14.
//
//

#ifndef __FilmGame__worldmap__
#define __FilmGame__worldmap__

#include "cocos2d.h"
#include "crew.h"
#include "CCGestureRecognizer/CCGestureRecognizer.h"
#include "CCGestureRecognizer/CCSwipeGestureRecognizer.h"
#include "Script.h"

using namespace cocos2d;
class worldmap : public CCLayer
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
    
    CCMenu* newGame;
    CCMenu* scriptButton;
    CCMenu* poButton;
    CCMenu* backButton;
    //CCTableView* tableView;
    CCMenuItemImage* backImage;
    
    CCMenuItemImage* startImage;
    CCMenuItemImage* startImage2;
    CCSwipeGestureRecognizer* SwipeGesture;
    int roomCount;
    int countDown;
    
    // a selector callback
    void menuCloseCallback(CCObject* pSender);
    
    void tempermentShift(vector<crew*>& cArray);
    void makeScript();
    void ProductionOfficeButton();
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
    void goback();
    // preprocessor macro for "static create()" constructor ( node() deprecated )
    CREATE_FUNC(worldmap);
    };


#endif /* defined(__FilmGame__worldmap__) */
