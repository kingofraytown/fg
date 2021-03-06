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
#include "Production.h"
#include "crew.h"
#include "roomConfig.h"
#include "cocos2d.h"
#include "Database.h"
#include "SavedUserData.h"
#include "tinyxml.h"
#include "Script.h"
#include "genre.h"
#include "equipment.h"


using namespace std;
//extern int gVal;
extern vector<string> words;
extern vector<crew*> crewMembers;
extern vector<crew*> room1crew;
extern vector<crew*> room2crew;
extern vector<crew*> room3crew;
extern vector<crew*> room4crew;
extern vector<crew*> preCrewMembers;
extern vector<equipment*> preEquipment;
extern vector<int> store1List;
extern vector<int> store2List;
extern vector<int> store3List;
extern vector<int> store4List;
extern map<string, vector<crew*> > CrewVectors;
extern map<string, genre::GenresEnum> genreMap;
extern map<int, vector<int>> storeInventories; //equipment ID's
extern map<int, bool> storeProgress;
extern string genreArray[15];
extern vector<Script*> scriptVector;
extern vector<int> crewList;
extern vector<crew*> theCrew;
extern vector<equipment*> equipmentList;
extern vector<int> equipmentIDs;
//extern CCArray* scriptVector;
//extern CCArray* crewList;
extern float sfx; //scaling factor
extern float sfy;
extern char xtext[20];
extern CCLabelTTF* xlabel;
extern crew* crew1;
extern crew* crew2;
extern string dbP;
extern roomConfig* rConfig;
extern CCDictionary* gameSave;
extern bool gMapExist;
extern string currentGameFile;
extern CCScene*  previousScene;
extern bool xmlLock;
extern ProductionClass* currentProduction;
extern Script* selectedPreScript;
//methods
extern vector<crew*> getCrewFromDB(vector<int> crewlist);
extern vector<crew*> getCrewFromDBQuery(string strQuery);
extern vector<equipment*> getEquipmentFromDB(vector<int> gear);


extern void initCrewMembers();
extern void mapCrewVector();
extern void makeNewGameFile();
extern void makeGenreMap();
extern void mapStoreInventories();
extern void loadScripts(string lScript);
extern void loadCrew(string lCrew);
extern void loadEquipment(string lEquipment);
extern void loadProgress(string fileName);
extern void addCrew(int crewID);
extern void loadStores(string fileName);
extern void loadHangouts(string fileName);
#endif

