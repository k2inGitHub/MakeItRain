//
//  MIRSpinLayer.cpp
//  MakeItRain
//
//  Created by SongYang on 14-5-9.
//
//



#include "MIRSpinLayer.h"
#include "MIRGameLayer.h"
//#include "Business.h"

#define TAG_INDICATOR   16

#define TAG_SPINTEXT    32

#define TAG_PAY         10

#define TAG_BRIBE       20

const static MIRSpinType SpinTypes[] = {
    
    MIRSpinType::GUILTY,
    MIRSpinType::SEIZURE,
    MIRSpinType::NOT_GUILTY,
    MIRSpinType::MIRACLE,
    MIRSpinType::GUILTY,
    MIRSpinType::SEIZURE,
    MIRSpinType::NOT_GUILTY,
    MIRSpinType::PLEA,
};


const static float spinXX[5] = {

    0.5,    //0.5,    //0.5
    
    0.3,    //0.2,
    
    0.2,    //0.1,
    
    0.05,   //0.15,
    
    0,  //0.05,
};

const static MIRSpinType SpinTargets[5] = {

    
    MIRSpinType::GUILTY,
    MIRSpinType::NOT_GUILTY,
    MIRSpinType::PLEA,
    MIRSpinType::SEIZURE,
    MIRSpinType::MIRACLE,
};



 void MIRSpinLayer::onEnterTransitionDidFinish()
{

    this->playEffect(SOUND_SIREN);

}

void MIRSpinLayer::updateBribe(Ref *sender)
{
    if (_bribeBadge) {
        _bribeBadge->setString(KTUtils::stringFormat("x%d", data->getBribe()));
    }
}

void MIRSpinLayer::itemClick(Ref *sender)
{
    MenuItem *item = (MenuItem *)sender;
    this->playEffect(SOUND_BUTTON);
    switch (item->getTag()) {
        case TAG_PAY:{
            
            _mirDelegate->spinResult(_result, this);
            
            
        }break;
        case TAG_BRIBE:{
        
            if (data->getBribe() > 0) {
                data->addBribe(-1);
                updateBribe(NULL);
                doCancel();
            } else {
                //goto 内购界面
                ((MIRGameLayer *)_mirDelegate)->purchase(3);
            }
        }break;
        default:
            break;
    }
    
    
    
}

