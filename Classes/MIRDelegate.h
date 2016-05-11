//
//  MIRDelegate.h
//  MakeItRain
//
//  Created by SongYang on 14-5-13.
//
//

#ifndef __MakeItRain__MIRDelegate__
#define __MakeItRain__MIRDelegate__

#include "MIRModel.h"
#include "MIRConfig.h"

class MIRDelegate
{
public:
    
    virtual void resetAll(){};
    
    virtual void setItemTouched(int index, Layer *setLayer){};
        
    virtual bool itemCanLevelUp(MIRModel *m){return false;};
    
    virtual void spinResult(MIRSpinType res, Layer *spinLayer){};
};

#endif /* defined(__MakeItRain__MIRDelegate__) */
