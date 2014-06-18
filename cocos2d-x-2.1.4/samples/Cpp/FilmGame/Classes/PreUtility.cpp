//
//  PreUtility.cpp
//  FilmGame
//
//  Created by Anthony Jones on 4/29/14.
//
//

#include "PreUtility.h"
#include "global.h"
#include "crewInfo.h"
#include "crew.h"
#include "Script.h"
#include "Production.h"
#include "Database.h"
#include <algorithm>
vector<crew*> PreUtility::GetCheapCrew(){
    vector<crew*> tempCrewVector;
    //1. get cheapest DP if there is one
    crew* cheapDP;
    
    for(int i = 0;i < theCrew.size();i++)
    {
        //loop through crew for
        if (theCrew[i]->role == "DP")
        {
            if(cheapDP == NULL)
            {
                cheapDP = theCrew[i];
            }
            else if(theCrew[i]->hireCost < cheapDP->hireCost)
            {
                cheapDP = theCrew[i];
            }
            
        }
    }

    //2. calculate shots to scenes based on DP skill
    
    //2.1 build the production object
    
    srand(time(NULL));
    float roll = rand()% 5 + .5; 
    
    currentProduction->numberOfScenes = selectedPreScript->pages * roll;
    
    srand(time(NULL) * roll);
    int sceneNumberRoll = rand()% 8 + 1;
    int DPBonus = 0;
    
    if((cheapDP != NULL) && (cheapDP->skill >= 70))
    {
        DPBonus = 1;
    }
    
    if((cheapDP != NULL) && (cheapDP->skill >= 80))
    {
        DPBonus = 2;
    }
    if((cheapDP != NULL) && (cheapDP->skill >= 90))
    {
        DPBonus = 3;
    }
    
    sceneNumberRoll = sceneNumberRoll - DPBonus;
    if(sceneNumberRoll < 1)
    {
        sceneNumberRoll = 1;
    }
    
    //3. get the score for 1 shot
        
    //score divided by scenes
    float sceneScore = selectedPreScript->difficulty / currentProduction->numberOfScenes;
    //scene score divided by shots
    float shotScore = sceneScore/ sceneNumberRoll;
    
    //4. calculate 80% of that score
    float decentScore = shotScore * .8;
    float departmentScore = decentScore/4;
    
    
    
    char crewQueryWithDept[300];
    string crewQuery = "SELECT * FROM CREW WHERE crew.DepartmentID = %i AND crew.CREWID IN %s ORDER BY skill DESC;";
    string crewQuery1 = "select * from crew where CREWID IN %s ORDER BY skill DESC";
    //build list of IDs
    size_t zero = 0;
    string crewString ="";
    if(crewList.size() > zero)
    {
        crewString = "(";
        
        for (int x = 0; x < crewList.size(); x++) {
            string crewStringID;
            stringstream out;
            
            out << crewList[x];
            crewStringID = out.str();
            crewString.append(crewStringID);
            
            if ((x+1) != crewList.size()) {
                crewString.append(",");
            }
            
        }
        crewString.append(")");
    }

    
    //5.find a crew member who can get 80% or more of their department score if all the tasks were completed. there should be a function that loops through the crew from highest skill to lowest, and to get that list of crew:
    for (int k = 0; k < 8;k++ )
    {
        vector<crew*> tempDepartmentVector;
        
        sprintf(crewQueryWithDept, crewQuery.c_str(), k, crewString.c_str());
        cout << "cheapCrew query"  << crewQueryWithDept,
        tempDepartmentVector = getCrewFromDBQuery(crewQueryWithDept);
        
        if(tempDepartmentVector.size() > 0)
        {
            crew* choosenCrew = new crew();
            //loop iterate throught vector for a suitable crew member
            for(int j = 0;j < tempDepartmentVector.size();j++)
            {
                if( tempDepartmentVector[j]->skill >= departmentScore)
                {
                    choosenCrew = tempDepartmentVector[j]; 
                }
                else if ((choosenCrew->crewID == 0) && (tempDepartmentVector[j]->skill < departmentScore))
                {
                    choosenCrew = tempDepartmentVector[j];
                    break;
                }
            }
            
            tempCrewVector.push_back(choosenCrew);
            
        }
        

    }
    
    return tempCrewVector;
}

