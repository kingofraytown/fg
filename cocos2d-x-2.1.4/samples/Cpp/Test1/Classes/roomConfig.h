//
//  roomConfig.h
//  Test1
//
//  Created by Anthony Jones on 5/19/13.
//
//

#ifndef __Test1__roomConfig__
#define __Test1__roomConfig__

#include <iostream>
#include "baseRoom.h"
#include "cocos2d.h"
#include <vector>



using namespace std;
class roomConfig : public cocos2d::CCNode 

{

//array of rooms
    
//shape

//create room config
public:
    vector<baseRoom*> rooms;
roomConfig();

    int shape;
/* random shape function
*  return a int or 
*/
int randomShape();
void printConfig();
};



#endif /* defined(__Test1__roomConfig__) */
