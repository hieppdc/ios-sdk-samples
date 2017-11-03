//
//  StringeeClient.h
//  Stringee
//
//  Created by Hoang Duoc on 10/11/17.
//  Copyright © 2017 Hoang Duoc. All rights reserved.
//

#import <Foundation/Foundation.h>

@class StringeeClient;
@class StringeeCall;
@class StringeeRoom;

@protocol StringeeConnectionDelegate <NSObject>

@required

- (void)requestAccessToken:(StringeeClient *)stringeeClient;

- (void)didConnect:(StringeeClient *)stringeeClient isReconnecting:(BOOL)isReconnecting;

- (void)didDisConnect:(StringeeClient *)stringeeClient isReconnecting:(BOOL)isReconnecting;

- (void)didFailWithError:(StringeeClient *)stringeeClient code:(int)code message:(NSString *)message;

@end


@protocol StringeeIncomingCallDelegate <NSObject>

@required

- (void)incomingCallWithStringeeClient:(StringeeClient *)stringeeClient isVideoCall:(BOOL)isVideoCall callId:(NSString *)callId from:(NSString *)from to:(NSString *)to fromAlias:(NSString *)fromAlias toAlias:(NSString *)toAlias;

@end



@interface StringeeClient : NSObject

@property (weak, nonatomic) id<StringeeConnectionDelegate> connectionDelegate;
@property (weak, nonatomic) id<StringeeIncomingCallDelegate> incomingCallDelegate;
@property (assign, nonatomic, readonly) BOOL hasConnected;
@property (strong, nonatomic, readonly) NSString *userId;


- (instancetype)initWithConnectionDelegate:(id<StringeeConnectionDelegate>)delegate;

- (void)connectWithAccessToken:(NSString *)accessToken;

@end
