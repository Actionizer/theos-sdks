/*	NSRunLoop.h
	Copyright (c) 1994-2019, Apple Inc. All rights reserved.
*/

#import <Foundation/NSObject.h>
#import <Foundation/NSDate.h>
#import <CoreFoundation/CFRunLoop.h>

@class NSTimer, NSPort, NSArray<ObjectType>, NSString;

NS_HEADER_AUDIT_BEGIN(nullability, sendability)

FOUNDATION_EXPORT NSRunLoopMode const NSDefaultRunLoopMode;
FOUNDATION_EXPORT NSRunLoopMode const NSRunLoopCommonModes API_AVAILABLE(macos(10.5), ios(2.0), watchos(2.0), tvos(9.0));

@interface NSRunLoop : NSObject

@property (class, readonly, strong) NSRunLoop *currentRunLoop NS_SWIFT_UNAVAILABLE_FROM_ASYNC("currentRunLoop cannot be used from async contexts.");
@property (class, readonly, strong) NSRunLoop *mainRunLoop API_AVAILABLE(macos(10.5), ios(2.0), watchos(2.0), tvos(9.0));

@property (nullable, readonly, copy) NSRunLoopMode currentMode;

- (CFRunLoopRef)getCFRunLoop CF_RETURNS_NOT_RETAINED;

- (void)addTimer:(NSTimer *)timer forMode:(NSRunLoopMode)mode;

- (void)addPort:(NSPort *)aPort forMode:(NSRunLoopMode)mode;
- (void)removePort:(NSPort *)aPort forMode:(NSRunLoopMode)mode;

- (nullable NSDate *)limitDateForMode:(NSRunLoopMode)mode;

- (void)acceptInputForMode:(NSRunLoopMode)mode beforeDate:(NSDate *)limitDate NS_SWIFT_UNAVAILABLE_FROM_ASYNC("acceptInput(for:before:) cannot be used from async contexts.");

@end

@interface NSRunLoop (NSRunLoopConveniences)

- (void)run NS_SWIFT_UNAVAILABLE_FROM_ASYNC("run cannot be used from async contexts.");

- (void)runUntilDate:(NSDate *)limitDate NS_SWIFT_UNAVAILABLE_FROM_ASYNC("run(until:) cannot be used from async contexts.");

- (BOOL)runMode:(NSRunLoopMode)mode beforeDate:(NSDate *)limitDate NS_SWIFT_UNAVAILABLE_FROM_ASYNC("run(_:before:) cannot be used from async contexts.");

#if TARGET_OS_OSX
- (void)configureAsServer API_DEPRECATED("Not supported", macos(10.0,10.5), ios(2.0,2.0), watchos(2.0,2.0), tvos(9.0,9.0));
#endif

/// Schedules the execution of a block on the target run loop in given modes.
/// - parameter: modes   An array of input modes for which the block may be executed.
/// - parameter: block   The block to execute
- (void)performInModes:(NSArray<NSRunLoopMode> *)modes block:(void (NS_SWIFT_SENDABLE ^)(void))block API_AVAILABLE(macosx(10.12), ios(10.0), watchos(3.0), tvos(10.0));

/// Schedules the execution of a block on the target run loop.
/// - parameter: block   The block to execute
- (void)performBlock:(void (NS_SWIFT_SENDABLE ^)(void))block API_AVAILABLE(macosx(10.12), ios(10.0), watchos(3.0), tvos(10.0));

@end

/**************** 	Delayed perform	 ******************/

@interface NSObject (NSDelayedPerforming)

- (void)performSelector:(SEL)aSelector withObject:(nullable id)anArgument afterDelay:(NSTimeInterval)delay inModes:(NSArray<NSRunLoopMode> *)modes;
- (void)performSelector:(SEL)aSelector withObject:(nullable id)anArgument afterDelay:(NSTimeInterval)delay;
+ (void)cancelPreviousPerformRequestsWithTarget:(id)aTarget selector:(SEL)aSelector object:(nullable id)anArgument;
+ (void)cancelPreviousPerformRequestsWithTarget:(id)aTarget;

@end

@interface NSRunLoop (NSOrderedPerform)

- (void)performSelector:(SEL)aSelector target:(id)target argument:(nullable id)arg order:(NSUInteger)order modes:(NSArray<NSRunLoopMode> *)modes;
- (void)cancelPerformSelector:(SEL)aSelector target:(id)target argument:(nullable id)arg;
- (void)cancelPerformSelectorsWithTarget:(id)target;

@end

NS_HEADER_AUDIT_END(nullability, sendability)
