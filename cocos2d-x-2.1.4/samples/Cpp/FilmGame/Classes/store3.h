//
//  store3.h
//  FilmGame
//
//  Created by Anthony Jones on 4/26/14.
//
//

#ifndef __FilmGame__store3__
#define __FilmGame__store3__

#include <iostream>
#include <stdlib.h>
#include "cocos2d.h"
#include <vector>
#include "equipment.h"
#include "tinyxml.h"
#include "BaseStore.h"

class store3 : public CCLayer, public BaseStore
{
public:
    // Method 'init' in cocos2d-x returns bool, instead of 'id' in cocos2d-iphone (an object pointer)
    virtual bool init();
    
    // there's no 'id' in cpp, so we recommend to return the class instance pointer
    static cocos2d::CCScene* scene();
    static vector<int> getInventory();
        // preprocessor macro for "static create()" constructor ( node() deprecated )
    CREATE_FUNC(store3);
};
#endif /* defined(__FilmGame__store3__) */
