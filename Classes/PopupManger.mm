//
//  PopupManger.cpp
//  MakeItRain2
//
//  Created by 宋扬 on 15/12/28.
//
//

#include "PopupManger.hpp"
#include "AdConfig.h"
#import "KTAlertView.h"
#include "MIRGameLayer.h"
#include "MIRDynamicData.h"
#include "KTUtils.h"
#include "AdManager.hpp"
#include "MIRDynamicData.h"


static PopupManager *_instance = nullptr;

void PopupManager::onAlertViewClick(int tag, int btnIdx){
    if (tag == 10 && btnIdx == 1) {
        //rate
        
        char buf[256] = {0};
        sprintf(buf,"itms-apps://itunes.apple.com/WebObjects/MZStore.woa/wa/viewContentsUserReviews?type=Purple+Software&id=%s",AppleID);
        
        [[UIApplication sharedApplication] openURL:[NSURL URLWithString:[NSString stringWithUTF8String:buf]]];
        
    }
    if(tag == 20){
    
        AdManager::getInstance()->setShowInterstitial(true);
    }
    if (tag == 30 && btnIdx == 1) {
        
        [[UIApplication sharedApplication] openURL:[NSURL URLWithString:[NSString stringWithUTF8String:MIRDynamicData::getInstance()->getRecURL()]]];
    }
}

void PopupManager::showReccomand()
{
    
    [[KTAlertView sharedInstance] showAlertView:@"" tag:30 message:[NSString stringWithUTF8String:MIRDynamicData::getInstance()->getRecText()] okTitle:@"欣然前往" noTitle:@"残忍拒绝"];
}

void PopupManager::showRate(){
    [[KTAlertView sharedInstance] showAlertView:@"" tag:10 message:@"五星好评，即可兑换" okTitle:@"欣然前往" noTitle:@"残忍拒绝"];
}

void PopupManager::showMoney()
{
    MIRGameLayer* game = MIRDynamicData::getInstance()->getGameLayer();
    float value = game->getGold() * 0.000001f;
    auto str = KTUtils::stringFormat("当前金额%.2lf元，金额过少，不足以兑换，请继续收集",value);
    
    KTAlertView* alertView =[KTAlertView sharedInstance];
    [alertView showAlertView:nil tag:20 message:[NSString stringWithUTF8String:str.c_str()] okTitle:@"确定" noTitle:@""];
    
}

PopupManager* PopupManager::getInstace(){
    if (!_instance) {
        _instance = new PopupManager();
    }
    return _instance;
}