//
//  MIRGameLayer.cpp
//  MakeItRain
//
//  Created by SongYang on 14-5-7.
//
//

#include "MIRGameLayer.h"
#include "MIRFinancialLayer.h"
#include "MIRBusinessLayer.h"
#include "MIRPoliticalLayer.h"
#include "MIRBucketLayer.h"
#include "MIRSpinLayer.h"
#include "MIRTipLayer.h"
#include "MIRSuperchargeLayer.h"
#include "KTParticleManager.h"
#include "AdManager.hpp"
#include "PopupManger.hpp"
//#include "Business.h"
//#include "InApp.h"

#define Tag_Loading 678

#define Move_HT   160.0f

#define Z_Menu      256

#define Z_Pop       128

#define Z_Label     64

#define Z_Envelope  512

#define Tag_Menu    257

//加成时间阈值 ms
#define Plus_Interval   500

#define FadeInTime  1.5

//const static Color3B changeColors[5] = {
//    Color3B(130, 208, 130),
//    Color3B(255, 255, 0),
//    Color3B(255, 153, 18),
//    Color3B(227, 23, 13),
//    Color3B(138, 43, 226),
//};

static const char* loadingContents[3] = {
    "金钱是万恶之源",
    "君子爱财取之以道",
    "钱不是万能的，\n没钱是万万不能的!",
};

void MIRGameLayer::cashFly(int number, int zOrder)
{
//    int ct = _rateGold > 10 ? 10 : _rateGold;
    
    
    for (int i = 0; i < number; i++) {
        
        auto sp = Sprite::create("flyingbill.png");
        
        Point pos = Point(CCRANDOM_0_1() * winSize.width, winSize.height);
        sp->cocos2d::Node::setPosition(pos);
        addChild(sp, zOrder);
        
//        auto animation = KTFactory::createAnimationFromSpriteFrameCache("flyingbill_", 10, 0, 0.2, -1);
//        auto ac = Animate::create(animation);
        float speed = 900;
        auto ac1 = MoveTo::create(winSize.height / speed, Point(pos.x, 0));
        auto callback = CallFuncN::create([](Ref *sender){
            
            Sprite *sp = (Sprite *)sender;
            
            sp->removeFromParent();
        });
        
        auto rotate = RotateBy::create(1.25, (CCRANDOM_MINUS1_1() > 0 ? 1 : -1) * 360);
        sp->runAction(Spawn::create(Sequence::create(Hide::create(), DelayTime::create(i * 0.3), Show::create(),ac1, callback, NULL), NULL));
        sp->runAction(RepeatForever::create(rotate));
    }
}

void MIRGameLayer::update_2(float dt)
{
    if (!_canTouch) {
        return;
    }
    
    if (!_changeColor.equals(_changeColors[0])) {
        
        if (_touchCashes.size() > 3) {
            _wrapFactor = 3;
             CCLOG("_wrapFactor = %d", _wrapFactor);
        } else if (_touchCashes.size() > 2) {
            _wrapFactor = 2;
             CCLOG("_wrapFactor = %d", _wrapFactor);
        } else {
            _wrapFactor = 1;
        }
    } else {
        _wrapFactor = 1;
    }
    
    
    if (_wrapFactor > 1) {
        
        Point pos = Point(winSize * CCRANDOM_0_1());
        
        auto label = Label::createWithTTF(KTUtils::stringFormat("×%d", _wrapFactor), TITLE_FONT, 100);
        label->setPosition(pos);
        addChild(label, Z_Menu + 10);
        
        auto ac = MoveBy::create(0.5, Point(0, 50));
        auto ac1 = FadeOut::create(0.5);
        auto spawn = Spawn::create(ac, ac1, NULL);
        
        auto callback = CallFuncN::create([=](Ref *sender){
        
            ((Node *)sender)->removeFromParent();
        
        });
        
        auto seq = Sequence::create(spawn, callback, NULL);
        label->runAction(seq);
    }
    int num =  _touchCashes.size() != 0 ? (_touchCashes.size() + 1) : 0;
    setWrapTotalGold((_wrapAddGold * num) * _wrapFactor);
    
//    CCLOG("_wrapTotalGold = %Lf", _wrapTotalGold);
}

void MIRGameLayer::update_3(float dt)
{
    if (!_canTouch) {
        return;
    }
    
    _counterUpdate_3++;
//    float scale = 0.5;
    if (_counterUpdate_3 == 3) {
        _counterUpdate_3 = 0;
//        scale = 0.4;
    }
    
    _autoAddCounter += (_autoAddGold + _wrapTotalGold)/3.0;
    
    long double tmp = KTUtils::MIRRound(_autoAddCounter);
    
    
    if (tmp >= 1.0) {
        addGold(tmp );
        _autoAddCounter = 0;
    }
}