vector<equipment*> PreUtility::GetCheapEquipment()
{
    vector<equipment*> tempEqList;
    vector<int> equipmentIDs;
    
    int camTier, audioTier, artTier, GafferTier, GripTier;
    bool ownedCam = false;
    bool ownedLens = false;
    bool ownedLights = false;
    bool ownedMic = false;
    
    equipment* tCamera = NULL;
    equipment* tLens= NULL;
    equipment* tMic= NULL;
    equipment* tLights = NULL;
    
    for(int t = 0; t < preEquipment.size();t++)
    {
        if(preEquipment[t]->m_type == "camera")
        {
            ownedCam = true;
        }
        
        if(preEquipment[t]->m_type == "lens")
        {
            ownedLens = true;
        }
        
        if(preEquipment[t]->m_type == "microphone")
        {
            ownedMic = true;
        }
        
        if(preEquipment[t]->m_type == "lights")
        {
            ownedLights = true;
        }
    }
    
    for(int i = 0; i <preCrewMembers.size();i++)
    {
        crew* tempCrew = preCrewMembers.at(i);
        int crewTier = 0;
        switch (tempCrew->tier){
            case 1:
                crewTier = 1;
                break;
            case 2:
                crewTier = 2;
                break;
                
            case 3:
                crewTier = 3;
                break;
                
            case 4:
                crewTier = 4;
                break;
                
            case 5:
                crewTier = 5;
                break;
                
            default:
                break;
        }
        
        switch (tempCrew->departmentID) {
            case 1:
                camTier = crewTier;
                break;
                
            case 2:
                audioTier = crewTier;
                break;
                
            case 4:
                GripTier = crewTier;
                break;
                
            case 5:
                GafferTier = crewTier;
                break;
                
            case 6:
                artTier = crewTier;
                break;
                
            default:
                break;
        }
    }
    
    //get vector of equipmentIDs from unlocked
    cout << "storeProgress" << storeProgress.size() << endl;
    for(int j = 0;j < storeProgress.size(); j++)
    {
        bool b = (bool)storeProgress.at(j+1);
        if(b == false)
        {
            vector<int> storeItems = storeInventories.at(j=+1);
            equipmentIDs.insert(equipmentIDs.end(), storeItems.begin(), storeItems.end());
        }
    }
    
    //query for equipment
    vector<equipment*> tempFullEqList = getEquipmentFromDB(equipmentIDs);
    
    for (int k = 0; k < tempFullEqList.size(); k++) {
        
        equipment* tEquipment = tempFullEqList.at(k);
        
        if((tEquipment->m_type == "camera") && (ownedCam == false))
        {
            if(tCamera == NULL)
            {
                tCamera = tEquipment;
            }
            else if(tCamera->rentalCost > tEquipment->rentalCost)
            {
                tCamera = tEquipment;
            }
        }
        
        if((tEquipment->m_type == "lens") && (ownedLens == false))
        {
            if(tLens == NULL)
            {
                tLens = tEquipment;
            }
            else if(tLens->rentalCost > tEquipment->rentalCost)
            {
                tLens = tEquipment;
            }
        }
        
        if((tEquipment->m_type == "light") && (ownedLights == false))
        {
            if(tLights == NULL)
            {
                tLights = tEquipment;
            }
            else if(tLights->rentalCost > tEquipment->rentalCost)
            {
                tLights = tEquipment;
            }
        }
        //((tEquipment->tier >= audioTier-1) && (tEquipment->tier <= audioTier))
        if((tEquipment->m_type == "microphone") && (ownedMic == false))
        {
            if(tMic == NULL)
            {
                tMic = tEquipment;
            }
            else if(tLights->rentalCost > tEquipment->rentalCost)
            {
                tMic = tEquipment;
            }
        }



    }
    tempEqList.push_back(tCamera);
    tempEqList.push_back(tLens);
    tempEqList.push_back(tLights);
    tempEqList.push_back(tMic);
   
    for (vector<equipment*>::iterator i=tempEqList.begin();i!=tempEqList.end();/*it++*/)
    {
        int j = std::distance( tempEqList.begin(), i );
        if (tempEqList.at(j) == NULL)
        {
            tempEqList.erase(i);
        }
        else
        {
            i++;
        }
    }
        
    //set rental flag
    for (int i = 0; i < tempEqList.size();i++ )
    {
        tempEqList[i]->rental = true;
    }
    
    return tempEqList;
    
}

