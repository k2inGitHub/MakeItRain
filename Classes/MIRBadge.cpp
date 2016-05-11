//
//  MIRBadge.cpp
//  MakeItRain
//
//  Created by SongYang on 14-5-7.
//
//

#include "MIRBadge.h"
#include "MIRConfig.h"
#include "KTUtils.h"

bool MIRBadge::init(int value)
{
    if (!Node::init()) {
        return false;
    }
    
    char file[64] = {0};
    sprintf(file, "level_indicator_%d.png", MIN(15, value));
    _bg = Sprite::createWithSpriteFrameName(file);
    addChild(_bg);
    
    _label = Label::createWithTTF(KTUtils::stringFormat("%d", value), TITLE_FONT, 32);
    addChild(_label);
    
    return true;
}

void MIRBadge::setValue(int v)
{
    if (getValue() != v) {
        char file[64] = {0};
        sprintf(file, "level_indicator_%d.png", MIN(14, v));
        _bg->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(file));
        _label->setString(KTUtils::stringFormat("%d", v));
    }
}

int MIRBadge::getValue()
{
    return atoi(_label->getString().c_str());
}