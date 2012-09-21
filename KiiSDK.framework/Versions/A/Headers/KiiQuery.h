//
//  KiiQuery.h
//  KiiSDK-Private
//
//  Created by Chris Beauchamp on 1/25/12.
//  Copyright (c) 2012 Chris Beauchamp. All rights reserved.
//

#import <Foundation/Foundation.h>

@class KiiClause;

/** A class to handle queries agains the data store.
 
 This class gives an application the opportunity to query the server for a refined set of results. A query must be initialized with a collection (class) to query against, can be composed of various attributes, and must contain either a KQWhere or KQExp clause for its main definition.
 */
@interface KiiQuery : NSObject 


/** The object collection being queried. nil if querying for files. */
@property (readonly) NSString *collection;

/** The file container being queried. nil if querying for objects. */
@property (readonly) NSString *container;

/** The file container being queried. nil if querying for objects. */
@property (readonly) NSString *sortField;

/** The maximum number of results to return (0 < N <= 100] */
@property (nonatomic, assign) int limit;

/** TRUE if the result set should be sorted in descending order */
@property (readonly) BOOL sortDescending;


/** Create a KiiQuery object based on a KiiClause
 
 @param clause The KiiClause to be executed with the query
 */
+ (KiiQuery*) queryWithClause:(KiiClause*)clause;


/** Set the query to sort by a field in descending order
 
 If a sort has already been set, it will be overwritten.
 @param field The key that should be used to sort
 */
- (void) sortByDesc:(NSString*)field;


/** Set the query to sort by a field in ascending order
 
 If a sort has already been set, it will be overwritten.
 @param field The key that should be used to sort
 */
- (void) sortByAsc:(NSString*)field;

@end