void PreUtility::GetNeededEquipment(){
    //search own equipment to needed equipment
    
    //make equipment type vectors
    vector<equipment*> cameraVector;
    vector<equipment*> lensVector;
    vector<equipment*> lightsVector;
    vector<equipment*> micVector;
    
    //iterate through equipmentlist
    for(int i = 0; i < equipmentList.size();i++)
    {
        //put equipment in vectors for each type
        if(equipmentList[i]->m_type == "camera")
        {
            cameraVector.push_back(equipmentList[i]);
        }
        else if (equipmentList[i]->m_type == "lens")
        {
            lensVector.push_back(equipmentList[i]);
        }
        
        else if (equipmentList[i]->m_type == "lights")
        {
            
            lightsVector.push_back(equipmentList[i]);
        }
        
        else if (equipmentList[i]->m_type == "microphone")
        {
            micVector.push_back(equipmentList[i]);
        }
        
    }
    
    //sort the vectors
    if(cameraVector.size() > 1){
        std::sort(cameraVector.begin(), cameraVector.end(), equipment::CompareTo);
    }
    
    if(lensVector.size() > 1){
        std::sort(lensVector.begin(), lensVector.end(), equipment::CompareTo);
    }
    
    if(lightsVector.size() > 1){
        std::sort(lightsVector.begin(), lightsVector.end(), equipment::CompareTo);
    }
    
    if(micVector.size() > 1){
        std::sort(micVector.begin(), micVector.end(), equipment::CompareTo);
    }
    
    //picking the top equipment in vectors
    
    if(cameraVector.size() > 0)
    {
        preEquipment.push_back(cameraVector[0]);
    }
    
    if(lensVector.size() > 0)
    {
        preEquipment.push_back(lensVector[0]);
    }
    
    if(lightsVector.size() > 0)
    {
        preEquipment.push_back(lightsVector[0]);
    }
    
    if(micVector.size() > 0)
    {
        preEquipment.push_back(micVector[0]);
    }
    
    
    
    
    
}

int PreUtility::GetShotWithDP(crew* c)
{
    int shots = 0;
    srand(time(NULL));
    float roll = rand()% 5 + .5;
    
    srand(time(NULL) * roll);
    int sceneNumberRoll = rand()% 8 + 1;
    int DPBonus = 0;
    
    if((c != NULL) && (c->skill >= 70))
    {
        DPBonus = 1;
    }
    
    if((c != NULL) && (c->skill >= 80))
    {
        DPBonus = 2;
    }
    if((c != NULL) && (c->skill >= 90))
    {
        DPBonus = 3;
    }
    
    shots = sceneNumberRoll - DPBonus;
    if(shots < 1)
    {
        shots = 1;
    }

    return shots;
}
void PreUtility::FillProductionSchedule()
{
    currentProduction->numberOfPages = selectedPreScript->pages;
    
    
    //check if number of scenes is null or 0
    if(currentProduction->numberOfScenes == 0)
    {
        int pages = currentProduction->numberOfPages;
        
        srand(time(NULL));
        float roll = rand()% 5 + .5;
        currentProduction->numberOfScenes = pages * roll;
    }
    
    
    //get DP if there is one
    crew* DP;
    
    for(int i = 0;i < preCrewMembers.size();i++)
    {
        //loop through crew for
        if (preCrewMembers[i]->role == "DP")
        {
            DP = preCrewMembers[i];
            break;
        }
    }

    
    if(currentProduction->scriptScore == 0)
    {
        currentProduction->scriptScore = selectedPreScript->difficulty;
    }
    
    //get possible scene score
    float scoreForScenes = currentProduction->scriptScore / currentProduction->numberOfScenes;
    
    srand(time(NULL));
    float roll = rand()% 5 + .5;
    
    srand(time(NULL) * roll);
    //int shotNumberRoll = rand()% 8 + 1;
    //int DPBonus = 0;

    
    for(int i = 0; i < (currentProduction->numberOfScenes);i++)
    {
        //loop for number of scenes
        
        //make new scene
        PScene* newScene = new PScene();
        int shots;
        //assign scene id
        newScene->sceneID = i + 1;
        //assign possible score
        newScene->sceneScore = scoreForScenes;
        //determine number of shots
    
        
        if(DP != NULL)
        {
            shots = GetShotWithDP(DP);
        }
        else
        {
            srand(time(NULL));
            float roll = rand()% 5 + .5;
            
            srand(time(NULL) * roll);
            shots = rand()% 8 + 1;

        }
        
        //for number of shots
        for (int k = 0; k < shots; k++) {
            PShot* newShot = new PShot();
            newShot->possibleScore = scoreForScenes / shots;
            newScene->shotList.push_back(newShot);
        }
        
        //add scene to vector of scene
        currentProduction->productionScenes.push_back(newScene);
    }
    
    
}

static void SaveCrewList()
{
    //open the xml
}