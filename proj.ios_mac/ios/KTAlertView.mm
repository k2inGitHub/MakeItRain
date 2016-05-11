//
//  KTAlertView.m
//  Unity-iPhone
//
//  Created by 宋扬 on 15/10/27.
//
//

#import "KTAlertView.h"
#import "KTUtils.h"
#include "PopupManger.hpp"

@implementation KTAlertView

- (void)alertView:(UIAlertView *)alertView clickedButtonAtIndex:(NSInteger)buttonIndex{
    
//    UnitySendMessage("PopupManager", "_onAlertViewClick", [KTUtils NSStringToChar:[NSString stringWithFormat:@"%d,%d", alertView.tag, buttonIndex]]);
    PopupManager::getInstace()->onAlertViewClick((int)alertView.tag, (int)buttonIndex);
}

- (void)showAlertView: (NSString *) title tag:(int)tag message: (NSString*) msg okTitle:(NSString*) b1 noTitle:(NSString *)b2{
    
    NSLog(@"b1 = %@, b2 = %@", b1, b2);
    if([[[UIDevice currentDevice] systemVersion] floatValue] < 9.0f){
        UIAlertView *alert = [[UIAlertView alloc] init];
        alert.tag = tag;
        [alert setTitle:title];
        [alert setMessage:msg];
        [alert setDelegate: [KTAlertView sharedInstance]];
        if (b2 != nil && b2.length > 0) {
            [alert addButtonWithTitle:b2];
        }
        [alert addButtonWithTitle:b1];
        [alert show];
    } else {
        UIAlertController *alertContrller = [UIAlertController alertControllerWithTitle:title message:msg preferredStyle:UIAlertControllerStyleAlert];
        if (b2 != nil && b2.length > 0){
            UIAlertAction *cancel = [UIAlertAction actionWithTitle:b2 style:UIAlertActionStyleCancel handler:^(UIAlertAction * _Nonnull action) {
                PopupManager::getInstace()->onAlertViewClick(tag, 0);
            }];
            [alertContrller addAction:cancel];
        }
        UIAlertAction *ok = [UIAlertAction actionWithTitle:b1 style:(UIAlertActionStyleDefault) handler:^(UIAlertAction *action) {
            PopupManager::getInstace()->onAlertViewClick(tag, 1);
        }];
        
        
        [alertContrller addAction:ok];
        
        [[UIApplication sharedApplication].keyWindow.rootViewController presentViewController:alertContrller animated:YES completion:nil];
    }  
}

+ (id)sharedInstance
{
    static KTAlertView *sharedInstance = nil;
    static dispatch_once_t onceToken;
    dispatch_once(&onceToken, ^{
        if (sharedInstance == nil) {
            sharedInstance = [[KTAlertView alloc] init];
        }
    });
    return sharedInstance;
}

extern "C" {
    
    void _ShowAlertView(char* title, int tag, char* message, char* b1, char* b2) {
        [[KTAlertView sharedInstance] showAlertView:[KTUtils charToNSString:title] tag:tag message:[KTUtils charToNSString:message] okTitle:[KTUtils charToNSString:b1] noTitle:[KTUtils charToNSString:b2]];
    }
}
@end


