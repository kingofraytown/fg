//
//  global.cpp
//  Test1
//
//  Created by Anthony Jones on 4/16/13.
//
//

#include "global.h"
#include "tinyxml/tinyxml.h"
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
std::map<genre::GenresEnum, string> genreMap;
roomConfig *rConfig;
float sfx;
float sfy;
CCDictionary* gameSave = new CCDictionary;
bool gMapExist = false;
string genreArray[15];
std::vector<Script*> scriptVector;
std::vector<int> crewList;
string currentGameFile = "";


extern vector<crew*> getCrewFromDB (vector<int> crewlist)
{
    vector<crew*> resultVector;
    
    Database *db;
    char rPath[300];
    
    
    string dbPath = CCFileUtils::sharedFileUtils()->getWritablePath();
    dbPath.append("dbPath.db");
    unsigned long tmpSize;
    unsigned char* xmlData = CCFileUtils::sharedFileUtils()->getFileData("gameDB.mp3", "rb", &tmpSize);
    FILE *fp = fopen(dbPath.c_str(), "wb");
    fwrite(xmlData, tmpSize, 1, fp);
    fclose(fp);
    sprintf(rPath,"%s",dbPath.c_str());
    db = new Database(rPath);
    size_t zero = 0;
    string crewString ="";
    if(crewlist.size() > zero)
    {
        crewString = "(";
        
        for (int x = 0; x < crewlist.size(); x++) {
            crewString.append(std::to_string( crewlist[x]));
            
            if ((x+1) != crewlist.size()) {
                crewString.append(",");
            }
            
        }
        crewString.append(")");
    }
    
    char strQuery[300];
    sprintf(strQuery,"SELECT * FROM crew WHERE crew.Crew_ID IN %s;", crewString.c_str());
    cout << strQuery << endl;
    vector<vector<string> > result = db->query(strQuery);
    //cout << result[0][2] << endl;
    
    //Remember to update when there is a schema change to the crew table
    int crewID = 0;
    int name = 1;
    int f_class = 2;
    int class_id = 3;
    int role = 4;
    int roleID = 5;
    int hirecost = 6;
    int dayRate = 7;
    int skill = 8;
    int speed = 9;
    int focus = 10;
    int social = 11;
    int morale = 12;
    int confidence = 13;
    int stamina = 14;
    int temp1 = 15;
    int temp2 = 16;
    int temp3 = 17;
    int ability = 18;
    int abilityID = 19;
    int image = 20;

    int locationMet = 21;
    int typeTendValue= 23;
    int typeTendOrder= 24;
    int genreTendValue = 25;
    int genreTendOrder = 26;
    int lengthTendValue= 27;
    int lengthTendOrder = 28;
    
    
    
    
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
        tempCrew->m_name = (row.at(name));
        tempCrew->m_class = (row.at(f_class));
        tempCrew->classID = atoi(row.at(class_id).c_str());
        tempCrew->roleID = atoi(row.at(roleID).c_str());
        tempCrew->role = (row.at(role));
        tempCrew->hireCost = atoi(row.at(hirecost).c_str());
        tempCrew->dayRate = atoi(row.at(dayRate).c_str());
        tempCrew->abilityID = atoi(row.at(abilityID).c_str());
        tempCrew->tendType = crew::convertType(row.at(typeTendValue));
        tempCrew->tendTypeOrder = atoi(row.at(typeTendOrder).c_str());
        tempCrew->tendGenre = crew::convertGenre(row.at(genreTendValue));
        tempCrew->tendGenreOrder = atoi(row.at(genreTendOrder).c_str());
        tempCrew->tendPage = crew::convertLength(row.at(lengthTendValue));
        tempCrew->tendPageOrder = atoi(row.at(lengthTendOrder).c_str());
        
        //assign texture filename
        cout << "images = " << row.at(image) << endl;
        
        tempCrew->setTexture(row.at(image));
        resultVector.push_back(tempCrew);
        //CrewVectors.at("room1crew").push_back(tempCrew);
    }
    
    db->close();
    
    return resultVector;

}

