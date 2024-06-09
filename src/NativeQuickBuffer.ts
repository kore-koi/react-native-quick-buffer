import { NativeModules, Platform } from "react-native"


// eslint-disable-next-line @typescript-eslint/no-empty-interface
export interface NativeQuickBuffer {}


interface NativQuickBufferModuleSpec {
  createNativeQuickBuffer: (length: number) => NativeQuickBuffer
}

declare global {
  // eslint-disable-next-line no-var
  var __BufferProxy: object | undefined | null
}

if (global.__BufferProxy === null || global.__BufferProxy === undefined) {
  // Get the native BigNumber ReactModule
  const QuickBufferModule = NativeModules.QuickBuffer
  if (QuickBufferModule === null) {
    let message = "Failed to install react-native-bignumber: The native `BigNumber` Module could not be found."
    message += "\n* Make sure react-native-bignumber is correctly autolinked (run `npx react-native config` to verify)"
    if (Platform.OS === "ios" || Platform.OS === "macos") {
      message += "\n* Make sure you ran `pod install` in the ios/ directory."
    }
    if (Platform.OS === "android") {
      message += "\n* Make sure gradle is synced."
    }
    // check if Expo
    const ExpoConstants =
      NativeModules.NativeUnimoduleProxy?.modulesConstants?.ExponentConstants
    if (ExpoConstants !== null) {
      if (ExpoConstants.appOwnership === "expo") {
        // We're running Expo Go
        throw new Error(
          "react-native-bignumber is not supported in Expo Go! Use EAS (`expo prebuild`) or eject to a bare workflow instead."
        )
      } else {
        // We're running Expo bare / standalone
        message += "\n* Make sure you ran `expo prebuild`."
      }
    }

    message += "\n* Make sure you rebuilt the app."
    throw new Error(message)
  }

  // Check if we are running on-device (JSI)
  if (QuickBufferModule.install === null || QuickBufferModule.install === undefined) {
    throw new Error("Failed to install react-native-bignumber: React Native is not running on-device. BigNumber can only be used when synchronous method invocations (JSI) are possible. If you are using a remote debugger (e.g. Chrome), switch to an on-device debugger (e.g. Flipper) instead.")
  }

  // Call the synchronous blocking install() function
  const result = QuickBufferModule.install()
  if (result !== true) {
    throw new Error(`Failed to install react-native-bignumber: The native BigNumber Module could not be installed! Looks like something went wrong when installing JSI bindings: ${result}`)
  }


  // Check again if the constructor now exists. If not, throw an error.
  if (global.__BufferProxy === null) {
    throw new Error("Failed to install react-native-bignumber, the native initializer function does not exist. Are you trying to use BigNumber from different JS Runtimes?")
  }

}

// eslint-disable-next-line @typescript-eslint/no-explicit-any
const proxy = global.__BufferProxy as any
// eslint-disable-next-line @typescript-eslint/no-explicit-any
const native = {} as any
Object.keys(proxy).forEach((key: string) => {
  native[key] = proxy[key]
})
export const NativeQuickBufferModule = native as NativQuickBufferModuleSpec
