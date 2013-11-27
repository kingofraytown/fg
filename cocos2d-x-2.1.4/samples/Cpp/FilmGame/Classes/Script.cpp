//
//  Script.cpp
//  FilmGame
//
//  Created by Anthony Jones on 11/3/13.
//
//

#include "Script.h"


Script::Script(vector<crew*> Authors)
{
    

    //get type
	collaborateType(Authors);
	
	//get page number
    pages = 0;
    for(int i = 0; i < Authors.size();i++)
    {
       pages += calcPages(Authors);
        
    }
	pages = pages/Authors.size();
	
    //initialize the Genres_bag with 1 of each genre
    for (int i = 0;i < 16; i++) {
        genre* tGenre = new genre(static_cast<genre::Genres>(i));
        
        Genre_bag.push_back(tGenre);
    }
    
	//get genre
	collaborateGenre(Authors);
    
	//make script title
    
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
          
    srand(firstRoll);
    
    genre::Genres tempGenreEnum;
    
    for(int i = 0; i < genreCount; i++)
    {
        tempGenreEnum = static_cast<genre::Genres>(rand()% Genre_bag.size() + 1);
        //add genre to vector
        genre* tempGenre = new genre(tempGenreEnum);
        scriptGenres.push_back(tempGenre);
    }
          
          
          
}
void Script::collaborateType(vector<crew*> Authors)
{
        crew* topAuthor;
        topAuthor = new crew(); //initalize writer stats in crew class to 0.0
        
        for(int i  = 0;i < Authors.size();i++)
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
            genre * tempGenre = new genre(static_cast<genre::Genres>(topAuthor->tendGenre)); //you mean Tend_genre?
            
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
    //get the pages tendency from each author
    for(int i = 0;i < Authors.size();i++)
    {
        pageSum += PagesByType(scriptType, Authors[i]);
    }
            
    //calculate the average page length
    AvgPages = pageSum/Authors.size();
            
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
    int a_ShortFilm[][6] = {{1,7, 7,12, 12,16}, {50,32, 31,25, 24,19}};
    
    //feature
    int a_feature[][6] {{50, 70, 70, 90, 90, 105}, {210, 190, 190, 170, 170, 150}};
    
    
    switch(type){
        case commercial:
            memcpy(&a_commercial, tempArray, sizeof(a_commercial));   //tempArray[2][6] = a_commercial;
			break;
        case ShortFilm:
           //int tempArray[2][6] = {{1,7, 7,12, 12,16}, {50,32, 31,25, 24,19}};
            memcpy(&a_ShortFilm, tempArray, sizeof(a_ShortFilm));
			break;
        case feature:
            memcpy(&a_feature, tempArray, sizeof(a_feature));
            //int tempArray[2][6] {{50, 70, 70, 90, 90, 105}, {210, 190, 190, 170, 170, 150}};
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
