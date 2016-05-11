//
//  AdManager.hpp
//  MakeItRain2
//
//  Created by 宋扬 on 15/12/28.
//
//

#ifndef AdManager_hpp
#define AdManager_hpp

#include <stdio.h>
#include "AdMogoImp.hpp"
#include "AdUnityImp.hpp"

class AdManager {
    
private:
    AdMogoImp *_adMogo;
    
    void init();
    
public:
    
    AdUnityImp *_adUnity;
    
    static AdManager* getInstance();
    
    void setShowBanner(bool value);
    
    void setShowInterstitial(bool value);
    
    void SetShowVideo(bool value);
};

#endif /* AdManager_hpp */


