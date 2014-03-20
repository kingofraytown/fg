//
//  worldmap.h
//  FilmGame
//
//  Created by Anthony Jones on 1/28/14.
//
//

#ifndef __FilmGame__loadGame__
#define __FilmGame__loadGame__

#include "cocos2d.h"
#include "crew.h"
#include "CCGestureRecognizer/CCGestureRecognizer.h"
#include "CCGestureRecognizer/CCSwipeGestureRecognizer.h"
#include "Script.h"

using namespace cocos2d;
class loadGame : public CCLayer
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
    
    CCMenu* load1;
    CCMenu* load2;
    CCMenu* load3;
    
    CCMenuItemImage* loadImage1;
    CCMenuItemImage* loadImage2;
    CCMenuItemImage* loadImage3;
    CCSwipeGestureRecognizer* SwipeGesture;
    int roomCount;
    int countDown;
    
    // a selector callback
    void menuCloseCallback(CCObject* pSender);
    
    void tempermentShift(vector<crew*>& cArray);
    void makeScript();
    void NewGameButton();
    bool checkForFile(string filename);
    void loadGame1();
    void loadGame2();
    void loadGame3();
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
    // preprocessor macro for "static create()" constructor ( node() deprecated )
    CREATE_FUNC(loadGame);
    };


#endif /* defined(__FilmGame__worldmap__) */