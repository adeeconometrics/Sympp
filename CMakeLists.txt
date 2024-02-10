cmake_minimum_required(VERSION 3.16.3)
project(Sympp
    VERSION 0.0.1
    DESCRIPTION "Symbolic Cpp library"
    LANGUAGES CXX
)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)

# Set output directories
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# Set compiler flags for debug and release versions
set(CMAKE_CXX_FLAGS_DEBUG "-g -O0 -Wall -Wextra -pedantic")
set(CMAKE_CXX_FLAGS_RELEASE "-O3 -Wall -Wextra -pedantic") # autovectorize is enabled

# Add source and include directories
file(GLOB_RECURSE SRC_FILES src/*.cpp)
file(GLOB_RECURSE INC_FILES include/*.hpp)

add_executable(${PROJECT_NAME} ${SRC_FILES})
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

# # Fetch GTest library
# set(CMAKE_PREFIX_PATH ${CMAKE_CURRENT_SOURCE_DIR}/lib/googletest)
# find_package(GTest REQUIRED CONFIG)

# include(FetchContent)
# FetchContent_Declare(
# googletest
# URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
# )

# if(WIN32)
# set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
# FetchContent_MakeAvailable(googletest)
# endif()

# # Add test directory
# enable_testing()

# add_executable(unittest ${CMAKE_CURRENT_SOURCE_DIR}/test/unittest.cpp)
# target_link_libraries(unittest PRIVATE GTest::gtest_main)

# include(GoogleTest)
# gtest_discover_tests(unittest)

# Specify the packaging information
set(CPACK_PACKAGE_NAME "sympp")
set(CPACK_PACKAGE_VERSION "0.0.1")
set(CPACK_GENERATOR "ZIP")
include(CPack)

# Doxygen

# look for Doxygen package
# find_package(Doxygen)

# if(DOXYGEN_FOUND)
# # set input and output files
# set(DOXYGEN_IN ${CMAKE_CURRENT_SOURCE_DIR}/docs_doxy/Doxyfile.in)
# set(DOXYGEN_OUT ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile.out)

# # request to configure the file
# configure_file(${DOXYGEN_IN} ${DOXYGEN_OUT} @ONLY)
# message("Doxygen build started")

# # Note: do not put "ALL" - this builds docs together with application EVERY TIME!
# add_custom_target(docs
# COMMAND ${DOXYGEN_EXECUTABLE} ${DOXYGEN_OUT}
# WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
# COMMENT "Generating API documentation with Doxygen"
# VERBATIM)
# else(DOXYGEN_FOUND)
# message("Doxygen need to be installed to generate the doxygen documentation")
# endif(DOXYGEN_FOUND)