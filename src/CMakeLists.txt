cmake_minimum_required(VERSION 3.23)

project(
  qt-cli_file_encryption-decryption
  VERSION 0.1.0
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

set(PROG_EXEC_NAME "${PROJECT_NAME}")
set(PROG_NAME "File encryption/decryption")
set(PROG_VERSION "${PROJECT_VERSION}")
set(PROG_HOMEPAGE "${PROJECT_HOMEPAGE_URL}")
set(PROG_DESCRIPTION "${PROJECT_DESCRIPTION}")

configure_file("${CMAKE_SOURCE_DIR}/configure/rz_config.h.in"
               "${CMAKE_SOURCE_DIR}/includes/rz_config.h")

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Core)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core)

add_executable(
  ${PROJECT_NAME}
  main.cpp includes/qaesencryption.cpp includes/qaesencryption.h
  includes/rz_options.h includes/cxxopts.hpp
  includes/rz_snippets.h
  includes/rz_qt-aes.h)
target_link_libraries(${PROJECT_NAME} Qt${QT_VERSION_MAJOR}::Core)
target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_23)

include(GNUInstallDirs)
install(
  TARGETS ${PROJECT_NAME}
  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
  RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})
