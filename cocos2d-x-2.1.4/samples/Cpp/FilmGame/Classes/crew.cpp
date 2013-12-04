//
//  Crew.cpp
//  testRoom
//
//  Created by Anthony Jones on 3/19/13.
//
//

#include "crew.h"

crew::crew(){
    //stat variables
    skill = 0;
    speed = 0;
    morale = 0;
    focus = 0;
    baseConfidence = 0;
    
    prodConfidence = 0;
    prodMorale = 0;
    prodSkill = 0;
    prodStamina = 0;
    prodSpeed = 0;
    prodFocus = 0;
    prodSocial = 0;
    tendGenre = 0;
    tendPage = 0;
    tendType = 0;
    tendGenreOrder = 0;
    tendPageOrder = 0;
    tendTypeOrder = 0;
    
    
    social = 0;
    stamina = 0;
    crewID = 0;
    temper = 0;
    //time variables
    hoursOnSet = 0;
    daysOnSet = 0;
    g_x = 20;
    g_y = 30;
    hireCost = 0;
    dayRate = 0;
    roleID = 0;
    classID = 0;
    role = "";
    m_name = "";
    m_class = "";
    
    char images[200];
    sprintf(images,image.c_str());
    //images = image.c_str();
    //the boolean variable ‘yesterday’ should be called for stat bonuses
    yesterday = false;
    onSet = false;
    isSwitchingRooms = false;
    temperament = {0,0,0};
    tempBonus = {0,0,0,0,0,0}; //stam,skill,speed,focus,morale,confidence
    direction = {0,0};
    vectorSpeed = 0.0;
    isFlicked = false;
    
    vector<string> Paths;
    Paths.push_back("Resources");
    cocos2d::CCFileUtils::sharedFileUtils()->setSearchPaths(Paths);
    cocos2d::CCSpriteFrameCache* cacher;
    cacher = cocos2d::CCSpriteFrameCache::sharedSpriteFrameCache();
    cacher->addSpriteFramesWithFile("testAtlas.plist");
    cout << "images = " << images << endl;
    this->initWithSpriteFrameName("blue_c");
    //this->initWithSpriteFrameName(images);
 
    
    
}

void crew::setTexture(string texture)
{
    char images[200];
    sprintf(images,texture.c_str());
    image = texture;
    vector<string> Paths;
    Paths.push_back("Resources");
    cocos2d::CCFileUtils::sharedFileUtils()->setSearchPaths(Paths);
    cocos2d::CCSpriteFrameCache* cacher;
    cacher = cocos2d::CCSpriteFrameCache::sharedSpriteFrameCache();
    cacher->addSpriteFramesWithFile("testAtlas.plist");
    cout << "images = " << images << endl;
    this->initWithSpriteFrameName(images);
    //this->initWithSpriteFrameName(images);
    this->temperAssign();
}
void crew::getAbility(){
    
    
}


void crew::updateStats(){
    
    
}

int crew::chStamina(){
    
    
    stamina--;
    return 0;
    
}

int crew::chConfidenceHour(){
    prodConfidence = prodConfidence + (1 + hoursOnSet);
    
    return 0;
}


int crew::chConfidenceDay(){
    prodConfidence = prodConfidence + (1 + daysOnSet);
    
    return 0;
}

int crew::resetConfidence(){
    prodConfidence = baseConfidence;
    return 0;
}

int crew::focusChanges () {
    //focus += chFocus;
	switch ( activeFocus ) {
            //Penalties for low focus
		case 3:
            chSkill(-1 * (.02 * activeSkill));
            chSpeed(-1 * (.02 * activeSpeed));
			//skill -= (.02 * skill);
			//speed -= (.02 * speed);
			break;
		case 2:
            chSkill(-1 * (.05 * activeSkill));
            chSpeed(-1 * (.05 * activeSpeed));
			//skill -= (.05 * skill);
			//speed -= (.05 * speed);
			break;
		case 1:
            chSkill(-1 * (.1 * activeSkill));
            chSpeed(-1 * (.1 * activeSpeed));
			//skill -= (.1 * skill);
			//speed -= (.1 * speed);
			break;
		case 0:
            chSkill(-1 * (.2 * activeSkill));
            chSpeed(-1 * (.2 * activeSpeed));
			//skill -= (.2 * skill);
			//speed -= (.2 * speed);
			break;
            //Bonuses for high focus
		case 7:
            chSkill(.05 * activeSkill);
            chSpeed(.05 * activeSpeed);
			//skill += (.05 * skill);
			//speed += (.05 * speed);
			break;
		case 8:
            chSkill(.08 * activeSkill);
            chSpeed(.08 * activeSpeed);
			//skill += (.08 * skill);
			//speed += (.08 * speed);
			break;
		case 9:
            chSkill(.1 * activeSkill);
            chSpeed(.1 * activeSpeed);
			//skill += (.1 * skill);
			//speed += (.1 * speed);
			break;
		case 10:
            chSkill(.15 * activeSkill);
            chSpeed(.15 * activeSpeed);
			//skill += (.15 * skill);
			//speed += (.15 * speed);
			break;
	}
	/*NOTE: in most languages if you multiply or divide an integer by a decimal, the resulting number will be an integer that is either rounded up or down.*/
    // Should our stats be data type ‘float’ then? (Sounds too complicated... Fuck it)
    
	//Return new stat values for skill and speed
	//Needs vector
    
	/*See below for some bullshit I attempted with vectors*/
    
    
	return 0;
}

