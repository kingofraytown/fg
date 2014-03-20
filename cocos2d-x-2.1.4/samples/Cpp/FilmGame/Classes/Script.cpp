//
//  Script.cpp
//  FilmGame
//
//  Created by Anthony Jones on 11/3/13.
//
//

#include "Script.h"
#include "tinyxml/tinyxml.h"
#include "global.h"


Script::Script()
{
    title = "";
    pages = 0;
}
Script::Script(vector<crew*> Authors)
{
    
    scriptAuthors = Authors;
    //get type
	collaborateType(Authors);
	
	//get page number
    pages = 0;
    int authorCount = 0;
    
    crew* testguy = Authors[0];
    for(int i = 0; i < Authors.size();i++)
    {
       pages += calcPages(Authors);
        authorCount++;
    }

	pages = pages/authorCount;
	
    //initialize the Genres_bag with 1 of each genre
    for (int i = 0;i < 16; i++) {
        genre* tGenre = new genre(static_cast<genre::GenresEnum>(i));
        
        Genre_bag.push_back(tGenre);
    }
    
	//get genre
	collaborateGenre(Authors);
    
	//make script title
    
    titleBuilder();
    
}


void Script::typePicker()
{
	srand( time(NULL));
	int roll = rand() % 3 + 1; //range 1 to 3
    //types t = types[roll];
	switch(roll){
        case 1:
            scriptType = ShortFilm;
            break;
            
        case 2:
            scriptType = commercial;
            break;
            
        case 3:
            scriptType = feature;
            break;
            
        default:
            break;
    }
	
	
}

void Script::genrePicker()
{
	int firstRoll, secondRoll, genreCount;
	
    srand(time(NULL));
          firstRoll = rand()% 100 + 1; //range 1 to 100
          
    if(firstRoll > 50)
    {
        genreCount = 1;
    }
    else
    {
        genreCount = 2;
    }
          
    //srand(firstRoll);
    
    genre::GenresEnum tempGenreEnum;
    
    int rd2 = rand() % 204;
    srand(time(NULL) + rd2);
    cout << "rd2 = " << rd2 << endl;
    for(int i = 0; i < genreCount; i++)
    {
        
        int rg = rand()% 149 + 0;
        cout << "rg = " << rg << endl;
        int randomNumber = rg;
        if((rg >= 0) && (rg <= 9))
        {
            randomNumber = 0;
        }
        if((rg >= 10) && (rg <= 19))
        {
            randomNumber = 1;
        }
        if((rg >= 20) && (rg <= 29))
        {
            randomNumber = 2;
        }
        if((rg >= 30) && (rg <= 39))
        {
            randomNumber = 3;
        }
        if((rg >= 40) && (rg <= 49))
        {
            randomNumber = 4;
        }
        if((rg >= 50) && (rg <= 59))
        {
            randomNumber = 5;
        }
        if((rg >= 60) && (rg <= 69))
        {
            randomNumber = 6;
        }
        if((rg >= 70) && (rg <= 79))
        {
            randomNumber = 7;
        }
        if((rg >= 80) && (rg <= 89))
        {
            randomNumber = 8;
        }
        if((rg >= 90) && (rg <= 99))
        {
            randomNumber = 9;
        }
        if((rg >= 100) && (rg <= 109))
        {
            randomNumber = 10;
        }
        if((rg >= 110) && (rg <= 119))
        {
            randomNumber = 11;
        }
        if((rg >= 120) && (rg <= 129))
        {
            randomNumber = 12;
        }
        if((rg >= 130) && (rg <= 139))
        {
            randomNumber = 13;
        }
        if((rg >= 140) && (rg <= 149))
        {
            randomNumber = 14;
        }

        tempGenreEnum = static_cast<genre::GenresEnum>(randomNumber);
        //add genre to vector
        
        genre* tempGenre = new genre(tempGenreEnum);
        scriptGenres.push_back(tempGenre);
    }
          
          
          
}
void Script::collaborateType(vector<crew*> Authors)
{
        crew* topAuthor;
        topAuthor = new crew(); //initalize writer stats in crew class to 0.0
        
        for(int i = 0;i < Authors.size();i++)
        {
            if(Authors[i]->skill > topAuthor->skill)
            {
                topAuthor = Authors[i];
            }
            
            scriptType = static_cast<types>(topAuthor->tendType);
        }
    }
          
