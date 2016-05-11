#include "AppDelegate.h"
#include "HelloWorldScene.h"
#include "KTUtils.h"
#include "MIRGameLayer.h"
#include "MIRDynamicData.h"
#include<iostream>
#include<iomanip>
#include "AdManager.hpp"
#include "MobClickCpp.h"
#include "AdConfig.h"

USING_NS_CC;

AppDelegate::AppDelegate() {

}

AppDelegate::~AppDelegate() 
{
}

//if you want a different context,just modify the value of glContextAttrs
//it will takes effect on all platforms
void AppDelegate::initGLContextAttrs()
{
    //set OpenGL context attributions,now can only set six attributions:
    //red,green,blue,alpha,depth,stencil
    GLContextAttrs glContextAttrs = {8, 8, 8, 8, 24, 8};

    GLView::setGLContextAttrs(glContextAttrs);
}

bool AppDelegate::applicationDidFinishLaunching() {
    // initialize director
    auto director = Director::getInstance();
    auto glview = director->getOpenGLView();
    if(!glview) {
        glview = GLViewImpl::createWithRect("MakeItRain2", Rect(0, 0, 640, 960));
        director->setOpenGLView(glview);
    }

    director->getOpenGLView()->setDesignResolutionSize(640, 960, ResolutionPolicy::FIXED_WIDTH);

    // turn on display FPS
    director->setDisplayStats(false);

    // set FPS. the default value is 1.0/60 if you don't call this
    director->setAnimationInterval(1.0 / 60);

    FileUtils::getInstance()->addSearchPath("res/resources-iphonehd");

    
    MOBCLICKCPP_START_WITH_APPKEY(UM_ID);
    
    umeng::MobClickCpp::updateOnlineConfig();
    
    srand( (unsigned)time( NULL) );
    
    // create a scene. it's an autorelease object
    auto scene = MIRGameLayer::scene();

    // run
    director->runWithScene(scene);
    
    AdManager::getInstance()->setShowBanner(true);

    
    return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground() {
    Director::getInstance()->stopAnimation();

    // if you use SimpleAudioEngine, it must be pause
    SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
    MIRDynamicData *data = MIRDynamicData::getInstance();
    
    data->localNotification();
    
    umeng::MobClickCpp::applicationDidEnterBackground();
    
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {
    Director::getInstance()->startAnimation();

    // if you use SimpleAudioEngine, it must resume here
    SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
    
    //update 版本三 加本地通知
    MIRDynamicData *data = MIRDynamicData::getInstance();
    
    data->bucketAutoAdd();
    
    umeng::MobClickCpp::applicationWillEnterForeground();
}
