//
//  KiiSocialConnect.h
//  KiiSDK-Private
//
//  Created by Chris Beauchamp on 7/3/12.
//  Copyright (c) 2012 Chris Beauchamp. All rights reserved.
//

#import <Foundation/Foundation.h>

@class KiiSocialConnectNetwork;
@class KiiSCNFacebook;

typedef enum {
    kiiSCNFacebook
} KiiSocialNetworkName;

/** An interface to link users to social networks
 
 The SDK furrently support the following social networks (KiiSocialNetworkName constant):
  
 1. Facebook (kiiSCNFacebook)
*/
@interface KiiSocialConnect : NSObject {
    KiiSCNFacebook *_facebookManager;
}

/** @constant KiiSocialNetworkName A list of constants representing social networks */

// private
@property (nonatomic, retain) NSMutableArray *availableNetworks;

// private
+ (KiiSocialConnect*) sharedInstance;
+ (BOOL) handleOpenURL:(NSURL*)url;

/** Set up a reference to one of the supported KiiSocialNetworks.
 
 The user will not be authenticated or linked to a KiiUser
 until one of those methods are called explicitly.
 @param network One of the supported KiiSocialNetworkName values
 @param key The SDK key assigned by the social network provider
 @param secret The SDK secret assigned by thte social network provider
 @param options Extra options that should be passed to the SNS. Examples could be (Facebook) an NSDictionary of permissions to grant to the authenticated user.
 */
+ (void) setupNetwork:(KiiSocialNetworkName)network 
              withKey:(NSString*)key 
            andSecret:(NSString*)secret 
           andOptions:(id)options;


/** Log a user into the social network provided
 
 This will initiate the login process for the given network, which for SSO-enabled services like Facebook, will send the user to the Facebook app for authentication. If a KiiUser has already been authenticated, this will authenticate and link the user to the network. Otherwise, this will generate a KiiUser that is automatically linked to the social network. The network must already be set up via setupNetwork:withKey:andSecret:andOptions:
 @param network One of the supported KiiSocialNetworkName values
 @param delegate The object to make any callback requests to
 @param callback The callback method to be called when the request is completed. The callback method should have a signature similar to:
 
     - (void) loggedIn:(KiiUser*)user usingNetwork:(KiiSocialNetworkName)network withError:(NSError*)error {
         
         // the process was successful - the user is now authenticated
         if(error == nil) {
             // do something with the user
         }
         
         else {
             // there was a problem
         }
     }
 
 */
+ (void) logIn:(KiiSocialNetworkName)network withDelegate:(id)delegate andCallback:(SEL)callback;


/** Link the currently logged in user with a social network
 
 This will initiate the login process for the given network, which for SSO-enabled services like Facebook, will send the user to the Facebook app for authentication. There must be a currently authenticated KiiUser. Otherwise, you can use the logIn: method to create and log in a KiiUser using Facbeook. The network must already be set up via setupNetwork:withKey:andSecret:andOptions:
 @param network One of the supported KiiSocialNetworkName values
 @param delegate The object to make any callback requests to
 @param callback The callback method to be called when the request is completed. The callback method should have a signature similar to:
 
     - (void) userLinked:(KiiUser*)user withNetwork:(KiiSocialNetworkName)network andError:(NSError*)error {
         
         // the process was successful - the user is now linked to the network
         if(error == nil) {
             // do something with the user
         }
         
         else {
             // there was a problem
         }
     }
 
 */
+ (void) linkCurrentUserWithNetwork:(KiiSocialNetworkName)network withDelegate:(id)delegate andCallback:(SEL)callback;


/** Unlink the currently logged in user from the social network.
 
 The network must already be set up via setupNetwork:withKey:andSecret:andOptions:
 @param network One of the supported KiiSocialNetworkName values
 @param delegate The object to make any callback requests to
 @param callback The callback method to be called when the request is completed. The callback method should have a signature similar to:
 
     - (void) userUnLinked:(KiiUser*)user fromNetwork:(KiiSocialNetworkName)network withError:(NSError*)error {
         
         // the process was successful - the user is no longer linked to the network
         if(error == nil) {
             // do something with the user
         }
         
         else {
             // there was a problem
         }
     }
 
 */
+ (void) unLinkCurrentUserWithNetwork:(KiiSocialNetworkName)network withDelegate:(id)delegate andCallback:(SEL)callback;

@end
