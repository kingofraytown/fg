//
//  PreUtility.h
//  FilmGame
//
//  Created by Anthony Jones on 4/29/14.
//
//

#ifndef __FilmGame__PreUtility__
#define __FilmGame__PreUtility__

#include <iostream>
#include "cocos2d.h"
#include "crew.h"
#include "Script.h"
#include "cocos-ext.h"
#include "CCTableView.h"
#include "equipment.h"
#include "Production.h"


using namespace cocos2d;
using namespace cocos2d::extension;

class PreUtility : public CCObject
{
    
    
public:
    
    //member variables
    
    /***Populate the production object***/
    
    //Assign the crewList
    static void SetCrewList(vector<crew*>);
    
    //get cheap crew
    static vector<crew*> GetCheapCrew();
    
    static crew FindCheapestDP();
    
    //get the best crew
    static vector<crew*> GetBestCrew();
    
    //Assign the equipmentList
    static void SetEquipmentList();
    
    //rent needed equipment
    static void GetNeededEquipment();
    
    //get cheap equipment from inventory
    static vector<equipment*> GetCheapEquipment();
    
    //get the best equipment from inventory
    static void GetBestEquipment();
    
    //Calculate the number of scene in the script
    static void CalcNumberOfScenes();
    //Calculate the shots for a given scene
    static void CalcNumberOfShot();
    //Calculate the 100% score for a shot
    static void CalcPossibleTopScore();
    
    //generate scenes and shots for those scenes
    static void FillProductionSchedule();
    
    //get number of shots with
    static int GetShotWithDP(crew* c);
    /***Saving the production object to XML file****/
    
    //Save crewList
    static void SaveCrewList();
    
    //Save EquipmentList
    static void SaveEquipmentList();
    
    //Save locations
    static void SaveLocation();
    
    //Save the production schedule
    static void SaveProductionSchedule();
    
    //Save script Data
    static void SaveScriptData();
    
    

};

#endif /* defined(__FilmGame__PreUtility__) */
