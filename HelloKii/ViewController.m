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
#import "LoginViewController.h"

// define the static bucket name
#define BUCKET_NAME     @"myObjects"

// define some class-specific variables
@interface ViewController () {
    NSMutableArray *_items;
    int objectCount;
}
@end

@implementation ViewController

// synth our UI elements
@synthesize tableView, navBar;

#pragma mark Kii delegate callbacks

// the object save request is complete
- (void) objectSaved:(KiiObject*)object
           withError:(NSError*)error {
    
    // hide the activity indicator
    [CBToast hideToast];
    
    // check for an error (successful request if error == nil)
    if(error == nil) {
        
        // place the new object at the beginning of the item list
        [_items insertObject:object atIndex:0];
        
        // tell the table we're about to modify its contents
        [self.tableView beginUpdates];
        
        // insert the row with a nice animation
        [self.tableView insertRowsAtIndexPaths:[NSArray arrayWithObject:[NSIndexPath indexPathForRow:0
                                                                                           inSection:0]]
                              withRowAnimation:UITableViewRowAnimationFade];
        
        // tell the table we're done
        [self.tableView endUpdates];
        
    }
    
    // there was an error with the request
    else {
        
        // tell the user
        [CBToast showToast:@"Error creating object" withDuration:CB_TOAST_LONG];
        
        // tell the console
        CBLog(@"Error creating object: %@", error.description);
    }
    
}

// the object delete request is complete
- (void) deleteDone:(KiiObject*)deletedObject
          withError:(NSError*)error {
    
    // hide the activity indicator
    [CBToast hideToast];
    
    // check for an error (successful request if error == nil)
    if(error == nil) {
        
        // get the index of the deleted object
        int ndx = [_items indexOfObject:deletedObject];
        
        // remove it from the table's data source
        [_items removeObject:deletedObject];
                
        // tell the table we're about to modify its contents
        [self.tableView beginUpdates];
        
        // insert the row with a nice animation
        [self.tableView deleteRowsAtIndexPaths:[NSArray arrayWithObject:[NSIndexPath indexPathForRow:ndx
                                                                                           inSection:0]]
                              withRowAnimation:UITableViewRowAnimationFade];
        
        // tell the table we're done
        [self.tableView endUpdates];
        
    }
    
    // there was an error with the request
    else {
        
        // tell the user
        [CBToast showToast:@"Error deleting object" withDuration:CB_TOAST_LONG];
        
        // tell the console
        CBLog(@"Error deleting object: %@", error.description);
    }
    
}

// the object query request is complete
- (void) doneLoadingObjects:(KiiQuery*)query
                   onBucket:(KiiBucket*)bucket
                withResults:(NSArray*)results
                    andNext:(KiiQuery*)nextQuery
                   andError:(NSError*)error {
    
    // hide the activity indicator
    [CBToast hideToast];
    
    // check for an error (successful request if error == nil)
    if(error == nil) {
        
        // add the resulting KiiObjects to the table's data source
        [_items addObjectsFromArray:results];
        
        // reload the table view with the new data
        [self.tableView reloadData];
    }
    
    // there was an error with the request
    else {
        
        // tell the user
        [CBToast showToast:@"Error loading objects" withDuration:CB_TOAST_LONG];
        
        // tell the console
        CBLog(@"Error loading objects: %@", error.description);
    }
    
}


#pragma mark IBActions

// the user has hit the '+' button to create an object
- (IBAction)createObject:(id)sender {
    
    // show a loading message
    [CBToast showPersistentToast:@"Creating object..."];
    
    // create a title for the object
    NSString *valueString = [NSString stringWithFormat:@"MyObject %d", ++objectCount];
    
    // get a bucket to put the object in
    KiiBucket *bucket = [[KiiUser currentUser] bucketWithName:BUCKET_NAME];
    
    // create the object
    KiiObject *object = [bucket createObject];
    
    // set a key/value pair
    [object setObject:valueString forKey:@"myObjectValue"];
    
    // perform an asynchronous save operation
    [object save:self withCallback:@selector(objectSaved:withError:)];
    
}

