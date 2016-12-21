cmake_minimum_required(VERSION 3.5)

project(BlindJump)
set(EXECUTABLE_NAME ${PROJECT_NAME})
set(PROJECT_SOURCE_DIR "../src/")
set(SFML_DIR "../deps/SFML-2.4.1")
set(LUA_DIR "../deps/lua-5.3.3/src")

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
file(GLOB_RECURSE blindjump_SOURCES "${PROJECT_SOURCE_DIR}/*.cpp")
file(GLOB_RECURSE blindjump_HEADERS "${PROJECT_SOURCE_DIR}/*.hpp")

# This bit is so that the CMAKE platform variables can map directly
# to preprocessor macros in config.h (CMAKE vars don't default to 0).
# The only part of the codebase that needs this is the resourcePath()
# function, it provides a path to resource files relative to the
# running executable, and cannot be done portably at the moment.
if(WIN32)
  set(SFML_STATIC_LIBRARIES ON)
  set(APPLE 0)
  set(UNIX 0)
elseif(APPLE)
  set(WIN32 0)
  set(UNIX 0)
elseif(UNIX)
  set(WIN32 0)
  set(APPLE 0)
endif()

set(CMAKE_BUILD_TYPE Release)

set(VERSION_MAJOR 0)
set(VERSION_MINOR 2)
configure_file(
  "${PROJECT_BINARY_DIR}/config.h.in"
  "${PROJECT_SOURCE_DIR}/config.h"
  )
include_directories("${PROJECT_BINARY_DIR}")

add_executable(${EXECUTABLE_NAME} WIN32 MACOSX_BUNDLE ${blindjump_SOURCES} ${RESOURCE_PATH})

set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake_modules" ${CMAKE_MODULE_PATH})

include_directories("${SFML_DIR}/include/" "${LUA_DIR}")
if(APPLE)
  target_link_libraries(${EXECUTABLE_NAME} "-L${LUA_DIR} -llua -framework sfml-window -framework sfml-graphics -framework sfml-system -framework sfml-audio -Xlinker -rpath -Xlinker @loader_path/../Frameworks")
  set(MACOSX_BUNDLE_BUNDLE_NAME ${EXECUTABLE_NAME})
  set(MACOSX_BUNDLE_ICON_FILE icon.icns)
  add_custom_target(pkg ALL mkdir -p ${EXECUTABLE_NAME}.app/Contents/Resources
    COMMAND mkdir -p ${EXECUTABLE_NAME}.app/Contents/Frameworks
    COMMAND cp -r ../res/* ${EXECUTABLE_NAME}.app/Contents/Resources
    COMMAND cp macos/icon.icns ${EXECUTABLE_NAME}.app/Contents/Resources
    COMMAND cp -r ${SFML_DIR}/lib/* ${EXECUTABLE_NAME}.app/Contents/Frameworks
    COMMAND cp -r ${SFML_DIR}/extlibs/libs-osx/Frameworks/* ${EXECUTABLE_NAME}.app/Contents/Frameworks)
  add_custom_target(res cp -r ../res/* ${EXECUTABLE_NAME}.app/Contents/Resources)
elseif(WIN32)
  # FIXME: I don't have Windows, cannot do this myself!!!
  target_link_libraries(${EXECUTABLE_NAME} ${SFML_LIBRARIES})
elseif(UNIX)
  # FIXME: I should install debian, redhat, etc. and get this working!!!
  target_link_libraries(${EXECUTABLE_NAME} ${SFML_LIBRARIES})
  find_package(Threads)
  target_link_libraries(${EXECUTABLE_NAME} ${CMAKE_THREAD_LIBS_INIT})
  if(EXISTS "/etc/debian_version")
    # TODO create deb package
  endif()
  if(EXISTS "/etc/redhat-release")
    # TODO create rpm: install centos in a vm and get this working!
  endif()
endif()