extern vector<crew*> getCrewFromDBQuery (string strQuery)
{
    vector<crew*> resultVector;
    
    Database *db;
    char rPath[300];
    
    string dbPath = CCFileUtils::sharedFileUtils()->getWritablePath();
    dbPath.append("dbPath.db");
    unsigned long tmpSize;
    unsigned char* xmlData = CCFileUtils::sharedFileUtils()->getFileData("gameDB.mp3", "rb", &tmpSize);
    FILE *fp = fopen(dbPath.c_str(), "wb");
    fwrite(xmlData, tmpSize, 1, fp);
    fclose(fp);
    sprintf(rPath,"%s",dbPath.c_str());
    db = new Database(rPath);
    
    char chQuery[300];
    sprintf(chQuery,"%s", strQuery.c_str());
    vector<vector<string> > result = db->query(chQuery);
    //cout << result[0][2] << endl;
    
    //Remember to update when there is a schema change to the crew table
    int crewID = 0;
    int name = 1;
    int f_class = 2;
    int class_id = 3;
    int role = 4;
    int roleID = 5;
    int hirecost = 6;
    int dayRate = 7;
    int skill = 8;
    int speed = 9;
    int focus = 10;
    int social = 11;
    int morale = 12;
    int confidence = 13;
    int stamina = 14;
    int temp1 = 15;
    int temp2 = 16;
    int temp3 = 17;
    int ability = 18;
    int abilityID = 19;
    int image = 20;
    int locationMet = 21;
    int typeTendValue= 23;
    int typeTendOrder= 24;
    int genreTendValue = 25;
    int genreTendOrder = 26;
    int lengthTendValue= 27;
    int lengthTendOrder = 28;
    
    
    
    
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
        tempCrew->m_name = (row.at(name));
        tempCrew->m_class = (row.at(f_class));
        tempCrew->classID = atoi(row.at(class_id).c_str());
        tempCrew->roleID = atoi(row.at(roleID).c_str());
        tempCrew->role = (row.at(role));
        tempCrew->hireCost = atoi(row.at(hirecost).c_str());
        tempCrew->dayRate = atoi(row.at(dayRate).c_str());
        tempCrew->abilityID = atoi(row.at(abilityID).c_str());
        tempCrew->tendType = crew::convertType(row.at(typeTendValue));
        tempCrew->tendTypeOrder = atoi(row.at(typeTendOrder).c_str());
        tempCrew->tendGenre = crew::convertGenre(row.at(genreTendValue));
        tempCrew->tendGenreOrder = atoi(row.at(genreTendOrder).c_str());
        tempCrew->tendPage = crew::convertLength(row.at(lengthTendValue));
        tempCrew->tendPageOrder = atoi(row.at(lengthTendOrder).c_str());
        
        //assign texture filename
        cout << "images = " << row.at(image) << endl;
        
        tempCrew->setTexture(row.at(image));
        resultVector.push_back(tempCrew);
        //CrewVectors.at("room1crew").push_back(tempCrew);
    }
    
    db->close();
    
    return resultVector;
    
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

