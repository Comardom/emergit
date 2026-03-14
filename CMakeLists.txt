cmake_minimum_required(VERSION 3.19)
project(emergit LANGUAGES CXX)

# 明确要求使用 C++23 标准
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED True)
# 非常重要的编译qrc开关(RCC编译器开关)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
# 版本是Qt6.5, Widget程序，使用多语言
find_package(Qt6 6.5 REQUIRED COMPONENTS Core Widgets LinguistTools)
find_package(Qt6 6.5 OPTIONAL_COMPONENTS DBus)

qt_standard_project_setup()

set(PROJECT_SOURCES
        app.qrc
        main.cpp
        Prologue.cpp
        Prologue.h
        BaseMultilingualWindow.cpp
        BaseMultilingualWindow.h
        BaseMultilingualWindow.ui
        OSymphonica.cpp
        OSymphonica.h
        OSymphonica.ui
        plugin/Shutdown/Shutdown.cpp
        plugin/Shutdown/Shutdown.h
        plugin/Shutdown/Shutdown.ui
        plugin/Shutdown/OS/ShutdownForOSInterface.h
)
if (WIN32)
    list(APPEND PROJECT_SOURCES
        plugin/Shutdown/OS/WindowsExecShutdown.cpp
        plugin/Shutdown/OS/WindowsExecShutdown.h
    )
    add_compile_definitions(OS_WIN)
elseif (CMAKE_SYSTEM_NAME STREQUAL "FreeBSD")
    list(APPEND PROJECT_SOURCES
        plugin/Shutdown/OS/FreeBSDExecShutdown.cpp
        plugin/Shutdown/OS/FreeBSDExecShutdown.h
    )
    add_compile_definitions(OS_FREEBSD)
elseif (CMAKE_SYSTEM_NAME STREQUAL "Linux")
    list(APPEND PROJECT_SOURCES
        plugin/Shutdown/OS/LinuxExecShutdown.cpp
        plugin/Shutdown/OS/LinuxExecShutdown.h
    )
    add_compile_definitions(OS_LINUX)
elseif (APPLE)
    message(STATUS "Build for macOS - Placeholder for future implementation")
    # 这里留给写 MacExecShutdown.mm
    # list(APPEND PROJECT_SOURCES plugin/Shutdown/OS/MacExecShutdown.mm)
    add_definitions(OS_MAC)
else()
    message(WARNING "Unknown OS: No shutdown implementation will be compiled.")
endif ()

qt_add_executable(emergit
        WIN32 MACOSX_BUNDLE
#        app.qrc
        ${PROJECT_SOURCES}
)


# 定义一个变量包含所有 UI 相关文件
#set(TS_SOURCES
#    main.cpp
#    Prologue.h Prologue.cpp
#    BaseMultilingualWindow.h BaseMultilingualWindow.cpp BaseMultilingualWindow.ui
#    OSymphonica.h OSymphonica.cpp OSymphonica.ui
#        plugin/Shutdown/Shutdown.h
#        plugin/Shutdown/Shutdown.cpp
#        plugin/Shutdown/Shutdown.ui
#)
# 告诉 lupdate，源代码中 tr() 包裹的文本是 zh_CN (简体中文)。
# 这样 lupdate 在生成 .ts 文件时，会将 zh_CN 的文本作为源文本。
# 这是实现“tr包裹简中”的关键。
set_property(SOURCE ${PROJECT_SOURCES}
        APPEND PROPERTY
        QT_TRANSLATION_SOURCE_LANGUAGE "zh_CN"
)


qt_add_translations(
    TARGETS emergit
    TS_FILES
        emergit_en_US.ts
        emergit_zh_TW.ts
        emergit_zh_CN.ts
)

target_link_libraries(emergit
    PRIVATE
        Qt::Core
        Qt::Widgets
#        Qt6::DBus
)
if(MSVC)
    target_compile_options(emergit PRIVATE /utf-8 /permissive-)
endif()
# 仅在 Windows 平台下链接系统 API 库
if(WIN32)
    target_link_libraries(emergit
        PRIVATE
            user32
            advapi32
    )
elseif (APPLE)
    # 预留 Mac 框架链接口子
    # target_link_libraries(emergit PRIVATE "-framework IOKit")
elseif (UNIX AND NOT APPLE)
    # 仅在支持 DBus 的 Unix 系统链接
    if(Qt6DBus_FOUND)
        target_link_libraries(emergit PRIVATE Qt6::DBus)
        target_compile_definitions(emergit PRIVATE USE_DBUS)
    endif()
endif()

#target_include_directories(emergit PRIVATE
#        /usr/x86_64-w64-mingw32/include
#    )


include(GNUInstallDirs)

install(TARGETS emergit
    BUNDLE  DESTINATION .
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

qt_generate_deploy_app_script(
    TARGET emergit
    OUTPUT_SCRIPT deploy_script
    NO_UNSUPPORTED_PLATFORM_ERROR
)
install(SCRIPT ${deploy_script})
