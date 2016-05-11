//
//  KTUtils.m
//  Unity-iPhone
//
//  Created by 宋扬 on 15/10/13.
//
//

#import "KTUtils.h"

@implementation KTUtils

+(NSString *) charToNSString:(char *)value {
    if (value != NULL) {
        return [NSString stringWithUTF8String: value];
    } else {
        return [NSString stringWithUTF8String: ""];
    }
}

+ (const char *)NSStringToChar:(NSString *)value {
    return [value UTF8String];
}

+(const char *)NSIntToChar:(NSInteger)value {
    NSString *tmp = [NSString stringWithFormat:@"%d", value];
    return [tmp UTF8String];
}

@end
