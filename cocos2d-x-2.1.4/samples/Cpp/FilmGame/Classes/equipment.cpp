//
//  equipment.cpp
//  FilmGame
//
//  Created by Anthony Jones on 4/22/14.
//
//

#include "equipment.h"

equipment::equipment()
{
    m_name = "";
    m_class = "";
    m_brand = "";
    m_type = "";
    tier = 0;
    equipmentID = 0;
    kitID = 0;
    cost = 0;
    rentalCost = 0;
    durability = 0;
    quality = 0;
    classID = 0;
    
    rental = false;
    
    
    
}

bool equipment::CompareTo(equipment* e1, equipment* e2)
{
    
    
    bool b = false; 
    
    if(e1->tier == e2->tier)
    {
        if(e1->classID == e2->classID)
        {
            if(e1->quality > e2->quality)
            {
                b = true;
            }
        
        }
        
        else if(e1->classID > e2->classID)
        {
            b =true;
        }
        
    }
    else if(e1->tier > e2->tier)
    {
        b = true;
    }
    
    
    return b;
}