void Script::collaborateGenre(vector<crew*> Authors)
{
        crew* topAuthor = new crew();
        int topAuthorCount;
        for(int i  = 0;i < Authors.size();i++)
        {
            //genre tempgenre = new genre();
            if(Authors[i]->skill > topAuthor->skill)
            {
                topAuthor = Authors[i];
                topAuthorCount++;
            }
            
            int tendMag = getMagnitude(Authors[i]);
            genre * tempGenre = new genre(static_cast<genre::GenresEnum>(topAuthor->tendGenre)); //you mean Tend_genre?
            
            for(int j = 0; j < tendMag ; j++)
            {
                Genre_bag.push_back(tempGenre);
            }
        }
        
        genrePicker();
}
          
int Script::getMagnitude(crew* c)
{
    int rMag;
    
    rMag = 0;
        
    if((c->skill > 0) && (c->skill <= 60))
    {
        rMag = 3;
    }
           
    else if((c->skill > 61) && (c->skill <= 85))
    {
        rMag = 6;
    }
           
    else if((c->skill >86) && (c->skill <= 110))
    {
        rMag = 9;
    }
           
    return rMag;
}			
           
           
int Script::calcPages(vector<crew*> Authors)
{	
    int AvgPages;
    int pageSum = 0;
    int authorCount = 0;
    //get the pages tendency from each author
    for(int i = 0;i < Authors.size();i++)
    {
        pageSum += PagesByType(scriptType, Authors[i]);
        authorCount++;
    }
            
    //calculate the average page length
    AvgPages = pageSum/authorCount;
            
    return AvgPages;
}			
           
int Script::PagesByType(types type, crew* writer)
{
        int p = 0;
        switch(type)
            {
                case ShortFilm:
                    
                    p = pagesByTendencyOrder(writer->tendPageOrder, ShortFilm, static_cast<crew::pageLength>(writer->tendPage));
                    
                    break;
                    
                case commercial:
                    p = pagesByTendencyOrder(writer->tendPageOrder, commercial, static_cast<crew::pageLength>(writer->tendPage));
                    break;
                    
                case feature:
                    p = pagesByTendencyOrder(writer->tendPageOrder, feature, static_cast<crew::pageLength>(writer->tendPage));
                    break;
            }
            
            
            return p;
        }
