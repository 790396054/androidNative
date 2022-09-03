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

set(kk vallllllllll)
message(${kk})
message(${CMAKE_CURRENT_LIST_DIR})
message(${CMAKE_CURRENT_LIST_FILE})
message(${PROJECT_NAME})

if (false)
    message("this is true")
endif ()

add_library( # Sets the name of the library.
        androidnative

        # Sets the library as a shared library.
        SHARED

        # Provides a relative path to your source file(s).
        native-lib.cpp)
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
include_directories(people/)


find_library( # Sets the name of the path variable.
        log-lib

        # Specifies the name of the NDK library that
        # you want CMake to locate.
        log)

# Specifies libraries CMake should link to your target library. You
# can link multiple libraries, such as libraries you define in this
# build script, prebuilt third-party libraries, or system libraries.

target_link_libraries( # Specifies the target library.
        androidnative
        people-lib
        # Links the target library to the log library
        # included in the NDK.
        ${log-lib})