void MIRGameLayer::update(float dt)
{
    if (!_canTouch) {
        return;
    }
    
    data->addSuperEnvTimer(dt);
    auto superEnvT = data->getSuperEnvTimer();
    if (superEnvT > data->getSuperEnvelopeTime()) {
        _superEnvelopeItem->setEnabled(true);
        _superEnvLabel->setVisible(false);
        
        if (_superEnvelopeItem->getActionByTag(323) == nullptr) {
            auto scale = ScaleBy::create(0.8f, 1.2f);
            auto reverse = scale->reverse();
            auto seq = Sequence::createWithTwoActions(scale, reverse);
            auto repeat = RepeatForever::create(seq);
            repeat->setTag(323);
            _superEnvelopeItem->runAction(repeat);
        }
        
        
    } else {
        _superEnvelopeItem->setEnabled(false);
        _superEnvelopeItem->stopActionByTag(323);
        _superEnvLabel->setVisible(true);
        
        float t = data->getSuperEnvelopeTime() - data->getSuperEnvTimer();
        int sec = (int)t % 60;
        int min = (int)(t/60)%60;
        
        char str[64];
        sprintf(str, "距离下次开抢\n%d:%0.2d",min, sec);
        _superEnvLabel->setString(str);
    }
    
    
    _elipse1 += dt;
    
    if (_elipse1 > 1.0) {
        
        float scale = data->getBucketCapacity() / data->getBucketTotalCapacity();
        
        if (_bucketItem->isVisible()) {
            data->addBucketCapacity(data->getBucketFlow()/3600.f);
            
            static const float rate[] = {
                0,
                0.25,
                0.5,
                0.75,
                1.0,
            };
            
            static const char* file[] = {
                "bucket.png",
                "bucket_1.png",
                "bucket_2.png",
                "bucket_3.png",
                "bucket_4.png",
            };
            
            for (int i = 4; i >= 0; i--) {
                if (scale >= rate[i]) {
                    
                    _bucketItem->setNormalImage(Sprite::create(file[i]));
                    
                    break;
                }
            }
        }
        
        if (_bucketLayer) {
            _bucketLayer->getCapacityLabel()->setString("￥" + KTUtils::MIRString(floorl(data->getBucketCapacity())));
            _bucketLayer->setBucketHeight(scale);
        }
        
        updateWrap();
        
        
        bool pawnEmitter = false;
        //颜色
        for (int i = 0; i < 5; i++) {
            int idx = 4 - i;
            if (_touchCashes.size() >= idx) {
                
                if (idx == 4 || i == 2) {
                    
                    int lastIdx = 0;
                    for (int j = 0; j < _changeColors.size(); j++) {
                        if (_changeColors.at(j).equals(_changeColor)) {
                            lastIdx = j;
                            break;
                        }
                    }
                    if (lastIdx < idx) {
                        pawnEmitter = true;
                    }
                }

                _changeColor = _changeColors[idx];
                
                break;
            }
        }
        
        if (pawnEmitter) {
            auto emitter = KTParticleManager::sharedParticleManager()->createParticle(ParticleType::COMET);
            emitter->setPosition(VisibleRect::leftTop() + Point(0, - 80) * _scale);
            addChild(emitter, 256);

            auto ac = MoveBy::create(0.8, Point(winSize.width, - 90 * _scale));
            auto callback = CallFuncN::create([=](Ref *sender){
                
                auto node = (Node *)sender;
                this->removeChild(node);
                
            });
            emitter->runAction(Sequence::create(ac, callback, NULL));
        }
        
        
        auto lastAc = (ActionInterval *)getActionByTag(123);
        if (lastAc) {
            stopAction(lastAc);
        }
        auto ac = TintTo::create(1.2f, _changeColor.r, _changeColor.g, _changeColor.b);
        ac->setTag(123);
        _bgLayer->runAction(ac);
       
        cashFly(MIN(_autoAddGold, 10), -1);
        
        //加钱
        _elipse1 = 0;
    }
    
    _elapseNormalEnvelope +=dt;
    
    if(_elapseNormalEnvelope > _timeNormalEnvelope) {
        
        if (!_normalEnvelopeItem->isVisible()) {
            auto pos = VisibleRect::center() + Vec2(rand_minus1_1() * 260, rand_minus1_1() * 300);
            _normalEnvelopeItem->setPosition(pos);
            if (data->getShowNormalEnvelop()) {
                _normalEnvelopeItem->setVisible(true);
                if (_normalEnvelopeItem->getActionByTag(323) == nullptr) {
                    auto scale = ScaleBy::create(0.8f, 1.2f);
                    auto reverse = scale->reverse();
                    auto seq = Sequence::createWithTwoActions(scale, reverse);
                    auto repeat = RepeatForever::create(seq);
                    repeat->setTag(323);
                    _normalEnvelopeItem->runAction(repeat);
                }
            }
        }
        _elapseNormalEnvelope = 0;
    }
    
    _elapsed60 += dt;
    
    if (_elapsed60 > 60) {
        _elapsed60 = 0;
        
        
        
        if (CCRANDOM_0_1() < 0.01) {
            
            auto la = MIRSpinLayer::create(this);
            la->setMIRDelegate(this);
            addChild(la, Z_Menu + 1, 40);
            
        }
    }
    
    
    _elapsed20 += dt;
    if (_elapsed20 > 20) {
        struct tm t = KTUtils::getCurrentTime();
        
        UserDefault *ud = UserDefault::getInstance();
        
        ud->setIntegerForKey("MIR_TIME_YEAR", t.tm_year);
        ud->setIntegerForKey("MIR_TIME_MON", t.tm_mon);
        ud->setIntegerForKey("MIR_TIME_DAY", t.tm_mday);
        ud->setIntegerForKey("MIR_TIME_HOUR", t.tm_hour);
        ud->setIntegerForKey("MIR_TIME_MIN", t.tm_min);
        ud->setIntegerForKey("MIR_TIME_SEC", t.tm_sec);
        
        ud->flush();
    }
    
    _elapsed30 += dt;
    if (_elapsed30 > 40) {
        
        if (_cpFlag1 == false) {
            
            //cp 在数钱界面，40秒内无操作
            CCLOG("CP1");
            
            if (!_popLayer) {
//                BBShowInterstitial();
                AdManager::getInstance()->setShowInterstitial(true);
            }
            
            
        }
        
        _cpFlag1 = false;
        
        _elapsed30 = 0;
    }
    
    if (_bottomBarClickIdx >= 4) {
        
        AdManager::getInstance()->setShowInterstitial(true);
        _bottomBarClickIdx = 0;
    }
    
}

void MIRGameLayer::pauseLayerDidQuit(KTPauseLayer *layer)
{
    switch (layer->getTag()) {
        case 1:{
            //bucket
            Menu *menu = (Menu *)getChildByTag(Tag_Menu);
            MenuItem *item = (MenuItem *) menu->getChildByTag(32);
            item->activate();
            
            
            _bucketLayer = NULL;
        }break;
        case 32:{
            //political
            
        }break;
        default:
            break;
    }
    removeChild(layer);
}

void MIRGameLayer::pauseLayerDidMakeSure(KTPauseLayer *layer)
{
    switch (layer->getTag()) {
        case 1:{
            
            //bucket
            addGold(data->getBucketCapacity());
            data->setBucketCapacity(0);
            
            _bucketLayer = NULL;
            
            this->playEffect(SOUND_REG);
            
            showTipLayer("icon_political_1.png", BUCKET_TIP_CONTENT);
            
        }break;
            
        default:
            break;
    }
    removeChild(layer);
}

