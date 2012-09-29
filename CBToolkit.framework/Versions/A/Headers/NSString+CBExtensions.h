//
//  NSString+CBExtensions.h
//  CBToolkit
//
//  Created by Chris Beauchamp on 9/11/12.
//  Copyright (c) 2012 Chris Beauchamp. All rights reserved.
//

#import <Foundation/Foundation.h>

typedef enum {
    CBCharacterSetUppercase         = 1 << 0,
    CBCharacterSetLowercase         = 1 << 1,
    CBCharacterSetNumeric           = 1 << 2,
    CBCharacterSetAlpha             = CBCharacterSetUppercase | CBCharacterSetLowercase,
    CBCharacterSetAlphanumeric      = CBCharacterSetAlpha | CBCharacterSetNumeric
} CBCharacterSet;

@interface NSString (CBExtensions)

+ (NSString*) cbRandomString:(int)len;
+ (NSString*) cbRandomString:(int)len withCharacterSet:(CBCharacterSet)charSet;

- (BOOL) cbContainsString:(NSString*)needle;
- (BOOL) cbContainsCharacter:(char)needle;

+ (NSString*) cbCharactersForSet:(CBCharacterSet)set;

@end