int crew::moraleShift() {
    
    int m = 0;
    
    //if morale is high
    if(activeMorale >= 80){
        m = 1;
    }
    
    //if morale is low
    if (activeMorale <= 30) {
        m = 2;
    }
    
    switch (m) {
        case 1:
            chSkill(5);
            chSpeed(5);
            chFocus(1);
            break;
            
        case 2:
            chSkill(-5);
            chFocus(-1);
            break;
            
        default:
            break;
    }
    return 0;
}

void crew::setg_x(float x)
{
    if(isSwitchingRooms != true){
        g_x = x;
    }
}
float crew::getg_x()
{
    
    return g_x ;
}

void crew::setg_y(float y)
{
    if(isSwitchingRooms != true){
        g_y = y;
    }
}
float crew::getg_y()
{
    
    return g_y;
}
void crew::temperAssign()
{
    //the 4 temperament groups
    //will increment each time a corresponding temperament is used
    
    int Sanguine = 0;
    int Phlegmatic = 0;
    int Choleric = 0;
    int Melancholic = 0;
    
    //social,skill,speed,focus,morale,confidence
    int tsocial =0;
    int tskill = 1;
    int tspeed = 2;
    int tfocus = 3;
    int tmorale = 4;
    int tconfidence = 5;
    
    
    //loop through the temperament vector
    for (int i = 0; i < temperament.size(); i++) {
        
        
        //if index = 0
        if (temperament[i] == 0){
            
            
        }
        //else if index = 1
        else if (temperament[i] == 1){
            tempBonus[tspeed] += 1;
            
            tempBonus[tfocus] -= 1;
            
            Sanguine++;
            
        }
        
        //else if index = 2
        else if (temperament[i] == 2){
            tempBonus[tfocus] += 1;
            tempBonus[tmorale] -= 1;
            
            Sanguine++;
            
        }
        
        
        //else if index = 3
        else if (temperament[i] == 3){
            
            tempBonus[tsocial] += 1;
            tempBonus[tspeed] -= 1;
            
            Sanguine++;
        }
        
        //else if index = 4
        else if (temperament[i] == 4){
            tempBonus[tmorale] += 1;
            tempBonus[tskill] -= 1;
            
            Sanguine++;
            
        }
        
        //else if index = 5
        else if (temperament[i] == 5){
            tempBonus[tmorale] += 1;
            tempBonus[tsocial] -= 1;
            
            Phlegmatic++;
            
        }
        
        
        //else if index = 6
        else if(temperament[i] == 6){
            tempBonus[tskill] += 1;
            tempBonus[tspeed] -= 1;
            
            Phlegmatic++;
            
        }
        
        //else if index = 7
        else if (temperament[i] == 7){
            tempBonus[tfocus] += 1;
            tempBonus[tskill] -= 1;
            
            Phlegmatic++;
            
        }
        
        //else if index = 8
        else if (temperament[i] == 8){
            tempBonus[tsocial] += 1;
            tempBonus[tfocus] -= 1;
            
            Phlegmatic++;
            
            
        }
        
        //else if index = 9
        else if (temperament[i] == 9){
            tempBonus[tspeed] += 1;
            tempBonus[tmorale] -= 1;
            
            Choleric++;
            
        }
        
        
        //else if index = 10
        else if (temperament[i] == 10){
            tempBonus[tskill] += 1;
            tempBonus[tfocus] -= 1;
            
            Choleric++;
            
        }
        
        //else if index = 11
        else if (temperament[i] == 11){
            tempBonus[tconfidence] += 1;
            tempBonus[tsocial] -= 1;
            
            Choleric++;
            
        }
        
        //else if index = 12
        else if (temperament[i] == 12){
            tempBonus[tfocus] += 1;
            tempBonus[tspeed] -= 1;
            
            Choleric++;
            
        }
        
        
        //else if index = 13
        else if (temperament[i] == 13){
            tempBonus[tfocus] += 1;
            tempBonus[tsocial] -= 1;
            
            Melancholic++;
        }
        
        //else if index = 14
        else if (temperament[i] == 14){
            tempBonus[tskill] += 1;
            tempBonus[tspeed] -= 1;
            
            Melancholic++;
            
        }
        
        //else if index = 15
        else if (temperament[i] == 15){
            tempBonus[tspeed] += 1;
            tempBonus[tconfidence] -= 1;
            
            Melancholic++;
            
        }
        
        //else if index = 16
        else if (temperament[i] == 16){
            tempBonus[tconfidence] += 1;
            tempBonus[tmorale] -= 1;
            
            Melancholic++;
            
            
        }
        
        
        //if group1 = 2
        if(Sanguine == 2){
            tempBonus[tsocial] += 1;
        }
        
        //if group2 = 2
        if(Phlegmatic == 2){
            tempBonus[tskill] += 1;
        }
        //if group3 = 2
        if(Choleric == 2){
            tempBonus[tconfidence] += 1;
        }
        //if group4 = 4
        if(Melancholic == 2){
            tempBonus[tfocus] += 1;
        }
    }
}

