//
//  MIRBucketLayer.cpp
//  MakeItRain
//
//  Created by SongYang on 14-5-8.
//
//

#include "MIRBucketLayer.h"
#include "MIRConfig.h"

void MIRBucketLayer::setBucketHeight(float scale)
{
    float totalHt = 300;
    float totalScale = 0.5;

    _bucketEllipse->setPosition(VisibleRect::center() + Point(0, - 250 + totalHt * scale) * _scale);
    _bucketEllipse->setScale(1 + totalScale * scale);
    _bucketFill->setPosition(_bucketEllipse->getPosition());
}

bool MIRBucketLayer::init(KTPauseLayerDelegate *delegate)
{
    if (!KTPauseLayer::init(delegate)) {
        return false;
    }
    
    data = MIRDynamicData::getInstance();
    
    auto bg = LayerColor::create(Color4B(0, 0, 0, 128));
    addChild(bg);
    
    auto water = Sprite::create();
    water->setPosition(VisibleRect::center() + Point(0, -30) * _scale);
    addChild(water);
    
    auto animation = KTFactory::createAnimation("water_stream_", 5, 1, 0.05, -1);
    auto animate = Animate::create(animation);
    water->runAction(animate);
    
    
    //NEW
    auto clip = ClippingNode::create();//设置裁剪节点
    clip->setInverted(false);//设置底板可见
    clip->setAlphaThreshold(0.0f);//设置透明度Alpha值为0
    this->addChild(clip,10);
    
    _bucketEllipse = Sprite::create("bucket_ellipse.png");
    clip->addChild(_bucketEllipse,2);
    
    _bucketFill = Sprite::create("bucket_filled.png");
    _bucketFill->setAnchorPoint(Point::ANCHOR_MIDDLE_TOP);
    _bucketFill->setPosition(_bucketEllipse->getPosition());
    clip->addChild(_bucketFill, 1);
    
    setBucketHeight(data->getBucketCapacity()/data->getBucketTotalCapacity());
    

    //创建模板，也就是你要在裁剪节点上挖出来的那个”洞“是什么形状的，这里我用close的图标来作为模板
    auto nodef = Node::create();//创建模版
    auto close = Sprite::create("bucket_tap.png");//这里使用的是close的那个图标
    close->setAnchorPoint(Point::ANCHOR_MIDDLE_RIGHT);
    nodef->addChild(close);//在模版上添加精灵
    nodef->setPosition(Point(winSize.width, winSize.height/2));//设置的坐标正好是在close button的坐标位置上
    addChild(nodef, 20);
    clip->setStencil(nodef);//设置模版
    
    
    _flowLabel = Label::createWithTTF("￥" + KTUtils::MIRString(floorl(data->getBucketFlow())), TITLE_FONT, 30 * _scale);
    _flowLabel->setPosition(Point(150, 170) * _scale + VisibleRect::center());
    addChild(_flowLabel, 64);
    
    auto hour = Label::createWithTTF("/小时", TITLE_FONT, 30 * _scale);
    hour->setPosition(VisibleRect::center() + Point(150, 140) * _scale);
    addChild(hour, 64);
    
    _capacityLabel = Label::createWithTTF("￥" + KTUtils::MIRString(data->getBucketCapacity()), TITLE_FONT, 60 * _scale);
    _capacityLabel->setPosition(VisibleRect::center() + Point(0, -110) * _scale);
    _capacityLabel->setColor(Color3B(46, 127, 85));
    addChild(_capacityLabel, 64);
    
    _totalCapacityLabel = Label::createWithTTF("/￥" + KTUtils::MIRString(data->getBucketTotalCapacity()), TITLE_FONT, 60 * _scale);
    _totalCapacityLabel->setPosition(VisibleRect::center() + Point(0, -170) * _scale);
    _totalCapacityLabel->setColor(Color3B(46, 127, 85));
    addChild(_totalCapacityLabel, 64);
    
    
    auto increaseItem = MenuItemImage::create("bucket_increase_size_button.png", "bucket_increase_size_button.png", [=](Ref *sender){
        this->playEffect(SOUND_BUTTON);
        doQuit();
    });
    increaseItem->setAnchorPoint(Point::ANCHOR_BOTTOM_LEFT);
    increaseItem->setPosition(VisibleRect::leftBottom() + Point(20, 20) * _scale);
    
    auto collectItem = MenuItemImage::create("bucket_collect_button.png", "bucket_collect_button.png", [=](Ref *sender){
    
        this->playEffect(SOUND_BUTTON);
        doMakeSure();
    });
    collectItem->setAnchorPoint(Point::ANCHOR_BOTTOM_RIGHT);
    collectItem->setPosition(VisibleRect::rightBottom() + Point(-20, 20) * _scale);
    
    auto cancelItem = MenuItemImage::create("close_investments.png", "close_investments.png", [=](Ref *sender){
        this->playEffect(SOUND_BUTTON);
        doCancel();
    });
    cancelItem->setAnchorPoint(Point::ANCHOR_TOP_RIGHT);
    cancelItem->setPosition(VisibleRect::rightTop() + Point(-20, -90) * _scale);
    cancelItem->setScale(1.5);
    
    Menu *menu = Menu::create(increaseItem, collectItem, cancelItem, NULL);
    menu->setAnchorPoint(Point::ZERO);
    menu->setPosition(Point::ZERO);
    addChild(menu);
    
    return true;
}