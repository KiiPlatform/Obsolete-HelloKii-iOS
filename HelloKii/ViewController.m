//
//
// Copyright 2012 Kii Corporation
// http://kii.com
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
// http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//
//

#import "ViewController.h"

// define the static bucket name
#define BUCKET_NAME     @"myObjects"

@interface ViewController() {
    int _objectCount;
}

@end

@implementation ViewController

// the user has hit the '+' button to create an object
- (void) createObject:(id)sender
{
    
    // show a loading message
    [KTLoader showLoader:@"Creating object..."];
    
    // create a title for the object
    NSString *valueString = [NSString stringWithFormat:@"MyObject %d", ++_objectCount];
    
    // get a bucket to put the object in
    KiiBucket *bucket = [[KiiUser currentUser] bucketWithName:BUCKET_NAME];
    
    // create the object
    KiiObject *object = [bucket createObject];
    
    // set a key/value pair
    [object setObject:valueString forKey:@"myObjectValue"];
    
    // perform an asynchronous save operation
    [object saveWithBlock:^(KiiObject *object, NSError *error) {
        
        // check for an error (successful request if error == nil)
        if(error == nil) {
            
            // hide the activity indicator
            [KTLoader showLoader:@"Object created!"
                        animated:TRUE
                   withIndicator:KTLoaderIndicatorSuccess
                 andHideInterval:KTLoaderDurationAuto];
            
            // and re-load our table
            [self refreshQuery];
        }
        
        // there was an error with the request
        else {
            
            // tell the user
            [KTLoader showLoader:@"Error creating object"
                        animated:TRUE
                   withIndicator:KTLoaderIndicatorError
                 andHideInterval:KTLoaderDurationAuto];
            
            // tell the console
            NSLog(@"Error creating object: %@", error.description);
        }

    }];
    
}

// the user hit the top-left edit/done button to turn the table editing on/off
- (void) toggleEditing:(id)sender
{
    // set the editing mode to its opposite (toggle)
    [self.tableView setEditing:!self.tableView.isEditing animated:TRUE];
    
    // update the button in the top toolbar
    UIBarButtonSystemItem item = (self.tableView.isEditing) ? UIBarButtonSystemItemDone : UIBarButtonSystemItemEdit;
    UIBarButtonItem *edit = [[UIBarButtonItem alloc] initWithBarButtonSystemItem:item target:self action:@selector(toggleEditing:)];
    [self.navigationItem setLeftBarButtonItem:edit animated:TRUE];

}

// initialize the view
- (void) viewDidLoad {
    [super viewDidLoad];
    
    self.navigationItem.title = @"My Objects";
    
    UIBarButtonItem *addButton = [[UIBarButtonItem alloc] initWithBarButtonSystemItem:UIBarButtonSystemItemAdd target:self action:@selector(createObject:)];
    self.navigationItem.rightBarButtonItem = addButton;
    
    UIBarButtonItem *editButton = [[UIBarButtonItem alloc] initWithBarButtonSystemItem:UIBarButtonSystemItemEdit target:self action:@selector(toggleEditing:)];
    self.navigationItem.leftBarButtonItem = editButton;

}

- (void) deleteObject:(int)index
{
    // show a loading message
    [KTLoader showLoader:@"Deleting object..."];
    
    // get a reference to the selected KiiObject
    KiiObject *object = [self kiiObjectAtIndex:index];
    
    // remove the object asynchronously
    [object deleteWithBlock:^(KiiObject *deletedObject, NSError *error) {
        
        // check for an error (successful request if error == nil)
        if(error == nil) {
            
            [KTLoader showLoader:@"Object deleted!"
                        animated:TRUE
                   withIndicator:KTLoaderIndicatorSuccess
                 andHideInterval:KTLoaderDurationAuto];
            
            // reload our table
            [self refreshQuery];
            
        }
        
        // there was an error with the request
        else {
            
            // tell the user
            [KTLoader showLoader:@"Error deleting object"
                        animated:TRUE
                   withIndicator:KTLoaderIndicatorError
                 andHideInterval:KTLoaderDurationAuto];
            
            // tell the console
            NSLog(@"Error deleting object: %@", error.description);
        }
        
    }];

}

- (void) viewDidAppear:(BOOL)animated {
    
    // if the user is logged in
    if([KiiUser loggedIn]) {
        
        // load the table
        // this defines the query
        KiiQuery *query = [KiiQuery queryWithClause:nil];
        [query sortByDesc:@"_created"];
        self.query = query;
        
        // and this defines the bucket
        self.bucket = [[KiiUser currentUser] bucketWithName:BUCKET_NAME];
        
        // we also want to refresh the table with the latest query and bucket
        [self refreshQuery];
    }
    
    // Show a login view, if there isn't a logged in user
    else {
        KTLoginViewController *vc = [[KTLoginViewController alloc] init];
        [self presentModalViewController:vc animated:TRUE];
    }

}

- (UITableViewCell*) tableView:(UITableView *)tableView
              cellForKiiObject:(KiiObject *)object
                   atIndexPath:(NSIndexPath *)indexPath
{
    static NSString *identifier = @"MyCell";
    UITableViewCell *cell = [[UITableViewCell alloc] initWithStyle:UITableViewCellStyleSubtitle
                                                   reuseIdentifier:identifier];
    
    cell.textLabel.text = [object getObjectForKey:@"myObjectValue"];
    cell.detailTextLabel.text = [object.created description];
    
    return cell;
}

#pragma mark - Table view data source

// this table supports editing, so handle delete requests
- (void)tableView:(UITableView *)tableView commitEditingStyle:(UITableViewCellEditingStyle)editingStyle forRowAtIndexPath:(NSIndexPath *)indexPath
{
    // this should always be true in this app
    if (editingStyle == UITableViewCellEditingStyleDelete) {
        [self deleteObject:indexPath.row];
    }
}



@end
