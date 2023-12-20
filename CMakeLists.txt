cmake_minimum_required(VERSION 3.5)

project(Rubix VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)
find_package(OpenCV REQUIRED)
find_package(Threads REQUIRED)
find_package(QT NAMES Qt6 REQUIRED COMPONENTS Widgets Gui Core)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS OpenGL)

include_directories(${OpenCV_INCLUDE_DIRS})

set(PROJECT_SOURCES
        main.cpp
        mainwindow.cpp
        mainwindow.h
        mainwindow.ui
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(Rubix
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
        openglwindow.h openglwindow.cpp
        rubixcube.h rubixcube.cpp
        cubie.h cubie.cpp
        moviment.h moviment.cpp
        point3.h point3.cpp
        utils.h
        utils.cpp
        mesh.h mesh.cpp
        face.h face.cpp
        facecubie.h facecubie.cpp
        vertexid.h vertexid.cpp
        src.qrc
        matrices.h
        matrices.cpp
        vectors.h
        rotation.h rotation.cpp
        camera.h
        camera.cpp
        GLee.h
        GLee.cpp
    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET Rubix APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(Rubix SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(Rubix
            ${PROJECT_SOURCES}
        )
    endif()
endif()


target_link_libraries(Rubix PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)
target_link_libraries(Rubix PRIVATE Qt${QT_VERSION_MAJOR}::OpenGL)
target_link_libraries(Rubix PRIVATE OpenGL::GL OpenGL::GLU)
target_link_libraries(Rubix PRIVATE glu32)
target_link_libraries(Rubix PRIVATE opengl32)
target_link_libraries(Rubix PRIVATE freeglut)
target_link_libraries(Rubix PRIVATE ${OpenCV_LIBS})


# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
if(${QT_VERSION} VERSION_LESS 6.1.0)
  set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.example.Rubix)
endif()
set_target_properties(Rubix PROPERTIES
    ${BUNDLE_ID_OPTION}
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

include(GNUInstallDirs)
install(TARGETS Rubix
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(Rubix)
endif()
