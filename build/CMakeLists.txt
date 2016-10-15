cmake_minimum_required(VERSION 3.5)

project(blindjump)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
file(GLOB_RECURSE blindjump_SOURCES "../src/*.cpp")
file(GLOB_RECURSE blindjump_HEADERS "../src/*.hpp")

if (APPLE)
  set(RESOURCE_PATH "macos/ResourcePath.mm")
elseif (WIN32)
  # TODO
  set(RESOURCE_PATH "debian/ResourcePath.cpp")
elseif (UNIX)
  set(RESOURCE_PATH "debian/ResourcePath.cpp")
endif()

set(CMAKE_BUILD_TYPE Release)

set(blindjump_VERSION_MAJOR 0)
set(blindjump_VERSION_MINOR 2)
configure_file(
  "${PROJECT_SOURCE_DIR}/config.h.in"
  "${PROJECT_BINARY_DIR}/config.h"
  )
include_directories("${PROJECT_BINARY_DIR}")

set(EXECUTABLE_NAME "blindjump")

add_executable(blindjump WIN32 MACOSX_BUNDLE ${blindjump_SOURCES} ${RESOURCE_PATH})

set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake_modules" ${CMAKE_MODULE_PATH})
find_package(SFML 2 REQUIRED system window graphics audio)
if (SFML_FOUND)
  include_directories(${SFML_INCLUDE_DIR})
  if (APPLE)
    target_link_libraries(${EXECUTABLE_NAME} "-framework sfml-window -framework sfml-graphics -framework sfml-system -framework sfml-audio -Xlinker -rpath -Xlinker @loader_path/../Frameworks -fobjc-link-runtime")
    set(MACOSX_BUNDLE_BUNDLE_NAME blindjump)
    set(MACOSX_BUNDLE_ICON_FILE icon.icns)
    add_custom_target(pkgconfig ALL mkdir -p blindjump.app/Contents/Resources
      COMMAND mkdir -p blindjump.app/Contents/Frameworks
      COMMAND cp ../res/* blindjump.app/Contents/Resources/
      COMMAND cp macos/icon.icns blindjump.app/Contents/Resources/
      COMMAND cp -r macos/Frameworks/* blindjump.app/Contents/Frameworks/)
  elseif (WIN32)
    # TODO
    add_executable(blindjump WIN32 ${blindjump_SOURCES})
  elseif (UNIX)
    add_executable(blindjump ${blindjump_SOURCES})
    target_link_libraries(${EXECUTABLE_NAME} ${SFML_LIBRARIES})
    find_package(Threads)
    target_link_libraries(blindjump ${CMAKE_THREAD_LIBS_INIT})
  endif()
endif()
