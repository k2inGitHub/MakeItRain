//
//  MIRTableViewCell.cpp
//  MakeItRain
//
//  Created by SongYang on 14-5-7.
//
//

#include "MIRTableViewCell.h"

bool MIRTableViewCell::getTouchEnable()
{
    return _touchEnable;
}

void MIRTableViewCell::setTouchEnable(bool touch)
{
    if (_touchEnable != touch) {
        _touchEnable = touch;
        if (_touchEnable) {
            _bg->setColor(Color3B::WHITE);
        } else {
            _bg->setColor(Color3B(192, 192, 192));
        }
    }
}

void MIRTableViewCell::layout(MIRModel *m)
{
    Size s = Director::getInstance()->getWinSize();
    //adapt
    Size cellSize;
    float scale;
    if (IS_IPAD) {
        cellSize = Size(s.width, 144);
        scale = 0.75;
    } else if (IS_IPAD_HD) {
        cellSize = Size(s.width, 144 * 2);
        scale = 1;
    } else {
        cellSize = Size(s.width, 210);
        scale = 1;
    }
    
    
    this->getIcon()->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(m->getIconFile().c_str()));
    
    this->getTitleLabel()->setString(m->getTitleName());
    
    this->getLevel()->setValue(m->getLevel());
    
    if (m->isLevelMax()) {
        setTouchEnable(false);
    }  else {
        setTouchEnable(true);
    }
    
    long double showPrice = m->getPrice();
    if (showPrice < 1000) {
        showPrice = floorl(showPrice);
    }
    this->getPriceLabel()->setString("￥" + KTUtils::MIRString(showPrice));
    
    if (_type == InvestmentType::POLITICAL) {
        Size s = Director::getInstance()->getWinSize();
        
        
        if (m->getBenefit() == 0 && m->getBenefit2() != 0) {
            this->getBenefitLabel()->setVisible(false);
            this->getBenefitLabel2()->setVisible(true);
            this->getBenefitLabel2()->setPosition(Point(s.width * 0.98, cellSize.height * 0.5));
            this->getBenefitLabel2()->setString("￥" + KTUtils::MIRString(m->getBenefit2()) + " 容量");
        } else if (m->getBenefit() != 0 && m->getBenefit2() == 0) {
            this->getBenefitLabel2()->setVisible(false);
            this->getBenefitLabel()->setVisible(true);
            this->getBenefitLabel()->setString("￥" + KTUtils::MIRString(m->getBenefit()) + "/小时");
            this->getBenefitLabel()->setPosition(Point(s.width * 0.98, cellSize.height * 0.5));
        } else {
            this->getBenefitLabel()->setVisible(true);
            this->getBenefitLabel2()->setVisible(true);
            this->getBenefitLabel()->setString("￥" + KTUtils::MIRString(m->getBenefit()) + "/小时");
            this->getBenefitLabel2()->setString("￥" + KTUtils::MIRString(m->getBenefit2()) + " 容量");
            this->getBenefitLabel2()->setPosition(Point(s.width * 0.98, cellSize.height * 0.63));
            this->getBenefitLabel2()->setPosition(Point(s.width * 0.98, cellSize.height * 0.37));
        }
        
        
        
    } else if (_type == InvestmentType::BUSINESS) {
        
        this->getBenefitLabel()->setString("￥" + KTUtils::MIRString(m->getBenefit()));
    } else if (_type == InvestmentType::FINANCIAL) {
        
        this->getBenefitLabel()->setString("+￥" + KTUtils::MIRString(m->getBenefit()) + "/秒");
    }
}

