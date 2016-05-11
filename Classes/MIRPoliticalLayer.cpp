//
//  MIRPoliticalLayer.cpp
//  MakeItRain
//
//  Created by SongYang on 14-5-8.
//
//

#include "MIRPoliticalLayer.h"
#include "MIRGameLayer.h"

void MIRPoliticalLayer::checkOrder()
{
    char key[64] = {0};
    sprintf(key, "POLITICAL_LEVEL_%ld", _dataArray.size() - 1);
    if (UserDefault::getInstance()->getIntegerForKey(key) == 0) {
     
        
        
    }
}

bool MIRPoliticalLayer::init(KTPauseLayerDelegate *delegate)
{
    if (!KTPauseLayer::init(delegate)) {
        return false;
    }
    
    //adapt
    float bgHt;
    float tableViewHt;
    if (IS_IPHONE5) {
        bgHt = 800;
        tableViewHt = 680;
    } else if (IS_IPAD) {
        bgHt = 640;
        tableViewHt = 520;
    } else if (IS_IPAD_HD) {
        bgHt = (640 + 100) * 2;
        tableViewHt = (520 + 100)* 2;
    } else {
        bgHt = 600;
        tableViewHt = 480;
    }
    
    auto bg = LayerColor::create(MIRCellColor, winSize.width, bgHt);
    addChild(bg, -1);
    
    __Dictionary *root = __Dictionary::createWithContentsOfFile("Financial.plist");
    
    
    __Array *array = (__Array *)root->objectForKey("political");
    
    for (int i = 0; i < array->count(); i++) {
        
        __Dictionary *dict = (__Dictionary *)array->getObjectAtIndex(i);
        
        MIRModel *m = new MIRModel(dict);
        _dataArray.insert(0, m);
        m->release();
        m->update(InvestmentType::POLITICAL, array->count() - 1 - i);
        
    }
    
    _tableView = TableView::create(this, Size(winSize.width, tableViewHt));
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
    
    
    auto type = Sprite::create("finantial_item.png");
    type->setScaleY(60/type->getContentSize().height);
    type->setAnchorPoint(Point::ZERO);
    type->setPosition(Point(0, _tableView->getPositionY() + _tableView->getViewSize().height));
    addChild(type);
    
    
    //画线
    drawer->drawSegment(type->getPosition(), Point(winSize.width, type->getPositionY()), 0.5, Color4F::WHITE);
    drawer->drawSegment(Point(0,type->getPositionY() + 60), Point(winSize.width, 60 + type->getPositionY()), 0.5, Color4F::WHITE);
    
    const float typeLabelX[4] = {static_cast<float>(0.06 * screenSize.width), static_cast<float>(0.38 * screenSize.width), static_cast<float>(0.6 * screenSize.width), static_cast<float>(0.89 * screenSize.width)};
    const char *typeStr[4] = {"项目", "等级", "消耗", "收益"};
    for (int i = 0; i < sizeof(typeLabelX)/sizeof(typeLabelX[0]); i++) {
        
        Label *typeLabel = Label::createWithTTF(typeStr[i], TITLE_FONT, 24);
        typeLabel->setPosition(Point(typeLabelX[i], type->getPositionY() + 30));
        typeLabel->setColor(MIRBrown);
        addChild(typeLabel);
    }
    
    auto header = Sprite::create("finantial_item.png");
    header->setScaleY(100/type->getContentSize().height);
    header->setAnchorPoint(Point::ZERO);
    header->setPosition(Point(0, type->getPositionY() + 60));
    addChild(header);
    
    auto titleLabel = Label::createWithTTF("海外投资", TITLE_FONT, 30);
    titleLabel->setPosition(Point(winSize.width/2, header->getPositionY() + 70));
    addChild(titleLabel);
    
    auto subTitle = Label::createWithTTF("（关闭游戏仍可获得收入）", TITLE_FONT, 26);
    subTitle->setTextColor(Color4B(MIRBrown));
    subTitle->setPosition(Point(winSize.width/2, header->getPositionY() + 26));
    addChild(subTitle);
    
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

void MIRPoliticalLayer::tableCellHighlight(TableView* table, TableViewCell* cell)
{
    MIRTableViewCell *c = (MIRTableViewCell *)cell;
    if (!c->getTouchEnable()) {
        return;
    }
    c->getBg()->setSpriteFrame(KTFactory::spriteFrameByName("finantial_item_pushed.png"));
}

void MIRPoliticalLayer::tableCellUnhighlight(TableView* table, TableViewCell* cell)
{
    MIRTableViewCell *c = (MIRTableViewCell *)cell;
    if (!c->getTouchEnable()) {
        return;
    }
    c->getBg()->setSpriteFrame(KTFactory::spriteFrameByName("finantial_item.png"));
}

Size MIRPoliticalLayer::tableCellSizeForIndex(TableView *table, ssize_t idx)
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

TableViewCell* MIRPoliticalLayer::tableCellAtIndex(TableView *table, ssize_t idx)
{
    MIRTableViewCell *cell = (MIRTableViewCell *)table->dequeueCell();
    if (!cell) {
        cell = new MIRTableViewCell(InvestmentType::POLITICAL);
        cell->autorelease();
    }
    
    MIRModel *m = _dataArray.at(idx);
    
    cell->layout(m);
    
    if (UserDefault::getInstance()->getIntegerForKey("POLITICAL_LEVEL_15") == 0) {
        if (idx != 15) {
                cell->setTouchEnable(false);
        }
    }
    return cell;
}

void MIRPoliticalLayer::tableCellTouched(TableView* table, TableViewCell* cell)
{
    MIRModel *m = _dataArray.at(cell->getIdx());
    
    MIRTableViewCell *c = ((MIRTableViewCell *)cell);
    
    if (!c->getTouchEnable()) {  
        return;
    }
    
    CCASSERT(_mirDelegate, "_mirDelegate不能为空");
    
    if (!_mirDelegate->itemCanLevelUp(m)) {
        return;
    }
    
    this->playEffect(SOUND_BUTTON);
    
    m->levelUp();
    
    c->layout(m);
    
    if (cell->getIdx() == 15) {
     
        table->reloadData();
    }
}

ssize_t MIRPoliticalLayer::numberOfCellsInTableView(TableView *table)
{
    return _dataArray.size();
}

MIRPoliticalLayer::MIRPoliticalLayer()
: _mirDelegate(NULL)
{
    
}

MIRPoliticalLayer::~MIRPoliticalLayer()
{
    _mirDelegate = NULL;
    _dataArray.clear();
}