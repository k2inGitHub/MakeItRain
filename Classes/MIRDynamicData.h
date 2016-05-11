//
//  MIRDynamicData.h
//  MakeItRain
//
//  Created by SongYang on 14-5-13.
//
//

#ifndef __MakeItRain__MIRDynamicData__
#define __MakeItRain__MIRDynamicData__

#include "cocos2d.h"
#include "MobClickCpp.h"
#include "MIRConfig.h"
USING_NS_CC;

class MIRGameLayer;

class MIRDynamicData : public Ref {
    
    
public:
    
    const char* getRecURL() {
        auto p = umeng::MobClickCpp::getConfigParam("RecURL");
#if MIR_DEBUG
        if (strcmp(p, "") == 0) {
            p = "http://www.google.com";
        }
#endif
        return p;
    }
    
    const char* getRecText(){
        auto p = umeng::MobClickCpp::getConfigParam("RecText");
#if MIR_DEBUG
        if (strcmp(p, "") == 0) {
            p = "推荐2";
        }
#endif
        return p;
    }
    
    bool getShowRecText(){
        bool ret = false;
        auto p = umeng::MobClickCpp::getConfigParam("ShowRecText");
        if (strcmp(p, "1") == 0) {
            ret = true;
        }
#if MIR_DEBUG
        ret = true;
#endif
        return ret;
    }
    
    float getSuperEnvelopeTime() {
        auto p = umeng::MobClickCpp::getConfigParam("SuperEnvelopeTime");
        if (strcmp(p, "") == 0) {
#if MIR_DEBUG
            p = "30";
#else
            p = "180";
#endif
        }
        return atoi(p);
    }
    
    void addSuperEnvTimer(float add) {
        _superEnvTimer += add;
    }
    
    CC_SYNTHESIZE(float, _superEnvTimer, SuperEnvTimer);
    
    int getRedEnvelopeTime(){
         auto p = umeng::MobClickCpp::getConfigParam("NormalEnvelopeTime");
        if (strcmp(p, "") == 0) {
#if MIR_DEBUG
            p = "10";
#else
            p = "60";
#endif
        }
        return atoi(p);
    }
    
    bool getShowPopup(){
        bool ret = false;
        auto p = umeng::MobClickCpp::getConfigParam("HaoPingSwitch");
        if (strcmp(p, "1") == 0) {
            ret = true;
        }
#if MIR_DEBUG
        ret = true;
#endif
        return ret;
    };
    
    bool getShowNormalEnvelop(){
        bool ret = false;
        auto p = umeng::MobClickCpp::getConfigParam("IsShowNormalEnvelop");
        if (strcmp(p, "1") == 0) {
            ret = true;
        }
#if MIR_DEBUG
        ret = true;
#endif
        return ret;
    }
    
    bool getShowSuperEnvelop(){
        bool ret = false;
        auto p = umeng::MobClickCpp::getConfigParam("IsShowSuperEnvelop");
        if (strcmp(p, "1") == 0) {
            ret = true;
        }
#if MIR_DEBUG
        ret = true;
#endif
        return ret;
    }
    
    const char* getSuperEnvelopeText(){
        auto p = umeng::MobClickCpp::getConfigParam("SuperEnvelopText");
        #if MIR_DEBUG
        if (strcmp(p, "") == 0) {
            p = "下载视频推荐的APP\n有机会开出大红包啊";
        }
        #endif
        return p;
    }
    
    bool getShowSuperEnvelopText(){
        bool ret = false;
        auto p = umeng::MobClickCpp::getConfigParam("IsShowSuperEnvelopText");
        if (strcmp(p, "1") == 0) {
            ret = true;
        }
#if MIR_DEBUG
        ret = true;
#endif
        return ret;
    }
    
    void localNotification();
    
    bool getSoundOff();
    
    void setSoundOff(bool val);
    
    UserDefault *ud;
    
    void bucketAutoAdd();
        
    int getBribe();
    
    void setBribe(int val);
    
    void addBribe(int add);
    
    CC_SYNTHESIZE(MIRGameLayer*, _gameLayer, GameLayer);
    
    //小时单位
    CC_PROPERTY(long double, _bucketFlow, BucketFlow);
    
    void addBucketFlow(long double add);
    
    CC_PROPERTY(long double, _bucketCapacity, BucketCapacity);
    
    void addBucketCapacity(long double add);
    
    CC_PROPERTY(long double, _bucketTotalCapacity, BucketTotalCapacity);
    
    void addBucketTotalCapacity(long double add);
    
    MIRDynamicData();
    
    ~MIRDynamicData();
    
    static MIRDynamicData* getInstance();
};

#endif /* defined(__MakeItRain__MIRDynamicData__) */
