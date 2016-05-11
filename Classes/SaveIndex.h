//
//  SaveIndex.h
//  zuanshimicheng
//
//  Created by zhangrui on 13-10-16.
//
//

#ifndef zuanshimicheng_SaveIndex_h
#define zuanshimicheng_SaveIndex_h
//
static inline CCPoint
ccpTransferPosition(CCPoint pos)
{
    return ccp(pos.x/CC_CONTENT_SCALE_FACTOR(),pos.y/CC_CONTENT_SCALE_FACTOR());
}

#define DOWN_HEIGHT 90/CC_CONTENT_SCALE_FACTOR()

//game debug
//#define GAME_DEBUG // 调试模式 枪全部解锁
//game config

#define HERO_MAX 6
#define WEAPON_MAX 100
#define BOSS_MAX 300
#define VIP_MAX 20
#define PLANDER_MAX 100

//game config end
//**************************************************//
#define SAVE_FIRST "first_game"

#define SAVE_TIME "save_time"

#define SAVE_MONEY "save_money"
#define SAVE_TOTAL_MONEY "save_total_money"
#define TOTAL_HARM "total_harm"
#define TOTAL_TAP "total_tap"
#define TOTAL_REWARD "total_reward"

#define HERO_COUNT "hero_count%d"
#define HERO_LEVEL "hero_level%d"
#define HERO_ADDHIT "hero_addhit%d"

#define BOSS_CURRENT_HEALTH "boss_current_health"
#define BOSS_KILL_COUNT "boss_kill_count"


#define OTHER_WEAPON_ADD "other_weapon_add%d"
#define WEAPON_IS_BUY "weapon_is_buy%d"


#define SAVE_SPEED_COUNT "save_speed_count"
#define SAVE_SPEED_TIME "save_speed_time"

#define SAVE_EGG_TIME "save_egg_time%d"
#define SAVE_IS_PET "save_is_pet%d"

#define SAVE_SW_COUNT "save_sw_count"
#define SAVE_PET_SW_COUNT "save_pet_sw_count"


#define SAVE_VIP "save_vip"
#define SAVE_VIP_GIFT "save_vip_gift%d"

#define CHECK_BANNER "check_banner"

#define SAVE_PHONE_MONEY "save_phone_money"
#define SAVE_IS_TURNTABLE "save_is_turntable"


#define SAVE_BOSS_TIME "save_boss_time"

#define SAVE_PLANDER_TIME "save_plander_time"


#define SAVE_HIGH_SEC_HIT "save_high_sec_hit"
#define SAVE_UNIT_TIME "save_unit_time"
#define SAVE_HIGH_UNIT_TIME "save_high_unit_time"


#define SAVE_DANMU_APPEAR "save_danmu_appear%d"

#define SAVE_PET_HAND "save_pet_hand%d"


//微信
#define SAVE_WEIXIN_SENT "save_weixin_sent"
#define SAVE_WEIXIN_NEXT_TIME "save_weixin_next_time"
#define SAVE_WEIXIN_DAY_TIME "save_weixin_day_time"

#define SAVE_WEIXIN_IS_FRIEND "save_weixin_is_friend"

#define SAVE_GET_WEIXIN_GIFT "save_get_weixin_gift"


#define SAVE_TIME_SEC "save_time_sec"

//game save

#define SCORE_WALL_OPEN (CCUserDefault::sharedUserDefault()->getIntegerForKey("ScoreWall")>0)
#define RATE_OPEN (CCUserDefault::sharedUserDefault()->getIntegerForKey("rate")>0)
#define MORE_GAME_OPEN (CCUserDefault::sharedUserDefault()->getIntegerForKey("recommend")>0)

#endif