void MIRGameLayer::pauseLayerDidCancel(KTPauseLayer *layer)
{
    if (layer->getTag() == 2 || layer->getTag() == 3) {
        //normal envelope
        
        
        
        MIRGetEnvelopLayer * env = dynamic_cast<MIRGetEnvelopLayer *>(layer);
        if (env != nullptr) {
            addGold(env->getToAdd());
            if (env->getType() == MIRGetEnvelopLayer::Type::Normal) {
                AdManager::getInstance()->setShowInterstitial(true);
            } else {
                AdManager::getInstance()->SetShowVideo(true);
                data->setSuperEnvTimer(0);
            }
        }
    } else {
    
        if (layer->getTag() >= 30 && layer->getTag() <= 33) {
            _popLayer = NULL;
            _menuBg->setColor(Color3B::WHITE);
            _menuBg->setOpacity(127);
            _drawer->clear();
            _tintRect->setVisible(false);
        }
    }
    
    _bucketLayer = NULL;
    removeChild(layer);
}

bool MIRGameLayer::onTouchBegan(Touch *touch, Event *unused_event)
{
    if (!_canTouch) {
        return false;
    }
    
    _cpFlag2 = _cpFlag1 = true;
    
    Point location = touch->getLocation();
    if (_cash->getBoundingBox().containsPoint(location)) {
        
        
        auto cash = Sprite::create(_isCashGold ? "skewed_bill_golden.png" : "skewed_bill.png");
        cash->setAnchorPoint(Point::ANCHOR_MIDDLE_TOP);
        cash->setPosition(_cash->getPosition());
        addChild(cash);
        
        
        if (_isCashGold) {
            _cash->setSpriteFrame(KTFactory::spriteFrameByName("cash.png"));
        }
        
        _touchCash = cash;
    }
    
    return true;
}

void MIRGameLayer::createGoldenCash()
{
    if (_isCashGold) {
        return;
    }
    //test
    if (CCRANDOM_0_1() < 0.01) {
                
        _isCashGold = true;
        
        _cash->setSpriteFrame(KTFactory::spriteFrameByName("cash_golden.png"));
        
    }
}

void MIRGameLayer::onTouchMoved(Touch *touch, Event *unused_event)
{
    if (!_canTouch) {
        return;
    }
    if (_touchCash) {
        Point delt = touch->getDelta();
        
        Point touchOldPos = _touchCash->getPosition();
        Point touchNewPos = touchOldPos + Point(0, delt.y);
        _touchCash->setPosition(touchNewPos);
        
        if (touchNewPos.y < _cash->getPositionY()) {
            _touchCash->setPositionY(_cash->getPositionY());
        }
        
        if (touchNewPos.y - _cash->getPositionY() > Move_HT) {
            //move
            
            if (_hand != nullptr) {
                _hand->removeFromParent();
                _hand = nullptr;
                
                UserDefault::getInstance()->setBoolForKey("MIR_ShowHand", false);
            }
            
            int dir = 0;
            if (delt.x > 45) {
                dir = 1;
            } else if (delt.x < -45){
                dir = -1;
            }
            
            float scale = 0.6;
            
            float ht = _touchCash->getContentSize().height * scale;
            
            Point target = VisibleRect::top() + Point(dir * 400, ht);
            
            CCLOG("pos = %s", CCStringFromPoint(_touchCash->getPosition())->getCString());
            CCLOG("target = %s", CCStringFromPoint(target)->getCString());
            
            float speed = winSize.height;
            
            float t = (target.y - _touchCash->getPositionY()) / speed;
            
            auto ac = MoveTo::create(t, target);
            auto ac1 = ScaleTo::create(t, scale);
            
            auto ac3 = RotateBy::create(t, 30 * dir);
            auto callback = CallFuncN::create(CC_CALLBACK_1(MIRGameLayer::cashMoveCallback, this));
            
            auto *ac2 = Spawn::create(ac, ac1, ac3, NULL);
            
            _touchCash->runAction(Sequence::create(ac2, callback, NULL));
            
            _touchCashes.pushBack(_touchCash);
            
            _touchCash = NULL;
            
            //加钱
            if (_isCashGold) {
                _isCashGold = false;
                
                addGold(_wrapAddGold * 50);
                
            
                auto la = MIRTipLayer::create();
                la->setContent("x50!");
                la->setCoverOthers(false);
                addChild(la, 1024);
                
            } else {
                addGold(_wrapAddGold * _wrapFactor);
            }
            
            
            const char * effect;
            if (_touchCashes.size() > 4) {
                effect = SOUND_SWIPE4;
            } else if (_touchCashes.size() > 3){
                effect = SOUND_SWIPE3;
            } else if (_touchCashes.size() > 2) {
                effect = SOUND_SWIPE2;
            } else if (_touchCashes.size() > 1) {
                effect = SOUND_SWIPE1;
            } else {
                effect = SOUND_SWIPE0;
            }
            
            this->playEffect(effect);
            
            cashFly(1, 128);
            
            createGoldenCash();
        }
    }
}



void MIRGameLayer::cashMoveCallback(Ref *sender)
{
    Sprite *cash = (Sprite *)sender;
    removeChild(cash);
    
//    _gold++;
//    
//    for (auto label : _labels) {
//        label->setValue(_gold);
//    }

    _touchCashes.eraseObject(cash);
    
    
}

void MIRGameLayer::onTouchEnded(Touch *touch, Event *unused_event)
{
    if (_touchCash) {
        removeChild(_touchCash);
        _touchCash = NULL;
        if (_isCashGold) {
            _cash->setSpriteFrame(KTFactory::spriteFrameByName("cash_golden.png"));
        }
    }
}
void MIRGameLayer::onTouchCancelled(Touch *touch, Event *unused_event)
{
    onTouchEnded(touch, unused_event);
}


void MIRGameLayer::updateWrap()
{
    for (int i = 9; i >= 0; i--) {
        if (getGold() >= wrapFactor[i]) {
            
            _wrap->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(wrapFile[i]));
            
            _wrapLabel->setString("￥" + KTUtils::MIRString(_wrapAddGold));
            
            
            break;
        }
    }
}

void MIRGameLayer::updateLabels()
{
    std::vector<int> vs = KTUtils::getDigValues(_gold);
    for (int i = 0; i < _labels.size(); i++) {
        _labels.at(i)->setValue(vs[i]);
    }
}

