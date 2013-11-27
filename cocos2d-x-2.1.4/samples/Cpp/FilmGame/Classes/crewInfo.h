//
//  crewInfo.h
//  Test1
//
//  Created by Anthony Jones on 6/5/13.
//
//

#ifndef __Test1__crewInfo__
#define __Test1__crewInfo__
#include "cocos2d.h"
#include <iostream>

using namespace cocos2d;
class crewInfo : public cocos2d::CCNode
{
public:
    CCInteger* crewId;
    CCDictionary* prodBonus;
    CCString room;
    CCFloat* g_x;
    CCFloat* g_y;
    
public: crewInfo();
    
    
    
    
};
#endif /* defined(__Test1__crewInfo__) */
