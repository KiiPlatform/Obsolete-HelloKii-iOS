//
//  LoginViewController.h
//  KiiWorld
//
//  Created by Chris Beauchamp on 9/10/12.
//  Copyright (c) 2012 Chris Beauchamp. All rights reserved.
//

#import <UIKit/UIKit.h>

#define CB_TOAST_LONG   2000
#define CB_TOAST_SHORT  1000

@interface CBToast : UILabel

#pragma mark - Public Static Methods

/* 
 The only method - static - and shows a toast with a given message at either
 a constant (found above) or at a user-defined time (in milliseconds)
 */
+ (void) showToast:(NSString*)msg
      withDuration:(NSUInteger)durationInMillis;


/*
 The only method - static - and shows a toast with a given message at either
 a constant (found above) or at a user-defined time (in milliseconds)
 */
+ (void) showPersistentToast:(NSString *)msg;

+ (void) hideToast;

@end
