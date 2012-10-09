//
//  KiiError.h
//  KiiSDK-Private
//
//  Created by Chris Beauchamp on 12/21/11.
//  Copyright (c) 2011 Chris Beauchamp. All rights reserved.
//

#import <Foundation/Foundation.h>

/** Custom Kii SDK errors */
@interface KiiError : NSError

+ (NSError*) errorWithCode:(NSString*)code andMessage:(NSString*)message;

///---------------------------------------------------------------------------------------
/// @name Application Errors (1xx)
///---------------------------------------------------------------------------------------

/** The application received invalid credentials and was not initialized */
+ (NSError*) invalidApplication;

///---------------------------------------------------------------------------------------
/// @name Connectivity Errors (2xx)
///---------------------------------------------------------------------------------------

/** Unable to connect to the internet */
+ (NSError*) unableToConnectToInternet;

/** Unable to parse server response */
+ (NSError*) unableToParseResponse;

/** Unable to authorize request */
+ (NSError*) unauthorizedRequest;

///---------------------------------------------------------------------------------------
/// @name User API Errors (3xx)
///---------------------------------------------------------------------------------------

/** Unable to retrieve valid access token */
+ (NSError*) invalidAccessToken;

/** Unable to authenticate user */
+ (NSError*) unableToAuthenticateUser;

/** Unable to retrieve file list */
+ (NSError*) unableToRetrieveUserFileList;

/** Invalid password format. Password must be at least 5 characters and can include these characters: a-z, A-Z, 0-9, @, #, $, %, ^, and & */
+ (NSError*) invalidPasswordFormat;

/** Invalid email format. Email must be a valid address */
+ (NSError*) invalidEmailFormat;

/** Invalid email address format or phone number format. A userIdentifier must be one of the two */
+ (NSError*) invalidUserIdentifier;

/** Invalid username format. The username must be 5-50 alphanumeric characters - the first character must be a letter. */
+ (NSError*) invalidUsername;

/** Invalid user object. Please ensure the credentials were entered properly */
+ (NSError*) invalidUserObject;

/** Invalid phone format. The username may begin with a '+' and must be at least 10 digits */
+ (NSError*) invalidPhoneFormat;

/** Invalid verification code */
+ (NSError*) unableToVerifyUser;

/** Invalid displayname format. The displayname must be 4-50 alphanumeric characters - the first character must be a letter. */
+ (NSError*) invalidDisplayName;

/** The user's email was unable to be updated on the server */
+ (NSError*) unableToUpdateEmail;

/** The user's phone number was unable to be updated on the server */
+ (NSError*) unableToUpdatePhoneNumber;

/** The request could not be made - the key associated with the social network is invalid. */
+ (NSError*) invalidSocialNetworkKey;

///---------------------------------------------------------------------------------------
/// @name File API Errors (4xx)
///---------------------------------------------------------------------------------------

/** Unable to delete file from cloud */
+ (NSError*) unableToDeleteFile;

/** Unable to upload file to cloud */
+ (NSError*) unableToUploadFile;

/** Unable to retrieve local file for uploading. May not exist, or may be a directory. */
+ (NSError*) localFileInvalid;

/** Unable to shred file. Must be in the trash before it is permanently deleted. */
+ (NSError*) shreddedFileMustBeInTrash;

/** Unable to perform operation - a valid container must be set first. */
+ (NSError*) fileContainerNotSpecified;

///---------------------------------------------------------------------------------------
/// @name Core Object Errors (5xx)
///---------------------------------------------------------------------------------------

/** Invalid objects passed to method. Must be already saved on server. */
+ (NSError*) invalidObjects;

/** Unable to parse object. Must be JSON-encodable */
+ (NSError*) unableToParseObject;

/** Duplicate entry exists */
+ (NSError*) duplicateEntry;

/** Invalid remote path set for KiiFile. Must be of form:  /root/path/subpath    */
+ (NSError*) invalidRemotePath;

/** Unable to delete object from cloud */
+ (NSError*) unableToDeleteObject;

/** Invalid KiiObject - the class name contains one or more spaces */
+ (NSError*) invalidObjectType;

/** Unable to set an object as a child of itself */
+ (NSError*) unableToSetObjectToItself;

/** The key of the object being set is a preferred key, please try a different key */
+ (NSError*) invalidAttributeKey;

/** The container you are trying to operate on does not exist */
+ (NSError*) invalidContainer;

/** The object you are trying to operate on does not exist */
+ (NSError*) objectNotFound;

/** The URI provided is invalid */
+ (NSError*) invalidURI;

/** The group name provided is not valid. Ensure it is alphanumeric and more than 0 characters in length */
+ (NSError*) invalidGroupName;

/** At least one of the ACL entries saved to an object failed. Please note there may also have been one or more successful entries. */
+ (NSError*) partialACLFailure;

///---------------------------------------------------------------------------------------
/// @name Query Errors (6xx)
///---------------------------------------------------------------------------------------

/** No more query results exist */
+ (NSError*) noMoreResults;

/** Query limit set too high */
+ (NSError*) singleQueryLimitExceeded;

@end
