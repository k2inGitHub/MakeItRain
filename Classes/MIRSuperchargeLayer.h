//
//  MIRSuperchargeLayer.h
//  MakeItRain
//
//  Created by SongYang on 14-5-15.
//
//

#ifndef __MakeItRain__MIRSuperchargeLayer__
#define __MakeItRain__MIRSuperchargeLayer__

#include "KTLayer.h"
#include "KTPauseLayer.h"
#include "MIRTableViewCell.h"
#include "MIRModel.h"
#include "MIRDelegate.h"

class MIRSuperchargeLayer : public KTPauseLayer, TableViewDataSource, TableViewDelegate {
    
public:
    
    UserDefault *ud;
    
    CC_SYNTHESIZE(MIRDelegate *, _mirDelegate, MIRDelegate);
    
//    ssize_t _toTouchIdx;
    
//    void checkOrder();
    
    Array *_dataArray;
        
    TableView *_tableView;
    
    virtual void scrollViewDidScroll(cocos2d::extension::ScrollView* view) {};
    virtual void scrollViewDidZoom(cocos2d::extension::ScrollView* view) {};
    
    virtual void tableCellHighlight(TableView* table, TableViewCell* cell);
    
    virtual void tableCellUnhighlight(TableView* table, TableViewCell* cell);
    
    virtual Size tableCellSizeForIndex(TableView *table, ssize_t idx);
    
    virtual TableViewCell* tableCellAtIndex(TableView *table, ssize_t idx);
    
    virtual void tableCellTouched(TableView* table, TableViewCell* cell);
    
    virtual ssize_t numberOfCellsInTableView(TableView *table);
    
    virtual bool init(KTPauseLayerDelegate *delegate);
    
    MIRSuperchargeLayer();
    
    ~MIRSuperchargeLayer();
    
    CREATE_FUNC_PARAM(MIRSuperchargeLayer, KTPauseLayerDelegate *, delegate);
};

#endif /* defined(__MakeItRain__MIRSuperchargeLayer__) */
