#import "DataChannelWrapper.hh"
#import "WebRTCModule.hh"

@interface RTCDataChannel (React)

@property(nonatomic, strong) NSNumber *peerConnectionId;

@end

@interface WebRTCModule (RTCDataChannel)<DataChannelWrapperDelegate>

- (NSString *)stringForDataChannelState:(RTCDataChannelState)state;

@end
