//
//  iRate.h
//  AppraiseDemo
//
//  Created by 张诚 on 14/12/2.
//  Copyright (c) 2014年 zhangcheng. All rights reserved.
//
/*
iOS研究院 305044955
 版本 1.0版本
 本demo主要解决系统评分的问题，有2种方法可以实现 1种代理方式，1种block方式
 */
#pragma mark block实现代码 注意需要真机测试
/*
 [[iRate sharedInstance]showAlertWithStoreID:897504228 BundleID:@"com.zc.weichat" MessageTitle:@"小苍冰天雪地360°跪求一个好评" Message:@"小苍如此辛苦的写应用，恳求大人您可怜可怜我，给我一个好评吧，么么哒😊" rateTitle:@"这就去给小苍鼓励" waitTitle:@"等待下次提示" cancelTitle:@"残忍的拒绝" Block:^(int x) {
 
 switch (x) {
 case 0:
 NSLog(@"拒绝评价");
 break;
 case 1:
 NSLog(@"评价");
 break;
 case 2:
 NSLog(@"下次评价");
 break;
 default:
 break;
 }
 }];

 */
#pragma mark 代理实现
/*
 iRate*rate= [iRate sharedInstance];
 //弹出警告框的文字说明，如果不设置也可以是默认的
 rate.messageTitle=@"小苍冰天雪地360°跪求一个好评";
 rate.message=@"小苍如此辛苦的写应用，恳求大人您可怜可怜我，给我一个好评吧，么么哒😊";
 rate.rateButtonLabel=@"这就去给小苍鼓励";
 rate.remindButtonLabel=@"等待下次提示";
 rate.cancelButtonLabel=@"残忍的拒绝";
 
 //设置代理
 rate.delegate=self;
 
 代理方法
 //评价
 - (void)iRateUserDidAttemptToRateApp{
 NSLog(@"评价");
 }
 //拒绝评价
 - (void)iRateUserDidDeclineToRateApp{
 NSLog(@"拒绝评价");
 //当拒绝后，就不会在本次启动中再次运行
 }
 //下次评价
 - (void)iRateUserDidRequestReminderToRateApp{
 NSLog(@"下次评价");
 //点击下次评价后，不会在本次启动中再次运行
 }
 */






#ifndef ah_retain
#if __has_feature(objc_arc)
#define ah_retain self
#define ah_dealloc self
#define release self
#define autorelease self
#else
#define ah_retain retain
#define ah_dealloc dealloc
#define __bridge
#endif
#endif

//  Weak delegate support

#ifndef ah_weak
#import <Availability.h>
#if (__has_feature(objc_arc)) && \
((defined __IPHONE_OS_VERSION_MIN_REQUIRED && \
__IPHONE_OS_VERSION_MIN_REQUIRED >= __IPHONE_5_0) || \
(defined __MAC_OS_X_VERSION_MIN_REQUIRED && \
__MAC_OS_X_VERSION_MIN_REQUIRED > __MAC_10_7))
#define ah_weak weak
#define __ah_weak __weak
#else
#define ah_weak unsafe_unretained
#define __ah_weak __unsafe_unretained
#endif
#endif

//  ARC Helper ends


#ifdef __IPHONE_OS_VERSION_MAX_ALLOWED
#import <UIKit/UIKit.h>
#else
#import <Cocoa/Cocoa.h>
#endif


extern NSUInteger const iRateAppStoreGameGenreID;
extern NSString *const iRateErrorDomain;


typedef enum
{
    iRateErrorBundleIdDoesNotMatchAppStore = 1,
    iRateErrorApplicationNotFoundOnAppStore,
    iRateErrorApplicationIsNotLatestVersion
}
iRateErrorCode;


@protocol iRateDelegate <NSObject>
@optional

- (void)iRateCouldNotConnectToAppStore:(NSError *)error;
- (void)iRateDidDetectAppUpdate;
- (BOOL)iRateShouldPromptForRating;
- (void)iRateUserDidAttemptToRateApp;
- (void)iRateUserDidDeclineToRateApp;
- (void)iRateUserDidRequestReminderToRateApp;

@end


@interface iRate : NSObject

