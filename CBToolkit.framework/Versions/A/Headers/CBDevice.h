//
//  CBDevice.h
//  Moni
//
//  Created by Chris Beauchamp on 9/28/12.
//  Copyright (c) 2012 Chris Beauchamp. All rights reserved.
//

#import <UIKit/UIKit.h>

#define kCBIphone5Difference    88.0f

@interface CBDevice : NSObject

+ (BOOL) isIphone;
+ (BOOL) isIpad;
+ (BOOL) isFourInchIphone;

// determines if a 4 inch screen, returns the original value plus the added value if so
+ (CGFloat) normalizeCoordinate:(CGFloat)coordinate;

@end
