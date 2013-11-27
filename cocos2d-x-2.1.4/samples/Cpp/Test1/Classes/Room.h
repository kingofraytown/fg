#ifndef __ROOM_SCENE_H__
#define __ROOM_SCENE_H__

#include "cocos2d.h"
#include "crew.h"
using namespace cocos2d;
class Room : public CCLayer
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
    CCSprite* leftArrow;
    CCSprite* rightArrow;
    CCSprite* topArrow;
    CCSprite* bottomArrow;
    
    CCSprite* topBorder;
    CCSprite* bottomBorder;
    CCSprite* rightBorder;
    CCSprite* leftBorder;
    
    
    int roomCount;
    
    // a selector callback
    void menuCloseCallback(CCObject* pSender);
    
    void tempermentShift(vector<crew*>& cArray);
    
    virtual bool ccTouchBegan(CCTouch* touches, CCEvent* event);
    virtual void ccTouchMoved(CCTouch* touches, CCEvent* event);
    virtual void ccTouchEnded(CCTouch* touches, CCEvent* event);
    virtual void ccTouchesCancelled(CCSet* touches, CCEvent* event);
    virtual void update(float dt);
    void registerWithTouchDispatcher();
    // preprocessor macro for "static create()" constructor ( node() deprecated )
    CREATE_FUNC(Room);
};

#endif // __HELLOWORLD_SCENE_H__