void MIRGameLayer::layoutLabels()
{
    int bigSpNum = _labels.size() / 3 - (_labels.size() % 3 == 0);//_labels.size() / 3 + (_labels.size()%3 != 0);
    
    //现金label宽度
    float labelWd = _labels.size() * BASE_SPACING_LABEL + BASE_SPACING_ADD * bigSpNum;
    //总宽度
    float wd = Cash_Width + labelWd;
    
    float scale = 1.0;
    if (labelWd > winSize.width - Cash_Width) {
        scale = (winSize.width - Cash_Width) / labelWd;
        _spacingLabel = BASE_SPACING_LABEL * scale;
        _spacingAdd = BASE_SPACING_ADD * scale;
        
        labelWd = winSize.width - Cash_Width;
        wd = winSize.width;
    } else {
        _spacingLabel = BASE_SPACING_LABEL;
        _spacingAdd = BASE_SPACING_ADD;
    }
    
    //现金label centerX
    float labelCenter = winSize.width/2 + Cash_Width + labelWd/2 - wd/2;
    _cashLabel->setPosition(Point(winSize.width/2 - wd/2, _cash->getPositionY() + 108 * _scale));
    
    for (int i = 0; i < _labels.size(); i++) {
        int row = i / 3;
//        CCLOG("row = %d", row);
        Point pos = Point(labelCenter + labelWd/2 - (i + 0.5) * _spacingLabel - row * _spacingAdd, _cash->getPositionY() + 100 * _scale);
        
        auto label = _labels.at(_labels.size() - 1 - i);
        label->setPosition(pos);
        label->setScale(scale);
    }
}

void MIRGameLayer::spinResult(MIRSpinType res, Layer *spinLayer)
{

    switch (res) {
        case MIRSpinType::GUILTY:{
            //扣除当前现金的50%，每秒增速减少20%
            setGold(getGold()*0.5);
            setAutoAddGold(getAutoAddGold()*0.5);
        }break;
        case MIRSpinType::NOT_GUILTY:{
            //无效果
        }break;
        case MIRSpinType::PLEA:{
            //扣除当前现金的25%
            setGold(getGold()*0.75);
        }break;
        case MIRSpinType::SEIZURE:{
            //扣除当前现金的50%，每秒增速减少10%
            setGold(getGold()*0.5);
            setAutoAddGold(getAutoAddGold()*0.9);
        }break;
        case MIRSpinType::MIRACLE:{
            //获得现金加成（当前现金总额的50%）
            setGold(getGold()*1.5);
        }break;
        
        default:
            break;
    }

    removeChild(spinLayer);
}

void MIRGameLayer::resetAll()
{
    
    if (_bucketItem) {
        _bucketItem->setVisible(false);
    }
    
    _spacingAdd = BASE_SPACING_ADD;
    _spacingLabel = BASE_SPACING_LABEL;
    
    data->setBucketCapacity(0);
    data->setBucketTotalCapacity(BaseBucketTotalCapacity);
    data->setBucketFlow(BaseBucketFlow);
    
    UserDefault *ud = UserDefault::getInstance();
    
    setGold(BaseGold);
    setAutoAddGold(BaseAutoAddGold);
    _autoAddCounter = 0;
    
    setWrapAddGold(BaseWrapAddGold);
    setWrapTotalGold(0);
    
    char key[64] = {0};
    
    const char* type[3] = {"BUSINESS", "FINANCIAL", "POLITICAL"};
    
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 20; j++) {
            sprintf(key, "%s_LEVEL_%d", type[i], j);
            ud->setIntegerForKey(key, 0);
        }
    }
    ud->flush();
}



void MIRGameLayer::setItemTouched(int index, Layer *setLayer)
{
    if (MIRDynamicData::getInstance()->getShowPopup()) {
        if (index == 4) {
            //reset
            
            auto la = MIRResetTipLayer::create(this);
            la->setMIRDelegate(this);
            addChild(la, 128);
            
        } else if (index == 3) {
            data->setSoundOff(!data->getSoundOff());
        } else if (index == 2){
            PopupManager::getInstace()->showMoney();
        } else if (index == 1) {
            AdManager::getInstance()->SetShowVideo(true);
        } else if (index == 0) {
            
            bool flag = UserDefault::getInstance()->getBoolForKey("mir_firstTouch", true);
            if (flag) {
                PopupManager::getInstace()->showRate();
                UserDefault::getInstance()->setBoolForKey("mir_firstTouch", false);
            } else {
                PopupManager::getInstace()->showMoney();
            }
        }
    } else {
        if (index == 0) {
            data->setSoundOff(!data->getSoundOff());
        } else if (index == 1) {
            auto la = MIRResetTipLayer::create(this);
            la->setMIRDelegate(this);
            addChild(la, 128);
        }
    }
    
    
    auto ac= DelayTime::create(0.2);
    auto cb = CallFuncN::create([=](Ref *sender){
        this->pauseLayerDidCancel((KTPauseLayer *)sender);
    });
    setLayer->runAction(Sequence::create(ac, cb, NULL));
}

void MIRGameLayer::purchase(int index)
{
//    BBPurchaseProduct(this, callfuncO_selector(MIRGameLayer::purchaseFinish), callfuncO_selector(MIRGameLayer::purchaseFail), inAppIDs[index]);
    //goto
//    InApp *inapp = InApp::shareInstance();
//    inapp->purchaseProduct(this,
//                           callfuncO_selector(MIRGameLayer::purchaseFinish),
//                           callfuncO_selector(MIRGameLayer::purchaseFail),
//                           inAppIDs[index-1]);
}

void MIRGameLayer::purchaseFinish(Ref *sender)
{
    showTipLayer("", "恭喜你，购买道具成功");
    if (_purchaseIdx == 0) {
        
        addWrapAddGold(getWrapAddGold());
    } else if (_purchaseIdx == 1) {
        
        addAutoAddGold(getAutoAddGold());
    } else if (_purchaseIdx == 2) {
    
        addGold(888888888888);
    } else if (_purchaseIdx == 3) {
        
        data->addBribe(5);
    } else if (_purchaseIdx == 4) {
        
        data->addBribe(25);
    }
}

void MIRGameLayer::purchaseFail(Ref *sender)
{

}

