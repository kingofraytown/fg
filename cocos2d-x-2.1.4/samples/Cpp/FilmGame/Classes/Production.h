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

class Production : public CCLayer
{
public:

//Script Data
//number of pages
    int
//number of scenes
//number of completed scenes with scores (key value pair)
//current scene with scores so far (key value pair)
//current shot (last unfinished shot)
//script difficulty (total possible points)
//script name

//Crew Data
//class sheet (array or vector of objects of the following)
//crewID
//days on set
//stat production bonus (from being on set so many days)

//Management Data
//current budget
//x days of production (total amount of days)
//current day of production
//nth hour of current day
//locations
//current location
//goal number of shoot days

//Equipment
//Equipment List (array or vector)
//EquipmentID
//quantity

//2. Functions that can update the production object
//Update the progress into the script
//completed scenes (add to list)
//scores on completed scenes
//current scene
//shots for current scene
//completion statuses of current shots with scores


//Update crew stats
//update days on set
//update production stat bonus

//Update Location
//Update Budget

//3. Functions to set member variables
//These functions will be called upon completing the pre-production setup
//set CallSheet
//set EquipmentList
//set Budget
//set Locations
//set FilmName
//set Days To Shoot

//4. Functions to write to xml file
//Make template of production xml structure so that section of it will just need to be populated
//add node to section
//assign section attribute a value
//assign node attribute a value
};


#endif /* defined(__FilmGame__Production__) */