extern void makeNewGameFile()
{
    //check saved game count
    
    //get write path
    string cpath = CCFileUtils::sharedFileUtils()->getWritablePath();
    
    
    //append file name
    cpath.append("GameCount.xml");
    cout << cpath << endl;
    
    TiXmlDocument cdoc(cpath.c_str());
    
    bool loadOkay = cdoc.LoadFile();
    int gameCount = 0;
    if(loadOkay){
        
        /*this will just reposition the crew for right now*/
        
        TiXmlElement* pElem;
        TiXmlHandle hroot(0);
        TiXmlHandle hdoc(&cdoc);


        pElem=hdoc.FirstChildElement().Element();
        hroot=TiXmlHandle(pElem);
     
        pElem=hroot.FirstChild("Count").Element();

        gameCount = atoi(pElem->Attribute("games"));//GetText());//Attribute("games");
    }
    
    if(gameCount < 3)
    {
    
    //**********************************************
    //get write path
    string path = CCFileUtils::sharedFileUtils()->getWritablePath();
    
    //append file name
    char filename[30];
    sprintf(filename, "GameMaster_%d.xml", gameCount + 1);
        currentGameFile = filename;
    path.append(filename);
    cout << path << endl;
    
    //*********************************
    TiXmlDocument *doc = new TiXmlDocument();
    
    //declearation
    TiXmlDeclaration* decl = new TiXmlDeclaration("1.0", "", "");
    doc->LinkEndChild( decl );
    
    //root
    TiXmlElement* root = new TiXmlElement("root");
    doc->LinkEndChild(root);
    TiXmlElement* production = new TiXmlElement("production");
    root->LinkEndChild(production);
    
    TiXmlElement* script = new TiXmlElement("script");
    script->SetAttribute("author", "");
    script->SetAttribute("title", "");
    script->SetAttribute("genre", "");
    script->SetAttribute("score","");
    script->SetAttribute("subtitle", "");
    production->LinkEndChild(script);
    TiXmlElement* callsheet = new TiXmlElement("callsheet");
    production->LinkEndChild(callsheet);
    TiXmlElement* scripts = new TiXmlElement("scripts");
    root->LinkEndChild(scripts);
    TiXmlElement* crewlist = new TiXmlElement("CrewList");
    root->LinkEndChild(crewlist);
    /***TEMP SWITCH FOR TESTING *******/
    switch(gameCount)
    {
        case 0:
        {
            //make array
            int crew1[5] = {1,3,5,7,9};
            
            for(int i = 0;i < 5;i++)
            {
            TiXmlElement* tcrew = new TiXmlElement("Crew");
            tcrew->SetAttribute("ID", crew1[i]);
            crewlist->LinkEndChild(tcrew);
            }
        }
            break;
        case 1:
        {
            //make array
            int crew2[5] = {2,4,6,8,10};
            
            for(int i = 0;i < 5;i++)
            {
                TiXmlElement* tcrew = new TiXmlElement("Crew");
                tcrew->SetAttribute("ID", crew2[i]);
                crewlist->LinkEndChild(tcrew);
            }
        }
            break;
        case 2:
        {
            //make array
            int crew3[5] = {1,2,3,4,5};
            
            for(int i = 0;i < 5;i++)
            {
                TiXmlElement* tcrew = new TiXmlElement("Crew");
                tcrew->SetAttribute("ID", crew3[i]);
                crewlist->LinkEndChild(tcrew);
            }
        }

            break;
    }
        
    doc->SaveFile(path.c_str());
    }
    
    //update game count
    if(loadOkay)
    {
        
        TiXmlElement* pElem;
        TiXmlHandle hroot(0);
        TiXmlHandle hdoc(&cdoc);
        
        
        pElem=hdoc.FirstChildElement().Element();
        hroot=TiXmlHandle(pElem);
        
        pElem=hroot.FirstChild("Count").Element();
        pElem->SetAttribute("games", gameCount + 1);
        
        cdoc.SaveFile(cpath.c_str());
    }
}

extern void makeGenreMap()
{    
    genreArray[0] = "action";
    genreArray[1] ="adventure";
    genreArray[2] ="comedy";
    genreArray[3] ="children";
    genreArray[4] ="romance";
    genreArray[5] ="thriller";
    genreArray[6] ="horror";
    genreArray[7] ="heist";
    genreArray[8] ="period";
    genreArray[9] ="indie";
    genreArray[10] ="cerebral";
    genreArray[11] ="documentary";
    genreArray[12] ="fantasty";
    genreArray[13] ="scifi";
    genreArray[14] ="experimental";
    
}

