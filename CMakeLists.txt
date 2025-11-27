cmake_minimum_required(VERSION 4.0)
project(s0l4r)

set(CMAKE_CXX_STANDARD 20)

include(FetchContent)

FetchContent_Declare(
        sfml
        GIT_REPOSITORY https://github.com/SFML/SFML.git
        GIT_TAG 3.0.2
)

FetchContent_MakeAvailable(sfml)

include_directories(include)

add_executable(s0l4r
        src/main.cpp
        src/astre.cpp
        include/astre.h
)

target_link_libraries(s0l4r PRIVATE sfml-graphics sfml-window sfml-system)