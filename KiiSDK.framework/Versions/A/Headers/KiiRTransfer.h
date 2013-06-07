//
//  KiiRTransfer.h
//  KiiSDK-Private
//
//  Created by Syah Riza on 3/26/13.
//  Copyright (c) 2013 Kii Corporation. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "KiiRTransferInfo.h"
#import "KiiFile.h"
@protocol KiiRTransfer;


typedef void(^KiiRTransferBlock)(id<KiiRTransfer> transferObject, NSError *error);

/** Protocol to encapsulate Resumable transfer process. Resumable transfer process consist of Download and Upload.
 */
@protocol KiiRTransfer <NSObject>

/** @name Resumable transfer process */

/** Synchronously get transfer process information. This is blocking method.
 @return KiiRTransferInfo an object contains information regarding transfer process.
 */
-(KiiRTransferInfo*) info;

/** Asynchronously proceed transfer process using block.
 This is non-blocking method.
 KiiRTransferBlock is a block defined as: typedef void(^KiiRTransferBlock)(id<KiiRTransfer> transferObject, NSError *error);

    [aTransfer transferWithProgressBlock:^(id <KiiRTransfer> transferObject, NSError *error) {
        if (nil == error) {
            KiiRTransferInfo *info = [transferObject info];
            NSLog(@"%d", [info completedSizeInBytes]);
        }
    } andCompletionBlock:^(id <KiiRTransfer> transferObject, NSError *error) {
        if (nil == error) {
            NSLog(@"Transfer is completed");
        }
    }];

 @param KiiRTransferBlock progress block. This can be nil.
 @param KiiRTransferBlock completion block to handle after process completed. This can be nil.
 */
-(void) transferWithProgressBlock:(KiiRTransferBlock) progress andCompletionBlock:(KiiRTransferBlock) completion;


/** Synchronously suspend transfer process.
 This is blocking method.
 @param error An NSError object, set to nil, to test for errors.
 */
-(void) suspend:(NSError**) error;


/** Synchronously terminate transfer process.
 This is blocking method.
 @param error An NSError object, set to nil, to test for errors.
 */
-(void) terminate:(NSError**) error;

@end
