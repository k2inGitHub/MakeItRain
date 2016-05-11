//
//  AdUnityImp.hpp
//  MakeItRain2
//
//  Created by 宋扬 on 15/12/29.
//
//

#ifndef AdUnityImp_hpp
#define AdUnityImp_hpp

#include <stdio.h>

enum class ShowResult{
    Failed,
    Skipped,
    Finished,
};

class AdUnityImp {
    
    bool isInitialized = false;
    
    bool isShowing = false;
    
    void deliverCallback(ShowResult result);
public:
    
    void onFetchCompleted();
    
    void onFetchFailed();
    
    void onHide();
    
    void onShow();
    
    void onVideoStarted();
    
    void onVideoComplete(const char* rewardItemKey, bool skipped);
    
    void show();
    
    void init(const char* appID, bool testMode);
};

#endif /* AdUnityImp_hpp */

extern "C"{
    AdUnityImp* GetUnityImp();
}
