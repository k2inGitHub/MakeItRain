//
//  MIRModel.h
//  MakeItRain
//
//  Created by 宋扬 on 14-5-7.
//
//

#ifndef __MakeItRain__MIRModel__
#define __MakeItRain__MIRModel__

#include "cocos2d.h"
#include "MIRConfig.h"
USING_NS_CC;

class MIRModel : public Ref {
    
protected:
//    ssize_t _idx = 0;
    //同步数据
    void update(int level);
    
    int _baseLevel;
    
    long double _basePrice;
    
    long double _baseBenefit;
    
    long double _baseBenefit2;
    
    const char* typeStr();
    
public:
    

    CC_SYNTHESIZE(ssize_t, _idx, Idx);
    
    CC_SYNTHESIZE(std::string, _iconfile, IconFile);
    
    CC_SYNTHESIZE(std::string, _titleName, TitleName);
    
    CC_SYNTHESIZE(int, _level, Level);
    
    CC_SYNTHESIZE(long double, _price, Price);
    
    CC_SYNTHESIZE(long double, _benefit, Benefit);
    
    CC_SYNTHESIZE(long double, _benefit2, Benefit2);
    
    CC_SYNTHESIZE(InvestmentType, _type, Type);
    
    //满级
    bool isLevelMax();
    
    //升级
    void levelUp();
    
    //同步数据
    void update(InvestmentType type, ssize_t idx);
    
    MIRModel(__Dictionary *dict);
//    MIRModel(ValueMap map);
    MIRModel(){};
    ~MIRModel();
};

#endif /* defined(__MakeItRain__MIRModel__) */
