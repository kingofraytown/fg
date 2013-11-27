#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "crew.h"
using namespace cocos2d;
class HelloWorld : public CCLayer
{
public:
    // Method 'init' in cocos2d-x returns bool, instead of 'id' in cocos2d-iphone (an object pointer)
    virtual bool init();

    // there's no 'id' in cpp, so we recommend to return the class instance pointer
    static cocos2d::CCScene* scene();
    CCLabelTTF* Lstamina;
    /*
    CCLabelTTF* Lspeed;
    CCLabelTTF* Lskill;
    CCLabelTTF* Lfocus;
    CCLabelTTF* Lsocial;
    CCLabelTTF* LbaseConfidence;
    CCLabelTTF* Lstamina2;
    CCLabelTTF* Lspeed2;
    CCLabelTTF* Lskill2;
    CCLabelTTF* Lfocus2;
    CCLabelTTF* Lsocial2;
    CCLabelTTF* LbaseConfidence2;
    CCLabelTTF* Lroom;
    CCLabelTTF* Lcontent;
    CCLabelTTF* Lsize;
    */
    vector<crew*> crewArray;
    vector<CCNode*> nodeArray;
    crew* target;
    CCSprite* button;
    CCSprite* room;
    CCSprite* leftArrow;
    CCSprite* rightArrow;
    
    
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
    CREATE_FUNC(HelloWorld);
};

#endif // __HELLOWORLD_SCENE_H__