int Script::pagesByTendencyOrder(int order, types type, crew::pageLength tendencyLength)
{
    
    //declare vaiables
    int tempArray[2][6];
    
    //short
    int a_commercial[2][6] = {{-2, 1, 1,2, 1,3}, {7,4, 5,4, 4,2}};
    
    //commercial
    int a_ShortFilm[2][6] = {{1,7, 7,12, 12,16}, {50,32, 31,25, 24,19}};
    
    //feature
    int a_feature[2][6] {{50, 70, 70, 90, 90, 105}, {210, 190, 190, 170, 170, 150}};
    
    
    switch(type){
        case commercial:
            //memcpy(&a_commercial, tempArray, sizeof(a_commercial));   //tempArray[2][6] = a_commercial;
            for (int i = 0; i < 2; i++){
                for (int j = 0; j < 6; j++){
                    tempArray[i][j] = a_commercial[i][j];
                }
            }
			break;
        case ShortFilm:
           //int tempArray[2][6] = {{1,7, 7,12, 12,16}, {50,32, 31,25, 24,19}};
            //memcpy(&a_ShortFilm, tempArray, sizeof(a_ShortFilm));
            for (int i = 0; i < 2; i++){
                for (int j = 0; j < 6; j++){
                    tempArray[i][j] = a_ShortFilm[i][j];
                }
            }

			break;
        case feature:
            //memcpy(&a_feature, tempArray, sizeof(a_feature));
            //int tempArray[2][6] {{50, 70, 70, 90, 90, 105}, {210, 190, 190, 170, 170, 150}};
            for (int i = 0; i < 2; i++){
                for (int j = 0; j < 6; j++){
                    tempArray[i][j] = a_feature[i][j];
                }
            }

			break;
    }
    int p = 0;
    switch(order){
        case 3:
            if(tendencyLength == crew::Short){
				srand(time(NULL));
				p = rand()% tempArray[0][0] + tempArray[0][1];
                
				//if p is over the limit of pages then set p to limit
            }
            
            else{
                srand(time(NULL));
                p = rand()% tempArray[1][0] + tempArray[1][1];
            }
			break;
			
        case 2:
            if(tendencyLength == crew::Short){
				srand(time(NULL));
				p = rand()% tempArray[0][2] + tempArray[0][3];
                
				//if p is over the limit of pages then set p to limit
            }
            
            else{
                srand(time(NULL));
                p = rand()% tempArray[1][2] + tempArray[1][3];
            }
            
			break;
            
        case 1:
            if(tendencyLength == crew::Short){
				srand(time(NULL));
				p = rand()% tempArray[0][4] + tempArray[0][5];
                
				//if p is over the limit of pages then set p to limit
            }
            
            else{
                srand(time(NULL));
                p = rand()% tempArray[1][4] + tempArray[1][5];
            }
            
			break;
    }
    
	return p;
}
string Script::getTitleLine(){
    string titleLine = "";
    int rowID;
    //generate a random number 1 to 100
    srand(time(NULL));
    rowID = rand()% 176 + 0;
    cout << "titleLine rand = " << rowID << endl;
    //connect to sqlite DB
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
    
    char strQuery[120];
    sprintf(strQuery, "SELECT TITLES FROM titles LIMIT 1 OFFSET %d ;", rowID);
    
    //query for row using the random number
    vector<vector<string> > result = db->query(strQuery);

    

    //assign results
    for(vector<vector<string> >::iterator it = result.begin(); it < result.end(); ++it)
    {
        
        vector<string> row = *it;
        if(row.size() != 0 ){
            try {
        titleLine = row.at(0);
                cout << titleLine << endl;
            }
            catch( exception e)
            {
                cout << e.what() << endl;
            }
        }
    }

    
    //close connection
    db->close();
    
    
    
    
    return titleLine;
}

string Script::getFiller(){
    string fillerLine = "";
    int rowID;
    //generate a random number 1 to 100
    srand(time(NULL));
    rowID = rand()% 95 + 0;
    cout << "fillerLine rand = " << rowID << endl;
    //connect to sqlite DB
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
    
    char strQuery[120];
    sprintf(strQuery, "SELECT FILLER FROM fillers LIMIT 1 OFFSET %d ;", rowID);
    
    //query for row using the random number
    vector<vector<string> > result = db->query(strQuery);
    
    
    
    //assign results
    for(vector<vector<string> >::iterator it = result.begin(); it < result.end(); ++it)
    {
        vector<string> row = *it;
        fillerLine = row.at(0);
        
    }
    
    
    //close connection
    db->close();
    
    return fillerLine;
}

