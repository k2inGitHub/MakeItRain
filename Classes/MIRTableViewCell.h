//
//  MIRTableViewCell.h
//  MakeItRain
//
//  Created by SongYang on 14-5-7.
//
//

#ifndef __MakeItRain__MIRTableViewCell__
#define __MakeItRain__MIRTableViewCell__

#include "cocos-ext.h"
#include "KTUtils.h"
#include "KTFactory.h"
#include "MIRConfig.h"
#include "MIRBadge.h"
#include "MIRModel.h"
USING_NS_CC_EXT;
USING_NS_CC;



class MIRTableViewCell : public TableViewCell {
    
public:
    
    CC_SYNTHESIZE(InvestmentType, _type, Type);
    
    CC_SYNTHESIZE(Sprite *, _bg, Bg);
    
    CC_SYNTHESIZE(Sprite *, _icon, Icon);
    
    CC_SYNTHESIZE(Label *, _titleLabel, TitleLabel);
    
    CC_SYNTHESIZE(MIRBadge *, _level, Level);
    
    CC_SYNTHESIZE(Label*, _priceLabel, PriceLabel);
    
    CC_SYNTHESIZE(Label*, _benefitLabel, BenefitLabel);
    
    CC_SYNTHESIZE(Label*, _benefitLabel2, BenefitLabel2);
    
//    CC_SYNTHESIZE(bool, _touchEnable, TouchEnable);
    
    CC_PROPERTY(bool, _touchEnable, TouchEnable);
    
    void layout(MIRModel *m);
    
    MIRTableViewCell(InvestmentType type = InvestmentType::FINANCIAL);
};

#endif /* defined(__MakeItRain__MIRTableViewCell__) */
