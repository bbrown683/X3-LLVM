cmake_minimum_required(VERSION 3.18)
project(clang_test)

set(CMAKE_CXX_STANDARD 20)

find_package(Boost CONFIG)
find_package(LLVM REQUIRED CONFIG)

message(STATUS "===================================")
message(STATUS "Found Boost ${Boost_VERSION}")

include_directories(${Boost_INCLUDE_DIRS})
message(STATUS "===================================")

message(STATUS "Found LLVM ${LLVM_PACKAGE_VERSION}")
message(STATUS "Using LLVMConfig.cmake in: ${LLVM_DIR}")

include_directories(${LLVM_INCLUDE_DIRS})
separate_arguments(LLVM_DEFINITIONS_LIST NATIVE_COMMAND ${LLVM_DEFINITIONS})
add_definitions(${LLVM_DEFINITIONS_LIST})
llvm_map_components_to_libnames(llvm_libs core)
message(STATUS "===================================")

add_executable(clang_test src/main.cpp
        src/include/AST.hpp
        src/include/Rules.hpp
        src/include/Generator.hpp
        src/include/Parser.hpp
)
target_link_libraries(clang_test ${Boost_LIBRARIES} ${llvm_libs})
