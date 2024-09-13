cmake_minimum_required(VERSION 3.12)
project(Game)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fexec-charset=GBK -static-libstdc++ -static-libgcc -g")

file(GLOB SOURCES "src/*.cpp")

include_directories(${PROJECT_SOURCE_DIR}/include)

add_executable(Game ${SOURCES})