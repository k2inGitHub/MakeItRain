//
//  MIRTipLayer.cpp
//  MakeItRain
//
//  Created by SongYang on 14-5-12.
//
//

#include "MIRTipLayer.h"
#include "MIRGameLayer.h"
#include "MobClickCpp.h"

bool MIRGetEnvelopLayer::init(KTPauseLayerDelegate *delegate, Type type){
    if (!KTPauseLayer::init(delegate)) {
        return  false;
    }
    
    _type = type;
    
    auto data = MIRDynamicData::getInstance();
    auto game = data->getGameLayer();
    
    auto la = LayerColor::create(Color4B(0, 0, 0, 127));
    addChild(la, -1);
    
    Sprite *sp = Sprite::create("Open.png");
    sp->setPosition(VisibleRect::center());
    addChild(sp);
    
    int roll = random(0, 2);
    if (roll == 0) {
        _toAdd = (game->getAutoAddGold() + 1) * 60;
    } else if (roll == 1) {
        _toAdd = (game->getAutoAddGold() + 1) * 80;
    } else {
        _toAdd = (game->getAutoAddGold() + 1) * 100;
    }
    
    if (_type == Type::Super) {
        _toAdd *= 10;
        
        auto label = Label::createWithTTF(KTUtils::stringFormat("获得 %d", _toAdd), TITLE_FONT, 64);
        label->setPosition(VisibleRect::center() + Vec2(0, 40));
        addChild(label, 1);
        
        if (data->getShowSuperEnvelopText()) {
            auto label2 = Label::createWithTTF(data->getSuperEnvelopeText(), TITLE_FONT, 36);
            label2->setPosition(VisibleRect::center() + Vec2(0, -40));
            label2->setTextColor(Color4B::YELLOW);
            
            addChild(label2, 1);
        }
        umeng::MobClickCpp::event("SuperEnvelopeNum");
    } else {
        umeng::MobClickCpp::event("NormalEnvelopeNum");
    }
    
    auto label = Label::createWithTTF(KTUtils::stringFormat("获得 %d", _toAdd), TITLE_FONT, 64);
    label->setPosition(VisibleRect::center() + Vec2(0, 40));
    addChild(label, 1);
    
   
    
    return true;
}

void MIRGetEnvelopLayer::onTouchEnded(Touch *touch, Event *unused_event)
{
    doCancel();
}

void MIRBucketTipLayer::onEnterTransitionDidFinish()
{
    this->playEffect(SOUND_MSG);

}

bool MIRBucketTipLayer::init(KTPauseLayerDelegate *delegate)
{
    if (!KTPauseLayer::init(delegate)) {
        return false;
    }

    auto la = LayerColor::create(Color4B(0, 0, 0, 127));
    addChild(la, -1);
    
    Sprite *sp = Sprite::createWithSpriteFrameName("icon_political_1.png");
    sp->setPosition(VisibleRect::center() + Point(0, 60) * _scale);
    addChild(sp);
    
    {
        TTFConfig ttfConfig(TIP_FONT, 50 * _scale, GlyphCollection::DYNAMIC,nullptr,true);
//        ttfConfig.outlineSize = 5;
        
        auto label = Label::createWithTTF(ttfConfig, "恭喜你，获得了水桶!", TextHAlignment::CENTER, winSize.width);
        label->setAnchorPoint(Point::ANCHOR_MIDDLE_TOP);
        label->setPosition(VisibleRect::center() + Point(0, 10) * _scale);
        addChild(label);
//        label->setTextColor(Color4B::GREEN);
        label->enableOutline(Color4B::WHITE);
    }
    
    {
        TTFConfig ttfConfig(TIP_FONT, 45, GlyphCollection::DYNAMIC,nullptr,true);
//        ttfConfig.outlineSize = 5;
        
        auto label = Label::createWithTTF(ttfConfig, "关闭游戏，你的水桶依然可以增加收益!", TextHAlignment::CENTER, winSize.width);
        label->setAnchorPoint(Point::ANCHOR_MIDDLE_TOP);
        label->setPosition(VisibleRect::center() + Point(0, -120) * _scale);
        addChild(label);
//        label->setTextColor(Color4B::RED);
        label->enableOutline(Color4B::WHITE);
    }
    getEventDispatcher()->setEnabled(false);
    
    auto ac = DelayTime::create(2.0);
    
    auto ac2 = CallFuncN::create([=](Ref *){
        
        this->getEventDispatcher()->setEnabled(true);
    
    });
    
    this->runAction(Sequence::create(ac, ac2, NULL));
    
    return true;
}

void MIRBucketTipLayer::onTouchEnded(Touch *touch, Event *unused_event)
{
    doCancel();
}

