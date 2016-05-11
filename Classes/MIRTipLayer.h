//
//  MIRTipLayer.h
//  MakeItRain
//
//  Created by SongYang on 14-5-12.
//
//

#ifndef __MakeItRain__MIRTipLayer__
#define __MakeItRain__MIRTipLayer__

#include "KTPauseLayer.h"
#include "MIRDelegate.h"



class MIRGetEnvelopLayer : public KTPauseLayer {
    
    
    
public:
    
    enum class Type{
        Normal,
        Super,
    };
    
    CC_SYNTHESIZE(Type, _type, Type);
    
    CC_SYNTHESIZE(int, _toAdd, ToAdd);
    
    virtual bool init(KTPauseLayerDelegate *delegate, Type type);
    
    virtual void onTouchEnded(Touch *touch, Event *unused_event);

    CREATE_FUNC_PARAM2(MIRGetEnvelopLayer, KTPauseLayerDelegate *, delegate, Type, type);
    
};

class MIRBucketTipLayer : public KTPauseLayer {

public :
    
    virtual void onEnterTransitionDidFinish();
    
    virtual bool init(KTPauseLayerDelegate *delegate);
    
    virtual void onTouchEnded(Touch *touch, Event *unused_event);
    
    CREATE_FUNC_PARAM(MIRBucketTipLayer, KTPauseLayerDelegate *, delegate);

};

class MIRTipBaseLayer : public KTPauseLayer
{
protected:
    virtual void removeSelf(float dt);
public :
        
    CC_SYNTHESIZE(bool, _removeSelf, RemoveSelf);
    
    virtual Sequence *moveSeq();
    
    virtual void onEnter();
    
    MIRTipBaseLayer(){_removeSelf = true;};
};


class MIRTipLayer : public MIRTipBaseLayer{
    
    
public:
    
    
//    void removeSelf(float dt);
    
    virtual void onEnterTransitionDidFinish();
    
    virtual void onEnter();
    
    CC_SYNTHESIZE(std::string, _file, File);
    
    CC_SYNTHESIZE(std::string, _content, Content);
    
    
    CREATE_FUNC(MIRTipLayer);
};


class MIRResetTipLayer : public MIRTipBaseLayer {
    
    Sequence *moveSeq();

    CC_SYNTHESIZE(MIRDelegate *, _mirDelegate, MIRDelegate);
    
    virtual void onEnter();
    
    virtual bool init(KTPauseLayerDelegate *delegate);
    
    CREATE_FUNC_PARAM(MIRResetTipLayer, KTPauseLayerDelegate *, delegate);
};

#endif /* defined(__MakeItRain__MIRTipLayer__) */