void crew::chConfidence(int diff)
{
    prodConfidence += diff;
    activeConfidence = prodConfidence + baseConfidence;
}

int crew::getActiveConfidence()
{
    return prodConfidence + baseConfidence;
}

void crew::chFocus(int diff)
{
    prodFocus += diff;
    activeFocus = prodFocus+ focus;
    focusChanges();
}

int crew::getActiveFocus()
{
    return prodFocus+ focus;
}

void crew::chStamina(int diff)
{
    prodStamina += diff;
    activeStamina = prodStamina+ stamina;
}

int crew::getActiveStamina()
{
    return prodStamina+ stamina;
}

void crew::chSpeed(int diff)
{
    prodSpeed += diff;
    activeSpeed = prodSpeed+ speed;
}

int crew::getActiveSpeed()
{
    return activeSpeed;
}

void crew::chSkill(int diff)
{
    prodSkill += diff;
    activeSkill = prodSkill+ skill;
}

int crew::getActiveSkill()
{
    return prodSkill+ skill;
}


void crew::chSocial(int diff)
{
    prodSocial += diff;
    activeSocial = prodSocial+ social;
}

int crew::getActiveSocial()
{
    return prodSocial+ social;
}

void crew::chMorale(int diff)
{
    prodMorale += diff;
    activeMorale = prodMorale+ morale;
}

int crew::getActiveMorale()
{
    return prodMorale+ morale;
}

float crew::getDistance(CCPoint p1, CCPoint p2)
{
    deltaX = p2.x-p1.x;
    deltaY = p2.y-p1.y;
    return fabs(sqrtf(deltaX*deltaX+deltaY*deltaY));
}

void crew::onGrab(CCPoint p)
{
    isGrabbed = true;
    grabStart = p;
    CCTime::gettimeofdayCocos2d(&gTimeStart, NULL);
}

void crew::onRelease()
{
    //get the last point and time
    grabEnded =  tempLocation;
    CCTime::gettimeofdayCocos2d(&gTimeStop, NULL);
    
    //get distance between the points
    float d = getDistance(grabStart, grabEnded);
    
    //get duration
    double duration = CCTime::timersubCocos2d(&gTimeStart, &gTimeStop);
    
    isGrabbed = false;
    cout << "isGrabbed = false" << endl;
    
        
    //decide if flick is true
    
    if (d>=flingMinDistance && duration<=flingMaxDuration)
    {
        cout << "isFlicked = true" << endl;
        //Assign direct vector values
        direction = {deltaX/d, deltaY/d};
        
        //calc speed
        vectorSpeed = 500/240;
        
        isFlicked = true;

    }
    
}

void crew::vectorPush()
{
    g_x = g_x + (direction[0] * vectorSpeed);
    g_y = g_y + (direction[1] * vectorSpeed);
    this->setPosition(ccp(g_x,g_y));
    
}




