cmake_minimum_required(VERSION 3.5)

project(InteractiveTimer LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# QtCreator supports the following variables for Android, which are identical to qmake Android variables.
# Check http://doc.qt.io/qt-5/deployment-android.html for more information.
# They need to be set before the find_package(Qt5 ...) call.

#if(ANDROID)
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
#    if (ANDROID_ABI STREQUAL "armeabi-v7a")
#        set(ANDROID_EXTRA_LIBS
#            ${CMAKE_CURRENT_SOURCE_DIR}/path/to/libcrypto.so
#            ${CMAKE_CURRENT_SOURCE_DIR}/path/to/libssl.so)
#    endif()
#endif()

find_package(Qt5 COMPONENTS Widgets Multimedia REQUIRED)

qt5_add_resources(RESOURCES res.qrc)

if(ANDROID)
  add_library(InteractiveTimer SHARED
    main.cpp
    interactivetimer.cpp
    interactivetimer.h
    timerwindow.cpp
    timerwindow.h
    timerwindow.ui
  )
else()
  add_executable(InteractiveTimer
    main.cpp
    timerwindow.cpp
    interactivetimer.cpp
    interactivetimer.h
    timerwindow.h
    timerwindow.ui
    ${RESOURCES}
  )
endif()

target_link_libraries(InteractiveTimer PRIVATE Qt5::Widgets Qt5::Multimedia)
