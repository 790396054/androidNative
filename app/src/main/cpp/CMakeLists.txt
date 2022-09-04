# For more information about using CMake with Android Studio, read the
# documentation: https://d.android.com/studio/projects/add-native-code.html

# Sets the minimum version of CMake required to build the native library.

cmake_minimum_required(VERSION 3.18.1)

# Declares and names the project.

project("androidnative")

# Creates and names a library, sets it as either STATIC
# or SHARED, and provides the relative paths to its source code.
# You can define multiple libraries, and CMake builds them for you.
# Gradle automatically packages shared libraries with your APK.

# set() 定义变量 kk 变量的值是 vallllllllll
set(kk vallllllllll)
# message() 打印日志，${} 引用变量
message(${kk})
# 以下 3 行是 CMAKE 默认的常量。可以直接使用。当然还有很多其他的常量。
message(${CMAKE_CURRENT_LIST_DIR})
message(${CMAKE_CURRENT_LIST_FILE})
message(${PROJECT_NAME})

# 逻辑判断。关键之和方法不区分大小写，但是变量区分大小写
if (true)
    message("this is true")
endif ()

# 添加动态库和静态库，SHARED是动态库，STATIC 是静态库
# androidnative 是动态库的名称，编译后为 libandroidnative.so
# SHARED 为动态库类型
# native-lib.cpp 要编译的源文件 多个用逗号隔开
add_library( # Sets the name of the library.
        androidnative
        # Sets the library as a shared library.
        SHARED
        # Provides a relative path to your source file(s).
        native-lib.cpp
        base/jvm.cpp
        jni/jni_exception.cpp
        jni/jni_bitmap.cpp
        jni/jni_thread.cpp
        Demo.cpp
        main.cpp)

# 编译 dynamic 动态库
add_library(dynamic-lib
        SHARED

        base/jvm.cpp
        base/AndroidLog.cpp
        jni/jni_type_demo.cpp
        jni/jni_dynamic_load.cpp)

# 编译 people 动态库
add_library(people-lib
        SHARED
        people/people.cpp)

# Searches for a specified prebuilt library and stores the path as a
# variable. Because CMake includes system libraries in the search path by
# default, you only need to specify the name of the public NDK library
# you want to add. CMake verifies that the library exists before
# completing its build.

# 将 people 文件夹设置到搜索路径中，这样头文件引用就可以这样写
# #include <people.h>
include_directories(${CMAKE_HOME_DIRECTORY}/people/)
include_directories(${CMAKE_HOME_DIRECTORY}/base/)

find_library( # Sets the name of the path variable.
        log-lib

        # Specifies the name of the NDK library that
        # you want CMake to locate.
        log)

# Specifies libraries CMake should link to your target library. You
# can link multiple libraries, such as libraries you define in this
# build script, prebuilt third-party libraries, or system libraries.

# 实现动态库的关联，将这 androidnative
#  people-lib 两个动态库关联起来，androidnative就可以引用people-lib中的代码了。
target_link_libraries( # Specifies the target library.
        androidnative
        people-lib
        # Links the target library to the log library
        # included in the NDK.
        ${log-lib})

target_link_libraries(
        dynamic-lib
        ${log-lib}
)