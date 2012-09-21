//
//  KiiRequest.h
//  KiiSDK-Private
//
//  Created by Chris Beauchamp on 12/21/11.
//  Copyright (c) 2011 Chris Beauchamp. All rights reserved.
//

#import <Foundation/Foundation.h>

@class KiiObject, KiiCallback, KiiFile;

typedef enum { GET, PUT, POST, FORMPOST, DELETE } HttpMethods;

@interface KiiRequest : NSObject {
        
    // these are dev-specific values
    KiiCallback *callback;
    
    BOOL _authenticating;
    
    NSValue *operation;
    
    KiiObject *mObject;
    KiiFile *mFile;
    
    NSString *filePath;
    NSString *downloadPath;
    
    BOOL complete;
    NSMutableData *responseData;
    NSError *responseError;
    NSInteger responseCode;
    NSDictionary *responseHeaders;
    long long responseExpectedSize;
    long long uploadFileSize;
    
}

@property (nonatomic, retain) NSValue *operation;

@property (nonatomic, retain) KiiCallback *callback;
@property (nonatomic, retain) KiiFile *mFile;

@property (nonatomic, retain) NSString *requestPath;
@property (nonatomic, retain) NSDictionary *postData;
@property (nonatomic, retain) NSString *plainText;
@property (nonatomic, retain) NSString *content;
@property (nonatomic, retain) NSString *accept;
@property (nonatomic, assign) BOOL anonymous;
@property (nonatomic, assign) int requestMethod;

@property (nonatomic, retain) NSString *filePath;
@property (nonatomic, retain) NSString *downloadPath;

@property (nonatomic, retain) NSMutableArray *customHeaders;
@property (nonatomic, retain) KiiObject *mObject;

- (id) initWithPath:(NSString*)path andApp:(BOOL)appInPath;
- (id) initWithPath:(NSString*)path;

- (void) setRequestPath:(NSString *)reqPath withApp:(BOOL)appInURL;

- (NSDictionary*) makeSynchronousRequest:(NSError**)sendError andResponse:(int*)response withETag:(int*)etag discardBody:(BOOL)discardBody;
- (NSDictionary*) makeSynchronousRequest:(NSError**)sendError andResponse:(int*)response discardBody:(BOOL)discardBody;
- (NSDictionary*) makeSynchronousRequest:(NSError**)sendError;

@end
