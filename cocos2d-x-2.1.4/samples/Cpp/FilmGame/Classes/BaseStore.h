//
//  BaseStore.h
//  FilmGame
//
//  Created by Anthony Jones on 4/26/14.
//
//

#ifndef __FilmGame__BaseStore__
#define __FilmGame__BaseStore__

#include <iostream>
#include <stdlib.h>
#include "cocos2d.h"
#include <vector>
#include "equipment.h"
#include "tinyxml.h"


using namespace std;
using namespace cocos2d;
class BaseStore
{
    public:
    int tier;
    bool locked;
    vector<int> availableEquipment;
    vector<equipment*> inventory;
    
    public:
    vector<int> getEquipmentIDs();
    vector<equipment*> getInvortory();
    
        
};

#endif /* defined(__FilmGame__BaseStore__) */
