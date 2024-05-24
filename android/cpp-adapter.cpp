#include <jni.h>
#include "react-native-quick-buffer.h"

extern "C"
JNIEXPORT jdouble JNICALL
Java_com_quickbuffer_QuickBufferModule_nativeMultiply(JNIEnv *env, jclass type, jdouble a, jdouble b) {
    return quickbuffer::multiply(a, b);
}
