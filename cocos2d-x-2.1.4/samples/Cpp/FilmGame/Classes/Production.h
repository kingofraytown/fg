//
//  Production.h
//  FilmGame
//
//  Created by Anthony Jones on 4/29/14.
//
//

#ifndef __FilmGame__Production__
#define __FilmGame__Production__



#include <iostream>
#include "cocos2d.h"
#include "crew.h"
#include "CCGestureRecognizer/CCGestureRecognizer.h"
#include "CCGestureRecognizer/CCSwipeGestureRecognizer.h"
#include "Script.h"
#include "cocos-ext.h"
#include "CCTableView.h"
#include "equipment.h"


using namespace cocos2d;
using namespace cocos2d::extension;
/*class buttonInfo : CCObject
 {
 public:
 string label;
 
 int contentID;
 
 };*/

class PShot : public CCObject
{
    public:
    float shotScore;
    bool currentShot;
    bool completed;
    
    PShot();
    
};

class PScene : public CCObject
{
public:
    int sceneID;
    int location;
    bool currentScene;
    bool completed;
    float sceneScore;
    CCArray shotList; //should hold PShot objects
    
    PScene();
    
};


class Production : public CCLayer
{
public:

//Script Data
//number of pages
    int numberOfPages;
//number of scenes
    int numberOfScene;
//number of completed scenes with scores (key value pair)
    CCArray productionScenes;
    
    int completedScenes;
    //current scene with scores so far (key value pair)
    PScene currentScene;
    
//current shot (last unfinished shot)
    PShot currentShot;
//script difficulty (total possible points)
    float scriptScore;
//script name
    string scriptName;

//Crew Data
    
//call sheet (array or vector of objects of the following)
    CCArray callSheet; //use crewInfo
//Management Data
    
//current budget
    float currentBudget;
    
//x days of production (total amount of days)
    int daysOfProduction;
    
//nth hour of current day
    int hourOfDay;
//locations
    CCArray locations;
//current location
    int currentLocation;
    string strLocation;
//goal number of shoot days
    int goalNumberShootDays;
//Equipment
//Equipment List (array or vector)
    CCArray ProductionEquipment; //fill equipment objects


    
public:
    //2. Functions that can update the production object
    //Update the progress into the script
//completed scenes (add to list)
    void updateCompletedScene(PScene* tScene);// update the current scene to complete
//scores on completed scenes
    void updateCompletedSceneScore(PScene* tScene); // add all the shot scores and assign that value to scene score
//current scene
    void updateCurrentScene(PScene* tScene); //pass in a scene and change the scene's currentScene member to true. Then get the 'currentScene' and set its current flag to false. Then set 'currentSence' to the scene that was passed in

//shots for current scene
	float shotsInScene(PScene* tScene); //return the number of shots in the scene

	void updateCompletedShot(PShot* tShot);// update the current shots to complete
//scores on completed scenes
    void updateCompletedShotScore(PShot* tShot); // add all the shot shots and assign that value to scene score
//current scene

//Update crew productive bonus stats
	void updateCrewStats(crew* tCrew); //get the crew object's production stat bonuses and copy to crewInfo object with the same ID
//update days on set
	void updateDaysOnSet(); //increament the DaysOnSet membervariable;

//Update Budget

//3. Functions to set member variables
//These functions will be called upon completing the pre-production setup
//set CallSheet
//set EquipmentList
//set Budget
//set Locations
//set FilmName
	void SetFilmName(string s);
//set Days To Shoot


};


#endif /* defined(__FilmGame__Production__) */
