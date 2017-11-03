//
//  StringeeCall.h
//  Stringee
//
//  Created by Hoang Duoc on 10/12/17.
//  Copyright © 2017 Hoang Duoc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <CoreTelephony/CTCall.h>
#import <CoreTelephony/CTCallCenter.h>
#import "StringeeClient.h"
#import "StringeeLocalVideoView.h"
#import "StringeeRemoteVideoView.h"

@class StringeeCall;

typedef enum {
    STRINGEE_CALLSTATE_INIT           = 0,
    STRINGEE_CALLSTATE_CALLING        = 1,
    STRINGEE_CALLSTATE_RINGING        = 2,
    STRINGEE_CALLSTATE_STARTING       = 3,
    STRINGEE_CALLSTATE_CONNECTED      = 4,
    STRINGEE_CALLSTATE_END            = 5
} StringeeCallState;

typedef enum {
    CallType_CallIn                     = 0,
    CallType_CallOut                    = 1,
    CallType_Internal_Incoming_Call     = 2,
    CallType_Internal_Call_Away         = 3
} CallType;

typedef enum {
    CallDTMF_Zero           = 0,
    CallDTMF_One            = 1,
    CallDTMF_Two            = 2,
    CallDTMF_Three          = 3,
    CallDTMF_Four           = 4,
    CallDTMF_Five           = 5,
    CallDTMF_Six            = 6,
    CallDTMF_Seven          = 7,
    CallDTMF_Eight          = 8,
    CallDTMF_Nine           = 9,
    CallDTMF_Star           = 10,
    CallDTMF_Pound          = 11
} CallDTMF;

typedef enum {
    VideoResolution_Normal      = 0, // 480 x 640
    VideoResolution_HD          = 1  // 720 x 1280
} VideoResolution;


@protocol StringeeCallStateDelegate <NSObject>

@required

- (void)didChangeState:(StringeeCall *)stringeeCall stringeeCallState:(StringeeCallState)state reason:(NSString *)reason;

@end


@protocol StringeeCallMediaDelegate <NSObject>

@required

- (void)didReceiveDtmfDigit:(StringeeCall *)stringeeCall digit:(NSString *)digit;

- (void)didReceiveLocalStream:(StringeeCall *)stringeeCall;

- (void)didReceiveRemoteStream:(StringeeCall *)stringeeCall;

@end


@interface StringeeCall : NSObject

@property (strong, nonatomic, readonly) NSString *callId;
@property (strong, nonatomic, readonly) NSString *from;
@property (strong, nonatomic, readonly) NSString *to;
@property (strong, nonatomic, readonly) NSString *fromAlias;
@property (strong, nonatomic, readonly) NSString *toAlias;
@property (weak, nonatomic) id<StringeeCallStateDelegate> callStateDelegate;
@property (weak, nonatomic) id<StringeeCallMediaDelegate> callMediaDelegate;
@property (assign, nonatomic, readonly) CallType callType;
@property (assign, nonatomic) BOOL isVideoCall;
@property (assign, nonatomic) VideoResolution videoResolution;
@property (strong, nonatomic, readonly) StringeeLocalVideoView *localVideoView;
@property (strong, nonatomic, readonly) StringeeRemoteVideoView *remoteVideoView;


// MARK: - Init

- (instancetype)initWithStringeeClient:(StringeeClient *)stringeeClient isIncomingCall:(BOOL)isIncomingCall from:(NSString *)from to:(NSString *)to;

- (instancetype)initWithStringeeClient:(StringeeClient *)stringeeClient isIncomingCall:(BOOL)isIncomingCall from:(NSString *)from to:(NSString *)to callId:(NSString *)callId;

// MARK: - Public

- (void)makeCallWithCompletionHandler:(void(^)(BOOL status, int code, NSString * message))completionHandler;

- (void)initAnswerCall;

- (void)answerCall;

- (void)hangup;

- (void)callDTMF:(CallDTMF)callDTMF completionHandler:(void(^)(BOOL status, int code, NSString * message))completionHandler;

- (void)switchCamera;

- (void)turnOnCamera:(BOOL)isOn;

- (void)autoOrientationOfLocalVideoViewWithSize:(CGSize)size withTransitionCoordinator:(id<UIViewControllerTransitionCoordinator>)coordinator;

- (void)mute:(BOOL)isMute;

- (void)statsWithCompletionHandler:
(void (^)( NSDictionary<NSString *, NSString *> *values ))completionHandler;

@end
