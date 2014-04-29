//
//  BaseStore.cpp
//  FilmGame
//
//  Created by Anthony Jones on 4/26/14.
//
//

#include "BaseStore.h"
#include "global.h"

vector<int> BaseStore::getEquipmentIDs()
{
    return equipmentIDs;
}

vector<equipment*> BaseStore::getInvortory()
{
    return inventory;
}