//
//  AppDelegate.m
//  HelloKii
//
//  Created by Chris Beauchamp on 9/10/12.
//  Copyright (c) 2012 Kii. All rights reserved.
//

#import <KiiSDK/Kii.h>

#import "AppDelegate.h"

#import "ViewController.h"

@implementation AppDelegate

- (BOOL)application:(UIApplication *)application didFinishLaunchingWithOptions:(NSDictionary *)launchOptions
{
    
    // Initialize the Kii SDK!
    [Kii beginWithID:@"sandboxios"
              andKey:@"dummy"
       withCustomURL:@"http://dev-ufe-jp.internal.kii.com:12090"];
                
    self.window = [[UIWindow alloc] initWithFrame:[[UIScreen mainScreen] bounds]];

    // Override point for customization after application launch.
    
    self.viewController = [[ViewController alloc] initWithNibName:@"ViewController" bundle:nil];
    self.window.rootViewController = self.viewController;
    [self.window makeKeyAndVisible];
    
    return YES;
}

@end
