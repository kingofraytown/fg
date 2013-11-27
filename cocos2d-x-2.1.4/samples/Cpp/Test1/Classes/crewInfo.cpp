//
//  crewInfo.cpp
//  Test1
//
//  Created by Anthony Jones on 6/5/13.
//
//

#include "crewInfo.h"

crewInfo::crewInfo()
{
    prodBonus = CCDictionary::create();
    CCInteger* holder = 0;
    prodBonus->setObject(holder, "STAMINA");
    prodBonus->setObject(holder, "SPEED");
    prodBonus->setObject(holder, "SKILL");
    prodBonus->setObject(holder, "SOCIAL");
    prodBonus->setObject(holder, "CONFIDENCE");
    prodBonus->setObject(holder, "FOCUS");
    prodBonus->setObject(holder, "MORALE");
    room = "";
    g_x = 0;
    g_y = 0;
    

}