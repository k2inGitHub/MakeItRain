//
//  MIRBucketLayer.h
//  MakeItRain
//
//  Created by SongYang on 14-5-8.
//
//

#ifndef __MakeItRain__MIRBucketLayer__
#define __MakeItRain__MIRBucketLayer__

#include "KTPauseLayer.h"
#include "MIRDynamicData.h"

class MIRBucketLayer : public KTPauseLayer {
    
public:
    
    Sprite *_bucketEllipse;
    
    Sprite *_bucketFill;
    
    /// max 1.0 min 0.0
    void setBucketHeight(float scale);
    
    MIRDynamicData *data;
    
    CC_SYNTHESIZE(Label *, _flowLabel, FlowLabel);
    
    CC_SYNTHESIZE(Label *, _capacityLabel, CapacityLabel);
    
    CC_SYNTHESIZE(Label *, _totalCapacityLabel, TotalCapacityLabel);
    
    virtual bool init(KTPauseLayerDelegate *delegate);
    
    CREATE_FUNC_PARAM(MIRBucketLayer, KTPauseLayerDelegate *, delegate);
};

#endif /* defined(__MakeItRain__MIRBucketLayer__) */
