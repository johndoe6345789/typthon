cmake_minimum_required(VERSION 3.22)

project(Typthon VERSION 3.14.0 LANGUAGES C)

# Allow using compilers provided by Conan if available
if(EXISTS "${CMAKE_BINARY_DIR}/conan_toolchain.cmake")
  include("${CMAKE_BINARY_DIR}/conan_toolchain.cmake")
endif()

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# NOTE: Building CPython requires proper configuration (./configure)
# This CMakeLists.txt is a work in progress to wire to the real interpreter

# Platform detection
if(UNIX AND NOT APPLE)
  set(LINUX TRUE)
endif()

# TODO: Collect and build Python core source files from:
# - Python/*.c (interpreter core)
# - Objects/*.c (built-in types)
# - Parser/*.c (parser)
# - Modules/*.c (built-in modules)

# TODO: Generate or provide pyconfig.h
# CPython normally generates this via ./configure

# Placeholder: Build Python executable
add_executable(typthon Programs/python.c)

# TODO: Link against Python core library once built
# target_link_libraries(typthon PRIVATE python_core)

if(UNIX)
  target_link_libraries(typthon PRIVATE m dl pthread util)
endif()

target_include_directories(typthon
  PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/Include
)

include(GNUInstallDirs)
install(
  TARGETS typthon
  RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

include(CTest)
if(BUILD_TESTING)
  add_test(NAME typthon_version COMMAND typthon --version)
endif()
