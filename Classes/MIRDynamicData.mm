//
//  MIRDynamicData.cpp
//  MakeItRain
//
//  Created by SongYang on 14-5-13.
//
//

#include "MIRDynamicData.h"
#include "MIRConfig.h"
#include "KTUtils.h"
#include "MIRGameLayer.h"
#import <Foundation/Foundation.h>

void MIRDynamicData::localNotification()
{
    NSTimeInterval t = 3600.f * (getBucketTotalCapacity() - getBucketCapacity() )/getBucketFlow();
    
    NSDateFormatter *formatter = [[NSDateFormatter alloc] init];
    NSTimeZone *timeZone = [NSTimeZone localTimeZone];
    [formatter setTimeZone:timeZone];
    [formatter setDateFormat : @"yyyy/MM/dd HH:mm:ss"];

    NSDate *tarDate = [NSDate dateWithTimeInterval:t sinceDate:[NSDate date]];
    [formatter release];
    
    UILocalNotification *notification = [[UILocalNotification alloc]init];
    notification.repeatInterval = NSDayCalendarUnit;
    [notification setAlertBody:[NSString stringWithUTF8String:LOCAL_NOTIF_BODY]];
    [notification setFireDate:tarDate];
    [notification setTimeZone:[NSTimeZone  localTimeZone]];
    [[UIApplication sharedApplication] setScheduledLocalNotifications:[NSArray arrayWithObject:notification]];
    [notification release];
}

int MIRDynamicData::getBribe()
{
    return ud->getIntegerForKey("MIR_BRIBE", BaseBribe);
}

void MIRDynamicData::setBribe(int val)
{
    ud->setIntegerForKey("MIR_BRIBE", val);
    ud->flush();
    NotificationCenter::getInstance()->postNotification("MIR_UPDATE_BRIBE");
}

bool MIRDynamicData::getSoundOff()
{
    return ud->getBoolForKey("MIR_SOUNDOFF", false);
}

void MIRDynamicData::setSoundOff(bool val)
{
    ud->setBoolForKey("MIR_SOUNDOFF", val);
    ud->flush();
}

void MIRDynamicData::bucketAutoAdd()
{
    struct tm t = KTUtils::getCurrentTime();
    struct tm last = t;
    
    last.tm_year = ud->getIntegerForKey("MIR_TIME_YEAR", t.tm_year);
    last.tm_mon = ud->getIntegerForKey("MIR_TIME_MON", t.tm_mon);
    last.tm_mday = ud->getIntegerForKey("MIR_TIME_DAY", t.tm_mday);
    last.tm_hour = ud->getIntegerForKey("MIR_TIME_HOUR", t.tm_hour);
    last.tm_min = ud->getIntegerForKey("MIR_TIME_MIN", t.tm_min);
    last.tm_sec = ud->getIntegerForKey("MIR_TIME_SEC", t.tm_sec);
    
    last.tm_zone = t.tm_zone;
    
    
    time_t tt1 = mktime(&last), tt2 = mktime(&t);
    
    double dt = difftime(tt2, tt1);
    
    CCLOG("bucketAutoAdd dt = %f", dt);
    
    addBucketCapacity(getBucketFlow()/3600.f * dt);
    
    addSuperEnvTimer(dt);
}

void MIRDynamicData::addBribe(int add)
{
    setBribe(getBribe() + add);
}

void MIRDynamicData::addBucketTotalCapacity(long double add)
{
    setBucketTotalCapacity(_bucketTotalCapacity + add);
}

void MIRDynamicData::setBucketCapacity(long double var)
{
    if (_bucketCapacity != var) {
        
        if (var > _bucketTotalCapacity) {
            //满了
            
            if (_bucketCapacity != _bucketTotalCapacity) {
                _bucketCapacity = _bucketTotalCapacity;
                
                NotificationCenter::getInstance()->postNotification("MIR_POP_BUCKET");
            }
        } else {
            _bucketCapacity = var;
            if (_bucketCapacity < 0) {
                _bucketCapacity = 0;
            }
        }
        
        char tmpStr[128] = {0};
        sprintf(tmpStr, "%Lf", _bucketCapacity);
        
        ud->setStringForKey("MIR_BUCKET_CAPACITY", tmpStr);
        ud->flush();
        
    }
}

long double MIRDynamicData::getBucketCapacity()
{
    return _bucketCapacity;
}

void MIRDynamicData::setBucketFlow(long double var)
{
    _bucketFlow = var;
    
    char tmpStr[128] = {0};
    sprintf(tmpStr, "%Lf", _bucketFlow);
    
    ud->setStringForKey("MIR_BUCKET_FLOW", tmpStr);
    ud->flush();
}

long double MIRDynamicData::getBucketFlow()
{
    return _bucketFlow;
}

void MIRDynamicData::setBucketTotalCapacity(long double var)
{
    _bucketTotalCapacity = var;
    
    char tmpStr[128] = {0};
    sprintf(tmpStr, "%Lf", _bucketTotalCapacity);
    
    ud->setStringForKey("MIR_BUCKET_TOTAL_CAPACITY", tmpStr);
    ud->flush();
}

long double MIRDynamicData::getBucketTotalCapacity()
{
    return _bucketTotalCapacity;
}


void MIRDynamicData::addBucketFlow(long double add)
{
    setBucketFlow(_bucketFlow + add);
}

void MIRDynamicData::addBucketCapacity(long double add)
{
    setBucketCapacity(_bucketCapacity + add);
}

MIRDynamicData::MIRDynamicData()
{

    ud = UserDefault::getInstance();
    
    char tmpStr[128] = {0};
    sprintf(tmpStr, "%Lf", BaseBucketFlow);
    
    
    _bucketFlow = KTUtils::atold(ud->getStringForKey("MIR_BUCKET_FLOW", tmpStr).c_str());
    
    sprintf(tmpStr, "%Lf", BaseBucketTotalCapacity);
    
    _bucketTotalCapacity = KTUtils::atold(ud->getStringForKey("MIR_BUCKET_TOTAL_CAPACITY", tmpStr).c_str());

    _bucketCapacity = KTUtils::atold(ud->getStringForKey("MIR_BUCKET_CAPACITY", "0").c_str());//_bucketCapacity
    
}

MIRDynamicData::~MIRDynamicData()
{



}

static MIRDynamicData *_shInstance = NULL;

MIRDynamicData* MIRDynamicData::getInstance()
{
    if (_shInstance == NULL) {
        _shInstance = new MIRDynamicData();
    }
    return _shInstance;
}