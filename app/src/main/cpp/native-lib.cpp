#include <jni.h>
#include <string>
#include <iostream>

//#include "people/people.h"
#include <people.h>

extern "C" JNIEXPORT jstring JNICALL
Java_com_didi_androidnative_MainActivity_stringFromJNI(
        JNIEnv *env,
        jobject /* this */) {
    std::string hello = "Hello from Native";
//    auto *people = new People();
    People people;
    return env->NewStringUTF(people.getString().c_str());
//    return env->NewStringUTF(hello.c_str());
}