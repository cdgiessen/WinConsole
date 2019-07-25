cmake_minimum_required(VERSION 3.7 FATAL_ERROR)

project(TankGame)

if(UNIX)
find_package(Curses) 
endif(UNIX)

set(CMAKE_CXX_STANDARD 17)

add_executable(tank WinConsole.cpp main.cpp WinConsole.h)

if(UNIX)
target_link_libraries(tank PRIVATE ${CURSES_LIBRARIES})
endif(UNIX)

