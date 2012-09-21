//
//  LoginViewController.h
//  KiiWorld
//
//  Created by Chris Beauchamp on 9/10/12.
//  Copyright (c) 2012 Chris Beauchamp. All rights reserved.
//

#import <UIKit/UIKit.h>

@interface CBLoader : UIView

#pragma mark - Public Static Methods

/* 
 The only method - static - and shows a toast with a given message at either
 a constant (found above) or at a user-defined time (in milliseconds)
 */
+ (void) showLoader:(NSString*)msg;

/*
 This can be called at any time. If any view is found that matches this
 class, it will be removed from its superview
 */
+ (void) hideLoader;

@end
