#import <React/RCTBridge+Private.h>
#import <React/RCTUtils.h>
#import <ReactCommon/RCTTurboModule.h>
#import <jsi/jsi.h>

#import "QuickBuffer.h"
#import "QuickBufferHostObject.hpp"

@implementation QuickBuffer

RCT_EXPORT_MODULE(QuickBuffer)

RCT_EXPORT_BLOCKING_SYNCHRONOUS_METHOD(install)
{
  NSLog(@"Installing JSI bindings for react-native-quick-buffer...");
  RCTBridge* bridge = [RCTBridge currentBridge];
  RCTCxxBridge* cxxBridge = (RCTCxxBridge*)bridge;
  if (cxxBridge == nil) {
    return @false;
  }

  using namespace facebook;

  auto jsiRuntime = (jsi::Runtime*) cxxBridge.runtime;
  if (jsiRuntime == nil) {
    return @false;
  }
    auto& runtime = *jsiRuntime;

    auto hostObject = std::make_shared<QuickBufferHostObject>();
  auto object = jsi::Object::createFromHostObject(runtime, hostObject);
  runtime.global().setProperty(runtime, "__BufferProxy", std::move(object));

  NSLog(@"Successfully installed JSI bindings for react-native-quick-buffer");
  return @true;
}

@end