bool MIRGameLayer::itemCanLevelUp(MIRModel *m)
{
    stopActionByTag(1223);
    //cp 在任意界面，点击升级后，3秒内无操作
    auto ac = DelayTime::create(4.5);
    auto cb = CallFuncN::create([=](Ref *sender){
    
        if (_cpFlag2 == false) {
            
            CCLOG("CP3");
//            BBShowInterstitial();
            AdManager::getInstance()->setShowInterstitial(true);
        }
        _cpFlag2 = false;
    });
    auto seq = Sequence::create(ac, cb, NULL);
    seq->setTag(1223);
    runAction(seq);
    
    //test
    if (getGold() < m->getPrice()) {
        showTipLayer("", "现金不足!");
        //cp 连续3次，现金不足
        _noGoldCounter++;
        if (_noGoldCounter >= 3) {
            CCLOG("CP2");
//            BBShowInterstitial();
            _noGoldCounter = 0;
        }
        return false;
    } else {
        addGold(-m->getPrice());
    }
    
    
    if (m->getType() == InvestmentType::BUSINESS) {
        
        setWrapAddGold(m->getBenefit());
        showTipLayer(m->getIconFile(), BUSINESS_TIP_CONTENT);
        
        
    } else if (m->getType() == InvestmentType::FINANCIAL) {
        addAutoAddGold(m->getBenefit());
        showTipLayer(m->getIconFile(), FINANCIAL_TIP_CONTENT);
    } else if (m->getType() == InvestmentType::POLITICAL) {
        
        data->addBucketFlow(m->getBenefit());
        data->addBucketTotalCapacity(m->getBenefit2());
        
        if (m->getIdx() == 15) {
            _bucketItem->setVisible(true);
            
            auto la = MIRBucketTipLayer::create(this);
            addChild(la, 512);
        } else {
                showTipLayer(m->getIconFile(), m->getBenefit() > 0 ?POLITICAL_TIP_CONTENT : POLITICAL_TIP_CONTENT2);
        }
    }
    
    return true;
}

void MIRGameLayer::firstInit()
{
    resetAll();
}

