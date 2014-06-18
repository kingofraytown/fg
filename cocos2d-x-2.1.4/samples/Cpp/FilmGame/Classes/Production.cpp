//
//  Production.cpp
//  FilmGame
//
//  Created by Anthony Jones on 4/29/14.
//
//

#include "Production.h"
#include "global.h"
#include "PreUtility.h"

PScene::PScene()
{
    sceneID  = 0;
    location = 0;
    currentScene = 0;
    completed = false;
    sceneScore = 0.0;
    possibleScore = 0.0;
    vector<PShot*> shotList; //should hold PShot objects
}

PShot::PShot()
{
    shotScore = 0.0;
    possibleScore = 0.0;
    currentShot = false;
    completed = false;
}


ProductionClass::ProductionClass()
{
    //Script Data
    //number of pages
    numberOfPages = 0;
    
    //number of scenes
    numberOfScenes = 0;
    
    //number of completed scenes with scores (key value pair)
    vector<PScene*> productionScenes;
    
    completedScenes = 0;
    //current scene with scores so far (key value pair)
    
    currentScene = new PScene();
    
    //current shot (last unfinished shot)
    currentShot = new PShot();
    
    //script difficulty (total possible points)
    scriptScore = 0.0;
    //script name
    scriptName = "";
    
    //Crew Data
    
    //call sheet (array or vector of objects of the following)
    vector<crewInfo*> callSheet; //use crewInfo
    //Management Data
    
    //current budget
    currentBudget = 0.0;
    
    //x days of production (total amount of days)
    daysOfProduction = 0.0;
    
    //nth hour of current day
    hourOfDay = 0.0;
    
    //locations
    vector<int> locations;
    
    //current location
    currentLocation = 0;
    strLocation = "";
    
    //goal number of shoot days
    goalNumberShootDays = 0;
    
    //Equipment
    //Equipment List (array or vector)
    vector<equipment*> ProductionEquipment; //fill equipment objects

}