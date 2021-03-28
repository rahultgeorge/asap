# This file is part of ASAP.
# Please see LICENSE.txt for copyright and licensing information.
include(GNUInstallDirs)
include_directories("/usr/local/include")
cmake_minimum_required(VERSION 3.16)
project(SanityChecks)

set(CMAKE_CXX_STANDARD 11)


find_package(LLVM REQUIRED CONFIG)
add_definitions(${LLVM_DEFINITIONS})
include_directories(${LLVM_INCLUDE_DIRS})
link_directories(${LLVM_LIBRARY_DIRS})

add_library(SanityChecks MODULE
  AsapPass.cpp
  CostModel.cpp
  ExitInsteadOfAbortPass.cpp
  GCOV.cpp
  SanityCheckCostPass.cpp
  SanityCheckInstructionsPass.cpp
  utils.cpp
)

add_dependencies(SanityChecks LLVMInstrumentation)
find_library(NEO4J_CLIENT neo4j-client)
target_link_libraries(SanityChecks PUBLIC "${NEO4J_CLIENT}")

# Create symlinks for asap-clang.rb
add_custom_command(OUTPUT ${CMAKE_BINARY_DIR}/bin/asap-clang
  COMMAND cd ${CMAKE_BINARY_DIR}/bin && ln -s ${CMAKE_CURRENT_SOURCE_DIR}/asap-clang.rb asap-clang
  COMMENT Creating symlink for asap-clang
  VERBATIM)
add_custom_command(OUTPUT ${CMAKE_BINARY_DIR}/bin/asap-clang++
  COMMAND cd ${CMAKE_BINARY_DIR}/bin && ln -s ${CMAKE_CURRENT_SOURCE_DIR}/asap-clang.rb asap-clang++
  COMMENT Creating symlink for asap-clang++
  VERBATIM)
add_custom_command(OUTPUT ${CMAKE_BINARY_DIR}/bin/asap-ranlib
  COMMAND cd ${CMAKE_BINARY_DIR}/bin && ln -s ${CMAKE_CURRENT_SOURCE_DIR}/asap-clang.rb asap-ranlib
  COMMENT Creating symlink for asap-ranlib
  VERBATIM)
add_custom_command(OUTPUT ${CMAKE_BINARY_DIR}/bin/asap-ar
  COMMAND cd ${CMAKE_BINARY_DIR}/bin && ln -s ${CMAKE_CURRENT_SOURCE_DIR}/asap-clang.rb asap-ar
  COMMENT Creating symlink for asap-ar
  VERBATIM)
add_custom_target(asap_clang_symlinks
  ALL
  DEPENDS ${CMAKE_BINARY_DIR}/bin/asap-clang
          ${CMAKE_BINARY_DIR}/bin/asap-clang++
          ${CMAKE_BINARY_DIR}/bin/asap-ranlib
          ${CMAKE_BINARY_DIR}/bin/asap-ar)
