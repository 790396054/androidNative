#include <jni.h>
#include <string>
#include <iostream>

extern "C" JNIEXPORT jstring JNICALL
Java_com_didi_androidnative_MainActivity_stringFromJNI(
        JNIEnv* env,
        jobject /* this */) {
    std::string hello = "Hello from Native";

    return env->NewStringUTF(hello.c_str());
}