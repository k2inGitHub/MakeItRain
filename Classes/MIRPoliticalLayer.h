//
//  MIRPoliticalLayer.h
//  MakeItRain
//
//  Created by SongYang on 14-5-8.
//
//

#ifndef __MakeItRain__MIRPoliticalLayer__
#define __MakeItRain__MIRPoliticalLayer__

#include "KTLayer.h"
#include "KTPauseLayer.h"
#include "MIRTableViewCell.h"
#include "MIRModel.h"
#include "MIRDelegate.h"

class MIRPoliticalLayer : public KTPauseLayer, TableViewDataSource, TableViewDelegate, MIRDelegate {
    
public:
    
    void checkOrder();
    
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
    
    MIRPoliticalLayer();
    
    ~MIRPoliticalLayer();
    
    CREATE_FUNC_PARAM(MIRPoliticalLayer, KTPauseLayerDelegate *, delegate);
};


#endif /* defined(__MakeItRain__MIRPoliticalLayer__) */
