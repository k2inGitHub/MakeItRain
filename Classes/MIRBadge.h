//
//  MIRBadge.h
//  MakeItRain
//
//  Created by SongYang on 14-5-7.
//
//

#ifndef __MakeItRain__MIRBadge__
#define __MakeItRain__MIRBadge__

#include "cocos2d.h"
#include "KTUtils.h"
USING_NS_CC;

class MIRBadge : public Node {
    
public:
    
    void setValue(int v);
    
    int getValue();
    
    Sprite *_bg;
    
    Label *_label;
    
    bool init(int value);
    
    CREATE_FUNC_PARAM(MIRBadge, int, value);
};

#endif /* defined(__MakeItRain__MIRBadge__) */