string Script::titleBuilder()
{
    makeGenreMap();
    string title = "";
    string titlePart = getTitleLine();
    string fillerPart = getFiller();
    title = titlePart;

    FindReplace(title, "{0}", fillerPart);

    cout << "titlePart" << titlePart << endl;
    cout << "fillerPart" << fillerPart << endl;
    cout << title << endl;
    if(checkTitle(title) == false)
    {
        string path = CCFileUtils::sharedFileUtils()->getWritablePath();

        //append file name
        path.append(currentGameFile);
       // cout << path << endl;
        
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
            
            TiXmlElement* addOne = new TiXmlElement("script");
            addOne->SetAttribute("title", title.c_str());
            //loop through Authors
            char attributeName1[30];
            if(scriptAuthors.size() == 0)
            {
                cout << "WARNING NO Author" <<endl;
                
            }
            for(int x = 0; x < scriptAuthors.size(); x++)
            {
                sprintf(attributeName1,"author_%d",x+1 );
                //genreMap.at(scriptGenres[x]);
                addOne->SetAttribute(attributeName1, scriptAuthors[x]->m_name.c_str());
            }

            char attributeName2[30];

            //loop through genres
            if(scriptGenres.size() == 0)
            {
                cout << "WARNING NO Genre" <<endl;
                
            }
            
            for(int x = 0; x < scriptGenres.size(); x++)
            {
                sprintf(attributeName2,"genre_%d",x+1 );
                //genreMap.at(scriptGenres[x]);
                int tg = static_cast<genre::GenresEnum>(scriptGenres[x]->m_genre);
                char gName[30];
                //string strGenre = "";
                //strGenre = genreMap.at(tg);
                //cout<< "string genre = "<< strGenre << endl;
                cout <<"tg = " << tg << endl;
                sprintf(gName,"%s",genreArray[tg].c_str());
                
                cout << "cstring g = " << gName << endl;
                addOne->SetAttribute(attributeName2, genreArray[tg].c_str());
            }
            addOne->SetAttribute("pages", pages);
            switch (scriptType) {
                case ShortFilm:
                    addOne->SetAttribute("type", "ShortFilm");
                    break;
                case commercial:
                    addOne->SetAttribute("type", "commercial");
                    break;
                case feature:
                    addOne->SetAttribute("type", "feature");
                    break;
                default:
                    break;
            }
            
            pElem->LinkEndChild(addOne);
            doc.SaveFile(path.c_str());

        }
    }
    

    
    return title;
}

bool Script::checkTitle(string s)
{
    bool titleExist = false;
    
    //open the master xml file
    
    //get write path
    string path = CCFileUtils::sharedFileUtils()->getWritablePath();
    
    
    
    //append file name
    path.append(currentGameFile);
    //cout << path << endl;
    
    TiXmlDocument doc(path.c_str());
    
    bool loadOkay = doc.LoadFile();
    
    if(loadOkay){
        
        /*this will just reposition the crew for right now*/
        
        TiXmlElement* pElem;
        TiXmlHandle hroot(0);
        TiXmlHandle hdoc(&doc);
        
        pElem=hdoc.FirstChildElement().Element();
        
        //cout << pElem->Value() <<endl;
        hroot=TiXmlHandle(pElem);
 
        pElem=hroot.FirstChild( "scripts" ).Element();
        //cout << pElem->Value() <<endl;
        

        if(!pElem->NoChildren())
        {
            //loop through all the scripts for a match
            //pElem=hroot.FirstChild( "crew" ).FirstChild().Element();
            for( pElem=pElem->FirstChild( "script" )->ToElement(); pElem; pElem=pElem->NextSiblingElement()){
                //tempElement
                
                //cout << s << " != " << pElem->Attribute("title") << endl;
                if(pElem->Attribute("title") == s)
                {
                    titleExist = true;
                    break;
                    
                }
                    
            }

            
        }
        
        else{
            titleExist = false;
        }
        
        
    }

    
    return titleExist;
}

void Script::FindReplace(std::string& str, const std::string& oldStr, const std::string& newStr)
{
    size_t pos = 0;
    while((pos = str.find(oldStr, pos)) != std::string::npos)
    {
        str.replace(pos, oldStr.length(), newStr);
        pos += newStr.length();
    }
}



