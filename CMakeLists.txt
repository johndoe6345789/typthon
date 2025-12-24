cmake_minimum_required(VERSION 3.22)

project(Typthon VERSION 3.14.0 LANGUAGES C)

# Allow using compilers provided by Conan if available
if(EXISTS "${CMAKE_BINARY_DIR}/conan_toolchain.cmake")
  include("${CMAKE_BINARY_DIR}/conan_toolchain.cmake")
endif()

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

configure_file(
  ${CMAKE_CURRENT_SOURCE_DIR}/cmake/version.h.in
  ${CMAKE_CURRENT_BINARY_DIR}/generated/typthon/version.h
  @ONLY
)

add_library(typthon_core STATIC src/runtime.c)
target_include_directories(
  typthon_core
  PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${CMAKE_CURRENT_BINARY_DIR}/generated
)
target_compile_features(typthon_core PUBLIC c_std_11)

add_executable(typthon src/main.c)
target_link_libraries(typthon PRIVATE typthon_core)

include(GNUInstallDirs)
install(
  TARGETS typthon_core typthon
  RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
  ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
)
install(
  DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/include/
  DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)
install(
  FILES ${CMAKE_CURRENT_BINARY_DIR}/generated/typthon/version.h
  DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/typthon
)

include(CTest)
if(BUILD_TESTING)
  add_executable(typthon_smoketest tests/smoke.c)
  target_include_directories(
    typthon_smoketest
    PRIVATE
      ${CMAKE_CURRENT_SOURCE_DIR}/include
      ${CMAKE_CURRENT_BINARY_DIR}/generated
  )
  target_link_libraries(typthon_smoketest PRIVATE typthon_core)

  add_test(NAME typthon_cli COMMAND typthon --version)
  add_test(NAME typthon_runtime_version COMMAND typthon_smoketest)
endif()
