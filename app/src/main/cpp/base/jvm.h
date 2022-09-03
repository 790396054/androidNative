//
// Created by andy on 2022/9/3.
//
#include <android/log.h>
#include <jni.h>

#ifndef ANDROIDNATIVE_JVM_H
#define ANDROIDNATIVE_JVM_H

#ifdef __cplusplus
extern "C" {
#endif
void setJvm(JavaVM *jvm);

JavaVM *getJvm();

#ifdef __cplusplus
}
#endif

#endif //ANDROIDNATIVE_JVM_H
