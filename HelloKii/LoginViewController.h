//
//  LoginViewController.h
//  HelloKii
//
//  Created by Chris Beauchamp on 9/10/12.
//  Copyright (c) 2012 Kii. All rights reserved.
//

#import <UIKit/UIKit.h>

@interface LoginViewController : UIViewController

// define our UI elements
@property (nonatomic, strong) IBOutlet UITextField *usernameField;
@property (nonatomic, strong) IBOutlet UITextField *passwordField;

// define our UI actions
- (IBAction)logInUser:(id)sender;
- (IBAction)registerUser:(id)sender;

@end
