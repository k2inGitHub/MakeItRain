//
//  LocalScoreLoader.h
//  BookReader
//
//  Created by terababy on 10-8-26.
//  Copyright 2010 terababy. All rights reserved.
//

#ifndef __GameHelper_H__
#define __GameHelper_H__

#include "cocos2d.h"

USING_NS_CC;

//addon


#define screenSize CCDirector::getInstance()->getWinSize()

#define isLandscape ((screenSize.width>screenSize.height)?1:0) 
#define isPortrait ((screenSize.width<screenSize.height)?1:0)


// 屏幕长边上的比率
#define LPRatio ((isLandscape==1)?screenSize.width/screenSize.height:screenSize.height/screenSize.width)
#define LandRatio ((isLandscape==1)?screenSize.width/1024.0f:screenSize.height/1024.0f)
// 屏幕窄边上的比率
#define PortRatio ((isPortrait==1)?screenSize.width/768.0f:screenSize.height/768.0f)


//IOS
#define IS_IPAD ((LandRatio == 1.0f&&PortRatio == 1.0f)?1:0 )
#define IS_IPHONE4 ((LPRatio == 1.5f)?1:0 )
#define IS_IPHONE5 ((LPRatio == 1136.0f/640.0f)?1:0 )

#define IS_RETINA (cocos2d::CCEGLView::sharedOpenGLView()->isRetinaEnabled()?1:0)

// 屏幕短边
#define SHORT_EDGE ((isLandscape==1)?screenSize.height:screenSize.width)
// 屏幕长边
#define TALL_EDGE ((isLandscape==1)?screenSize.width:screenSize.height)

#define IS_SMALL_SCREEN ((SHORT_EDGE<=480)?1:0)

#define IS_BIG_SCREEN ((SHORT_EDGE>480)?1:0)


//添加节点到父节点时，按父节点大小百分比分配位置
static inline CCPoint
ccpContent(CCSize size, float xp, float yp)
{
    return CCPoint(xp * size.width / 100.0f, yp * size.height / 100.0f);
}

//按百分比分配位置
static inline CCPoint
ccpH(float x, float y)
{
    if (SHORT_EDGE > 320){
        return CCPoint(x*2, y*2);
    }
    return CCPoint(x, y);
}

//按百分比分配位置
static inline CCPoint
ccpPercent(float x, float y)
{
    CCSize size = CCDirector::getInstance()->getWinSize();
    return ccpContent(size, x, y);
}

//位置，自动按1024,768生成百分比
static inline CCPoint
ccpAuto(float x, float y)
{
    if (isLandscape) {
        return ccpPercent(x/10.240f, y/7.680f);
    } else {
        return ccpPercent(x/7.680f, y/10.240f);
    }
}

//end


class GameHelper {
    
public:
};

#endif // __GameHelper_H__