bool MIRGameLayer::init()
{
    if (!KTLayer::init()) {
        return false;
    }
    auto data = MIRDynamicData::getInstance();
    _timeNormalEnvelope = data->getRedEnvelopeTime();
    CCLOG("_timeNormalEnvelope = %f", _timeNormalEnvelope);
    
    MIRDynamicData::getInstance()->setGameLayer(this);
    
    ud = UserDefault::getInstance();
    
    if (ud->getBoolForKey("MIR_FIRST_GAME", true) == true) {
        
        firstInit();
        ud->setBoolForKey("MIR_FIRST_GAME", false);
    }
    
    if (ud->getBoolForKey("MIR_ShowHand", true) == true ) {
        _hand = Sprite::create("hand.png");
        _hand->setPosition(VisibleRect::center() + Vec2(0, -200));
        _hand->setGlobalZOrder(Z_Label + 2);
        addChild(_hand);
        MoveBy *ac1 = MoveBy::create(1.f, Vec2(0, 400));
        auto ac2 = ac1->reverse();
        auto ac3 = Sequence::createWithTwoActions(ac1, ac2);
        auto ac4 = RepeatForever::create(ac3);
        _hand->runAction(ac4);
        _hand->setVisible(false);
    }
    
    Color3B changeColors[5] = {
        Color3B(130, 208, 130),
        Color3B(255, 255, 0),
        Color3B(255, 153, 18),
        Color3B(227, 23, 13),
        Color3B(138, 43, 226),
    };
    for (int i = 0; i < 5; i++) {
        _changeColors.push_back(changeColors[i]);
    }
    
    
    const char* file[] = {"flipclock_numbers_cropped.plist", "flyingbills.plist", "icons_investments.plist", "level_indicators.plist", "wrappers.plist"};
    //加载资源
    for (int i = 0; i < sizeof(file)/sizeof(file[0]); i++) {
        SpriteFrameCache::getInstance()->addSpriteFramesWithFile(file[i]);
    }
    
    //adapt
    float cashHt;
    float wrapHt;
    float menuBgHt = 120;
    float baseWidth = 120;
    Point buckItemPos = Point(100, 200);
    
    
    if (IS_IPHONE6) {
        wrapHt = 450;
        cashHt = 400;
    } else if (IS_IPHONE6P) {
        wrapHt = 740;
        cashHt = 690;
    } else if (IS_IPHONE5) {
        wrapHt = 380;
        cashHt = 324;
    } else if (IS_IPHONE4) {
        wrapHt = 360;
        cashHt = 220;
    } else if (IS_IPAD) {
        wrapHt = 360;
        cashHt = 240;
        baseWidth = 150;
    } else if (IS_IPAD_HD) {
        wrapHt = 360 * 2;
        cashHt = 240 * 2;
        
        menuBgHt *= 2;
        baseWidth = 300;
        buckItemPos = buckItemPos * 2;
        
        BASE_SPACING_ADD *= 2;
        BASE_SPACING_LABEL *= 2;
        Cash_Width *= 2;
    }
    
    
    _bgLayer = LayerColor::create(Color4B(130, 208, 130, 255));
    _bgLayer->setPosition(Point::ZERO);
    addChild(_bgLayer, -10);
    
    _cash = Sprite::create("cash.png");
    _cash->setAnchorPoint(Point::ANCHOR_MIDDLE_TOP);
    _cash->setPosition(VisibleRect::center() + Point(0, cashHt));
    addChild(_cash);
    
    _cash->setVisible(false);
    
    char tmpStr[128] = {0};
    sprintf(tmpStr, "%Lf", BaseGold);
    
//    const char* goldstr = ud->getStringForKey("MIR_GOLD", tmpStr).c_str();
//    CCLOG("gold str = %s", goldstr);
    
    sprintf(tmpStr, "%Lf", BaseGold);
    
    //test
    _gold = KTUtils::atold(ud->getStringForKey("MIR_GOLD", tmpStr).c_str());//18420000000000000000; //4 * 3zero
    sprintf(tmpStr, "%Lf", BaseAutoAddGold);
    _autoAddGold = KTUtils::atold(ud->getStringForKey("MIR_AUTO_ADD_GOLD", tmpStr).c_str());//1110003300099000000;
    sprintf(tmpStr, "%Lf", BaseWrapAddGold);
    _wrapAddGold = KTUtils::atold(ud->getStringForKey("MIR_WRAP_ADD_GOLD", tmpStr).c_str());
    
    if (_autoAddGold >= 1) {
        this->playBackgroundMusic(SOUND_PAPER_FLUTTERS);
    }
    
    
    //wrap
    _wrap = Sprite::create();
    _wrap->setPosition(Point(winSize.width/2, wrapHt));
    addChild(_wrap, Z_Label);
    
    _wrap->setVisible(false);
    
    sprintf(tmpStr, "￥%.1LfK", _wrapAddGold);
    
    _wrapLabel = Label::createWithTTF(tmpStr, TITLE_FONT, 60 * _scale);
    _wrapLabel->setColor(Color3B::BLACK);
    _wrapLabel->setPosition(_wrap->getPosition());
    addChild(_wrapLabel, Z_Label + 1);
    
    _wrapLabel->setVisible(false);
    
    updateWrap();
    
   
    int ct = KTUtils::getNumDig(_gold);
    
    _cashLabel = Label::createWithTTF("￥", TITLE_FONT, 60 * _scale);
    _cashLabel->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
    addChild(_cashLabel, Z_Label);
    _cashLabel->setScale(0.8);
    
    _cashLabel->setVisible(false);
    
    //labels
    for (int i = 0; i < ct; i ++) {
        auto label = MIRLabel::create(0);
        addChild(label, Z_Label);
        _labels.push_back(label);
        label->setOpacity(0);
    }
    
    layoutLabels();
    updateLabels();
    
    std::string str;
    if (_autoAddGold == 0.5 && !_wrapTotalGold) {
        str = std::string("￥0.5 / 秒");
    } else {
        str = std::string("￥" + KTUtils::MIRString(_autoAddGold + _wrapTotalGold) + " / 秒");
    }
    
    _rateLabel = Label::createWithTTF(str, TITLE_FONT, 40 * _scale);
    _rateLabel->setPosition(Point(winSize.width/2, _cash->getPositionY() + 20 *_scale));
    addChild(_rateLabel, Z_Label);
    
    _rateLabel->setVisible(false);
    
    _bucketItem = MenuItemImage::create("bucket.png", "bucket.png", CC_CALLBACK_1(MIRGameLayer::itemClick, this));
    _bucketItem->setTag(1);
    _bucketItem->setPosition(buckItemPos);
    
    int num = ud->getIntegerForKey("POLITICAL_LEVEL_15", 0);
    if (num == 0) {
        _bucketItem->setVisible(false);
    }
    
    _superEnvelopeItem = MenuItemImage::create("super_redenvelope1.png", "super_redenvelope1.png", "super_redenvelope2.png", CC_CALLBACK_1(MIRGameLayer::itemClick, this));
    _superEnvelopeItem->setTag(3);
    _superEnvelopeItem->setPosition(VisibleRect::rightBottom() + Vec2(-100, 200));
    
    _superEnvLabel = Label::createWithTTF("距离下次开抢\n3:00", TITLE_FONT, 32, Size::ZERO, TextHAlignment::CENTER);
    _superEnvLabel->setTextColor(Color4B::BLACK);
    _superEnvelopeItem->addChild(_superEnvLabel);
    _superEnvLabel->setPosition(60, 150);
    
   _superEnvelopeItem->setVisible(data->getShowSuperEnvelop());

    auto lowMenu = Menu::create(_bucketItem, _superEnvelopeItem, NULL);
    lowMenu->setAnchorPoint(Point::ANCHOR_BOTTOM_LEFT);
    lowMenu->setPosition(Point::ZERO);
    addChild(lowMenu, Z_Label, 555);
    
    lowMenu->setVisible(false);
    
    
    _normalEnvelopeItem = MenuItemImage::create("redenvelope.png", "redenvelope.png", CC_CALLBACK_1(MIRGameLayer::itemClick, this));
    _normalEnvelopeItem->setTag(2);
    _normalEnvelopeItem->setPosition(winSize.width/2, winSize.height/2);
    _normalEnvelopeItem->setVisible(false);
    
    auto envelopMenu = Menu::create(_normalEnvelopeItem, NULL);
    envelopMenu->setAnchorPoint(Point::ANCHOR_BOTTOM_LEFT);
    envelopMenu->setPosition(Point::ZERO);
    addChild(envelopMenu, Z_Envelope);
    
    //menu
    _menuBg = LayerColor::create(Color4B(255, 255, 255, 127), winSize.width, menuBgHt);
    _menuBg->setPosition(Point::ZERO);
    addChild(_menuBg, Z_Menu - 1);
    
    _menuBg->setVisible(false);
    
    char normal[64] = {0};
    char sel[64] = {0};
    Vector<MenuItem *> items;
   
    
    float itemWidth = (winSize.width - baseWidth * 2)/3;
    for (int i = 0; i < 4; i++) {
        
        sprintf(normal, "investment%d.png", i + 1);
        sprintf(sel, "investment%d_pushed.png", i + 1);
        
        auto *item = MenuItemImage::create(normal, sel, CC_CALLBACK_1(MIRGameLayer::itemClick, this));
        item->setTag(i + 30);
        item->setPosition(Point(baseWidth + i * itemWidth, menuBgHt * 0.5));
        items.pushBack(item);
    }
    
    _tintRect = LayerColor::create(Color4B(0, 0, 0, 127), menuBgHt, menuBgHt);
    addChild(_tintRect, Z_Menu - 1);
    _tintRect->setVisible(false);
    
    auto *menu = Menu::createWithArray(items);
    menu->setPosition(Point::ZERO);
    addChild(menu, Z_Menu, Tag_Menu);
    
    menu->setVisible(false);
    
    //loading label
    
    auto loading = Sprite::create("loading.png");
    lazyScale(loading);
    loading->setPosition(VisibleRect::center());
    addChild(loading, -9, Tag_Loading);
    
    _canTouch = false;
    
    Label *label = Label::createWithTTF(loadingContents[arc4random()%3], TITLE_FONT, 50 * _scale);
    
    label->setWidth(winSize.width);
    
    label->setAlignment(TextHAlignment::CENTER);
    
    label->setPosition(VisibleRect::center() + Point(0, 30) * _scale);
    
    addChild(label);
    
    auto ac = DelayTime::create(3.0);
    
    auto ac2 = CallFuncN::create(CC_CALLBACK_1(MIRGameLayer::startLableCallback, this));
    label->runAction(Sequence::create(ac, ac2, NULL));
    
    auto touchListener = EventListenerTouchOneByOne::create();
    touchListener->onTouchBegan = CC_CALLBACK_2(MIRGameLayer::onTouchBegan, this);
    touchListener->onTouchMoved = CC_CALLBACK_2(MIRGameLayer::onTouchMoved, this);
    touchListener->onTouchEnded = CC_CALLBACK_2(MIRGameLayer::onTouchEnded, this);
    touchListener->onTouchCancelled = CC_CALLBACK_2(MIRGameLayer::onTouchCancelled, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);

    _drawer = DrawNode::create();
    addChild(_drawer, Tag_Menu);
    
    scheduleUpdate();
    
    schedule(schedule_selector(MIRGameLayer::update_3), 1.0/3.0, kRepeatForever, 0);
    
    schedule(schedule_selector(MIRGameLayer::update_2), 0.5, kRepeatForever, 0);
    
    NotificationCenter::getInstance()->addObserver(this, callfuncO_selector(MIRGameLayer::popBucketLayer), "MIR_POP_BUCKET", NULL);
    
    AdManager::getInstance()->setShowBanner(true);
    
    
    int count = UserDefault::getInstance()->getIntegerForKey("MIR_Show_Rec");
    
    if (count >= 3) {
        auto txt = MIRDynamicData::getInstance()->getRecText();
        bool flag = strcmp(txt, UserDefault::getInstance()->getStringForKey("MIR_Rec_Text").c_str()) != 0;
        if (flag && data->getShowRecText()) {
            
            UserDefault::getInstance()->setStringForKey("MIR_Rec_Text", txt);
            UserDefault::getInstance()->flush();
            PopupManager::getInstace()->showReccomand();
        }
    }
    UserDefault::getInstance()->setIntegerForKey("MIR_Show_Rec", ++count);
    return true;
}

