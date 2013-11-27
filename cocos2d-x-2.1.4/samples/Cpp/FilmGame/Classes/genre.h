//
//  genre.h
//  FilmGame
//
//  Created by Anthony Jones on 11/3/13.
//
//

#ifndef __FilmGame__genre__
#define __FilmGame__genre__

#include <iostream>
#include "cocos2d.h"
#include <vector>
#include "crew.h"



using namespace std;
using namespace cocos2d;
class genre : public cocos2d::CCSprite
{

    public:
        //multipliers
        float post, pre, ge, cast, sound, camera, art;
        int m_genre;
    
        enum Genres {
            action,
            adventure,
            comedy,
            children,
            romance,
            thriller,
            horror,
            heist,
            period,
            indie,
            cerebral,
            documentary,
            fantasty,
            scifi,
            experimental
        };
    
    genre(Genres g);
    
    
};

#endif /* defined(__FilmGame__genre__) */