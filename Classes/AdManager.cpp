//
//  AdManager.cpp
//  MakeItRain2
//
//  Created by 宋扬 on 15/12/28.
//
//

#include "AdManager.hpp"
#include "AdMogoImp.hpp"
#include "AdConfig.h"

static AdManager *_instance;

void AdManager::init(){

    _adMogo = new AdMogoImp();
    _adMogo->init(MogoIDiPhone, MogoIDiPad);
    
    _adUnity = new AdUnityImp();
    _adUnity->init(UnityID, false);
}

AdManager* AdManager::getInstance(){
    if (_instance == nullptr) {
        _instance = new AdManager();
        _instance->init();
    }
    return _instance;
}

void AdManager::setShowBanner(bool value){

    _adMogo->setShowBanner(value);
}

void AdManager::SetShowVideo(bool value)
{
    if (value) {
        _adUnity->show();
    }
}

void AdManager::setShowInterstitial(bool value){

    _adMogo->setShowInterstitial(value);
}