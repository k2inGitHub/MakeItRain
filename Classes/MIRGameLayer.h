//
//  MIRGameLayer.h
//  MakeItRain
//
//  Created by SongYang on 14-5-7.
//
//

#ifndef __MakeItRain__MIRGameLayer__
#define __MakeItRain__MIRGameLayer__

#include "cocos2d.h"
#include "KTLayer.h"
#include "MIRLabel.h"
#include "KTPauseLayer.h"
#include "MIRConfig.h"
#include "MIRDelegate.h"
#include "MIRBucketLayer.h"
USING_NS_CC;

class MIRGameLayer : public KTLayer, KTPauseLayerDelegate, MIRDelegate {
    
public:
    
    Sprite *_hand;
    
    float _timeNormalEnvelope = 0;
    
    float _elapseNormalEnvelope = 0;
    
    int _bottomBarClickIdx = 0;
    
    void purchase(int index);
    
    //插屏逻辑 false 无操作 true 有操作
    bool _cpFlag1;
    
    bool _cpFlag2;
    
    int _noGoldCounter;
    
    int _purchaseIdx;
    
    void purchaseFinish(Ref *sender);
    
    void purchaseFail(Ref *sender);
    
    bool _canTouch = true;
    
    std::vector<Color3B> _changeColors;
    
    LayerColor *_tintRect;
    
    MenuItemImage *_bucketItem;
    
    MenuItemImage *_normalEnvelopeItem;
    
    MenuItemImage *_superEnvelopeItem;
    
    Label *_superEnvLabel;
        
    float BASE_SPACING_LABEL = 64.f;
    
    float BASE_SPACING_ADD   = 10.f;
    
    float Cash_Width         = 40.0f;
    
    UserDefault *ud;
    
    void firstInit();
    
    MIRBucketLayer *_bucketLayer;
    
    
    Color3B _changeColor;
    
    int _wrapFactor;
    
    CC_PROPERTY(long double , _wrapTotalGold, WrapTotalGold);
    
    //每次拖动会增加的金币 sum = (_wrapAddGold * (cashCount + 1)) * factor factor = 0.3s内cashCount 橙色以上的颜色
//    CC_SYNTHESIZE(long double, _wrapAddGold, WrapAddGold);
    CC_PROPERTY(long double, _wrapAddGold, WrapAddGold);
    
    void addWrapAddGold(long double add);
    
    void popBucketLayer(Ref *sender);
    
    Sprite *_wrap;
    
    Label *_wrapLabel;
    
    DrawNode *_drawer;
    
    Vector<Sprite *> _touchCashes;
    
    int _counterUpdate_3;
    
    //label间距
    float _spacingLabel;
    
    ///3个之间的增量
    float _spacingAdd;
    
    //挂机金币增加计数器
    long double _autoAddCounter;
    //挂机金币增加数量s
    long double _autoAddGold;
    
    long double getAutoAddGold(){return _autoAddGold;};
    
    void setAutoAddGold(long double gold);
    
    void addAutoAddGold(long double gold);

    
    //每秒钱数
    Label *_rateLabel;
    
    //计时器间隔 1s的
    float _elipse1 = 0;
    //60s 计时器
    float _elapsed60 = 0;
    
    float _elapsed20 = 0;
    
    float _elapsed30 = 0;
    
    Label *_cashLabel;
    
    Sequence* fadeIn();
    
    std::vector<MIRLabel *> _labels;
    
    void addGold(long double add);
    
    CC_PROPERTY(long double , _gold, Gold);
    
    LayerColor *_bgLayer;
    
    Sprite *_cash;
    
    Sprite *_touchCash;
    
    Layer *_popLayer;
    
    LayerColor *_menuBg;
    
    bool _isCashGold;
    
    void startLableCallback(Ref *sender);
    
    void createGoldenCash();
    
    virtual void resetAll();
    
    virtual void setItemTouched(int index, Layer *setLayer);
    
    virtual void spinResult(MIRSpinType res, Layer *spinLayer);
    
    virtual bool itemCanLevelUp(MIRModel *m);
    
    void updateWrap();
    
    //label刷新
    void updateLabels();
    //label布局
    void layoutLabels();
    
    void cashFly(int number, int zOrder);
    
    void showInvestmentLayer(InvestmentType type);
    
    void itemClick(Ref *sender);
    
    void cashMoveCallback(Ref *sender);
    
    virtual void update(float dt);
    
    void update_3(float dt);
    
    void update_2(float dt);
    
    ///恢复游戏
//    virtual void pauseLayerDidResume(KTPauseLayer *layer);
//    ///重新开始游戏
//    virtual void pauseLayerDidRestart(KTPauseLayer *layer);
    ///退出
    virtual void pauseLayerDidQuit(KTPauseLayer *layer);
    ///取消
    virtual void pauseLayerDidCancel(KTPauseLayer *layer);
    ///确定
    virtual void pauseLayerDidMakeSure(KTPauseLayer *layer);
    
    virtual bool onTouchBegan(Touch *touch, Event *unused_event);
    virtual void onTouchMoved(Touch *touch, Event *unused_event);
    virtual void onTouchEnded(Touch *touch, Event *unused_event);
    virtual void onTouchCancelled(Touch *touch, Event *unused_event);
    
    virtual bool init();
    
    MIRGameLayer();
    
    ~MIRGameLayer();
    
    CREATE_FUNC(MIRGameLayer);
    
    static Scene* scene(){
        auto *sc = Scene::create();
        auto *la = MIRGameLayer::create();
        sc->addChild(la);
        return sc;
    }
};

#endif /* defined(__MakeItRain__MIRGameLayer__) */
