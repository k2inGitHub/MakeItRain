//
//  AdUnityImp.cpp
//  MakeItRain2
//
//  Created by 宋扬 on 15/12/29.
//
//

#include "AdUnityImp.hpp"
#import <UnityAds/UnityAds.h>
#import <UIKit/UIKit.h>
#import "UnityAdsUnityWrapper.h"
#include "MIRDynamicData.h"
#include "MIRGameLayer.h"

static AdUnityImp* _instance = nullptr;

void AdUnityImp::onFetchCompleted(){

    isInitialized = true;
    CCLOG("onFetchCompleted");
}

void AdUnityImp::onFetchFailed(){
    CCLOG("onFetchFailed");
}

void AdUnityImp::onHide(){
    isShowing = false;
    deliverCallback(ShowResult::Skipped);
}

void AdUnityImp::onShow(){
CCLOG("onShow");
}

void AdUnityImp::onVideoStarted(){
CCLOG("onVideoStarted");
}

 void AdUnityImp::onVideoComplete(const char* rewardItemKey, bool skipped)
{
    CCLOG("onVideoComplete skipped = %d" , skipped);
    if (skipped) {
        //skipped
        deliverCallback(ShowResult::Skipped);
    } else {
        //success
        deliverCallback(ShowResult::Finished);
    }
}

void AdUnityImp::show(){

    
    if (!isInitialized || isShowing) {
        deliverCallback (ShowResult::Failed);
        return;
    }
    
    UnityAdsShow("", "", "");
}

void AdUnityImp::deliverCallback(ShowResult result){
    isShowing = false;
    
    if (result == ShowResult::Finished) {
        //reward
        MIRGameLayer* game = MIRDynamicData::getInstance()->getGameLayer();
        game->addGold(1000);
    }
}

void AdUnityImp::init(const char* appID, bool testMode){
    if (!_instance) {
        _instance = this;
    }
    UnityAdsInit(appID, testMode, false, "", "");
}

extern "C"{
    AdUnityImp* GetUnityImp(){
        return _instance;
    }
}