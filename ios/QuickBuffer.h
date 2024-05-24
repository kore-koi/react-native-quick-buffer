#ifdef __cplusplus
#import "react-native-quick-buffer.h"
#endif

#ifdef RCT_NEW_ARCH_ENABLED
#import "RNQuickBufferSpec.h"

@interface QuickBuffer : NSObject <NativeQuickBufferSpec>
#else
#import <React/RCTBridgeModule.h>

@interface QuickBuffer : NSObject <RCTBridgeModule>
#endif

@end
