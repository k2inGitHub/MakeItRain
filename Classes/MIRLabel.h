//
//  MIRLabel.h
//  MakeItRain
//
//  Created by SongYang on 14-5-7.
//
//

#ifndef __MakeItRain__MIRLabel__
#define __MakeItRain__MIRLabel__

#include "cocos2d.h"
#include "KTUtils.h"
USING_NS_CC;

class MIRLabel : public Node {
    
public:
    
    void showEffect();
    
    void addValue();
    
    CC_PROPERTY(int, _value, Value);
    
    Sprite *_up;
    
    Sprite *_down;
    
    Sprite *_oldDown;
    
    virtual bool init();
    
    CREATE_FUNC(MIRLabel);
    
    virtual bool init(int value);
    
    CREATE_FUNC_PARAM(MIRLabel, int , value);
};

#endif /* defined(__MakeItRain__MIRLabel__) */
