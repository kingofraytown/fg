//
//  worldmap.h
//  FilmGame
//
//  Created by Anthony Jones on 1/28/14.
//
//

#ifndef __FilmGame__equipmentRoom__
#define __FilmGame__equipmentRoom__

#include "cocos2d.h"
#include "crew.h"
#include "CCGestureRecognizer/CCGestureRecognizer.h"
#include "CCGestureRecognizer/CCSwipeGestureRecognizer.h"
#include "Script.h"
#include "cocos-ext.h"
#include "CCTableView.h"
#include "equipment.h"


using namespace cocos2d;
using namespace cocos2d::extension;
/*class buttonInfo : CCObject
{
public:
    string label;
    
    int contentID;
    
};*/

class equipmentRoom : public CCLayer, public CCTableViewDataSource, public CCTableViewDelegate
{
public:
    // Method 'init' in cocos2d-x returns bool, instead of 'id' in cocos2d-iphone (an object pointer)
    virtual bool init();
    
    // there's no 'id' in cpp, so we recommend to return the class instance pointer
    static cocos2d::CCScene* scene();
    
    vector<equipment*> crewArray;
    vector<CCNode*> nodeArray;
    int menuSwitch;
    crew* target;
    unsigned int crewCount;
    //int crewCount;
    CCSprite* poHeader;
    CCSprite* poFooter;
    CCSprite* poTint;
    CCSprite* leftBorder;
    CCNode * _bgNode;
    CCSprite *_bgSprite;
    CCSprite* infoView;
    
    vector<buttonInfo> m_buttons;
    
    CCSprite* rightArrow;
    bool startAnimation;
    bool nextReel;
    bool enterGameReel;
    bool crewPressed;
    bool crewsPressed;
    CCMenu* inventoryButton;
    CCMenu* crewsButton;
    CCMenu* backButton;
    CCMenu* continueButton;
    CCTableView* tableView;
    CCMenuItemImage* backImage;

    CCMenuItemImage* inventoryImage;
    CCMenuItemImage* continueImage;
    CCSwipeGestureRecognizer* SwipeGesture;
    
    
    CCLabelTTF* sName;
    CCLabelTTF* sType;
    CCLabelTTF* sBrand;
    CCLabelTTF* sCost;
    CCLabelTTF* sClass;
    CCLabelTTF* lHeader;
    // a selector callback
    void menuCloseCallback(CCObject* pSender);
    
    void tempermentShift(vector<crew*>& cArray);
    void makeScript();
    virtual bool ccTouchBegan(CCTouch* touches, CCEvent* event);
    virtual void ccTouchMoved(CCTouch* touches, CCEvent* event);
    virtual void ccTouchEnded(CCTouch* touches, CCEvent* event);
    virtual void ccTouchesCancelled(CCSet* touches, CCEvent* event);
    virtual void update(float dt);
    
    virtual void scrollViewDidScroll (CCScrollView * view);
    virtual void scrollViewDidZoom (CCScrollView * view);
    virtual void tableCellTouched (CCTableView * table, CCTableViewCell * cell);
    virtual CCSize cellSizeForTable (CCTableView * table);
    virtual CCTableViewCell * tableCellAtIndex (CCTableView * table, unsigned int idx);
    virtual unsigned int numberOfCellsInTableView (CCTableView * table );
    virtual void tableCellHighlight (CCTableView * table,CCTableViewCell * cell);
    virtual void tableCellUnhighlight (CCTableView * table, CCTableViewCell * cell);
    void handleSwipe(CCObject* obj);
    void gestureBufferRight();
    void gestureBufferLeft();
    void gestureBufferDown();
    void gestureBufferUp();
    void registerWithTouchDispatcher();
    void viewInventory();
    void startPreProduction();
    void continueProduction();
    void viewCrew();
    void viewScripts();
    
    void goback();
    // preprocessor macro for "static create()" constructor ( node() deprecated )
    CREATE_FUNC(equipmentRoom);
    };


#endif /* defined(__FilmGame__equipmentRoom__) */
