//
//  global.cpp
//  Test1
//
//  Created by Anthony Jones on 4/16/13.
//
//

#include "global.h"
using namespace std;
using namespace cocos2d;

std::vector<std::string> words;
std::vector<crew*> crewMembers;
std::vector<crew*> room1crew;
std::vector<crew*> room2crew;
std::vector<crew*> room3crew;
std::vector<crew*> room4crew;
char xtext[20];
CCLabelTTF *xlabel;
std::string dbP = "";
std::map<string, vector<crew*>> CrewVectors;
roomConfig *rConfig;
float sfx;
float sfy;
CCDictionary* gameSave = new CCDictionary;

extern void getCrewFromDB(vector<int> crewlist)
{
    Database *db;
    char rPath[300];
    /*
    string dbPath = cocos2d::CCFileUtils::sharedFileUtils()->getWritablePath();
    dbP = dbPath;
    dbPath.append("gameDB.db");
    //string strPath = cocos2d::CCFileUtils::sharedFileUtils()->full("gameDB.db");
    //cout << strPath << endl;
    sprintf(rPath,"%s",dbPath.c_str());
    //rPath = cocos2d::CCFileUtils::sharedFileUtils()->getSearchPaths();
     */
    
    string dbPath = CCFileUtils::sharedFileUtils()->getWritablePath();
    dbPath.append("dbPath.db");
    unsigned long tmpSize;
    unsigned char* xmlData = CCFileUtils::sharedFileUtils()->getFileData("gameDB.mp3", "rb", &tmpSize);
    FILE *fp = fopen(dbPath.c_str(), "wb");
    fwrite(xmlData, tmpSize, 1, fp);
    fclose(fp);
    sprintf(rPath,"%s",dbPath.c_str());
    db = new Database(rPath);
    
    vector<vector<string> > result = db->query("SELECT * FROM crew;");
    //cout << result[0][2] << endl;
    int crewID = 0;
    int name = 1;
    int skill = 7;
    int speed = 8;
    int focus = 9;
    int social = 10;
    int morale = 11;
    int confidence = 12;
    int stamina = 13;
    int temp1 = 14;
    int temp2 = 15;
    int temp3 = 16;
    int image = 18;
    
    
    
    
    for(vector<vector<string> >::iterator it = result.begin(); it < result.end(); ++it)
    {
        vector<string> row = *it;
        cout << "Values: (A=" << row.at(0) << ", B=" << row.at(1) << ")" << endl;
        crew* tempCrew = new crew();
        
        tempCrew->crewID = atoi(row.at(crewID).c_str());
        //assign stats
        tempCrew->skill = atoi(row.at(skill).c_str());
        tempCrew->speed = atoi(row.at(speed).c_str());
        tempCrew->focus = atoi(row.at(focus).c_str());
        tempCrew->social = atoi(row.at(social).c_str());
        tempCrew->morale = atoi(row.at(morale).c_str());
        tempCrew->baseConfidence = atoi(row.at(confidence).c_str());
        tempCrew->stamina = atoi(row.at(stamina).c_str());
        //assign temperaments
        tempCrew->temperament.push_back(atoi(row.at(temp1).c_str()));
        tempCrew->temperament.push_back(atoi(row.at(temp2).c_str()));
        tempCrew->temperament.push_back( atoi(row.at(temp3).c_str()));
        //assign texture filename
        cout << "images = " << row.at(image) << endl;
        
        tempCrew->setTexture(row.at(image));
        
        CrewVectors.at("room1crew").push_back(tempCrew);
    }
    
    db->close();

}

extern void mapCrewVector()
{
    CrewVectors.insert(std::pair<string, vector<crew*>>("room1crew",room1crew));
    CrewVectors.insert(std::pair<string, vector<crew*>>("room2crew",room2crew));
    CrewVectors.insert(std::pair<string, vector<crew*>>("room3crew",room3crew));
    CrewVectors.insert(std::pair<string, vector<crew*>>("room4crew",room4crew));
    
}
extern void initCrewMembers()
{

    crew *Doug = new crew();
    crew *Jmo = new crew();
    
    crewMembers.push_back(Doug);
    crewMembers.push_back(Jmo);
    
    Doug->setScaleX(sfx);
    Doug->setScaleY(sfy);
    
    Jmo->setScaleX(sfx);
    Jmo->setScaleY(sfy);
    
    Jmo->cocos2d::CCNode::setPosition(ccp(Jmo->getg_x() * sfx, Jmo->g_y * sfy));
    //Doug->setAnchorPoint(ccp(0.5, 0.0));
    Doug->cocos2d::CCNode::setPosition(ccp(Doug->getg_x() * sfx, Doug->g_y * sfy));
    
    Doug->temperament[0] = 1;
    Doug->temperament[1] = 4;
    
    
    Jmo->temperament[0] = 4;
    Jmo->temperament[1] = 10;
    
    
    
    
    Doug->social = 60;
    Doug->focus = 8;
    Doug->skill = 80;
    Doug->speed = 80;
    Doug->morale = 80;
    Doug->stamina = 80;
    Doug->baseConfidence = 80;
    
    Jmo->stamina = 70;
    Jmo->speed = 70;
    Jmo->skill = 70;
    Jmo->social = 70;
    Jmo->focus = 7;
    Jmo->morale = 65;
    Jmo->baseConfidence = 70;
    
    Doug->temperAssign();
    Jmo->temperAssign();
    vector<int> v = {0,0};
    //getCrewFromDB(v);
    //room1crew.push_back(Doug);
    //room1crew.push_back(Jmo);
    mapCrewVector();
    rConfig = new roomConfig();
     getCrewFromDB(v);
    //CrewVectors.at("room1crew").push_back(Doug);
    //CrewVectors.at("room1crew").push_back(Jmo);
    
}
