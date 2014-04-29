#ifndef __CUSTOMTABELVIEWCELL_H__
#define __CUSTOMTABELVIEWCELL_H__

#include "cocos2d.h"
#include "cocos-ext.h"

class CustomTableViewCell : public cocos2d::extension::CCTableViewCell
{
public:
    public:
        bool isHighlighted;
        int containedID;
        CCTableViewCell* cell;
    
        CustomTableViewCell();
        virtual void draw();
};

#endif /* __CUSTOMTABELVIEWCELL_H__ */

