cmake_minimum_required(VERSION 3.5)

project(BlindJump)
set(EXECUTABLE_NAME ${PROJECT_NAME})
set(PROJECT_SOURCE_DIR "../src/")

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
file(GLOB_RECURSE blindjump_SOURCES "${PROJECT_SOURCE_DIR}/*.cpp")
file(GLOB_RECURSE blindjump_HEADERS "${PROJECT_SOURCE_DIR}/*.hpp")

# This bit is so that the CMAKE platform variables can map directly
# to preprocessor macros in config.h (CMAKE vars don't default to 0)
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

find_package(SFML 2.4 REQUIRED graphics window network audio system)
if(SFML_FOUND)
  include_directories(${SFML_INCLUDE_DIR})
  if(APPLE)
    target_link_libraries(${EXECUTABLE_NAME} "-framework sfml-window -framework sfml-graphics -framework sfml-system -framework sfml-audio -Xlinker -rpath -Xlinker @loader_path/../Frameworks")
    set(MACOSX_BUNDLE_BUNDLE_NAME ${EXECUTABLE_NAME})
    set(MACOSX_BUNDLE_ICON_FILE icon.icns)
    add_custom_target(pkg ALL mkdir -p ${EXECUTABLE_NAME}.app/Contents/Resources
      COMMAND mkdir -p ${EXECUTABLE_NAME}.app/Contents/Frameworks
      COMMAND cp ../res/* ${EXECUTABLE_NAME}.app/Contents/Resources
      COMMAND cp macos/icon.icns ${EXECUTABLE_NAME}.app/Contents/Resources
      COMMAND cp -r macos/Frameworks/* ${EXECUTABLE_NAME}.app/Contents/Frameworks)
  elseif(WIN32)
    target_link_libraries(${EXECUTABLE_NAME} ${SFML_LIBRARIES})
  elseif(UNIX)
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
endif()
