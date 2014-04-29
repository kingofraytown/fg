//
//  worldmap.h
//  FilmGame
//
//  Created by Anthony Jones on 1/28/14.
//
//

#ifndef __FilmGame__Inventory__
#define __FilmGame__Inventory__

#include "cocos2d.h"
#include "crew.h"
#include "CCGestureRecognizer/CCGestureRecognizer.h"
#include "CCGestureRecognizer/CCSwipeGestureRecognizer.h"
#include "Script.h"
#include "cocos-ext.h"
#include "CCTableView.h"


using namespace cocos2d;
using namespace cocos2d::extension;
class buttonInfo : CCObject
{
public:
    string label;
    
    int contentID;
    
};

class Inventory : public CCLayer, public CCTableViewDataSource, public CCTableViewDelegate
{
public:
    // Method 'init' in cocos2d-x returns bool, instead of 'id' in cocos2d-iphone (an object pointer)
    virtual bool init();
    
    // there's no 'id' in cpp, so we recommend to return the class instance pointer
    static cocos2d::CCScene* scene();
    
    enum states {e_equipment = 0 ,e_crew = 1, e_script = 2 };
    
    vector<crew*> crewArray;
    vector<CCNode*> nodeArray;
    int menuSwitch;
    int currentState;
    crew* target;
    unsigned int tableCount;
    string cellUpImage;
    string cellDownImage;
    CCSprite* poHeader;
    CCSprite* poFooter;
    CCSprite* poTint;
    CCSprite* leftBorder;
    CCNode * _bgNode;
    CCSprite *_bgSprite;
    vector<buttonInfo> m_buttons;
    
    CCSprite* rightArrow;
    bool startAnimation;
    bool nextReel;
    bool enterGameReel;
    bool crewPressed;
    bool scriptsPressed;
    CCMenu* inventoryButton;
    CCMenu* scriptsButton;
    CCMenu* crewButton;
    CCMenu* backButton;
    CCMenu* continueButton;
    CCTableView* tableView;
    CCTableView* itemTable;
    CCMenuItemImage* backImage;
    CCMenuItemImage* scriptsImage;
    CCMenuItemImage* crewImage;
    CCMenuItemImage* inventoryImage;
    CCMenuItemImage* continueImage;
    CCSwipeGestureRecognizer* SwipeGesture;
    
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
    void viewEquipment();
    void switchTable(CCTableView* currentTable,CCTableView* newTable);
    void switchData();
    
    void goback();
    // preprocessor macro for "static create()" constructor ( node() deprecated )
    CREATE_FUNC(Inventory);
    };


#endif /* defined(__FilmGame__ProductionOffice__) */
