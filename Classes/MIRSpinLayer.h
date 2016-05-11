//
//  MIRSpinLayer.h
//  MakeItRain
//
//  Created by SongYang on 14-5-9.
//
//

#ifndef __MakeItRain__MIRSpinLayer__
#define __MakeItRain__MIRSpinLayer__

#include "KTPauseLayer.h"
#include "MIRDelegate.h"


class MIRSpinLayer : public KTPauseLayer, MIRDelegate {
    
public:
    
    Label *_bribeBadge;
    
    MIRSpinType _result;
    
    Menu *_menu;
    
    void itemClick(Ref *sender);
    
    Label *_payLabel;
    
    Label *_bribeLabel;
    
    CC_SYNTHESIZE(MIRDelegate *, _mirDelegate, MIRDelegate);
    
    Sprite *_spin;
    
    void updateBribe(Ref *sender);
    
    virtual void onEnterTransitionDidFinish();
//    virtual void onEnterTransitionDidFinish();
    
    virtual bool onTouchBegan(Touch *touch, Event *unused_event);
    virtual void onTouchMoved(Touch *touch, Event *unused_event);
    virtual void onTouchEnded(Touch *touch, Event *unused_event);
    virtual void onTouchCancelled(Touch *touch, Event *unused_event);
    
    virtual bool init(KTPauseLayerDelegate *delegate);
    
    CREATE_FUNC_PARAM(MIRSpinLayer, KTPauseLayerDelegate *, delegate);
    
    MIRSpinLayer();
    
    ~MIRSpinLayer();
};

#endif /* defined(__MakeItRain__MIRSpinLayer__) */
