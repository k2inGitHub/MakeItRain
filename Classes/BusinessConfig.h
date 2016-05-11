

#include "cocos2d.h"

// 以下都是iOS平台的参数体系

// AppStore 应用ID
#define AppId           @"927785105"

// 用户分析 - 友盟ID
#define umengAppKey     @"53c89ed256240bcfc608241b"

// 广告 ------------------------------------------------

// 是否使用横幅广告
#define AdAdvertise     true

// 芒果广告 ID - iPhone和iPad版
#define AdKeyiPhone     @"7050b47d1eed462da707dcda173aefed"
#define AdKeyiPad       @"2146cb050e5f463da32496966db4be0e"

// iPhone版广告条位置
#define WinSize cocos2d::CCDirector::sharedDirector()->getWinSize()
#define AdFrameiPhone   CGPointMake(0, WinSize.height - 45)
// iPad版广告条位置
#define AdFrameiPad     CGPointMake(10, WinSize.height - 90)

// 全屏广告

// 是否使用全屏广告
#define AdFullAdvertise     true

// 是否显示测试按钮，用于调试全屏广告
#define AdFullAdvertiseDebug    false

// 全屏广告iPhone Key
#define AdFullKeyiPhone  @"7050b47d1eed462da707dcda173aefed"

// 全屏广告iPad Key
#define AdFullKeyiPad  @"2146cb050e5f463da32496966db4be0e"


// 点入 0000C40B0F000049
#define WallDianRuAppKey        @"0000490B11000049"
// 多盟
#define WallDomobPublisherId    @"96ZJ0C2wzehW7wTALj"
// 力美
#define WallImmobUnitId         @"103c9b844b95abfee4a500c1d5f71696"
// 人人网
#define aderWallId @"e64a165483ec4fe5ab56fa5fbfd404c0"
//MobiSage
#define WallMobiSageId          @"c477ad73e9b146c18731e2444af5d58f"
#define WallMobiSageIdDemo      @"c477ad73e9b146c18731e2444af5d58f"
//发布ID： 046d56f5f0fe2001应用密钥： 33e764c5eecafa3a
//有米
#define YouMiWallId  @"794a48de547b9e0b"
#define YouMiKey  @"48ca7e2c1cd3fb47"


#define wallDianJinkey  @"f0d8919934c38797389ac783b3ea251e"


// 应用评价弹窗 ------------------------------------------------
#define RateQuote           @"喜欢城管来了吗, 给个5星好评吧! 激励我们推出更多免费升级! ^_^"
#define RateTitle           @"鼓励一下我们吧"
#define RateCancel          @"No, Thanks"
#define RateLater           @"就不给"
#define RateOK              @"就不给"

#define RateDaysUntilPrompt  1
#define RateUserUntilPrompt  10
#define RateSigEventsUntilPrompt  -1
#define RateTimeBeforeReminding  1


// 本地通知 ------------------------------------------------
#define LocalNotificationQuote  @"亲们，赶紧来吧，潮叔等得花儿都谢了！~现在进入游戏免费拿金币哦~"
#define LocalNotificationCancel @"没空啦"

// 远程通知 ------------------------------------------------
#define UseRemoteNotification   false
#define DeviceTokenServer   @"http://211.99.196.19/apns/getToken.php"
#define DeviceTokenAppId    @"16"


// GameCenter ------------------------------------------------
#define UseGameCenter   true

//every play 录屏
#define CLIENT_ID @"55db1a4997102ca92c4d71073e155d3c5d1daf1f"
#define CLIENT_SECRET @"5f985b00dc70c4b98214991ce1428f07060332f8"








