//
//  global.h
//  Test1
//
//  Created by Anthony Jones on 4/16/13.
//
//
#ifndef global_h
#define global_h
#include <vector>
#include "crew.h"
#include "roomConfig.h"
#include "cocos2d.h"
#include "Database.h"
#include "SavedUserData.h"

using namespace std;
//extern int gVal;
extern vector<string> words;
extern vector<crew*> crewMembers;
extern vector<crew*> room1crew;
extern vector<crew*> room2crew;
extern vector<crew*> room3crew;
extern vector<crew*> room4crew;
extern map<string, vector<crew*>> CrewVectors;
extern float sfx; //scaling factor
extern float sfy;
extern char xtext[20];
extern CCLabelTTF* xlabel;
extern crew* crew1;
extern crew* crew2;
extern string dbP;
extern roomConfig* rConfig;
extern void getCrewFromDB(vector<int> crewlist);
extern void initCrewMembers();
extern void mapCrewVectors();
extern CCDictionary* gameSave;
#endif

