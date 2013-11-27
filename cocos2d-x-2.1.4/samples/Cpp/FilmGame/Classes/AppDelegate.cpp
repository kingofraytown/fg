//
//  testRoomAppDelegate.cpp
//  testRoom
//
//  Created by Anthony Jones on 3/12/13.
//  Copyright __MyCompanyName__ 2013. All rights reserved.
//

#include "AppDelegate.h"
#include "global.h"
#include "crew.h"
#include "cocos2d.h"
#include "HelloWorldScene.h"
#include "StartPage.h"

USING_NS_CC;

AppDelegate::AppDelegate()
{
    Resource smallResource  =  { cocos2d::CCSizeMake(480, 320), "iphone" };
    Resource mediumResource =  { cocos2d::CCSizeMake(1024, 768), "ipad"   };
    Resource largeResource  =  { cocos2d::CCSizeMake(2048, 1536), "ipadhd" };
    cocos2d::CCSize designResolutionSize = cocos2d::CCSizeMake(480, 320);
}

AppDelegate::~AppDelegate()
{
}

bool AppDelegate::applicationDidFinishLaunching()
{
    
      
    // initialize director
    CCDirector *pDirector = CCDirector::sharedDirector();
    pDirector->setOpenGLView(CCEGLView::sharedOpenGLView());

    // turn on display FPS
    pDirector->setDisplayStats(true);

    // set FPS. the default value is 1.0/60 if you don't call this
    pDirector->setAnimationInterval(1.0 / 60);

    // create a scene. it's an autorelease object
    
    CCScene *pScene = StartPage::scene();

    // run
 
    pDirector->runWithScene(pScene);
    //initCrewMembers();
    CCSize screenSize = CCDirector::sharedDirector()->getWinSize();
    //float adjScaleW = screenSize.width/480;
    sfy = screenSize.height/320;
    sfx = screenSize.width/480;
    
    //crew *crew1 = new crew();
    //crew2 = new crew();
   
 

    
    

    return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground()
{
    CCDirector::sharedDirector()->pause();

    // if you use SimpleAudioEngine, it must be paused
    // SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground()
{
    CCDirector::sharedDirector()->resume();
    
    // if you use SimpleAudioEngine, it must resume here
    // SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
}

