# For more information about using CMake with Android Studio, read the
# documentation: https://d.android.com/studio/projects/add-native-code.html

# Sets the minimum version of CMake required to build the native library.

cmake_minimum_required(VERSION 3.4.1)

set( AMPEMVL2_VER 03.00.012)
set( AMPCMPNT_VER 01.01.007)
set( SDK AMP6500SDK)
set( SDK_VER AMP6500SDKv1.2.0)
set( POSLIBS_VER sdkv1.7.0)
set( AMPEMVL2_PATH C:/${SDK_VER}/${SDK}/${SDK_VER}/AMPEMVL2/${AMPEMVL2_VER})
set( AMPCMPNT_PATH C:/${SDK_VER}/${SDK}/${SDK_VER}/AMPCMPNT/${AMPCMPNT_VER})
set( SDK_POS_PATH C:/${SDK_VER}/${SDK}/${SDK_VER}/AMPPOSLibs/${POSLIBS_VER}/sdk_pos)

# This command can be used to add any flags, but it is intended to add preprocessor definitions.
# Flags beginning in -D or /D that look like preprocessor definitions are automatically added to the
# COMPILE_DEFINITIONS directory property for the current directory.

add_definitions(-DANDROID_POS)

# Creates and names a library, sets it as either STATIC
# or SHARED, and provides the relative paths to its source code.
# You can define multiple libraries, and CMake builds them for you.
# Gradle automatically packages shared libraries with your APK.

add_library( # Sets the name of the library.
             AmpEmvL2AndroidIF

             # Sets the library as a shared library.
             SHARED

             # CoreSrc Folder
             src/main/cpp/CoreSrc/Source/Agnos/CoreAgnosEmvFunc.cpp
             src/main/cpp/CoreSrc/Source/Agnos/CoreAgnosEmvCtlsFunc.cpp
             src/main/cpp/CoreSrc/Source/Agnos/CoreAgnosEmvTrans.cpp
             src/main/cpp/CoreSrc/Source/Card/CoreCardUtils.cpp
             src/main/cpp/CoreSrc/Source/Flow/CoreAmountEntry.cpp
             src/main/cpp/CoreSrc/Source/Flow/CoreCardEntry.cpp
             src/main/cpp/CoreSrc/Source/Flow/CoreDataEntry.cpp
             src/main/cpp/CoreSrc/Source/Screen/CoreScreens.cpp
             src/main/cpp/CoreSrc/Source/Utils/CoreUtils.cpp
             src/main/cpp/CoreSrc/Source/Storage/CoreTransObj.cpp

             # Project Folder
             src/main/cpp/Project/Source/AmpBaseAndroidIF.cpp
             src/main/cpp/Project/Source/AmpEmvL2AndroidIF.cpp
             src/main/cpp/Project/Source/Screens.cpp
             src/main/cpp/Project/Source/Purchase.cpp
             src/main/cpp/Project/Source/AMPUtils.cpp
             )

add_library(AMPEMVL2 SHARED IMPORTED)

set_target_properties(AMPEMVL2 PROPERTIES IMPORTED_LOCATION
    ${AMPEMVL2_PATH}/lib/libAMPEMVL2.so)

add_library(AMPCMPNT SHARED IMPORTED)

set_target_properties(AMPCMPNT PROPERTIES IMPORTED_LOCATION
        ${AMPCMPNT_PATH}/lib/libAMPCmpnt.so)

target_include_directories(
            AmpEmvL2AndroidIF PRIVATE

           ${AMPEMVL2_PATH}/include
           ${AMPCMPNT_PATH}/include
           ${SDK_POS_PATH}/include
           src/main/cpp/CoreSrc/Include
           src/main/cpp/Project/Include

)

# Searches for a specified prebuilt library and stores the path as a
# variable. Because CMake includes system libraries in the search path by
# default, you only need to specify the name of the public NDK library
# you want to add. CMake verifies that the library exists before
# completing its build.

find_library( # Sets the name of the path variable.
              log-lib

              # Specifies the name of the NDK library that
              # you want CMake to locate.
              log )

# Specifies libraries CMake should link to your target library. You
# can link multiple libraries, such as libraries you define in this
# build script, prebuilt third-party libraries, or system libraries.

target_link_libraries( # Specifies the target library.
                       AmpEmvL2AndroidIF
                       AMPEMVL2
                       AMPCMPNT
                       # Links the target library to the log library
                       # included in the NDK.
                       ${log-lib} )