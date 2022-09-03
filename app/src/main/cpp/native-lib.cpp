#include <jni.h>
#include <string>
#include <iostream>
#include "Demo.h"

// C 语言中 双引号的头文件默认充当前路径下查找，尖括号的头文件充搜索路径查找。
// 自定义的 c 和cpp 文件如果想要写为尖括号引入，那么需要在 CmakeLists.txt 文件中配置 include_directories(people/)
// 这也的为搜索路径，就可以使用 <> 引用头文件了。
//#include "people/people.h"
#include <people.h>
#include <android/log.h>

extern "C" JNIEXPORT jstring JNICALL
Java_com_didi_androidnative_MainActivity_stringFromJNI(
        JNIEnv *env,
        jobject /* this */) {
    std::string hello = "Hello from Native";
//    auto *people = new People();
    People people;
    int result = add(1,2);
    __android_log_print(ANDROID_LOG_DEBUG, "MainActivity", "dynamic lib loaded");
    std::string s = people.getString() + " " +std::to_string(result);
    return env->NewStringUTF(s.c_str());
//    return env->NewStringUTF(hello.c_str());
}