void MIRTipBaseLayer::onEnter()
{
    KTPauseLayer::onEnter();

    auto la = LayerColor::create(Color4B(0, 0, 0, 127));
    addChild(la, -1);
    
    if (_removeSelf) {
        scheduleOnce(schedule_selector(MIRTipBaseLayer::removeSelf), 2.0);
    }
}

void MIRTipBaseLayer::removeSelf(float dt)
{
    removeFromParent();
}

 Sequence *MIRTipBaseLayer::moveSeq()
{
    auto ac = MoveBy::create(0.5, Point(- winSize.width, 0));
    auto ac1 = DelayTime::create(1.0);
    auto ac2 = ac->clone();
    
    return Sequence::create(ac, ac1, ac2, NULL);
}

void MIRTipLayer::onEnterTransitionDidFinish()
{
   this->playEffect(SOUND_MSG);
}

void MIRTipLayer::onEnter()
{
    MIRTipBaseLayer::onEnter();
    
    
    std::string test;
    CCLOG("%lu", test.size());
    
    Point labelPos = VisibleRect::center() + Point(winSize.width, -30);
    
    if (_file.size()!=0) {
        Sprite *sp = NULL;
        if (!FileUtils::getInstance()->isFileExist(_file)) {
            sp = Sprite::createWithSpriteFrameName(_file);
        } else {
            sp = Sprite::create(_file);
        }
        
        sp->setPosition(VisibleRect::center() + Point(winSize.width, 60 * _scale));
        addChild(sp);
        sp->runAction(this->moveSeq());
    } else {
        labelPos = VisibleRect::center() + Point(winSize.width, 10 * _scale);
    }
    
    TTFConfig ttfConfig(TIP_FONT, 50 * _scale, GlyphCollection::DYNAMIC,nullptr,true);
//    ttfConfig.outlineSize = 5;
    
    auto label = Label::createWithTTF(ttfConfig, _content, TextHAlignment::CENTER, winSize.width);
    label->setAnchorPoint(Point::ANCHOR_MIDDLE_TOP);
    label->setPosition(labelPos);
    addChild(label);
//    label->setTextColor(Color4B::GREEN);
    label->enableOutline(Color4B::WHITE);
    
    label->runAction(this->moveSeq());
}

Sequence *MIRResetTipLayer::moveSeq()
{
    auto ac = MoveBy::create(0.5, Point(- winSize.width, 0));
    auto ac1 = DelayTime::create(1.0);
    return Sequence::create(ac, ac1, NULL);
}

bool MIRResetTipLayer::init(KTPauseLayerDelegate *delegate)
{
    if (!MIRTipBaseLayer::init()) {
        return false;
    }

    setDelegate(delegate);
    
    _mirDelegate = NULL;
    
    setRemoveSelf(false);
    
    return true;
}

void MIRResetTipLayer::onEnter()
{
    MIRTipBaseLayer::onEnter();
    
    auto label = Label::createWithTTF("重新开始游戏(所有数据将重置为0)?", TITLE_FONT, 42 * _scale);
    label->setWidth(winSize.width);
    label->setAlignment(TextHAlignment::CENTER);
    label->setPosition(VisibleRect::center() + Point(winSize.width, 160 * _scale));
    addChild(label);
    
    auto label2 = Label::createWithTTF("(本次操作无法撤消!)", TITLE_FONT, 30 * _scale);
    label2->setPosition(VisibleRect::center() + Point(winSize.width, 20 * _scale));
    addChild(label2);
    
    auto reset = MenuItemImage::create("button_green.png", "button_green.png", [=](Ref *sender){
    
        if (_mirDelegate) {
            _mirDelegate->resetAll();
        }
        doCancel();
    });
    reset->setPosition(VisibleRect::center() + Point(winSize.width, - 90 * _scale));
    auto cancel = MenuItemImage::create("button_red.png", "button_red.png", [=](Ref *sender){
    
        doCancel();
    });
    
    cancel->setPosition(VisibleRect::center() + Point(winSize.width, - 210 * _scale));
    
    auto menu = Menu::create(reset, cancel, NULL);
    menu->setAnchorPoint(Point::ANCHOR_BOTTOM_LEFT);
    menu->setPosition(Point::ZERO);
    addChild(menu);
    
    
    auto l1 = Label::createWithTTF("确定", TITLE_FONT, 42 * _scale);
    l1->setPosition(reset->getPosition());
    addChild(l1);
    
    auto l2 = Label::createWithTTF("取消", TITLE_FONT, 42 * _scale);
    l2->setPosition(cancel->getPosition());
    addChild(l2);
    
    l1->runAction(moveSeq());
    l2->runAction(moveSeq());
    
    label->runAction(moveSeq());
    label2->runAction(moveSeq());
    reset->runAction(moveSeq());
    cancel->runAction(moveSeq());
    
}



