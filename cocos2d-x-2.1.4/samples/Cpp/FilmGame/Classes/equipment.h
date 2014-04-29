//
//  equipment.h
//  FilmGame
//
//  Created by Anthony Jones on 4/22/14.
//
//

#ifndef __FilmGame__equipment__
#define __FilmGame__equipment__

#include <iostream>

#include "cocos2d.h"
#include <vector>

#define flingMaxDuration 250
#define flingMinDistance 60



using namespace std;
using namespace cocos2d;
class equipment : public cocos2d::CCSprite

{
    //member variables
    public: int
    equipmentID,
    cost,
    rentalCost,
    quality,
    durability,
    kitID;
    
    string m_type;
    string m_brand;
    string m_name;
    string m_class;
    
    //functions
    equipment();
    
};


#endif /* defined(__FilmGame__equipment__) */