MIRTableViewCell::MIRTableViewCell(InvestmentType type) : _touchEnable(true)
{
    _type = type;
    
    Size s = Director::getInstance()->getWinSize();
    
    _bg = Sprite::create("finantial_item.png");
    _bg->setAnchorPoint(Point::ZERO);
    addChild(_bg, -1);
    
    
    //adapt
    Size cellSize;
    float scale;
    if (IS_IPAD) {
        cellSize = Size(s.width, 144);
        scale = 0.75;
    } else if (IS_IPAD_HD) {
        cellSize = Size(s.width, 144 * 2);
        scale = 1;
    } else {
        cellSize = Size(s.width, 210);
        scale = 1;
    }
    
    const float typeLabelX[4] = {static_cast<float>(0.06 * screenSize.width), static_cast<float>(0.38 * screenSize.width), static_cast<float>(0.6 * screenSize.width), static_cast<float>(0.89 * screenSize.width)};
    
    _icon = Sprite::create();
    _icon->setPosition(typeLabelX[0] + 56, cellSize.height * 0.55);
    _icon->setScale((IS_IPAD || IS_IPAD_HD) ? 0.75 : 1);
    addChild(_icon);
    
    _titleLabel = Label::createWithTTF("title", TITLE_FONT, 36 * scale);
    _titleLabel->setAlignment(TextHAlignment::LEFT);
    _titleLabel->setAnchorPoint(Point::ANCHOR_MIDDLE);
    _titleLabel->setPosition(Point(typeLabelX[0] + 56, cellSize.height * 0.17));
    addChild(_titleLabel);
    
    _level = MIRBadge::create(0);
    _level->setPosition(typeLabelX[1], cellSize.height * 0.5);
    addChild(_level);
    
    auto priceBg = Sprite::create("item_purchase.png");
    priceBg->setPosition(Point(typeLabelX[2], cellSize.height * 0.5));
    addChild(priceBg);
    
    _priceLabel = Label::createWithTTF("￥383", TITLE_FONT, 30 * scale);
    _priceLabel->setAlignment(TextHAlignment::LEFT);
    _priceLabel->setAnchorPoint(Point::ANCHOR_MIDDLE);
    _priceLabel->setPosition(Point(typeLabelX[2], cellSize.height * 0.5));
    _priceLabel->setColor(Color3B::GREEN);
    addChild(_priceLabel);
    
    if (type == InvestmentType::FINANCIAL) {
        float size = 24;
        if (IS_IPAD || IS_IPAD_HD) {
            size = 30;
        }
        
        _benefitLabel = Label::createWithTTF("+￥0.5/秒", TITLE_FONT, size * scale);
        _benefitLabel->setAlignment(TextHAlignment::RIGHT);
        _benefitLabel->setAnchorPoint(Point::ANCHOR_MIDDLE_RIGHT);
        _benefitLabel->setPosition(Point(s.width * 0.98, cellSize.height * 0.5));
        addChild(_benefitLabel);
    } else if (type == InvestmentType::BUSINESS) {
        
        auto bill = Sprite::create("dollar.png");
        bill->setPosition(Point(s.width * 0.89, cellSize.height * 0.5));
        addChild(bill);
        float size = 24;
        if (IS_IPAD || IS_IPAD_HD) {
            size = 30;
        }
        _benefitLabel = Label::createWithTTF("", TITLE_FONT, size * scale);
        _benefitLabel->setAlignment(TextHAlignment::CENTER);
        _benefitLabel->setAnchorPoint(Point::ANCHOR_MIDDLE);
        _benefitLabel->setPosition(Point(s.width * 0.89, cellSize.height * 0.5));
        _benefitLabel->setColor(Color3B(0, 0, 0));
        addChild(_benefitLabel);
    } else {
        float size = 24;
        if (IS_IPAD || IS_IPAD_HD) {
            size = 30;
        }
        _benefitLabel = Label::createWithTTF("+￥0.5/秒", TITLE_FONT, size * scale);
        _benefitLabel->setAlignment(TextHAlignment::RIGHT);
        _benefitLabel->setAnchorPoint(Point::ANCHOR_MIDDLE_RIGHT);
        _benefitLabel->setPosition(Point(s.width * 0.98, cellSize.height * 0.63));
        addChild(_benefitLabel);
        
        _benefitLabel2 = Label::createWithTTF("+￥0.5/秒", TITLE_FONT, size * scale);
        _benefitLabel2->setAlignment(TextHAlignment::RIGHT);
        _benefitLabel2->setAnchorPoint(Point::ANCHOR_MIDDLE_RIGHT);
        _benefitLabel2->setPosition(Point(s.width * 0.98, cellSize.height * 0.37));
        addChild(_benefitLabel2);
    }
}