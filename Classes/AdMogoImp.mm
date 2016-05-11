//
//  AdMogoImp.cpp
//  MakeItRain2
//
//  Created by 宋扬 on 15/12/28.
//
//


#import <UIKit/UIKit.h>
#import "Reachability.h"
#include "AdMogoImp.hpp"


void AdMogoImp::init(const char* banner_iphone, const char* banner_ipad)
{
    bool isPad = [[[UIDevice currentDevice] model] rangeOfString:@"iPad"].length > 0;
    if ( isPad ) {
         _mogoID = banner_ipad;
        _adBannerType = AdsmogoBannerTypeMediumBanner;
    } else {
        _mogoID = banner_iphone;
        _adBannerType = AdsmogoBannerTypeNormalBanner;
    }
//    cocos2d::CCString
//    char mogoid []= strdup(banner_iphone);//"e959054ecf584d28ae5c7bddf489d0a9";
//    auto mogoid = const_cast<char *>(_mogoID.c_str());
    AdsmogoBanner::sharedBanner()->createBanner(_mogoID.c_str(), _adBannerType,AdMoGoPointTypeTop_middle, false);
    AdsMogoInterstitial::sharedInterstitial()->loadInterstitial(_mogoID.c_str(), AdsMogoInterstitialTypeFullScreen, false, false);
}

void AdMogoImp::setShowBanner(bool value){
    if (value) {
        //char mogoid []="e959054ecf584d28ae5c7bddf489d0a9";
//        char idStr[] = "e959054ecf584d28ae5c7bddf489d0a9";//const_cast<char *>(_mogoID.c_str());
//       AdsmogoBanner::sharedBanner()->createBanner(idStr, AdsmogoBannerTypeNormalBanner, AdMoGoPointTypeTop_middle,false);
        AdsmogoBanner::sharedBanner()->showBanner();
    } else {
        AdsmogoBanner::sharedBanner()->hidenBanner();
    }
}

void AdMogoImp::setShowInterstitial(bool value){

    if (value) {
//        char str[] = "bb0bf739cd8f4bbabb74bbaa9d2768bf";
       
        AdsMogoInterstitial::sharedInterstitial()->showInterstitial();
    } else {
        AdsMogoInterstitial::sharedInterstitial()->hideInterstitial();
    }
}

void AdMogoImp::RequestInterstitial()
{
//    char  mogoid[]="acf550905a7a474394db7c93e8ef6e19";
//    AdsMogoInterstitial::sharedInterstitial()->loadInterstitial(mogoid,AdsMogoInterstitialTypeFullScreen,false,false);
    char idStr[64] = "bb0bf739cd8f4bbabb74bbaa9d2768bf";//const_cast<char *>(_mogoID.c_str());
    AdsMogoInterstitial::sharedInterstitial()->loadInterstitial( idStr, AdsMogoInterstitialTypeFullScreen, false, false);
}

bool AdMogoImp::getIsInterstitialLoaded() {
    Reachability* reachability = [Reachability reachabilityWithHostName:@"www.apple.com"];
    return [reachability currentReachabilityStatus] != NotReachable;
}