cmake_minimum_required(VERSION 3.19)
project(database)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_CXX_FLAGS_DEBUG "-std=c++17 -Wall -Werror -g" CACHE STRING "" FORCE)

set(CMAKE_CXX_FLAGS_RELEASE  "${CMAKE_CXX_FLAGS_DEBUG} -O3" CACHE STRING "" FORCE)

set(CMAKE_CXX_FLAGS_SANITIZED "${CMAKE_CXX_FLAGS_DEBUG} -fsanitize=address,undefined,leak" CACHE STRING
        "" FORCE)

mark_as_advanced(
        CMAKE_CXX_FLAGS_DEBUG
        CMAKE_CXX_FLAGS_RELEASE
        CMAKE_CXX_FLAGS_SANITIZED
)


file(MAKE_DIRECTORY ${CMAKE_BINARY_DIR}/app)

set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/app)

add_subdirectory(src)

set (SOURCES
        ${ALL_SOURCE_FILES}
        )

add_executable(${CMAKE_PROJECT_NAME} ${SOURCES})

target_include_directories(${CMAKE_PROJECT_NAME}
        PRIVATE
        ${PROJECT_SOURCE_DIR}/include
        )
