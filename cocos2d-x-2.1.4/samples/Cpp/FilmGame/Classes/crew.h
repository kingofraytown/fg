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

#define flingMaxDuration 250
#define flingMinDistance 60



using namespace std;
using namespace cocos2d;
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
    
    //these values should be read in from the database as enum and then converted to ints when they are being assigned as member variables
    int tendPageOrder, tendPage, tendTypeOrder, tendType, tendGenreOrder, tendGenre;
    enum pageLength {Short = 0, Length = 1};
    
    //time variables
    int hoursOnSet, daysOnSet;
    string image;
    
    //the boolean variable ‘yesterday’ should be called for stat bonuses
    bool yesterday, onSet, isSwitchingRooms, isGrabbed, isFlicked;

    CCPoint grabStart;
    CCPoint grabEnded;
    CCPoint tempLocation;
    
    struct cc_timeval gTimeStart;
    struct cc_timeval gTimeStop;
    
    enum departmentEnums {all, post, pre, ge, cast, sound, camera, art};
    
    
    //GPS
private: float g_x;
public: float g_y;
    
    
    //temperament
    public: vector<int> temperament;
    public: vector<int> tempBonus;
    //flick variables
    vector<float> direction;
    float vectorSpeed;
    float deltaX;
    float deltaY;
    
    
public: void setTexture(string texture);

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
    float getDistance(CCPoint p1, CCPoint p2);
    void onGrab(CCPoint p);
    void onRelease();
    void vectorPush();



};

#endif /* defined(__testRoom__Crew__) */
