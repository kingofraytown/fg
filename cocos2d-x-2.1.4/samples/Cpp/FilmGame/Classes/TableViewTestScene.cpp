#include "TableViewTestScene.h"
#include "CustomTableViewCell.h"
#include "global.h"

USING_NS_CC;
USING_NS_CC_EXT;

CCScene*  TableViewTestLayer::scene()
{
	CCScene *pScene = CCScene::create();
	TableViewTestLayer *pLayer = TableViewTestLayer::create();
	pScene->addChild(pLayer);
	//CCDirector::sharedDirector()->replaceScene(pScene);
    
    return pScene;
}

// on "init" you need to initialize your instance
bool TableViewTestLayer::init()
{
    if ( !CCLayer::init() )
    {
        return false;
    }

	CCSize winSize = CCDirector::sharedDirector()->getWinSize();

    CCTableView* tableView = CCTableView::create(this, CCSizeMake(250, 60));
    tableView->setDirection(kCCScrollViewDirectionHorizontal);
    tableView->setPosition(ccp(20,winSize.height/2-30));
    tableView->setDelegate(this);
    this->addChild(tableView);
    tableView->reloadData();

	tableView = CCTableView::create(this, CCSizeMake(130, 250));
	tableView->setDirection(kCCScrollViewDirectionVertical);
	tableView->setPosition(ccp(winSize.width-150,winSize.height/2-120));
	tableView->setDelegate(this);
	tableView->setVerticalFillOrder(kCCTableViewFillTopDown);
	this->addChild(tableView);
	tableView->reloadData();

	// Back Menu
	/*CCMenuItemFont *itemBack = CCMenuItemFont::create("Back", this, menu_selector(TableViewTestLayer::toExtensionsMainLayer));
	itemBack->setPosition(ccp(VisibleRect::rightBottom().x - 50, VisibleRect::rightBottom().y + 25));
	CCMenu *menuBack = CCMenu::create(itemBack, NULL);
	menuBack->setPosition(CCPointZero);
	addChild(menuBack);*/

    return true;
}

/*void TableViewTestLayer::toExtensionsMainLayer(cocos2d::CCObject *sender)
{
	ExtensionsTestScene *pScene = new ExtensionsTestScene();
	pScene->runThisTest();
	pScene->release();
}*/

void TableViewTestLayer::tableCellTouched(CCTableView* table, CCTableViewCell* cell)
{
    CCLOG("cell touched at index: %i", cell->getIdx());
}

CCSize TableViewTestLayer::tableCellSizeForIndex(CCTableView *table, unsigned int idx)
{
    /*if (idx == 2) {
        return CCSizeMake(100, 100);
    }*/
    return CCSizeMake(120, 60);
}

CCTableViewCell* TableViewTestLayer::tableCellAtIndex(CCTableView *table, unsigned int idx)
{
    CCString *string = CCString::create(scriptVector[idx]->title);
    
    CCTableViewCell *cell = table->dequeueCell();
    if (!cell) {
        cell = new CustomTableViewCell();
        cell->autorelease();
        CCSprite *sprite = CCSprite::create("Icon.png");
        sprite->setAnchorPoint(CCPointZero);
        sprite->setPosition(ccp(0, 0));
        sprite->setTag(4);
        cell->addChild(sprite);

        CCLabelTTF *label = CCLabelTTF::create(string->getCString(), "Helvetica", 12.0);
        label->setPosition(CCPointZero);
		label->setAnchorPoint(CCPointZero);
        label->setTag(123);
        cell->addChild(label);
    }
    else
    {
        CCLabelTTF *label = (CCLabelTTF*)cell->getChildByTag(123);
        label->setString(string->getCString());
    }


    return cell;
}

unsigned int TableViewTestLayer::numberOfCellsInTableView(CCTableView *table)
{
    return 10;
}

//just used for highlighting a cell when we click.I haven't used it but you can use
void TableViewTestLayer :: tableCellHighlight (CCTableView * table, CCTableViewCell * cell)
{
        
    CCTexture2D * aTexture = CCTextureCache :: sharedTextureCache () -> addImage ("Icon_red.png");
    CCSprite * pSprite = (CCSprite *) cell-> getChildByTag(4);
    pSprite-> setTexture (aTexture);
}

//when we move away from the cell and unhighlight it.This also I haven't used because I just want some buttons to be added and scrolled up and down.
void TableViewTestLayer :: tableCellUnhighlight (CCTableView * table,CCTableViewCell * cell)
{
    CCTexture2D * aTexture = CCTextureCache :: sharedTextureCache () -> addImage ("Icon.png");
    CCSprite * pSprite = (CCSprite *) cell-> getChildByTag (4);
    pSprite->setTexture(aTexture);
}
