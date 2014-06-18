//
//  PreProductionLanding.h
//  FilmGame
//
//  Created by Anthony Jones on 1/28/14.
//
//

#ifndef __FilmGame__PreProductionLanding__
#define __FilmGame__PreProductionLanding__

#include "cocos2d.h"
#include "crew.h"
#include "CCGestureRecognizer/CCGestureRecognizer.h"
#include "CCGestureRecognizer/CCSwipeGestureRecognizer.h"
#include "Script.h"
#include "PreUtility.h"

using namespace cocos2d;
class PreProductionLanding : public CCLayer
{
public:
    // Method 'init' in cocos2d-x returns bool, instead of 'id' in cocos2d-iphone (an object pointer)
    virtual bool init();
    
    // there's no 'id' in cpp, so we recommend to return the class instance pointer
    static cocos2d::CCScene* scene();
    
    vector<crew*> crewArray;
    vector<CCNode*> nodeArray;
    crew* target;

    
    CCSprite* rightArrow;
    bool startAnimation;
    bool nextReel;
    bool enterGameReel;
    
    CCMenu* manualButton;
    CCMenu* cheapButton;
    CCMenu* wellDoneButton;
    CCMenu* backButton;
    //CCTableView* tableView;
    CCMenuItemImage* backImage;
    
    CCMenuItemImage* manualImage;
    CCMenuItemImage* wellDoneImage;
    CCMenuItemImage* cheapImage;
    CCSwipeGestureRecognizer* SwipeGesture;
    int roomCount;
    int countDown;
    
    // a selector callback
    void menuCloseCallback(CCObject* pSender);
    
    void ManualSelection();
    void DoItCheap();
    void DoItWell();
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
    CREATE_FUNC(PreProductionLanding);
    };


#endif /* defined(__FilmGame__PreProductionLanding__) */
