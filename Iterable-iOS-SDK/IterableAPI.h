//
//  Iterable_API.h
//  Iterable-iOS-SDK
//
//  Created by Ilya Brin on 11/19/14.
//  Copyright (c) 2014 Iterable. All rights reserved.
//

@import Foundation;
#import "CommerceItem.h"

/**
 `IterableAPI` contains all the essential functions for communicating with Iterable's API
 */

@interface IterableAPI : NSObject

/**
 * Enum representing platform 
 */
typedef NS_ENUM(NSInteger, PushServicePlatform) {
    /** The sandbox push service */
    APNS_SANDBOX,
    /** The production push service */
    APNS
};

/////////////////////////////////
/// @name Creating an IterableAPI
/////////////////////////////////

/*!
 @method
 
 @abstract Initializes Iterable with just an API key and email, but no launchOptions
 
 @param apiKey   your Iterable apiKey
 @param email    the email of the user logged in
 
 @return an instance of IterableAPI
 */
- (instancetype) initWithApiKey:(NSString *)apiKey andEmail:(NSString *) email;

/*!
 @method
 
 @abstract Initializes Iterable with launchOptions
 
 @param apiKey          your Iterable apiKey
 @param email           the email of the user logged in
 @param launchOptions   launchOptions from application:didFinishLaunchingWithOptions
 
 @return an instance of IterableAPI
 */
- (instancetype) initWithApiKey:(NSString *)apiKey andEmail:(NSString *) email launchOptions:(NSDictionary *)launchOptions;

/*!
 @method
 
 @abstract Initializes a shared instance of Iterable with launchOptions
 
 @discussion This method will set up a singleton instance of the `IterableAPI` class for
 you using the given project API key. When you want to make calls to Iterable
 elsewhere in your code, you can use `sharedInstance`. If launchOptions is there and
 the app was launched from a remote push notification, we will track a pushOpen.
 
 @param apiKey          your Iterable apiKey
 @param email           the email of the user logged in
 @param launchOptions   launchOptions from application:didFinishLaunchingWithOptions
 
 @return an instance of IterableAPI
 */
+ (IterableAPI *) sharedInstanceWithApiKey:(NSString *)apiKey andEmail:(NSString *) email launchOptions:(NSDictionary *)launchOptions;

/*!
 @method
 
 @abstract Get the previously instantiated singleton instance of the API
 
 @discussion Must be initialized with `sharedInstanceWithApiKey:` before
 calling this class method.
 
 @return the existing IterableAPI instance
 */
+ (IterableAPI *)sharedInstance;

/////////////////////////////
/// @name Registering a token
/////////////////////////////

/*!
 @method 
 
 @abstract Register this device's token with Iterable

 @param token       The token representing this device/application pair, obtained from
                    `application:didRegisterForRemoteNotificationsWithDeviceToken`
                    after registering for remote notifications
 @param appName     The application name, as configured in Iterable during set up of the push integration
 @param pushServicePlatform     Dictates whether to register this token in the sandbox or production environment
 
 */
- (void)registerToken:(NSData *)token appName:(NSString *)appName pushServicePlatform:(PushServicePlatform)pushServicePlatform;

/////////////////////////
/// @name Tracking events
/////////////////////////

/*!
 @method
 
 @abstract Tracks a purchase
 
 @discussion Pass in the total purchase amount and an `NSArray` of `CommerceItem`s
 
 @param total       total purchase amount
 @param items       list of purchased items
 @param dataFields  an `NSDictionary` containing any additional information to save along with the event
 */
- (void)trackPurchase:(NSNumber *)total items:(NSArray<CommerceItem>*)items dataFields:(NSDictionary *)dataFields;

/*!
 @method
 
 @abstract Tracks a pushOpen event.
 
 @discussion Pass in the `userInfo` from the push notification payload
 
 @param userInfo    the push notification payload
 @param dataFields  an `NSDictionary` containing any additional information to save along with the event
 */
- (void)trackPushOpen:(NSDictionary *)userInfo dataFields:(NSDictionary *)dataFields;

/*!
 @method
 
 @abstract Tracks a pushOpen event
 
 @discussion Pass in the the relevant campaign data
 
 @param campaignId          The campaignId of the the push notification that caused this open event
 @param templateId          The templateId  of the the push notification that caused this open event
 @param appAlreadyRunning   This will get merged into the dataFields. Whether the app is already running when the notification was received
 @param dataFields          An `NSDictionary` containing any additional information to save along with the event
 */
- (void)trackPushOpen:(NSNumber *)campaignId templateId:(NSNumber *)templateId appAlreadyRunning:(BOOL)appAlreadyRunning dataFields:(NSDictionary *)dataFields;

/*!
 @method
 
 @abstract Tracks a custom event.
 
 @discussion Pass in the the custom event data.
 
 @param eventName   Name of the event
 @param dataFields  An `NSDictionary` containing any additional information to save along with the event
 */
- (void)track:(NSString *)eventName dataFields:(NSDictionary *)dataFields;

@end