bool MIRSpinLayer::onTouchBegan(Touch *touch, Event *unused_event)
{
    if (_result != MIRSpinType::EMPTY) {
        return false;
    }
    return true;
}

 void MIRSpinLayer::onTouchMoved(Touch *touch, Event *unused_event)
{
    if (_result != MIRSpinType::EMPTY) {
        return;
    }
    Point delt = touch->getDelta();
    
    if (_spin->getActionByTag(123)) {
        return;
    }
    
    if (delt.x > 0 && delt.y < 0) {
        //rotate
        //test
        
        //goto 概率
//        float roll = CCRANDOM_0_1();
//        MIRSpinType target;
//        for (int i = 4 ; i >= 0; i--) {
//            if (roll > spinXX[i]) {
//                target = SpinTargets[i];
//            }
//        }
        
        this->playEffect(SOUND_WHEEL);

        auto ac = RotateBy::create(2.0, 360 * 4 + int(CCRANDOM_0_1() * 8) * 45 );
        auto ac1 = EaseElasticOut::create(EaseOut::create(ac, 2), 0.2);
        auto callback = CallFuncN::create([=](Ref *sender){
        
            
            auto sp = (Sprite *)sender;
            
            int rotation = (int)sp->getRotation() % 360;
            
            for (int i = 7; i >= 0; i--) {
                if (rotation >= i * 45) {
                    _result = SpinTypes[i];
                    
                    break;
                }
            }
            //test
//            _result = MIRSpinType::NOT_GUILTY;
//            if (_mirDelegate) {
//                _mirDelegate->spinResult(res, this);
//            }
            
            _spin->setVisible(false);
            this->getChildByTag(TAG_INDICATOR)->setVisible(false);
            this->getChildByTag(TAG_SPINTEXT)->setVisible(false);
            
            const char* file;
            const char* title;
            
            
            MIRGameLayer *gl = (MIRGameLayer *) _mirDelegate;
            
            switch (_result) {
                case MIRSpinType::GUILTY:{
                    //扣除当前现金的50%，每秒增速减少20%
                    file = "gavel.png";
                    title = "有罪!";
                    
                    auto itemA = MenuItemImage::create("button_red.png", "button_red.png", CC_CALLBACK_1(MIRSpinLayer::itemClick, this));
                    itemA->setTag(TAG_PAY);
                    itemA->setPosition(VisibleRect::center() + Point(0, -100) * _scale);
                    _menu->addChild(itemA);
                    
                    auto itemB = MenuItemImage::create("button_green.png", "button_green.png", CC_CALLBACK_1(MIRSpinLayer::itemClick, this));
                    itemB->setTag(TAG_BRIBE);
                    itemB->setPosition(VisibleRect::center() + Point(0, -200) * _scale);
                    _menu->addChild(itemB);
                    
                    
                    
                    auto labelA = Label::createWithTTF("没收 ￥" + KTUtils::MIRString(gl->getGold()*0.5)  + " 并且减少￥" + KTUtils::MIRString(gl->getAutoAddGold()*0.2) + "/秒", TITLE_FONT, 24 * _scale);
                    labelA->setMaxLineWidth(itemA->getContentSize().width);
                    labelA->setPosition(itemA->getPosition());
                    labelA->setAlignment(TextHAlignment::CENTER);
                    addChild(labelA, _menu->getLocalZOrder() + 1);
                    
                    const char * ctnt;
                    if (data->getBribe()>0) {
                        ctnt = "使用免罪卡";
                    } else {
                        ctnt = "购买5张免罪卡";
                    }
                    auto labelB = Label::createWithTTF(ctnt, TITLE_FONT, 30 * _scale);
                    labelB->setMaxLineWidth(itemB->getContentSize().width);
                    labelB->setPosition(itemB->getPosition());
                    addChild(labelB, _menu->getLocalZOrder() + 1);
                    
                }break;
                case MIRSpinType::NOT_GUILTY:{
                    //无效果
                    file = "fbi_earn.png";
                    title = "无罪!";
                
                    
                    auto item = MenuItemImage::create("button_green.png", "button_green.png", CC_CALLBACK_1(MIRSpinLayer::itemClick, this));
                    item->setPosition(VisibleRect::center() + Point(0, -200) * _scale);
                    item->setTag(TAG_PAY);
                    _menu->addChild(item);
                    
                    auto ok = Label::createWithTTF("确定", TITLE_FONT, 36 * _scale);
                    ok->setPosition(item->getPosition());
                    addChild(ok, _menu->getLocalZOrder() + 1);
                    
//                    auto labelA = Label::createWithTTF("Congratulations, you are free and you win 50% of your cash !", TITLE_FONT, 24);
//                    labelA->setMaxLineWidth(item->getContentSize().width);
//                    labelA->setPosition(item->getPosition() + Point(0, 120));
//                    labelA->setAlignment(TextHAlignment::CENTER);
//                    addChild(labelA, _menu->getLocalZOrder() + 1);
                    
                    
                }break;
                case MIRSpinType::PLEA:{
                    //扣除当前现金的25%
                    file = "plea.png";
                    title = "处罚!";
                    
                    auto itemA = MenuItemImage::create("button_red.png", "button_red.png", CC_CALLBACK_1(MIRSpinLayer::itemClick, this));
                    itemA->setTag(TAG_PAY);
                    itemA->setPosition(VisibleRect::center() + Point(0, -100) * _scale);
                    _menu->addChild(itemA);
                    
                    auto itemB = MenuItemImage::create("button_green.png", "button_green.png", CC_CALLBACK_1(MIRSpinLayer::itemClick, this));
                    itemB->setTag(TAG_BRIBE);
                    itemB->setPosition(VisibleRect::center() + Point(0, -200) * _scale);
                    _menu->addChild(itemB);
                    
                    
                    auto labelA = Label::createWithTTF("没收 ￥" + KTUtils::MIRString(gl->getGold()*0.25), TITLE_FONT, 30 * _scale);
                    labelA->setMaxLineWidth(itemA->getContentSize().width);
                    labelA->setPosition(itemA->getPosition());
                    labelA->setAlignment(TextHAlignment::CENTER);
                    addChild(labelA, _menu->getLocalZOrder() + 1);
                    
                    const char * ctnt;
                    if (data->getBribe()>0) {
                        ctnt = "使用免罪卡";
                    } else {
                        ctnt = "购买5张免罪卡";
                    }
                    auto labelB = Label::createWithTTF(ctnt, TITLE_FONT, 30 * _scale);
                    labelB->setMaxLineWidth(itemB->getContentSize().width);
                    labelB->setPosition(itemB->getPosition());
                    addChild(labelB, _menu->getLocalZOrder() + 1);
                    
                }break;
                case MIRSpinType::SEIZURE:{
                    //扣除当前现金的50%，每秒增速减少10%
                    file = "seizure.png";
                    title = "扣押!";
                    
                    auto itemA = MenuItemImage::create("button_red.png", "button_red.png", CC_CALLBACK_1(MIRSpinLayer::itemClick, this));
                    itemA->setTag(10);
                    itemA->setPosition(VisibleRect::center() + Point(0, -100) * _scale);
                    _menu->addChild(itemA);
                    
                    auto itemB = MenuItemImage::create("button_green.png", "button_green.png", CC_CALLBACK_1(MIRSpinLayer::itemClick, this));
                    itemB->setTag(20);
                    itemB->setPosition(VisibleRect::center() + Point(0, -200) * _scale);
                    _menu->addChild(itemB);
                    
                    
                    auto labelA = Label::createWithTTF("没收 ￥" + KTUtils::MIRString(gl->getGold()*0.5)  + " 并且减少￥" + KTUtils::MIRString(gl->getAutoAddGold()*0.1) + "/秒", TITLE_FONT, 24 * _scale);
                    labelA->setMaxLineWidth(itemA->getContentSize().width);
                    labelA->setPosition(itemA->getPosition());
                    labelA->setAlignment(TextHAlignment::CENTER);
                    addChild(labelA, _menu->getLocalZOrder() + 1);
                    
                    const char * ctnt;
                    if (data->getBribe()>0) {
                        ctnt = "使用免罪卡";
                    } else {
                        ctnt = "购买5张免罪卡";
                    }
                    auto labelB = Label::createWithTTF(ctnt, TITLE_FONT, 30 * _scale);
                    labelB->setMaxLineWidth(itemB->getContentSize().width);
                    labelB->setPosition(itemB->getPosition());
                    addChild(labelB, _menu->getLocalZOrder() + 1);
                    
                }break;
                case MIRSpinType::MIRACLE:{
                    //获得现金加成（当前现金总额的50%）
                    file = "spinnerBill.png";
                    title = "奇迹!";
                    
                    auto item = MenuItemImage::create("button_green.png", "button_green.png", CC_CALLBACK_1(MIRSpinLayer::itemClick, this));
                    item->setPosition(VisibleRect::center() + Point(0, -200) * _scale);
                    item->setTag(TAG_PAY);
                    _menu->addChild(item);
                    
                    auto ok = Label::createWithTTF("确定", TITLE_FONT, 36 * _scale);
                    ok->setPosition(item->getPosition());
                    addChild(ok, _menu->getLocalZOrder() + 1);
                    
                    auto labelA = Label::createWithTTF("恭喜你，自由了并且获得了50%的现金补偿!", TITLE_FONT, 24 * _scale);
                    labelA->setMaxLineWidth(item->getContentSize().width);
                    labelA->setPosition(item->getPosition() + Point(0, 120) * _scale);
                    labelA->setAlignment(TextHAlignment::CENTER);
                    addChild(labelA, _menu->getLocalZOrder() + 1);
                    
                }break;
                    
                default:
                    break;
            }
            
            auto item = Sprite::create(file);
            item->setPosition(VisibleRect::center() + Point(0, 150) * _scale);
            this->addChild(item);
            
            auto titleLabel = Label::createWithTTF(title, TITLE_FONT, 56 * _scale);
            titleLabel->setPosition(VisibleRect::center() + Point(0, 20) * _scale);
            this->addChild(titleLabel);
            
            
        });
        
        auto ac3 = Sequence::create(ac1, DelayTime::create(2.0), callback, NULL);
        ac3->setTag(123);
        _spin->runAction(ac3);
    }
}

 void MIRSpinLayer::onTouchEnded(Touch *touch, Event *unused_event)
{
//    Point delt = touch->getDelta();
    
    
}

 void MIRSpinLayer::onTouchCancelled(Touch *touch, Event *unused_event)
{


}

