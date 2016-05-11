//
//  KTUtils.cpp
//  colorful
//
//  Created by SongYang on 13-10-27.
//
//

#include "KTUtils.h"
#import <Foundation/Foundation.h>

const char* KTUtils::localString(const char *key)
{
    NSString *str = NSLocalizedString([NSString stringWithUTF8String:key], nil);
    return str.UTF8String;
}

//CCSprite *createSpriteFromWriteablePath(const char* name)
//{
//    std::string path = CCFileUtils::sharedFileUtils()->getWritablePath();
//    path+=name;
//    FILE* fp = fopen(path.c_str(),"rb");
//    if (!fp)
//    {
//        return NULL;
//    }
//    fseek(fp,0,SEEK_END);
//    int len = ftell(fp);
//    fseek(fp,0,SEEK_SET);
//    char* buf = (char*)malloc(len);
//    fread(buf,len,1,fp);
//    fclose(fp);
//    CCImage* img = new CCImage;
//    img->initWithImageData(buf,len);
//    free(buf);
//    cocos2d::CCTexture2D* texture = new cocos2d::CCTexture2D();
//    bool isImg = texture->initWithImage(img);
//    img->release();
//    if (!isImg)
//    {
//        delete texture;
//        return CCSprite::create("50black.png");//加载资源并非图片时返回的默认图
//    }
//    CCSprite* sprite = CCSprite::createWithTexture(texture);
//    texture->release();
//    return sprite;
//}
