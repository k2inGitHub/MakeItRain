//
//  MIRConfig.h
//  MakeItRain
//
//  Created by SongYang on 14-5-7.
//
//

#ifndef MakeItRain_MIRConfig_h
#define MakeItRain_MIRConfig_h

#include "KTUtils.h"

#define LOCAL_NOTIF_BODY    "水桶内奖金已满，请您尽快领取现金！"

static const char* inAppIDs[] = {"com.champagnebo.qian.meizhangdouble1", "com.champagnebo.qian.meimiaodouble", "com.champagnebo.qian.lijihuode", "com.champagnebo.qian.mianzui5", "com.champagnebo.qian.mianzui25"};

const Color3B MIRBrown  (97, 16, 14);

const Color4B MIRCellColor (178, 143, 223, 255);//Color4B(239, 73, 58, 255) 默认红色

#define TITLE_FONT  "fonts/DFPHeiW9-GB.TTF"//"fonts/Avenir LT 95 Black.ttf"

#define TIP_FONT    "fonts/DFPHeiW9-GB.TTF"//"fonts/Shag-Lounge.ttf"

#define BUCKET_TIP_CONTENT  "成功获取现金!"

#define FINANCIAL_TIP_CONTENT   "每秒收益提高!"

#define BUSINESS_TIP_CONTENT    "每张收益增加!"

#define POLITICAL_TIP_CONTENT   "收益提高!"

#define POLITICAL_TIP_CONTENT2   "容量增大!"

#define SOUND_BUTTON    "Sounds/button.mp3"
#define SOUND_MSG       "Sounds/msg.mp3"
#define SOUND_PAPER_FLUTTERS    "Sounds/paper_flutters.mp3"
#define SOUND_REG       "Sounds/register.mp3"
#define SOUND_SIREN     "Sounds/siren.mp3"
#define SOUND_SWIPE0    "Sounds/swipe0.mp3"
#define SOUND_SWIPE1    "Sounds/swipe1.mp3"
#define SOUND_SWIPE2    "Sounds/swipe2.mp3"
#define SOUND_SWIPE3    "Sounds/swipe3.mp3"
#define SOUND_SWIPE4    "Sounds/swipe4.mp3"
#define SOUND_WHEEL     "Sounds/wheel.mp3"


enum class MIRSpinType {
    
    GUILTY,
    SEIZURE,
    NOT_GUILTY,
    MIRACLE,
    PLEA,
    
    EMPTY,
};

enum class InvestmentType
{
    FINANCIAL,
    BUSINESS,
    POLITICAL,
    SUPERCHARGE,
};

#define BaseBucketFlow              ((long double)0) //50

#define BaseBucketTotalCapacity     ((long double)0) //300

#define BaseWrapAddGold             ((long double)1)

#define BaseGold                    ((long double)0)

#define BaseAutoAddGold             ((long double)0)

#define BaseBribe                   ((long double)1)

const static char* wrapFile[10] = {
    
    "wrap_rubberband.png",
    "wrap_paper.png",
    "wrap_bronze.png",
    "wrap_silver.png",
    "wrap_gold.png",
    "wrap_platinum.png",
    "wrap_diamond.png",
    "wrap_led.png",
    "wrap_crocodile.png",
    "wrap_lasers.png",

};

const long double wrapFactor[10] = {

    0,
    10,
    100,
    1000,
    10000,
    100000,
    1000000,
    1000000000,
    100000000000,
    100000000000000,

};

const long double financialFactor[] = {
    1,
    5,
    20,
    100,
    487.5,
    1950,
    8125,
    20250,
    40625,
    65000,
    609375,
    6500000,
    97500000,
    8125000000,
    275000000000,
    1206250000000,
    15000000000000,
    325000000000000,
    4875000000000000,
};

const long double politicalFactor[] = {
    1,
    5,
    7.5,
    15,
    62.5,
    165,
    625,
    5000,
    50000,
    187500,
    1000000,
    45000000,
    250000000,
    1625000000,
    50000000000,
    10000000000000,
};

#endif
