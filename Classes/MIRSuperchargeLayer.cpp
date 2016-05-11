//
//  MIRSuperchargeLayer.cpp
//  MakeItRain
//
//  Created by SongYang on 14-5-15.
//
//

#include "MIRSuperchargeLayer.h"
//#include "Business.h"

const static char* files[] = {
    
    "icon_supercharge_doublecash.png",
    "icon_supercharge_doublecash.png",
    "icon_supercharge_cashblast.png",
//    "icon_supercharge_bribe.png",
//    "icon_supercharge_bribe.png",
    "icon_supercharge_sound.png",
    "icon_supercharge_reset.png",
    
};

const static char* titles[] = {
    "兑换微信红包",
    "看视频并下载得\n海量金币",
    "免费兑换",
//    "5张免罪卡",
//    "25张免罪卡",
    "开启音效",
    "重新开始",
};

const static char* info[] = {

    "GO",
    "GO",
    "GO",
//    "￥6",
//    "￥12",
    "GO",
    "GO",
};

bool MIRSuperchargeLayer::init(KTPauseLayerDelegate *delegate)
{
    if (!KTPauseLayer::init(delegate)) {
        return false;
    }
    
    float tableViewHt;
    float headHt;
    float bgHt;
    if (IS_IPHONE5) {
        tableViewHt = 740;
        bgHt = headHt = 860;
    } else if (IS_IPAD) {
        
        tableViewHt = 580;
        bgHt = headHt = 700;
    } else if (IS_IPAD_HD) {
        tableViewHt = (580 + 100)*2;
        bgHt = headHt = (700 + 100)*2;
    } else {
        tableViewHt = 540;
        bgHt = headHt = 660;
    }
    
    
    ud = UserDefault::getInstance();
    
    auto bg = LayerColor::create(MIRCellColor, winSize.width, bgHt);
    addChild(bg, -1);
    
    
    _dataArray = new Array();
    _dataArray->init();
    //test
//    if (ud->getIntegerForKey("ScoreWallSwitch", 0) != 0) {
//        Dictionary *dict = Dictionary::create();
//        dict->setObject(String::create("mzk.png"), "file");
//        dict->setObject(String::create("0"), "title");
//        dict->setObject(String::create("0"), "info");
//        _dataArray->addObject(dict);
//    }
    if (MIRDynamicData::getInstance()->getShowPopup()) {
        for (int i = 0; i < 5; i++) {
            Dictionary *dict = Dictionary::create();
            dict->setObject(String::create(files[i]), "file");
            dict->setObject(String::create(titles[i]), "title");
            dict->setObject(String::create(info[i]), "info");
            _dataArray->addObject(dict);
        }
    } else {
        for (int i = 3; i < 5; i++) {
            Dictionary *dict = Dictionary::create();
            dict->setObject(String::create(files[i]), "file");
            dict->setObject(String::create(titles[i]), "title");
            dict->setObject(String::create(info[i]), "info");
            _dataArray->addObject(dict);
        }
    }
    
    
    _tableView = TableView::create(this, Size(winSize.width, tableViewHt));
    _tableView->setVerticalFillOrder(TableView::VerticalFillOrder::TOP_DOWN);
    _tableView->setDirection(ScrollView::Direction::VERTICAL);
    _tableView->setDelegate(this);
    _tableView->setPosition(Point(0, 120 * _scale));
    _tableView->setColor(Color3B(255, 0, 0));
    addChild(_tableView);
    _tableView->reloadData();
    
    auto drawer = DrawNode::create();
    drawer->setAnchorPoint(Point::ANCHOR_BOTTOM_LEFT);
    drawer->setPosition(Point::ZERO);
    addChild(drawer, 128);
    
    //画线
    drawer->drawSegment(_tableView->getPosition() + Point(0, _tableView->getViewSize().height), _tableView->getPosition() + Point(winSize.width, _tableView->getViewSize().height), 0.5, Color4F::WHITE);

    
    auto header = Sprite::create("finantial_item.png");
    header->setScaleY(100/header->getContentSize().height);
    header->setAnchorPoint(Point::ZERO);
    header->setPosition(Point(0, headHt));
    addChild(header);
    
    auto titleLabel = Label::createWithTTF("超级收入", TITLE_FONT, 30);
    titleLabel->setPosition(Point(winSize.width/2, header->getPositionY() + 50));
    addChild(titleLabel);
    
    MenuItemImage *item = MenuItemImage::create("close_investments.png", "close_investments.png", [=](Ref *sender){
        this->playEffect(SOUND_BUTTON);
        doCancel();
    });
    item->setPosition(Point(winSize.width - 42, titleLabel->getPositionY()));
    
    auto menu = Menu::create(item, NULL);
    menu->setAnchorPoint(Point::ANCHOR_BOTTOM_LEFT);
    menu->setPosition(Point::ZERO);
    addChild(menu);
    
    
    
    return true;
}