bool MIRSpinLayer::init(KTPauseLayerDelegate *delegate)
{
    if (!KTPauseLayer::init(delegate)) {
        return false;
    }

    auto bgLayer = LayerColor::create(Color4B(255, 255, 255, 127));
    addChild(bgLayer, -1);
    
    auto fbiBg = Sprite::create("FBI_bg.png");
    fbiBg->setPosition(VisibleRect::center());
    addChild(fbiBg);
    
    _spin = Sprite::create("spin.png");
    _spin->setPosition(VisibleRect::center() + Point(0, - 60 * _scale));
    addChild(_spin);
    _spin->setRotation(22.5);
    
    auto indicator = Sprite::create("spin_indicator.png");
    indicator->setPosition(VisibleRect::center() + Point(0, 180 * _scale));
    addChild(indicator, 1, TAG_INDICATOR);
    
    auto spinText = Sprite::create("spin_text.png");
    spinText->setPosition(VisibleRect::center() + Point(180 * _scale, 140 * _scale));
    addChild(spinText, 1, TAG_SPINTEXT);
    
    
    Vector<MenuItem *> items;
    
    //adapt
    Point bribePos;
    Point swPos;
    if (IS_IPAD) {
        bribePos = Point(-190, -320);
        swPos = Point(150, -320);
    } else if (IS_IPAD_HD) {
        bribePos = Point(-190, -320) * _scale;
        swPos = Point(150, -320) * _scale;
    } else {
        bribePos = Point(-200, -360);
        swPos = Point(150, -360);
    }
 
    auto bribeItem = MenuItemSprite::create(Sprite::createWithSpriteFrameName("icon_supercharge_bribe.png"), Sprite::createWithSpriteFrameName("icon_supercharge_bribe.png"));
    bribeItem->setTag(0);
    bribeItem->setPosition(VisibleRect::center() + bribePos);
    items.pushBack(bribeItem);
    
    int sw = UserDefault::getInstance()->getIntegerForKey("ScoreWallSwitch", 0);
//    sw = 5;
    if (sw != 0) {
        auto swItem = MenuItemImage::create("mzk.png", "mzk.png", [=](Ref *sender){
            char str[64] = {0};
            sprintf(str, "%d", sw);
//            BBShowScoreWall(str);
        });
        swItem->setPosition(VisibleRect::center() + swPos);
        items.pushBack(swItem);
    }
    
    _menu = Menu::createWithArray(items);
    _menu->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
    _menu->setPosition(Point::ZERO);
    addChild(_menu, 10);
    
    _bribeBadge = Label::createWithTTF(KTUtils::stringFormat("x%d", data->getBribe()), TITLE_FONT, 24 * _scale);
    _bribeBadge->setPosition(Point(18 * _scale, 36 * _scale) + ccRectRight(bribeItem->getBoundingBox()));
    addChild(_bribeBadge, 12);
    
    NotificationCenter::getInstance()->addObserver(this, callfuncO_selector(MIRSpinLayer::updateBribe), "MIR_UPDATE_BRIBE", NULL);
    
    return true;
}

MIRSpinLayer::MIRSpinLayer()
: _mirDelegate(NULL)
, _result(MIRSpinType::EMPTY)
{


}

MIRSpinLayer::~MIRSpinLayer()
{
    _mirDelegate = NULL;
    NotificationCenter::getInstance()->removeAllObservers(this);
}




