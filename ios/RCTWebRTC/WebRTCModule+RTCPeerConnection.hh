#import <WebRTC/RTCPeerConnection.h>
#import "DataChannelWrapper.hh"
#import "WebRTCModule.hh"

@interface RTCPeerConnection (React)

@property(nonatomic, strong) NSNumber *reactTag;
@property(nonatomic, strong) NSMutableDictionary<NSString *, DataChannelWrapper *> *dataChannels;
@property(nonatomic, strong) NSMutableDictionary<NSString *, RTCMediaStream *> *remoteStreams;
@property(nonatomic, strong) NSMutableDictionary<NSString *, RTCMediaStreamTrack *> *remoteTracks;
@property(nonatomic, weak) id webRTCModule;

@end

@interface WebRTCModule (RTCPeerConnection)<RTCPeerConnectionDelegate>

@end