void MIRGameLayer::startLableCallback(Ref *sender)
{
    _canTouch = true;
    
    Node *node = (Node *)sender;
    removeChild(node);
    
    removeChildByTag(Tag_Loading);
    
    
    for (auto label : _labels) {
        label->runAction(fadeIn());
    }
    
    _cash->runAction(fadeIn());
    
    _cashLabel->runAction(fadeIn());
    
    _wrap->runAction(fadeIn());
    
    _wrapLabel->runAction(fadeIn());
    
    _rateLabel->runAction(fadeIn());
    
    if (_hand != nullptr) {
        _hand->runAction(fadeIn());
    }
    
    auto ac = CallFuncN::create([=](Ref *sender){
        Node *n = (Node *)sender;
        n->setVisible(true);
        n->setOpacity(0);
    });
    auto ac1 = FadeTo::create(FadeInTime, 127);
    auto callbak = CallFuncN::create([=](Ref *sender){
        
    });
    
    _menuBg->runAction(Sequence::create(ac, ac1, callbak, NULL));
    
    getChildByTag(555)->runAction(fadeIn());
    
    getChildByTag(Tag_Menu)->runAction(fadeIn());
    
    data->bucketAutoAdd();
}

void MIRGameLayer::popBucketLayer(Ref *sender)
{
    _bucketLayer = MIRBucketLayer::create(this);
    addChild(_bucketLayer, Z_Menu + 1, 1);
}

void MIRGameLayer::showInvestmentLayer(InvestmentType type)
{
    _noGoldCounter = 0;
    int tag = 30;
    if (type == InvestmentType::BUSINESS) {
        tag = 31;
    } else if (type == InvestmentType::POLITICAL) {
        tag = 32;
    } else if (type == InvestmentType::SUPERCHARGE) {
        tag = 33;
    }
    if (!_popLayer) {
        
    } else if (_popLayer->getTag() == tag) {
        //关闭pop
        removeChild(_popLayer);
        _popLayer = NULL;
        _menuBg->setColor(Color3B::WHITE);
        _menuBg->setOpacity(127);
        _drawer->clear();
        _tintRect->setVisible(false);
        return;
    } else {
        removeChild(_popLayer);
        _popLayer = NULL;
    }
    
    _menuBg->setColor(Color3B(MIRCellColor));
    _menuBg->setOpacity(255);
    
    _drawer->drawSegment(Point(0, _menuBg->getContentSize().height), Point(_menuBg->getContentSize()), 0.5, Color4F::BLACK);
    
    auto menu = getChildByTag(Tag_Menu);
    auto menuItem = (MenuItemImage *)menu->getChildByTag(tag);
    
    _tintRect->setPosition(menuItem->getPosition() - Point(_tintRect->getContentSize()/2));
    _tintRect->setVisible(true);
    
    Layer *la = NULL;
    if (type == InvestmentType::FINANCIAL) {
        auto layer = MIRFinancialLayer::create(this);
        layer->setMIRDelegate(this);
        la = layer;
    } else if (type == InvestmentType::BUSINESS) {
        auto layer = MIRBusinessLayer::create(this);
        layer->setMIRDelegate(this);
        la = layer;
    } else if (type == InvestmentType::POLITICAL) {
        auto layer = MIRPoliticalLayer::create(this);
        layer->setMIRDelegate(this);
        la = layer;
    } else if (type == InvestmentType::SUPERCHARGE) {
        auto layer = MIRSuperchargeLayer::create(this);
        layer->setMIRDelegate(this);
        la = layer;
    }
    la->setPosition(Point::ZERO);
    addChild(la, Z_Pop, tag);
    _popLayer = la;
}

Sequence* MIRGameLayer::fadeIn()
{
    auto ac = CallFuncN::create([=](Ref *sender){
        Node *n = (Node *)sender;
        n->setVisible(true);
        n->setOpacity(0);
    });
    auto ac1 = FadeIn::create(FadeInTime);
    auto callbak = CallFuncN::create([=](Ref *sender){
    
        
    });
    return Sequence::create(ac, ac1, callbak, NULL);
}

