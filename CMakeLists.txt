cmake_minimum_required(VERSION 3.14)

project(RoutingAlgoSolver)

# Try to find a locally installed raylib, but don't quit on fail
find_package(raylib 5.5 QUIET)

#Static link some c++ libraries on windows
if(WIN32)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -static-libgcc -static-libstdc++ -static")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -static -lpthread")
endif()

# This code downloads raylib into a directory called _deps and adds it as a subdirectory, compiling it with the program when running the build command
include(FetchContent)
if (NOT raylib_FOUND)
    FetchContent_Declare(
        raylib
        URL https://github.com/raysan5/raylib/archive/refs/tags/5.5.tar.gz
        DOWNLOAD_EXTRACT_TIMESTAMP True #This option is not required but suppresses a warning
    )
    FetchContent_MakeAvailable(raylib)
endif()

#MY_DIRS
include_directories(src)
include_directories(src/app)
include_directories(src/core)
include_directories(src/core/frontend)
include_directories(src/core/backend)

# We don't want raylib's examples built. This option is picked up by raylib's CMakeLists.txt
set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

#EXECUTABLE
add_executable(${PROJECT_NAME}
    src/app/main.cpp
    src/app/Renderer.cpp
    src/app/Application.cpp

    src/core/backend/Node.cpp
    src/core/backend/NodeHelper.cpp
    src/core/backend/Edge.cpp
    src/core/backend/EdgeHelper.cpp
    src/core/backend/Graph.cpp
    src/core/backend/routingAlgos.cpp

    src/core/frontend/Window.cpp
    src/core/frontend/TextCase.cpp
    src/core/frontend/Button.cpp
    src/core/frontend/Checkbox.cpp
    src/core/frontend/OutputWindow.h
    src/core/frontend/OutputWindow.cpp
)

# Link raylib to project
target_link_libraries(${PROJECT_NAME} 
    raylib
)
# Make project find the <raylib.h> header (and others)
target_include_directories(${PROJECT_NAME} PUBLIC "${raylib_SOURCE_DIR}/src")

#COMPILER OPTION
target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_17)
