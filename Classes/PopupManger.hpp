//
//  PopupManger.hpp
//  MakeItRain2
//
//  Created by 宋扬 on 15/12/28.
//
//

#ifndef PopupManger_hpp
#define PopupManger_hpp

#include <stdio.h>

class PopupManager {
    
    
    
public:
    void onAlertViewClick(int tag, int btnIdx);
    
    void showReccomand();
    
    void showRate();
    
    void showMoney();
    
    static PopupManager* getInstace();
};

#endif /* PopupManger_hpp */
