//
//  StartPage.h
//  Test1
//
//  Created by Anthony Jones on 4/20/13.
//
//

#ifndef __Test1__StartPage__
#define __Test1__StartPage__

#include "cocos2d.h"
#include "crew.h"
#include "CCGestureRecognizer/CCGestureRecognizer.h"
#include "CCGestureRecognizer/CCSwipeGestureRecognizer.h"

using namespace cocos2d;
class StartPage : public CCLayer
{
public:
    // Method 'init' in cocos2d-x returns bool, instead of 'id' in cocos2d-iphone (an object pointer)
    virtual bool init();
    
    // there's no 'id' in cpp, so we recommend to return the class instance pointer
    static cocos2d::CCScene* scene();
 
    vector<crew*> crewArray;
    vector<CCNode*> nodeArray;
    crew* target;
    CCSprite* button;
    CCSprite* room;
    
    CCSprite* topBorder;
    CCSprite* bottomBorder;
    CCSprite* rightBorder;
    CCSprite* leftBorder;
    CCSprite* vertFilm;
    CCSprite* horzFilm;
    CCSprite* pLight1;
    CCSprite* pLight2;
    
    CCSprite* rightArrow;
    bool startAnimation;
    bool nextReel;
    bool enterGameReel;  
    
    CCMenu* newGame;
    CCMenu* loadGame;
    CCMenu* playButton;
    //CCMenu* loadGame;
    
    CCMenuItemImage* startImage;
    CCMenuItemImage* startImage2;
    CCMenuItemImage* startImage3;
    CCSwipeGestureRecognizer* SwipeGesture; 
    int roomCount;
    int countDown;
    int gamesFilesCount;
    // a selector callback
    void menuCloseCallback(CCObject* pSender);
    
    void tempermentShift(vector<crew*>& cArray);
    void PlayButton();
    void NewGameButton();
    void LoadGameButton();
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
    bool checkSavedGame();
    void makeSaveGameCounter();
    // preprocessor macro for "static create()" constructor ( node() deprecated )
    CREATE_FUNC(StartPage);
};


#endif /* defined(__Test1__StartPage__) */
