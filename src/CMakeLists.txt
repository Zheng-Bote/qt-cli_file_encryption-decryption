cmake_minimum_required(VERSION 3.23)

project(
  qt-cli_file_encryption-decryption
  VERSION 2.0.0
  DESCRIPTION "cli app to encrypt and decrypt a given file"
  HOMEPAGE_URL "https://github.com/Zheng-Bote/qt-cli_file_encryption-decryption"
  LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
if(CMAKE_SYSTEM_NAME STREQUAL "Linux")
  set(CMAKE_CXX_COMPILER clang++)
endif()

if(CMAKE_SYSTEM_NAME STREQUAL "Linux" AND ${CMAKE_BUILD_TYPE} STREQUAL "Debug")
  set(CMAKE_CXX_CLANG_TIDY clang-tidy;
                           -header-filter=.;-checks=cppcoreguidelines-*)
endif()

set(CMAKE_PREFIX_PATH "${CMAKE_BUILD_DIR}")

set(PROG_EXEC_NAME "${PROJECT_NAME}")
set(PROG_NAME "File encryption/decryption")
set(PROG_VERSION "${PROJECT_VERSION}")
set(PROG_HOMEPAGE "${PROJECT_HOMEPAGE_URL}")
set(PROG_AUTHOR "ZHENG Robert")
set(PROG_AUTHOR_CONTACT "robert.hase-zheng.net")
set(PROG_DESCRIPTION "${PROJECT_DESCRIPTION}")
set(PROG_COPYRIGHT "Copyright (c) 2025 ZHENG Robert")
set(PROG_BUILD_TYPE "${CMAKE_BUILD_TYPE}")

configure_file("${CMAKE_SOURCE_DIR}/configure/rz_config.h.in"
               "${CMAKE_SOURCE_DIR}/includes/rz_config.h")

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Core)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core)

add_executable(
  ${PROJECT_NAME}
  main.cpp
  includes/qaesencryption.cpp
  includes/qaesencryption.h
  includes/rz_options.h
  includes/cxxopts.hpp
  includes/rz_snippets.h
  includes/rz_qt-aes.h
  includes/dotenv.h)
target_link_libraries(${PROJECT_NAME} Qt${QT_VERSION_MAJOR}::Core)
target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_23)

include(GNUInstallDirs)
install(
  TARGETS ${PROJECT_NAME}
  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
  RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})

  install(TARGETS ${PROJECT_NAME} RUNTIME_DEPENDENCY_SET libDeps)
install(RUNTIME_DEPENDENCY_SET libDeps)

# IFW needs to set external export QTIFWDIR=...
set(QTIFWDIR "/opt/Qt/Tools/QtInstallerFramework/4.8/bin")
include(InstallRequiredSystemLibraries)
set(CPACK_IFW_ROOT "${GLOBAL}/Qt/Tools/QtInstallerFramework/4.8")
set(CPACK_RESOURCE_FILE_LICENSE  ${CMAKE_CURRENT_SOURCE_DIR}/../LICENSE)
set(CPACK_PACKAGE_VENDOR "${PROG_AUTHOR}")
set(CPACK_PACKAGE_CONTACT "${PROG_AUTHOR_CONTACT}")
set(CPACK_RPM_PACKAGE_VENDOR "${PROG_AUTHOR_CONTACT}")
set(CPACK_PACKAGE_DESCRIPTION "${PROJECT_DESCRIPTION}")
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "encrypt and decrypt a given file")
set(CPACK_THREADS "6")
set(CPACK_PACKAGE_CHECKSUM SHA256)
set(CPACK_DEBIAN_PACKAGE_SECTION "utils")
set(CPACK_PACKAGE_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/Packaging")
set(CPACK_GENERATOR "DEB;ZIP;TBZ2;RPM")

include(CPack)

# the end
message("Build with CMake version: ${CMAKE_VERSION} and c++${CMAKE_CXX_STANDARD}")
include(ProcessorCount)
ProcessorCount(N)
message("number of processors: " ${N})
message("cmake -S ../src -B . --parallel ${N}")

