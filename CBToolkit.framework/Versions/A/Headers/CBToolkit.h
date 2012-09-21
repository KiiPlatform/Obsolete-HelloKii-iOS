//
//  CBToolkit.h
//  CBToolkit
//
//  Created by Chris Beauchamp on 9/11/12.
//  Copyright (c) 2012 Chris Beauchamp. All rights reserved.
//

#ifndef CBToolkit_CBToolkit_h
#define CBToolkit_CBToolkit_h

#import "CBLoader.h"
#import "CBToast.h"

#import "NSString+CBExtensions.h"

#define CBLog(fmt, ...) NSLog((@"%s [Line %d] " fmt), __PRETTY_FUNCTION__, __LINE__, ##__VA_ARGS__);

#endif
