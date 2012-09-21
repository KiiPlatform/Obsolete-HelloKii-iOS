//
//  KiiACL.h
//  KiiSDK-Private
//
//  Created by Chris Beauchamp on 5/14/12.
//  Copyright (c) 2012 Chris Beauchamp. All rights reserved.
//

#import <Foundation/Foundation.h>

@class KiiACLEntry;

/** A reference to the ACL of a KiiObject or KiiFile
 
 A single KiiACL object can contain multiple KiiACLEntry objects, which grant/prevent access of the associated object to users and groups.
 */
@interface KiiACL : NSObject

/** Get the list of active ACLs associated with this object from the server
 
 This is a blocking method
 @param error An NSError object, set to nil, to test for errors
 @return An array of KiiACLEntry objects
 */
- (NSArray*) listACLEntriesSynchronous:(NSError**)error; 


/** Asynchronously gets the list of active ACLs associated with this object from the server

 This is a non-blocking method
 @param delegate The object to make any callback requests to
 @param callback The callback method to be called when the request is completed. The callback method should have a signature similar to:
 
     - (void) listRetrieved:(KiiACL*)forACL withResults:(NSArray*)aclList andError:(NSError*)error {
         
         // the request was successful
         if(error == nil) {
             // do something with the list
         }
         
         else {
             // there was a problem
         }
     }
 
 */
- (void) listACLEntries:(id)delegate withCallback:(SEL)callback; 


/** Add a KiiACLEntry to the local object, if not already present
 
 @param entry The KiiACLEntry to add
 */
- (void) putACLEntry:(KiiACLEntry*)entry; 


/** Remove a KiiACLEntry from the local object
 
 @param entry The KiiACLEntry to remove
 */
- (void) removeACLEntry:(KiiACLEntry*)entry; 


/** Save the list of ACLEntry objects associated with this ACL object to the server
 
 This is a blocking method
 @param error An NSError object, set to nil, to test for errors
 */
- (void) saveSynchronous:(NSError**)error; 


/** Asynchronously saves the list of ACLEntry objects associated with this ACL object to the server
 
 This is a non-blocking method
 @param delegate The object to make any callback requests to
 @param callback The callback method to be called when the request is completed. The callback method should have a signature similar to:
 
     - (void) aclSaved:(KiiACL*)acl withError:(NSError*)error {
     
         // the request was successful
         if(error == nil) {
             // do something with the list
         }
         
         else {
             // there was a problem
         }
     }
 
 */
- (void) save:(id)delegate withCallback:(SEL)callback; 

@end
