//
//  MIRModel.cpp
//  MakeItRain
//
//  Created by 宋扬 on 14-5-7.
//
//

#include "MIRModel.h"
#include "KTUtils.h"

const char* MIRModel::typeStr()
{
    if (_type == InvestmentType::BUSINESS) {
        return "BUSINESS";
    } else if (_type == InvestmentType::FINANCIAL) {
        return "FINANCIAL";
    } else {
        return "POLITICAL";
    }
}

//满级
bool MIRModel::isLevelMax()
{
    bool res = false;
    if (_type == InvestmentType::BUSINESS) {
        res = (_level >= 3);
    } else if (_type == InvestmentType::FINANCIAL) {
        res = false;
    } else if (_type == InvestmentType::POLITICAL) {
        
        if (_idx == 16 - 1) {
            if (_level >= 1) {
                res = true;
            } else {
                res = false;
            }
        } else {
            res = false;
        }
    }
    return res;
}

//升级
void MIRModel::levelUp()
{
    if (isLevelMax()) {
        return;
    }
    update(++_level);
    UserDefault *ud = UserDefault::getInstance();
    char key[64] = {0};
    sprintf(key, "%s_LEVEL_%ld", typeStr(), _idx);
    ud->setIntegerForKey(key, _level);
    ud->flush();
}

void  MIRModel::update(int level)
{
    if (_type == InvestmentType::BUSINESS) {
        if (level == 0) {
            _price = _basePrice;
            _benefit = _baseBenefit;
        } else if (level == 1) {
            _price = _basePrice * 2;
            _benefit = _baseBenefit *2;
        } else {
            _price = _basePrice * 4;
            _benefit = _baseBenefit * 5;
        }
    } else if (_type == InvestmentType::FINANCIAL) {
        //79.44*EXP(0.2618*等级)+0.7299
        float res = exp(0.2618 * (float)_level) * 79.44 + 0.7299;
        _price = res * financialFactor[19 - 1 - _idx];
    } else if (_type == InvestmentType::POLITICAL) {
        //61.14*EXP(0.2618*等级)+0.7299
        float res = exp(0.2618 * (float)_level) * 61.14 + 0.7299;
        _price = res * politicalFactor[16 - 1 - _idx];
        
        if (_idx == 16 - 1) {
            _basePrice = _price = 30;
        }
    }
}

void MIRModel::update(InvestmentType type, ssize_t idx)
{
    _type = type;
    _idx = idx;
    UserDefault *ud = UserDefault::getInstance();
    char key[64] = {0};
    sprintf(key, "%s_LEVEL_%ld", typeStr(), idx);

    _level = MAX(ud->getIntegerForKey(key, 0), _baseLevel);
    
    update(_level);
}

MIRModel::MIRModel(__Dictionary *dict)
{
    _iconfile = ((__String *)dict->objectForKey("icon"))->getCString();
    
    _titleName = dict->valueForKey("title")->getCString();
    
    _baseLevel = _level = dict->valueForKey("level")->intValue();
    
//    long double tmpPrice = KTUtils::atold(dict->valueForKey("price")->getCString());
//    if (tmpPrice < 1000) {
//        CCLOG("before = %Lf", tmpPrice);
//        tmpPrice = floorl(tmpPrice);
//        CCLOG("later = %Lf", tmpPrice);
//    }

    _basePrice = _price = KTUtils::atold(dict->valueForKey("price")->getCString());
    
    CCLOG("str = %s", dict->valueForKey("price")->getCString());
    
    CCLOG("price = %Lf", _price);
    
    _baseBenefit = _benefit = KTUtils::atold(dict->valueForKey("benefit")->getCString());
    
    _baseBenefit2 = _benefit2 = KTUtils::atold(dict->valueForKey("benefit2")->getCString());
    
    CCLOG("_benefit2 = %Lf", _benefit2);
    
}

MIRModel::~MIRModel()
{
}