void MIRGameLayer::itemClick(Ref *sender)
{
    MenuItem *item = (MenuItem *)sender;
    int itemTag = item->getTag();
    this->playEffect(SOUND_BUTTON);
    _cpFlag2 = _cpFlag1 = true;
    switch (itemTag) {
        case 1:{
            
            _bucketLayer = MIRBucketLayer::create(this);
            addChild(_bucketLayer, Z_Menu + 1, itemTag);
            
            //test
//            NotificationCenter::getInstance()->postNotification("GetMoneyFromWall", String::create("2600"));
            
        }break;
        case 2:{
            item->setVisible(false);
            auto layer = MIRGetEnvelopLayer::create(this, MIRGetEnvelopLayer::Type::Normal);
            addChild(layer, Z_Envelope + 1, itemTag);
        }break;
        case 3:{
            
            
            auto layer = MIRGetEnvelopLayer::create(this, MIRGetEnvelopLayer::Type::Super);
            addChild(layer, Z_Envelope + 1, itemTag);
        }break;
        case 30:{
            showInvestmentLayer(InvestmentType::FINANCIAL);
            _bottomBarClickIdx++;
            
//            AdManager::getInstance()->setShowInterstitial(true);
        }break;
        case 31:{
            showInvestmentLayer(InvestmentType::BUSINESS);
            _bottomBarClickIdx++;
            
//            AdManager::getInstance()->setShowBanner(true);
        }break;
        case 32: {
            showInvestmentLayer(InvestmentType::POLITICAL);
            _bottomBarClickIdx++;
        }break;
        case 33:{
            //test
            showInvestmentLayer(InvestmentType::SUPERCHARGE);
            _bottomBarClickIdx++;
//            auto la = MIRSpinLayer::create(this);
//            la->setMIRDelegate(this);
//            addChild(la, Z_Menu + 1, 40);
        }break;
        default:
            break;
    }
}

void MIRGameLayer::addAutoAddGold(long double gold)
{
    setAutoAddGold(_autoAddGold + gold);
}

void MIRGameLayer::setAutoAddGold(long double gold)
{
    if (_autoAddGold != gold) {
        _autoAddGold = gold;
        
        char tmpStr[128] = {0};
        sprintf(tmpStr, "%Lf", _autoAddGold);
        
        ud->setStringForKey("MIR_AUTO_ADD_GOLD", tmpStr);
        ud->flush();
        
        if (_autoAddGold >= 1) {
            if (!SimpleAudioEngine::getInstance()->isBackgroundMusicPlaying()) {
                this->playBackgroundMusic(SOUND_PAPER_FLUTTERS);
            } else {
                SimpleAudioEngine::getInstance()->stopBackgroundMusic();
            }
        }
        
        std::string str;
        if (_autoAddGold == 0.5 && !_wrapTotalGold) {
            str = std::string("￥0.5 / 秒");
        } else {
            str = std::string("￥" + KTUtils::MIRString(_autoAddGold + _wrapTotalGold) + " / 秒");
        }
        _rateLabel->setString(str);
    }
}

void MIRGameLayer::setWrapTotalGold(long double gold)
{
    if (_wrapTotalGold != gold) {
        _wrapTotalGold = gold;
        
        std::string str;
        if (_autoAddGold == 0.5 && !_wrapTotalGold) {
            str = std::string("￥0.5 / 秒");
        } else {
            str = std::string("￥" + KTUtils::MIRString(_autoAddGold + _wrapTotalGold) + " / 秒");
        }
        _rateLabel->setString(str);
    }
}

long double MIRGameLayer::getWrapTotalGold()
{
    return _wrapTotalGold;
}

long double MIRGameLayer::getWrapAddGold()
{
    return _wrapAddGold;
}

void MIRGameLayer::setWrapAddGold(long double var)
{
    _wrapAddGold = var;
    
    char tmpStr[128] = {0};
    sprintf(tmpStr, "%Lf", _wrapAddGold);
    
    ud->setStringForKey("MIR_WRAP_ADD_GOLD", tmpStr);
    ud->flush();
}


void MIRGameLayer::addGold(long double add)
{
    setGold(_gold + (long double)add);
}

void MIRGameLayer::setGold(long double gold)
{
    if (_gold != gold) {
        _gold = gold;
        //1914780000407
        if (ud->getBoolForKey("MIR_HAVE_POP_BUCKET") == false) {
            
            if (_gold >= 30) {
                _bucketItem->setVisible(true);
                
                auto la = MIRBucketTipLayer::create(this);
                addChild(la, 512);
                
                
                data->addBucketFlow(50);
                data->addBucketTotalCapacity(300);
                
                ud->setBoolForKey("MIR_HAVE_POP_BUCKET", true);
                ud->setIntegerForKey("POLITICAL_LEVEL_15", 1);
                ud->flush();
                _gold -= 30;
            }
            
        }
        
        if (ud->getBoolForKey("MIR_HAVE_POP_80") == false) {
            if (_gold >= 80) {
                showTipLayer("", "做一个金融投资，更快获得收益!");
                ud->setBoolForKey("MIR_HAVE_POP_80", true);
                ud->flush();
            }
        }
        if (ud->getBoolForKey("MIR_HAVE_POP_100") == false) {
            if (_gold >= 200) {
                showTipLayer("", "做一个商业投资，获得更高收益!");
                ud->setBoolForKey("MIR_HAVE_POP_100", true);
                ud->flush();
            }
        }
        
        if (_gold < 0) {
            _gold = 0;
        }
        
        char tmpStr[128] = {0};
        sprintf(tmpStr, "%Lf", _gold);

        
        ud->setStringForKey("MIR_GOLD", tmpStr);
        ud->flush();
        
        int dig = KTUtils::getNumDig(_gold);
        if (dig != _labels.size()) {
            for (auto label : _labels) {
                removeChild(label);
            }
            _labels.clear();
            for (int i = 0; i < dig; i++) {
                auto label = MIRLabel::create(0);
                addChild(label, Z_Label);
                _labels.push_back(label);
            }
            layoutLabels();
        }
        updateLabels();
    }
}

long double MIRGameLayer::getGold()
{
    return _gold;
}

void MIRGameLayer::addWrapAddGold(long double add)
{
    setWrapAddGold(_wrapAddGold + add);
}

MIRGameLayer::MIRGameLayer()
: _touchCash(NULL)
, _gold(0)
, _popLayer(NULL)
, _elipse1(0)
, _autoAddCounter(0)
, _autoAddGold(0)
, _spacingLabel(0)
, _spacingAdd(0)
, _wrapAddGold(0)
, _wrapFactor(0)
, _wrapTotalGold(0)
, _bucketLayer(NULL)
, _isCashGold(false)
, _elapsed60(0)
, _elapsed20(0)
, _bucketItem(NULL)
, _cpFlag1(false)
, _cpFlag2(false)
, _noGoldCounter(0)
, _hand(nullptr)
{
    

}

MIRGameLayer::~MIRGameLayer()
{
    NotificationCenter::getInstance()->removeAllObservers(this);
    
    _touchCashes.clear();
}