//required for 32-bit Macs
#ifdef __i386
{
    @private
    
    NSUInteger _appStoreID;
    NSUInteger _appStoreGenreID;
    NSString *_appStoreCountry;
    NSString *_applicationName;
    NSString *_applicationVersion;
    NSString *_applicationBundleID;
    NSUInteger _usesUntilPrompt;
    NSUInteger _eventsUntilPrompt;
    float _daysUntilPrompt;
    float _remindPeriod;
    NSString *_messageTitle;
    NSString *_message;
    NSString *_cancelButtonLabel;
    NSString *_remindButtonLabel;
    NSString *_rateButtonLabel;
    NSURL *_ratingsURL;
    BOOL _disableAlertViewResizing;
    BOOL _promptAgainForEachNewVersion;
    BOOL _onlyPromptIfLatestVersion;
    BOOL _onlyPromptIfMainWindowIsAvailable;
    BOOL _promptAtLaunch;
    BOOL _verboseLogging;
    BOOL _previewMode;
    id<iRateDelegate> __ah_weak _delegate;
    id _visibleAlert;
    int _previousOrientation;
    BOOL _currentlyChecking;
}
#endif

+ (iRate *)sharedInstance;

//app store ID - this is only needed if your
//bundle ID is not unique between iOS and Mac app stores
@property (nonatomic, assign) NSUInteger appStoreID;

//application details - these are set automatically
@property (nonatomic, assign) NSUInteger appStoreGenreID;
@property (nonatomic, copy) NSString *appStoreCountry;
@property (nonatomic, copy) NSString *applicationName;
@property (nonatomic, copy) NSString *applicationVersion;
@property (nonatomic, copy) NSString *applicationBundleID;

//usage settings - these have sensible defaults
@property (nonatomic, assign) NSUInteger usesUntilPrompt;
@property (nonatomic, assign) NSUInteger eventsUntilPrompt;
@property (nonatomic, assign) float daysUntilPrompt;
@property (nonatomic, assign) float remindPeriod;

//message text, you may wish to customise these, e.g. for localisation
@property (nonatomic, copy) NSString *messageTitle;
@property (nonatomic, copy) NSString *message;
@property (nonatomic, copy) NSString *cancelButtonLabel;
@property (nonatomic, copy) NSString *remindButtonLabel;
@property (nonatomic, copy) NSString *rateButtonLabel;

//debugging and prompt overrides
@property (nonatomic, assign) BOOL disableAlertViewResizing;
@property (nonatomic, assign) BOOL promptAgainForEachNewVersion;
@property (nonatomic, assign) BOOL onlyPromptIfLatestVersion;
@property (nonatomic, assign) BOOL onlyPromptIfMainWindowIsAvailable;
@property (nonatomic, assign) BOOL promptAtLaunch;
@property (nonatomic, assign) BOOL verboseLogging;
@property (nonatomic, assign) BOOL previewMode;

//advanced properties for implementing custom behaviour
@property (nonatomic, strong) NSURL *ratingsURL;
@property (nonatomic, strong) NSDate *firstUsed;
@property (nonatomic, strong) NSDate *lastReminded;
@property (nonatomic, assign) NSUInteger usesCount;
@property (nonatomic, assign) NSUInteger eventCount;
@property (nonatomic, assign) BOOL declinedThisVersion;
@property (nonatomic, readonly) BOOL declinedAnyVersion;
@property (nonatomic, assign) BOOL ratedThisVersion;
@property (nonatomic, readonly) BOOL ratedAnyVersion;
@property (nonatomic, ah_weak) id<iRateDelegate> delegate;

//manually control behaviour
- (BOOL)shouldPromptForRating;
- (void)promptForRating;
- (void)promptIfNetworkAvailable;
- (void)openRatingsPageInAppStore;
- (void)logEvent:(BOOL)deferPrompt;


//添加block的指针
@property(nonatomic,copy)void(^alertBlock)(int);
-(void)showAlertWithStoreID:(int)storeID BundleID:(NSString*)bundleID  MessageTitle:(NSString*)title Message:(NSString*)message rateTitle:(NSString*)rateTitle waitTitle:(NSString*)waitTitle cancelTitle:(NSString*)cancelTitle Block:(void(^)(int))a;


@end
