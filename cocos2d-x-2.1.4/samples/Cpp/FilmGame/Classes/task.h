//
//  task.h
//  Test1
//
//  Created by Anthony Jones on 6/18/13.
//
//

#ifndef __Test1__task__
#define __Test1__task__

#include <iostream>
#include "cocos2d.h"


using namespace cocos2d;
class task : public cocos2d::CCNode
{
public:
    //task complexity(int)
    CCInteger complexity;
    
    //suggested department(string)
    CCString department;
    
    //task name(string)
    CCString name;
    
    //task description(string)
    CCString description;
    
    //precent finished (double)
    CCDouble pfinshed;
    
    //task score(double)
    CCDouble score;
    //perfect task score(double)
    CCDouble perfectScore;
    
    //crew on task (vector)
    CCArray crewOnTask;
    
public: task();
    
    //get precent 
    
};

#endif /* defined(__Test1__task__) */
