//
//  ViewController.h
//  HelloKii
//
//  Created by Chris Beauchamp on 9/10/12.
//  Copyright (c) 2012 Kii. All rights reserved.
//

#import <UIKit/UIKit.h>

@interface ViewController : UIViewController <UITableViewDataSource, UITableViewDelegate>

// define our UI elements
@property (nonatomic, strong) IBOutlet UITableView *tableView;
@property (nonatomic, strong) IBOutlet UINavigationBar *navBar;

// define our UI actions
- (IBAction)toggleEditing:(id)sender;
- (IBAction)createObject:(id)sender;

@end
