cmake_minimum_required(VERSION 3.19)
project(emergit LANGUAGES CXX)

# 明确要求使用 C++23 标准
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED True)
# 非常重要的编译qrc开关(RCC编译器开关)
set(CMAKE_AUTORCC ON)

find_package(Qt6 6.5 REQUIRED COMPONENTS Core Widgets LinguistTools)

qt_standard_project_setup()

qt_add_executable(emergit
        WIN32 MACOSX_BUNDLE
        main.cpp
        mainwindow.cpp
        mainwindow.h
        mainwindow.ui
        app.qrc
        splash/FirstSplash.cpp
        splash/FirstSplash.h
        splash/FirstSplash.ui
        BaseMultilingualWindow.cpp
        BaseMultilingualWindow.h
        BaseMultilingualWindow.ui
        splash/FirstSplashThread.cpp
        splash/FirstSplashThread.h
#        img/dyingStarUndMaria.bmp
#        img/haizhiyun.jpg
)

# 告诉 lupdate，源代码中 tr() 包裹的文本是 zh_CN (简体中文)。
# 这样 lupdate 在生成 .ts 文件时，会将 zh_CN 的文本作为源文本。
# 这是实现“tr包裹简中”的关键。
set_property(SOURCE
        main.cpp
        mainwindow.cpp
        mainwindow.h
        mainwindow.ui
        APPEND PROPERTY
        QT_TRANSLATION_SOURCE_LANGUAGE "zh_CN"
)

# set(RESOURCE_FILES app.qrc)
# qt_add_resources(emergit_RESOURCES ${RESOURCE_FILES})

qt_add_translations(
    TARGETS emergit
    TS_FILES
        emergit_en_US.ts
        emergit_zh_TW.ts
        emergit_zh_CN.ts
        # （旧的）关键：指定 .qm 文件的输出目录，以便 QRC 文件能找到它们
#        OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/i18n
        # 注意：移除了 OUTPUT_DIRECTORY。
        # 让 Qt 自动管理路径，它会自动生成一个包含 .qm 的内部资源文件
        # 并自动将其挂载到 ":/i18n/" 路径下（默认行为）。
)

target_link_libraries(emergit
    PRIVATE
        Qt::Core
        Qt::Widgets
)

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
