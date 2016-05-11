//
//  MIRFinancialLayer.h
//  MakeItRain
//
//  Created by SongYang on 14-5-7.
//
//

#ifndef __MakeItRain__MIRFinancialLayer__
#define __MakeItRain__MIRFinancialLayer__

#include "KTLayer.h"
#include "KTPauseLayer.h"
#include "MIRTableViewCell.h"
#include "MIRModel.h"
#include "MIRDelegate.h"

class MIRFinancialLayer : public KTPauseLayer, TableViewDataSource, TableViewDelegate, MIRDelegate {
    
public:
    
    CC_SYNTHESIZE(MIRDelegate *, _mirDelegate, MIRDelegate);
    
    Vector<MIRModel *> _dataArray;
    
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
    
    MIRFinancialLayer();
    
    ~MIRFinancialLayer();
    
    CREATE_FUNC_PARAM(MIRFinancialLayer, KTPauseLayerDelegate *, delegate);
};

#endif /* defined(__MakeItRain__MIRFinancialLayer__) */
