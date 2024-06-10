cmake_minimum_required(VERSION 3.16.3)
project(Sympp
    VERSION 0.0.1
    DESCRIPTION "Generic Lazy Matrix"
    LANGUAGES CXX
)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)

# Set output directories
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

if(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
    # Set the target architecture to arm64
    set(CMAKE_OSX_ARCHITECTURES "arm64")
    message("macOS detected " ${CMAKE_OSX_ARCHITECTURES})

    # Set compiler flags for macOS
    set(CMAKE_CXX_FLAGS_DEBUG "-g -O0 -Wall -Wextra -pedantic -Xclang -pthread")
    set(CMAKE_CXX_FLAGS_RELEASE " -O3 -Wall -Wextra -pedantic -Xclang -pthread")
else()
    # Set compiler flags for other systems
    set(CMAKE_CXX_FLAGS_DEBUG "-g -O0 -Wall -Wextra -pedantic -pthread")
    set(CMAKE_CXX_FLAGS_RELEASE "-O3 -Wall -Wextra -pedantic -pthread -ffast-math -march=native -ftree-vectorize")
endif()

# Add source and include directories
file(GLOB_RECURSE SRC_FILES src/*.cpp)
file(GLOB_RECURSE INC_FILES include/*.hpp)

add_executable(${PROJECT_NAME} ${SRC_FILES})
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
set_target_properties(${PROJECT_NAME} PROPERTIES LINKER_LANGUAGE CXX)


# Specify the packaging information
set(CPACK_PACKAGE_NAME "sympp")
set(CPACK_PACKAGE_VERSION "0.0.1")
set(CPACK_GENERATOR "ZIP")
include(CPack)

