//
//  Script.h
//  FilmGame
//
//  Created by Anthony Jones on 11/3/13.
//
//

#ifndef __FilmGame__Script__
#define __FilmGame__Script__

#include <iostream>
#include "cocos2d.h"
#include <vector>
#include "crew.h"
#include "time.h"
#include "genre.h"
#include "Database.h"
#include "tinyxml/tinyxml.h"

using namespace std;
using namespace cocos2d;
class Script : public cocos2d::CCSprite
{
    //
    public:
    enum types {ShortFilm = 1, commercial = 2, feature = 3};
    int pages;
    string title;
    //genre scriptGenre;
    string scriptAuthor;
    
    types scriptType;
    vector<genre*> Genre_bag;
    vector<genre*> scriptGenres;
    vector<crew*> scriptAuthors;
    vector<string> authorNames;
    public:
    //constructor
    Script(vector<crew*> Authors);

    //generation methods
    Script();
    void typePicker();

    void genrePicker(); //randomly chooses 1 or 2 genres then randomly selects a genre for each

    void collaborateType(vector<crew*> Authors);//this will assign a type to the type member variable

    void collaborateGenre(vector<crew*> Authors);//this will populate the genre vector
    
    string static getTitleLine();
    
    string static getFiller();
    
    string makeSequel(string s);
    
    string titleBuilder();
    
    void static FindReplace(string& str, const string& oldStr, const string& newStr);
    bool static checkTitle(string s);


    int calcPages(vector<crew*> Authors);// this could be used when authors are used and assuming that the skill parameter is like an average of the writers skills.

    int getMagnitude(crew *);
    
    int PagesByType(types t, crew* c);
    int pagesByTendencyOrder(int order, types type, crew::pageLength tendencyLength);
};

#endif /* defined(__FilmGame__Script__) */
