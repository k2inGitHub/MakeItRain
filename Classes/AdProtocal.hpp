//
//  AdProtocal.hpp
//  MakeItRain2
//
//  Created by 宋扬 on 15/12/28.
//
//

#ifndef AdProtocal_hpp
#define AdProtocal_hpp

#include <stdio.h>

class AdProtocal {
    
    
public:
    virtual void setShowBanner(bool value) = 0;
    
    
    virtual void setShowInterstitial(bool value) = 0;
    
    virtual bool getIsInterstitialLoaded() = 0;
};

#endif /* AdProtocal_hpp */
