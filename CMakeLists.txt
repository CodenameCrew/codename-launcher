cmake_minimum_required(VERSION 3.0)
project(codename_launcher CXX)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_BUILD_TYPE Debug)

# Adding Raylib
include(FetchContent)
set(FETCHCONTENT_QUIET FALSE)
set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE) # don't build the supplied examples
set(BUILD_GAMES    OFF CACHE BOOL "" FORCE) # don't build the supplied example games

FetchContent_Declare(
    raylib
    GIT_REPOSITORY "https://github.com/raysan5/raylib.git"
    GIT_TAG "master" # 5.5
    GIT_PROGRESS TRUE
)

FetchContent_MakeAvailable(raylib)

FetchContent_Declare(
    nfd
    GIT_REPOSITORY "https://github.com/mlabbe/nativefiledialog"
    GIT_TAG "master"
    GIT_PROGRESS TRUE
)

FetchContent_MakeAvailable(nfd)

# Adding our source files
file(GLOB_RECURSE PROJECT_SOURCES CONFIGURE_DEPENDS "${CMAKE_CURRENT_LIST_DIR}/src/*.cpp") # Define PROJECT_SOURCES as a list of all source files
set(PROJECT_INCLUDE "${CMAKE_CURRENT_LIST_DIR}/src/") # Define PROJECT_INCLUDE to be the path to the include directory of the project

# Declaring our executable
add_executable(${PROJECT_NAME})
target_sources(${PROJECT_NAME} PRIVATE ${PROJECT_SOURCES})
target_include_directories(${PROJECT_NAME} PRIVATE
    ${PROJECT_INCLUDE}
)
target_link_libraries(${PROJECT_NAME} PRIVATE raylib)

# Setting ASSETS_PATH
if(CMAKE_BUILD_TYPE MATCHES "Release")
    target_compile_definitions(${PROJECT_NAME} PUBLIC ASSETS_PATH="./assets/") # Set the asset path macro in release mode to a relative path that assumes the assets folder is in the same directory as the game executable
else()
    target_compile_definitions(${PROJECT_NAME} PUBLIC ASSETS_PATH="${CMAKE_CURRENT_SOURCE_DIR}/assets/") # Set the asset path macro to the absolute path on the dev machine
endif()

include(CheckCXXCompilerFlag)

function(enable_cxx_compiler_flag_if_supported flag)
    string(FIND "${CMAKE_CXX_FLAGS}" "${flag}" flag_already_set)
    if(flag_already_set EQUAL -1)
        check_cxx_compiler_flag("${flag}" flag_supported)
        if(flag_supported)
            set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${flag}" PARENT_SCOPE)
        endif()
        unset(flag_supported CACHE)
    endif()
endfunction()

enable_cxx_compiler_flag_if_supported("-Wall")
enable_cxx_compiler_flag_if_supported("-Wno-unknown-pragmas")
enable_cxx_compiler_flag_if_supported("-Wno-write-strings")
enable_cxx_compiler_flag_if_supported("-pedantic")
enable_cxx_compiler_flag_if_supported("-fsanitize=address,undefined")
enable_cxx_compiler_flag_if_supported("-fsanitize=thread")

# enable_cxx_compiler_flag_if_supported("-Wshadow") # Disabled due to classes and fields being named the same thing just with different capitalization
enable_cxx_compiler_flag_if_supported("-Wconversion")
enable_cxx_compiler_flag_if_supported("-Wnon-virtual-dtor")
enable_cxx_compiler_flag_if_supported("-Woverloaded-virtual")
enable_cxx_compiler_flag_if_supported("-Wunused")
enable_cxx_compiler_flag_if_supported("-Wnull-dereference")
enable_cxx_compiler_flag_if_supported("-Wformat=2")
enable_cxx_compiler_flag_if_supported("-fstack-protector-all")
# enable_cxx_compiler_flag_if_supported("-Wfloat-equal") # Can't use this since raylib has warnings due to it

enable_cxx_compiler_flag_if_supported("-fno-rtti")

# if debug mode, enable debug stuff
if(CMAKE_BUILD_TYPE MATCHES "Debug")
    target_compile_options(${PROJECT_NAME} PRIVATE -g)
    enable_cxx_compiler_flag_if_supported("-D_GLIBCXX_DEBUG")
    enable_cxx_compiler_flag_if_supported("-g3")
endif()

# if release mode, strip the binary
if(CMAKE_BUILD_TYPE MATCHES "Release")
    add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
            COMMAND ${CMAKE_STRIP} "$<TARGET_FILE:${PROJECT_NAME}>"
            COMMENT "Stripping release binary")
endif()

# if release mode, enable optimizations
if(CMAKE_BUILD_TYPE MATCHES "Release")
    target_compile_options(${PROJECT_NAME} PRIVATE -O2)
    target_compile_options(${PROJECT_NAME} PRIVATE -flto)
    target_link_options(${PROJECT_NAME} PRIVATE -flto)
endif()