void MIRSuperchargeLayer::tableCellHighlight(TableView* table, TableViewCell* cell)
{
    ((Sprite *)cell->getChildByTag(10))->setSpriteFrame(KTFactory::spriteFrameByName("finantial_item_pushed.png"));
}

void MIRSuperchargeLayer::tableCellUnhighlight(TableView* table, TableViewCell* cell)
{
    ((Sprite *)cell->getChildByTag(10))->setSpriteFrame(KTFactory::spriteFrameByName("finantial_item.png"));
}

Size MIRSuperchargeLayer::tableCellSizeForIndex(TableView *table, ssize_t idx)
{
    Size s;
    //adapt
    if (IS_IPAD) {
        s = Size(winSize.width, 144);
    } else if (IS_IPAD_HD) {
        s = Size(winSize.width, 144 * 2);
    } else {
        s = Size(winSize.width, 210);
    }
    return s;
}

TableViewCell* MIRSuperchargeLayer::tableCellAtIndex(TableView *table, ssize_t idx)
{
    TableViewCell *cell = table->dequeueCell();
    
    titles[3] = data->getSoundOff() ? "开启音效" : "关闭音效";
    
    //adapt
    Size cellSize;
    float scale;
    if (IS_IPAD) {
        cellSize = Size(winSize.width, 144);
        scale = 0.75;
    } else if (IS_IPAD_HD) {
        cellSize = Size(winSize.width, 144 * 2);
        scale = 2;
    } else {
        cellSize = Size(winSize.width, 210);
        scale = 1;
    }
    
    Dictionary *dict = (Dictionary *)_dataArray->getObjectAtIndex(idx);
    
    bool showScoreWall = ((String *)dict->objectForKey("file"))->isEqual(String::create("mzk.png"));
    
    if (!cell) {
        cell = new TableViewCell();
        cell->autorelease();
        
            auto sp = Sprite::create("mzk.png");
            sp->setPosition(winSize.width/2, cellSize.height/2);
            cell->addChild(sp, 0, 70);
        
            auto bg = Sprite::create("finantial_item.png");
            bg->setAnchorPoint(Point::ZERO);
            cell->addChild(bg, -1, 10);
            
        auto icon = showScoreWall ? Sprite::create() : Sprite::createWithSpriteFrameName(dict->valueForKey("file")->getCString());
            icon->setPosition(0.06 * winSize.width + 45, cellSize.height * 0.5);
            icon->setScale((IS_IPAD_HD || IS_IPAD) ? 0.75 : 1);
            cell->addChild(icon, 0, 20);
            
            auto titleLabel = Label::createWithTTF(dict->valueForKey("title")->getCString(), TITLE_FONT, 30 * _scale);
            titleLabel->setAlignment(TextHAlignment::LEFT);
            titleLabel->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
            titleLabel->setPosition(Point(0.26 * winSize.width,  cellSize.height * (idx == 2 ? 0.63 : 0.5)));
            cell->addChild(titleLabel, 0, 30);
            
            auto subLabel = Label::createWithTTF("", TITLE_FONT, 24 * _scale);
            subLabel->setAlignment(TextHAlignment::LEFT);
            subLabel->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
            subLabel->setPosition(Point(0.26 * winSize.width, cellSize.height * 0.37));
            cell->addChild(subLabel, 0, 50);
            
            auto btn = Sprite::create("supercharge_purchase.png");
            btn->setPosition(Point(0.84 * winSize.width, cellSize.height * 0.5));
            cell->addChild(btn, 0, 80);
            
            auto btnLabel = Label::createWithTTF(dict->valueForKey("info")->getCString(), TITLE_FONT, 30 * _scale);
            btnLabel->setPosition(btn->getPosition());
            cell->addChild(btnLabel, 2, 40);
        
        if (showScoreWall) {
            
            (cell->getChildByTag(70))->setVisible(true);
            
            cell->getChildByTag(20)->setVisible(false);
            
            cell->getChildByTag(30)->setVisible(false);
            
            cell->getChildByTag(40)->setVisible(false);
            
            cell->getChildByTag(50)->setVisible(false);
            
            cell->getChildByTag(80)->setVisible(false);
        } else {
            cell->getChildByTag(70)->setVisible(false);
            
            cell->getChildByTag(20)->setVisible(true);
            
            cell->getChildByTag(30)->setVisible(true);
            
            cell->getChildByTag(40)->setVisible(true);
            
            cell->getChildByTag(50)->setVisible(true);
            
            cell->getChildByTag(80)->setVisible(true);
        }
    } else {
        
        if (showScoreWall) {
            
            (cell->getChildByTag(70))->setVisible(true);
            
            cell->getChildByTag(20)->setVisible(false);
            
            cell->getChildByTag(30)->setVisible(false);
            
            cell->getChildByTag(40)->setVisible(false);
            
            cell->getChildByTag(50)->setVisible(false);
            
            cell->getChildByTag(80)->setVisible(false);
            
        } else {
        
            ((Sprite *)cell->getChildByTag(20))->setSpriteFrame(KTFactory::spriteFrameByName(dict->valueForKey("file")->getCString()));
            auto titleLabel = ((Label *)cell->getChildByTag(30));
            titleLabel->setString(dict->valueForKey("title")->getCString());
            titleLabel->setPosition(Point(0.26 * winSize.width,  cellSize.height * (idx == 2 ? 0.58 : 0.5)));
            
//            if (idx == 2) {
//                ((Label *)cell->getChildByTag(50))->setString("（￥ 888 888 888 888）");
//            } else
            {
                ((Label *)cell->getChildByTag(50))->setString("");
            }
            
            ((Label *)cell->getChildByTag(40))->setString(dict->valueForKey("info")->getCString());
            
            cell->getChildByTag(70)->setVisible(false);
            
            cell->getChildByTag(20)->setVisible(true);
            
            cell->getChildByTag(30)->setVisible(true);
            
            cell->getChildByTag(40)->setVisible(true);
            
            cell->getChildByTag(50)->setVisible(true);
            
            cell->getChildByTag(80)->setVisible(true);
        }
    }
    
    return cell;
}

void MIRSuperchargeLayer::tableCellTouched(TableView* table, TableViewCell* cell)
{
    ssize_t idx = cell->getIdx();
    

    this->playEffect(SOUND_BUTTON);
    
    Dictionary *dict = (Dictionary *)_dataArray->getObjectAtIndex(idx);
    
    bool showScoreWall = ((String *)dict->objectForKey("file"))->isEqual(String::create("mzk.png"));
    if (showScoreWall) {
//        BBShowScoreWall(ud->getStringForKey("ScoreWallSwitch").c_str());
    } else {
        if (_mirDelegate) {
            _mirDelegate->setItemTouched(idx, this);
        }
    }
}

ssize_t MIRSuperchargeLayer::numberOfCellsInTableView(TableView *table)
{
    return _dataArray->count();
}

MIRSuperchargeLayer::MIRSuperchargeLayer()
: _mirDelegate(NULL)
{
    
}

MIRSuperchargeLayer::~MIRSuperchargeLayer()
{
    _mirDelegate = NULL;
    CC_SAFE_RELEASE(_dataArray);
}


