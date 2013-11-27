//
//  Crew.h
//  testRoom
//
//  Created by Anthony Jones on 3/19/13.
//
//

#ifndef __testRoom__Crew__
#define __testRoom__Crew__

#include <iostream>

#include "cocos2d.h"
#include <vector>



using namespace std;
class crew : public cocos2d::CCSprite

{
    //stat variables
    public: int skill,
    speed,
    morale,
    focus,
    baseConfidence,
    social,
    stamina,
    crewID,
    temper,
    prodConfidence,
    prodSpeed,
    prodMorale,
    prodFocus,
    prodSocial,
    prodStamina,
    prodSkill;

    int activeStamina,
    activeSpeed,
    activeSocial,
    activeFocus,
    activeConfidence,
    activeMorale,
    activeSkill;
    
    //time variables
    int hoursOnSet, daysOnSet;
    string image;
    //GPS
private: float g_x;
public: float g_y;
    
    
    //temperament
    public: vector<int> temperament;
    public: vector<int> tempBonus;
    
public: void setTexture(string texture);
    
    
    //the boolean variable ‘yesterday’ should be called for stat bonuses
    bool yesterday, onSet, isSwitchingRooms;
    
    
    void getAbility();
    crew();
    
    
    
    void updateStats();
    void chSpeed(int diff);
    void chMorale(int diff);
    void chSocial(int diff);
    void chConfidence(int diff);
    void chFocus(int diff);
    void chSkill(int diff);
    void chStamina(int diff);
    
    //MAKE GETTERS FOR ACTIVE SPEED
    int getActiveStamina();
    int getActiveSkill();
    int getActiveSpeed();
    int getActiveSocial();
    int getActiveFocus();
    int getActiveConfidence();
    int getActiveMorale();
    
    
    int chStamina();
    
    int chConfidenceHour();
    int chConfidenceDay();
    int resetConfidence();
    int focusChanges();
    int moraleShift();
    void temperAssign();
    void setg_x(float x);
    float getg_x();
    void setg_y(float y);
    float getg_y();
    

    
};

#endif /* defined(__testRoom__Crew__) */
