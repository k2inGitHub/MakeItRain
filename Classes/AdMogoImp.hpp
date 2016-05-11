//
//  AdMogoImp.hpp
//  MakeItRain2
//
//  Created by 宋扬 on 15/12/28.
//
//

#ifndef AdMogoImp_hpp
#define AdMogoImp_hpp

#include <stdio.h>
#include "AdProtocal.hpp"
#include "AdsmogoBanner.h"
#include "AdsMogoInterstitial.h"

class AdMogoImp : AdProtocal{
    
private:
    
    std::string _mogoID;
    
    AdsmogoBannerType _adBannerType;
    
    void RequestInterstitial();
    
public:
    void init(const char* banner_iphone, const char* banner_ipad);
    
    virtual void setShowBanner(bool value) override;
    
    
    virtual void setShowInterstitial(bool value) override;
    
    virtual bool getIsInterstitialLoaded() override;
};

#endif /* AdMogoImp_hpp */