extern void loadScripts(string fileName)
{
    //get write path
    string path = CCFileUtils::sharedFileUtils()->getWritablePath();
    
    
    //append file name
    path.append(currentGameFile);
    cout << path << endl;
    
    TiXmlDocument doc(path.c_str());
    
    bool loadOkay = doc.LoadFile();
    
    if(loadOkay){
        
        /*this will just reposition the crew for right now*/
        
        TiXmlElement* pElem;
        TiXmlHandle hroot(0);
        TiXmlHandle hdoc(&doc);
        
        pElem=hdoc.FirstChildElement().Element();
        
        cout << pElem->Value() <<endl;
        hroot=TiXmlHandle(pElem);
        
        pElem=hroot.FirstChild( "scripts" ).Element();
        cout << pElem->Value() <<endl;
        
        if(!pElem->NoChildren())
        {
            //loop through all the scripts for a match
            //pElem=hroot.FirstChild( "crew" ).FirstChild().Element();
            for( pElem=pElem->FirstChild( "script" )->ToElement(); pElem; pElem=pElem->NextSiblingElement())
            {
                //tempElement
                
                //make a new script object
                Script * tempScript = new Script();
                tempScript->title = pElem->Attribute("title");
                tempScript->pages = atoi(pElem->Attribute("pages"));
                
                //loop through authors
                tempScript->authorNames.push_back(pElem->Attribute("author_1"));
                
                if(pElem->Attribute("author_2")){
                    tempScript->authorNames.push_back(pElem->Attribute("author_2"));
                }
                
                if(pElem->Attribute("author_3")){
                    tempScript->authorNames.push_back(pElem->Attribute("author_3"));
                }

                //loop through genres
                tempScript->authorNames.push_back(pElem->Attribute("genre_1"));
                
                if(pElem->Attribute("genre_2")){
                    tempScript->authorNames.push_back(pElem->Attribute("genre_2"));
                }
                
                if(pElem->Attribute("genre_3")){
                    tempScript->authorNames.push_back(pElem->Attribute("genre_3"));
                }
                //assign the type
                if(string(pElem->Attribute("type")) == "ShortFilm") {
                    tempScript->scriptType = Script::ShortFilm;
                }
                
                else if(string(pElem->Attribute("type")) == "commercial") {
                    tempScript->scriptType = Script::commercial;
                }
                
                else if(string(pElem->Attribute("type")) == "feature") {
                    tempScript->scriptType = Script::feature;
                }
                
                scriptVector.push_back(tempScript);
                
            }
            
            
        }

    }

}

extern void loadCrew(string fileName)
{
    //get write path
    string path = CCFileUtils::sharedFileUtils()->getWritablePath();
    
    
    //append file name
    path.append(currentGameFile);
    cout << path << endl;
    
    TiXmlDocument doc(path.c_str());
    
    bool loadOkay = doc.LoadFile();
    
    if(loadOkay){
        
        /*this will just reposition the crew for right now*/
        
        TiXmlElement* pElem;
        TiXmlHandle hroot(0);
        TiXmlHandle hdoc(&doc);
        
        pElem=hdoc.FirstChildElement().Element();
        
        cout << pElem->Value() <<endl;
        hroot=TiXmlHandle(pElem);
        
        pElem=hroot.FirstChild( "CrewList" ).Element();
        cout << pElem->Value() <<endl;
        
        if(!pElem->NoChildren())
        {
            //loop through all the scripts for a match
            //pElem=hroot.FirstChild( "crew" ).FirstChild().Element();
            for( pElem=pElem->FirstChild( "Crew" )->ToElement(); pElem; pElem=pElem->NextSiblingElement())
            {
                //tempElement
                
                //make a new script object
                int tempCrewID = 0;
                tempCrewID = atoi(pElem->Attribute("ID"));
                crewList.push_back(tempCrewID);
                
            }
            
            
        }
        
    }

    
}
extern void addCrew(int crewID)
{
    //push crew_ID to vector
    crewList.push_back(crewID);
    
    //add child to crewList XML
    //get write path
    string path = CCFileUtils::sharedFileUtils()->getWritablePath();
    
    
    //append file name
    path.append(currentGameFile);
    cout << path << endl;
    
    TiXmlDocument doc(path.c_str());
    
    bool loadOkay = doc.LoadFile();
    
    if(loadOkay){
        
    
        
        TiXmlElement* pElem;
        TiXmlHandle hroot(0);
        TiXmlHandle hdoc(&doc);
        
        pElem=hdoc.FirstChildElement().Element();
        
        cout << pElem->Value() <<endl;
        hroot=TiXmlHandle(pElem);
        
        pElem=hroot.FirstChild( "CrewList" ).Element();
        
        
        
    }
    
    
}
