cmake_minimum_required(VERSION 3.5)

project(blindjump)
set(EXECUTABLE_NAME ${PROJECT_NAME})

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

add_executable(${EXECUTABLE_NAME} WIN32 MACOSX_BUNDLE ${blindjump_SOURCES} ${RESOURCE_PATH})

set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake_modules" ${CMAKE_MODULE_PATH})
find_package(SFML 2 REQUIRED system window graphics audio)
if (SFML_FOUND)
  include_directories(${SFML_INCLUDE_DIR})
  if (APPLE)
    target_link_libraries(${EXECUTABLE_NAME} "-framework sfml-window -framework sfml-graphics -framework sfml-system -framework sfml-audio -Xlinker -rpath -Xlinker @loader_path/../Frameworks -fobjc-link-runtime")
    set(MACOSX_BUNDLE_BUNDLE_NAME ${EXECUTABLE_NAME})
    set(MACOSX_BUNDLE_ICON_FILE icon.icns)
    add_custom_target(package ALL mkdir -p ${EXECUTABLE_NAME}.app/Contents/Resources
      COMMAND mkdir -p ${EXECUTABLE_NAME}.app/Contents/Frameworks
      COMMAND cp ../res/* ${EXECUTABLE_NAME}.app/Contents/Resources/
      COMMAND cp macos/icon.icns ${EXECUTABLE_NAME}.app/Contents/Resources/
      COMMAND cp -r macos/Frameworks/* ${EXECUTABLE_NAME}.app/Contents/Frameworks/)
  elseif (WIN32)
    # TODO
    add_executable(${EXECUTABLE_NAME} WIN32 ${blindjump_SOURCES})
  elseif (UNIX)
    target_link_libraries(${EXECUTABLE_NAME} ${SFML_LIBRARIES})
    find_package(Threads)
    target_link_libraries(${EXECUTABLE_NAME} ${CMAKE_THREAD_LIBS_INIT})
    if (EXISTS "/etc/debian_version")
      add_custom_target(package mkdir -p temp/DEBIAN
	COMMAND cp debian/control temp/DEBIAN/
	COMMAND mkdir -p temp/usr/bin/
	COMMAND mv ${EXECUTABLE_NAME} temp/usr/bin/
	COMMAND mv temp ${EXECUTABLE_NAME}
	COMMAND dpkg-deb --build ${EXECUTABLE_NAME}
	COMMAND rm -rf ${EXECUTABLE_NAME})
    endif()
    if (EXISTS "/etc/redhat-release")
      # create rpm TODO: install centos in a vm and get this working!
    endif()
  endif()
endif()