// the user hit the top-left edit/done button to turn the table editing on/off
- (IBAction)toggleEditing:(id)sender {
    
    // set the editing mode to its opposite (toggle)
    [self.tableView setEditing:!self.tableView.isEditing animated:TRUE];
    
    // update the button in the top toolbar
    UIBarButtonSystemItem item = (self.tableView.isEditing) ? UIBarButtonSystemItemDone : UIBarButtonSystemItemEdit;
    UIBarButtonItem *edit = [[UIBarButtonItem alloc] initWithBarButtonSystemItem:item target:self action:@selector(toggleEditing:)];
    [navBar.topItem setLeftBarButtonItem:edit animated:TRUE];

}

// initialize the view
- (void) viewDidLoad {
    _items = [[NSMutableArray alloc] init];
}

// loads the objects associated with the user from the server
- (void) loadObjects {
    
    // show a loading message
    [CBToast showPersistentToast:@"Loading objects..."];
    
    // clear the objects from the local data source - this is a full refresh
    [_items removeAllObjects];
    
    // create an empty query (will return all objects in the bucket)
    KiiQuery *query = [KiiQuery queryWithClause:nil];
    
    // sort it by the creation date
    [query sortByAsc:@"_created"];
    
    // create a reference to the proper bucket belonging to the current user
    KiiBucket *bucket = [[KiiUser currentUser] bucketWithName:BUCKET_NAME];
    
    // asynchronously execute the query
    [bucket executeQuery:query
            withDelegate:self
             andCallback:@selector(doneLoadingObjects:onBucket:withResults:andNext:andError:)];
    
}

- (void) viewDidAppear:(BOOL)animated {
    
    // if the user is logged in
    if([KiiUser loggedIn]) {
        
        // load the table
        [self loadObjects];        
    }
    
    // Show a login view, if there isn't a logged in user
    else {
        LoginViewController *vc = [[LoginViewController alloc] initWithNibName:@"LoginViewController" bundle:nil];
        [self presentModalViewController:vc animated:TRUE];        
    }

}

#pragma mark - Table view data source

- (NSInteger)numberOfSectionsInTableView:(UITableView *)tableView
{
    // Return the number of sections.
    return 1;
}

- (NSInteger)tableView:(UITableView *)tableView numberOfRowsInSection:(NSInteger)section
{
    // Return the number of rows in the section.
    return [_items count];
}

- (UITableViewCell *)tableView:(UITableView *)tv cellForRowAtIndexPath:(NSIndexPath *)indexPath
{
        
    // create the table cell
    static NSString *CellIdentifier = @"Cell";
    UITableViewCell *cell = [tv dequeueReusableCellWithIdentifier:CellIdentifier];
    if (cell == nil) {
        cell = [[UITableViewCell alloc] initWithStyle:UITableViewCellStyleSubtitle reuseIdentifier:CellIdentifier];
    }

    // Configure the cell...
    KiiObject *object = [_items objectAtIndex:indexPath.row];
    cell.textLabel.text = [object getObjectForKey:@"myObjectValue"];
    cell.detailTextLabel.text = [object.created description];
    
    return cell;
}

// this table supports editing, so handle delete requests
- (void)tableView:(UITableView *)tableView commitEditingStyle:(UITableViewCellEditingStyle)editingStyle forRowAtIndexPath:(NSIndexPath *)indexPath {
    
    // this should always be true in this app
    if (editingStyle == UITableViewCellEditingStyleDelete) {
        
        // show a loading message
        [CBToast showPersistentToast:@"Deleting object..."];

        // get a reference to the selected KiiObject
        KiiObject *object = [_items objectAtIndex:indexPath.row];

        // remove the object asynchronously
        [object delete:self withCallback:@selector(deleteDone:withError:)];

    }
    
}



@end
