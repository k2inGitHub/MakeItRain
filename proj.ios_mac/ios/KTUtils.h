//
//  KTUtils.h
//  Unity-iPhone
//
//  Created by 宋扬 on 15/10/13.
//
//

#import <Foundation/Foundation.h>

@interface KTUtils : NSObject

+ (const char *)NSStringToChar:(NSString *)value;

+(NSString *) charToNSString:(char *)value;

+(const char *)NSIntToChar:(NSInteger)value;

@end
