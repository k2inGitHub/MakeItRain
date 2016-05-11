//
//  MIRLabel.cpp
//  MakeItRain
//
//  Created by SongYang on 14-5-7.
//
//

#include "MIRLabel.h"

void MIRLabel::addValue()
{
    setValue(_value + 1);
}

void MIRLabel::showEffect()
{
    char name[64] = {0};
    sprintf(name, "number_%d_up.png", _value);
    _up->setSpriteFrame(name);
    
    sprintf(name, "number_%d_down.png", _value);
    _down->setSpriteFrame(name);
    
    auto orbit1 = OrbitCamera::create(0.5,1, 0, 270, 90, 90, 0);
    
    
    //NEW
//    [] don't capure anything
//    
//    [&] capture-by-reference
//    
//    [=] capture-by-value (copy)
    auto callback = CallFuncN::create([&](Ref *sender) {
        
        _oldDown->setSpriteFrame(_down->getSpriteFrame());
        
    });
    _down->runAction(Sequence::create(orbit1, callback, NULL));
}

void MIRLabel::setValue(int value)
{
    if (_value != value) {
        _value = value;
        showEffect();
    }
}

int MIRLabel::getValue()
{
    return _value;
}

bool MIRLabel::init(int value)
{
    if (!Node::init()) {
        return false;
    }
    
    _cascadeOpacityEnabled = true;
    
    _value = value;
    
    _up = Sprite::createWithSpriteFrameName("number_0_up.png");
    _up->setAnchorPoint(Point::ANCHOR_MIDDLE_BOTTOM);
    //    up->setPosition(pos);
    addChild(_up);
    
    
    _down = Sprite::createWithSpriteFrameName("number_0_down.png");
    _down->setAnchorPoint(Point::ANCHOR_MIDDLE_TOP);
    //    down->setPosition(pos);
    addChild(_down);
    
    _oldDown = Sprite::createWithSpriteFrame(_down->getSpriteFrame());
    _oldDown->setAnchorPoint(Point::ANCHOR_MIDDLE_TOP);
    addChild(_oldDown, -1);
    
    
    return true;
}

bool MIRLabel::init()
{
    return init(0);
}